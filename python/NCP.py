import requests
import json
import time
import datetime
import threading
import os
import psycopg2
import csv
import logging
import argparse
import random
import re
from bs4 import BeautifulSoup

logger = logging.getLogger(__name__)
logger.setLevel(level = logging.INFO)
handler = logging.FileHandler('ncp.log')
handler.setLevel(logging.INFO)
formatter = "%(message)s %(asctime)-15s %(levelname)s %(filename)s %(lineno)d %(process)d "
formatter = logging.Formatter(formatter)
handler.setFormatter(formatter)
logger.addHandler(handler)
# console = logging.StreamHandler()
# console.setLevel(logging.INFO)
# logger.addHandler(console)

user_agent_list = [
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77 Safari/537.36',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.132 Safari/537.36',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:73.0) Gecko/20100101 Firefox/73.0',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_3) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/13.0.5 Safari/605.1.15',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36 Edge/16.16299',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:63.0) Gecko/20100101 Firefox/63.0',
    'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.4150.1 Iron Safari/537.36',
    'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.108 Mobile Safari/537.36',
    'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.81 Safari/537.36 Maxthon/5.3.8.2000',
    'Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:68.9) Gecko/20100101 Goanna/4.4 Firefox/68.9 PaleMoon/28.8.4'
]
headers = {'User-Agent': random.choice(user_agent_list)}

class MyPostgreSQL:
    def __init__(self,dbname,user,password,host,port):
        self.dbname=dbname
        self.host=host
        self.port=port
        self.user=user
        self.password=password
        self.conn = psycopg2.connect(database=self.dbname,user=self.user,password=self.password,host=self.host,port=self.port)
        self.cursor = self.conn.cursor()
    
    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.cursor.close()
        self.conn.close()

    def connect(self,dbname,user,password,host,port):
        self.conn = psycopg2.connect(dbname,user,password,host,port)
        self.cursor = conn.cursor()
    
    def execute(self,SQL,**args):
        try:
            if args:
                self.cursor.execute(SQL,args)
            else:
                self.cursor.execute(SQL)
        except Exception as e:
            logger.info(e)
            self.conn.rollback()
            self.cursor.execute(SQL)
        self.conn.commit()

def DBSave(records,**extra):
    # psql = MyPostgreSQL(dbname='HLD',user='operator',password='5302469',host='127.0.0.1',port='2012')    
    # logger.info(records)
    # """简单实用，属于游标的对象方法"""
    name = 'NCP'
    columns = ["update","continentName","countryName","provinceName","cityName","currentConfirmedCount","confirmedCount","suspectedCount","curedCount","deadCount","comment"]
    # SQL = f"""insert into {name} ({','.join(columns)}) values ({','.join(['%s'] * len(columns))});"""
    # logger.info(SQL)
    # logger.info('type(records)={}'.format(type(records)))
    rows = []
    # logger.info('columns={}'.format(columns))
    SQL = f"""
        insert into "{name}" ("{'","'.join(columns)}") values ({','.join(['%s'] * len(columns))})
        ON CONFLICT ON CONSTRAINT ncp_unique 
        DO UPDATE SET 
        "currentConfirmedCount" = EXCLUDED."currentConfirmedCount",
        "confirmedCount" = EXCLUDED."confirmedCount",
        "suspectedCount"= EXCLUDED."suspectedCount",
        "curedCount" = EXCLUDED."curedCount",
        "deadCount" = EXCLUDED."deadCount",
        "comment" = EXCLUDED."comment"               
        ;
    """
    # logger.info(SQL)
    for record in records:       
        row = []
        citys = []
        if "updateTime" in record:
            dt = record["updateTime"]
            # logger.info('type(dt)=%r,dt=%r',type(dt),dt)
            # logger.info('%r\n',record)
            if type(dt)=='int':
                d = datetime.datetime.fromtimestamp(dt/1000.0,tz=None)
            elif type(dt)=='str':
                d = datetime.datetime.fromisoformat(dt)
            else:
                continue
            sd = d.strftime("%Y-%m-%d")
            updateTime = sd
            continentName = record["continentName"] if "continentName" in record else None
            countryName = record["countryName"] if "countryName" in record else None
            provinceName = record["provinceName"] if "provinceName" in record else None
            cityName = record["cityName"] if "cityName" in record else None
            comment = record['comment'] if "comment" in record else None
            
            continentName = continentName if continentName else ''
            countryName = countryName if countryName != continentName else '' 
            provinceName = provinceName if provinceName != countryName else ''
            cityName = cityName if cityName else ''
            # china_json 数据处理
            if extra:
                continentName = extra['continentName']
                countryName = extra['countryName']
            if "generalRemark" in record:
                comment = record['generalRemark']            
            comment = comment if comment else ''
           
            currentConfirmedCount = record["currentConfirmedCount"] if "currentConfirmedCount" in record else None
            confirmedCount = record["confirmedCount"] if "confirmedCount" in record else None
            suspectedCount = record["suspectedCount"] if "suspectedCount" in record else None
            curedCount = record["curedCount"] if "curedCount" in record else None
            deadCount = record["deadCount"] if "deadCount" in record else None

            currentConfirmedCount = currentConfirmedCount if isinstance(currentConfirmedCount,int) else 0
            confirmedCount = confirmedCount if isinstance(confirmedCount,int) else 0
            suspectedCount = suspectedCount if isinstance(suspectedCount,int) else 0
            curedCount = curedCount if isinstance(curedCount,int) else 0
            deadCount = deadCount if isinstance(deadCount,int) else 0
            # 2月9日以前没有当前确诊记录，只有确诊记录。
            logger.info('%r<%r=%r',d,datetime.datetime(2020,2,9),d<datetime.datetime(2020,2,9))
            if d <= datetime.datetime(2020,2,9,0,0):
                logger.info('update=%r,currentConfirmedCount=%r,confirmedCount=%r,suspectedCount=%r,curedCount=%r,deadCount=%r',d,currentConfirmedCount,confirmedCount,suspectedCount,curedCount,deadCount)                
                currentConfirmedCount = confirmedCount if currentConfirmedCount==0 else currentConfirmedCount

            row.append(updateTime)
            row.append(continentName)   
            row.append(countryName)
            row.append(provinceName)
            row.append(cityName)
            row.append(currentConfirmedCount)
            row.append(confirmedCount)
            row.append(suspectedCount)
            row.append(curedCount)
            row.append(deadCount)
            row.append(comment)            
            if 'cities' in record:
                citys = record['cities']
                # logger.info('citysTable={}'.format(citys))
                if citys:                            
                    for city in citys:
                        # logger.info('city={}'.format(city))
                        cityRow=[]
                        if 'cityName' in city:
                            cityName = city['cityName'] 
                        else:
                            continue 
                        currentConfirmedCount = city["currentConfirmedCount"] if "currentConfirmedCount" in city else None
                        confirmedCount = city["confirmedCount"] if "confirmedCount" in city else None
                        suspectedCount = city["suspectedCount"] if "suspectedCount" in city else None
                        curedCount = city["curedCount"] if "curedCount" in city else None
                        deadCount = city["deadCount"] if "deadCount" in city else None

                        comment = city['comment'] if "comment" in city else None
                        comment = comment if comment else ''

                        currentConfirmedCount = currentConfirmedCount if isinstance(currentConfirmedCount,int) else 0
                        confirmedCount = confirmedCount if isinstance(confirmedCount,int) else 0
                        suspectedCount = suspectedCount if isinstance(suspectedCount,int) else 0
                        curedCount = curedCount if isinstance(curedCount,int) else 0
                        deadCount = deadCount if isinstance(deadCount,int) else 0
                        if d <= datetime.datetime(2020,2,9,0,0):
                            logger.info('update=%r,currentConfirmedCount=%r,confirmedCount=%r,suspectedCount=%r,curedCount=%r,deadCount=%r',d,currentConfirmedCount,confirmedCount,suspectedCount,curedCount,deadCount)
                            currentConfirmedCount = confirmedCount if currentConfirmedCount==0 else currentConfirmedCount

                        cityRow.append(sd)
                        cityRow.append(continentName)
                        cityRow.append(countryName)
                        cityRow.append(provinceName)                            
                        cityRow.append(cityName)
                        cityRow.append(currentConfirmedCount)
                        cityRow.append(confirmedCount)
                        cityRow.append(suspectedCount)
                        cityRow.append(curedCount)
                        cityRow.append(deadCount)
                        cityRow.append(comment)
                        # logger.info('cityRow={}'.format(cityRow))
                        if cityRow:
                            rows.append(cityRow)
                else:
                    cityName = None                                            
        else:
            continue     
        if row:
            # logger.info('row={}\n'.format(row))
            rows.append(row)
            # psql.execute(SQL,row)
            # psql.cursor.execute(SQL,row)
            # psql.conn.commit()
    # if rows:
    #     logger.info('整理后第一条数据:\n%r\n',row[0])
    # logger.info('有%r条记录等待存入数据库',len(rows))
    # for row in rows:
    #     logger.info(row)
    psql.cursor.executemany(SQL,rows)
    psql.conn.commit()
    # psql.cursor.copy_from(f, "NCP",columns=fieldnames,sep=',', null='\\N', size=16384)
    # filename = 'NCP.csv'
    # with open(filename, 'w', newline='') as csvfile:
    #     fieldnames = records[0].keys()
    #     logger.info(fieldnames)
    #     writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
    #     writer.writeheader()
    #     writer.writerows(records)

    # psql.cursor.copy_from(csvfile, 'ncp',columns=fieldnames,sep=',', size=16384)

def crawl_NCP(url,params,timeout):
    response = requests.get(url,headers=headers,params=params,timeout=timeout)
    # json_reads = json.loads(response.text)
    logger.info('response.status_code=%r',response.status_code)
    if response.status_code==200:
        json_reads = response.json()
        logger.info('json_reads=%r',json_reads)
        records=json_reads["results"]
        if url == "https://lab.isaaclin.cn/nCoV/api/area" :
            logger.info('crawl NCP data')
            filename = 'NCP.json'
            DBSave(records)
        if url == "https://lab.isaaclin.cn/nCoV/api/overall" :
            logger.info('crawl china NCP data')
            filename = 'NCP_china.json'
            extra = {'continentName':'亚洲','countryName':'中国'}
            DBSave(records,**extra)
        with open(filename,'w') as f:
            json.dump(records,f,ensure_ascii=False)
    if response.status_code>=500:
        msg = '服务端拒绝服务：{}'.format(response.status_code)
        logger.error(msg)
    # logger.info(type(records))

def crawl_NCP_dingxiang(url,timeout):
    response = requests.get(url,headers=headers,timeout=timeout)
    msg = 'response.status_code={}'.format(response.status_code)
    # logger.info('msg=%r content=%r',msg,response.content) 
    soup = BeautifulSoup(response.content, 'lxml')

    overall_information = re.search(r'(\{"id".*\}\})\}', str(soup.find('script', attrs={'id': 'getStatisticsService'})))
    logger.info('overall_information=%r',overall_information)
    # if overall_information:
    #     self.overall_parser(overall_information=overall_information)

    area_information = re.search(r'\[(.*)\]', str(soup.find('script', attrs={'id': 'getAreaStat'})))
    # if area_information:
    #     self.area_parser(area_information=area_information)

    abroad_information = re.search(r'\[(.*)\]', str(soup.find('script', attrs={'id': 'getListByCountryTypeService2true'})))
    # if abroad_information:
    #     self.abroad_parser(abroad_information=abroad_information)

    news_chinese = re.search(r'\[(.*?)\]', str(soup.find('script', attrs={'id': 'getTimelineServiceundefined'})))
    # if news_chinese:
    #     self.news_parser(news=news_chinese)

    news_english = re.search(r'\[(.*?)\]', str(soup.find('script', attrs={'id': 'getTimelineService2'})))
    # if news_english:
    #     self.news_parser(news=news_english)

    rumors = re.search(r'\[(.*?)\]', str(soup.find('script', attrs={'id': 'getIndexRumorList'})))
    # if rumors:
    #     self.rumor_parser(rumors=rumors)       

def crawl_NCP_qq():
    # 腾讯数据接口
    # url='https://view.inews.qq.com/g2/getOnsInfo?name=disease_h5'
    # url='https://view.inews.qq.com/g2/getOnsInfo?name=disease_other'    
    # 国内
    url='https://view.inews.qq.com/g2/getOnsInfo'
    headers = {'User-Agent': random.choice(user_agent_list)}
    timeout = 9
    params = {}
    params['name'] = 'disease_h5'
    params['callback'] = 'jQuery341001657575837432268_1581070969707'
    # params['_'] = '1581070969708'
    params['_'] = int(time.time()*1000)
    # url = 'https://view.inews.qq.com/g2/getOnsInfo?name=disease_h5&callback=jQuery341001657575837432268_1581070969707&_=1581070969708'
    url='https://view.inews.qq.com/g2/getOnsInfo?name=disease_h5'
    response = requests.get(url,headers=headers,params=params,timeout=timeout)
    if response.status_code==200:
        content = response.text
        a = params['callback']+'('
        b = content.split(a)[1].split(')')[0]
        c = json.loads(b)
        china_json = json.loads(c['data'])
        # logger.info('china_json=%r',china_json.keys())    

    # 国外
    url = 'https://view.inews.qq.com/g2/getOnsInfo'
    params['name'] = 'disease_foreign'
    params['callback'] = 'jQuery34108116985782396278_1584837309333'
    params['_'] =  int(time.time()*1000)
    response = requests.get(url,headers=headers,params=params,timeout=timeout)
    # logger.info('url=%r\nheaders=%r\n,params=%r\n,timeout=%r\n',url,headers,params,timeout)
    if response.status_code==200:
        content = response.text
        a = params['callback']+'('
        b = content.split(a)[1].split(')')[0]
        c = json.loads(b)
        foreign_json = json.loads(c['data'])
        # logger.info('foreign_json=%r',foreign_json.keys())

    url='https://view.inews.qq.com/g2/getOnsInfo'
    del params['callback']
    del params['_']
    params['name']='disease_other'
    response = requests.get(url,headers=headers,params=params,timeout=timeout)
    # logger.info('url=%r\nheaders=%r\n,params=%r\n,timeout=%r\n',url,headers,params,timeout)    
    if response.status_code==200:
        content = response.json()['data']
        other_json=json.loads(content)
        # logger.info(other_json)

    rows=[]
    row=[]
    totoalProvinceRecords=[]
    totalCityRecords=[]
    data=china_json.copy()
    data.update(foreign_json)
    data.update(other_json)
    # logger.info('chinaDayList=%r',data['chinaDayList'])
    # logger.info('foreignList=%r',data['foreignList'])
    # logger.info('areaTree=%r',data['areaTree'])     
    if data:
        records = data['chinaDayList']
        for record in records:
            continent = '亚洲'
            country = '中国'
            remark = '' 
            temp=record['date'].split('.')
            sd = '2020-'+temp[0]+'-'+temp[1]
            update = datetime.date.fromisoformat(sd).isoformat()
            confirmation=record['nowConfirm']
            totalConfirmation=record['confirm']
            suspect = record['suspect']
            cure = record['heal']
            dead = record['dead']
            row=[update,continent,country,confirmation,totalConfirmation,suspect,cure,dead,remark]
            rows.append(row)
            logger.info('%r\n',row)        
        records = data['foreignList']
        for record in records:
            remark = ''
            temp=record['date'].split('.')
            sd = '2020-'+temp[0]+'-'+temp[1]
            update = datetime.date.fromisoformat(sd).isoformat()
            continent = record['continent']            
            country = record['name']
            confirmation=record['nowConfirm']
            totalConfirmation=record['confirm']
            suspect = record['suspect']
            cure = record['heal']
            dead = record['dead']
            row=[update,continent,country,confirmation,totalConfirmation,suspect,cure,dead,remark]
            if 'children' in record:
                provinceRecords = record['children']
                for record in provinceRecords:
                    temp=record['date'].split('.')
                    sd = '2020-'+temp[0]+'-'+temp[1]                
                    record['remark'] = ''
                    record['country'] = country
                    record['province'] = record.pop('name')
                    record['update'] = datetime.date.fromisoformat(sd).isoformat()
                    # record['confirmation']=record.pop('nowConfirm')
                    record['totalConfirmation']=record.pop('confirm')
                    record['cure'] = record.pop('heal')
                    totoalProvinceRecords.append(record)                  
            rows.append(row)
        records = data['areaTree']
        for record in records:
            update = datetime.date.fromtimestamp(time.time()).isoformat()
            continent = '亚洲'
            country = '中国'
            remark = ''
            confirmation=record['total']['nowConfirm']
            totalConfirmation=record['total']['confirm']
            suspect = record['total']['suspect']
            cure = record['total']['heal']
            dead = record['total']['dead']
            row=[update,continent,country,confirmation,totalConfirmation,suspect,cure,dead,remark]
            # logger.info('china row=%r',row)
            rows.append(row)
            if 'children' in record:
                provinceRecords = record['children']
                for x in provinceRecords:
                    provinceRecord={}
                    provinceRecord['update'] = update
                    provinceRecord['country'] = country
                    provinceRecord['province'] = x['name']
                    provinceRecord['confirmation']=x['total']['nowConfirm']
                    provinceRecord['totalConfirmation']=x['total']['confirm']
                    provinceRecord['suspect'] = x['total']['suspect']
                    provinceRecord['cure'] = x['total']['heal']
                    provinceRecord['dead'] = x['total']['dead']
                    provinceRecord['remark'] = ''
                    totoalProvinceRecords.append(provinceRecord)
                    province = provinceRecord['province']
                    if 'children' in x:
                        cityRecords = x['children']
                        for xx in cityRecords:
                            cityRecord={}
                            cityRecord['update'] = update
                            cityRecord['country'] = country
                            cityRecord['province'] = province
                            cityRecord['city'] = xx['name']
                            cityRecord['confirmation']=xx['total']['nowConfirm']
                            cityRecord['totalConfirmation']=xx['total']['confirm']
                            cityRecord['suspect'] = xx['total']['suspect']
                            cityRecord['cure'] = xx['total']['heal']
                            cityRecord['dead'] = xx['total']['dead']
                            cityRecord['remark'] = ''
                            totalCityRecords.append(cityRecord)                                                             
                            # logger.info('confirmation=%r',cityRecord['confirmation'])
                            # logger.info('xx[total][nowConfirm]=%r',xx['total']['nowConfirm'])
                        

    name = 'golbal'
    constraint = 'global_unique'
    columns = ["update","continent","country","confirmation","totalConfirmation","suspect","cure","dead","remark"]
    SQL = f"""
        insert into "{name}" ("{'","'.join(columns)}") values ({','.join(['%s'] * len(columns))})    
        ON CONFLICT ON CONSTRAINT "{constraint}" 
        DO UPDATE SET 
        "confirmation" = EXCLUDED."confirmation",
        "totalConfirmation" = EXCLUDED."totalConfirmation",
        "suspect"= EXCLUDED."suspect",
        "cure" = EXCLUDED."cure",
        "dead" = EXCLUDED."dead",
        "remark" = EXCLUDED."remark"               
	;        
    """
    logger.info('keys=%r',data.keys())
    # logger.info('data=%r\n',data)
    # for x in totoalProvinceRecords:
    #     logger.info(x)        
    psql.cursor.executemany(SQL,rows)
    psql.conn.commit()

    rows=[]    
    for record in totoalProvinceRecords:
        row=[]
        record['confirmation'] = record['confirmation'] if 'confirmation' in record else 0
        record['suspect'] = record['suspect'] if 'suspect' in record else 0
        row.append(record['update'])
        row.append(record['country'])
        row.append(record['province'])
        row.append(record['confirmation'])
        row.append(record['totalConfirmation'])
        row.append(record['suspect'])
        row.append(record['cure'])
        row.append(record['dead'])
        row.append(record['remark'])
        rows.append(row)
    logger.info('totoalProvinceRecords %r',len(totoalProvinceRecords))
    logger.info('totalCityRecords %r',len(totalCityRecords))
    name = "country"
    constraint='country_unique'
    columns = ["update","country","province","confirmation","totalConfirmation","suspect","cure","dead","remark"]
    SQL = f"""
        insert into "{name}" ("{'","'.join(columns)}") values ({','.join(['%s'] * len(columns))})    
        ON CONFLICT ON CONSTRAINT "{constraint}" 
        DO UPDATE SET 
        "confirmation" = EXCLUDED."confirmation",
        "totalConfirmation" = EXCLUDED."totalConfirmation",
        "suspect"= EXCLUDED."suspect",
        "cure" = EXCLUDED."cure",
        "dead" = EXCLUDED."dead",
        "remark" = EXCLUDED."remark"               
    ;        
    """
    psql.cursor.executemany(SQL,rows)
    psql.conn.commit()

    rows=[]    
    for record in totalCityRecords:
        row=[]
        record['confirmation'] = record['confirmation'] if 'confirmation' in record else 0
        record['suspect'] = record['suspect'] if 'suspect' in record else 0
        record['totalConfirmation'] = record['totalConfirmation'] if 'totalConfirmation' in record else 0
        row.append(record['update'])
        row.append(record['country'])
        row.append(record['province'])
        row.append(record['city'])
        row.append(record['confirmation'])
        row.append(record['totalConfirmation'])
        row.append(record['suspect'])
        row.append(record['cure'])
        row.append(record['dead'])
        row.append(record['remark'])
        rows.append(row)
        # logger.info('cityRecord=%r',record)
    name = "province"
    constraint='province_unique'
    columns = ["update","country","province","city","confirmation","totalConfirmation","suspect","cure","dead","remark"]
    SQL = f"""
        insert into "{name}" ("{'","'.join(columns)}") values ({','.join(['%s'] * len(columns))})    
        ON CONFLICT ON CONSTRAINT "{constraint}" 
        DO UPDATE SET 
        "confirmation" = EXCLUDED."confirmation",
        "totalConfirmation" = EXCLUDED."totalConfirmation",
        "suspect"= EXCLUDED."suspect",
        "cure" = EXCLUDED."cure",
        "dead" = EXCLUDED."dead",
        "remark" = EXCLUDED."remark"               
    ;        
    """
    # logger.info(SQL)
    # logger.info(rows)
    psql.cursor.executemany(SQL,rows)
    psql.conn.commit()         

def DXY_csv_to_database(filename):
    # logger.info("filename is %r",filename)
    with open(filename, newline='', encoding='UTF-8-sig') as csvfile:
        # spamreader = csv.reader(csvfile)
        # dialect = csv.Sniffer().sniff(csvfile.read(1024))
        # csvfile.seek(0)
        # reader = csv.reader(csvfile, dialect)        
        reader = csv.DictReader(csvfile)
        # logger.info('records=%r',type(reader))
        records=[]
        cityRow=[]
        provinceRow=[]
        rows=[]
        for row in reader:
            records.append(row)
            # logger.info(row)
        # logger.info('type(records)=%r type(records[0])=%r',type(records),type(records[0]))
        # logger.info('type(records)=%r,len(records)=%r',type(records),len(records))
        # DBSave(records)
        for record in records:
            if "updateTime" in record:
                dt = record["updateTime"]
                # logger.info('%r\n',record)
                if isinstance(dt,int):
                    d = datetime.datetime.fromtimestamp(dt/1000.0,tz=None)
                elif isinstance(dt,str):
                    d = datetime.datetime.fromisoformat(dt)
                else:
                    continue
                # if d < datetime.datetime(2020,3,1,0,0):
                #     continue
                sd = d.strftime("%Y-%m-%d")
                updateTime = sd
                continentName = record["continentName"] if "continentName" in record else None
                countryName = record["countryName"] if "countryName" in record else None
                provinceName = record["provinceName"] if "provinceName" in record else None
                cityName = record["cityName"] if "cityName" in record else None
                comment = record['comment'] if "comment" in record else None
                
                continentName = continentName if continentName else ''
                countryName = countryName if countryName != continentName else '' 
                provinceName = provinceName if provinceName != countryName else ''
                cityName = cityName if cityName else ''
                comment = comment if comment else ''
                # logger.info('record : %r',sd)

                if cityName:
                    currentConfirmedCount = record["city_currentConfirmedCount"] if "city_currentConfirmedCount" in record else None
                    confirmedCount = record["city_confirmedCount"] if "city_confirmedCount" in record else None
                    suspectedCount = record["city_suspectedCount"] if "city_suspectedCount" in record else None
                    curedCount = record["city_curedCount"] if "city_curedCount" in record else None
                    deadCount = record["city_deadCount"] if "city_deadCount" in record else None

                    currentConfirmedCount = currentConfirmedCount if currentConfirmedCount else 0
                    confirmedCount = confirmedCount if confirmedCount else 0
                    suspectedCount = suspectedCount if suspectedCount else 0
                    curedCount = curedCount if curedCount else 0
                    deadCount = deadCount if deadCount else 0                    

                    cityRow.append(sd)
                    cityRow.append(continentName)
                    cityRow.append(countryName)
                    cityRow.append(provinceName)                            
                    cityRow.append(cityName)
                    cityRow.append(currentConfirmedCount)
                    cityRow.append(confirmedCount)
                    cityRow.append(suspectedCount)
                    cityRow.append(curedCount)
                    cityRow.append(deadCount)
                    cityRow.append(comment)
                    # logger.info('cityRow=%r\n',cityRow)    
                    rows.append(cityRow)
                    cityRow=[]
                else:
                    currentConfirmedCount = record["province_currentConfirmedCount"] if "province_currentConfirmedCount" in record else None
                    confirmedCount = record["province_confirmedCount"] if "province_confirmedCount" in record else None    
                    suspectedCount = record["province_suspectedCount"] if "province_suspectedCount" in record else None
                    curedCount = record["province_curedCount"] if "province_curedCount" in record else None
                    deadCount = record["province_deadCount"] if "province_deadCount" in record else None

                    currentConfirmedCount = currentConfirmedCount if currentConfirmedCount else 0
                    confirmedCount = confirmedCount if confirmedCount else 0
                    suspectedCount = suspectedCount if suspectedCount else 0
                    curedCount = curedCount if curedCount else 0
                    deadCount = deadCount if deadCount else 0                      

                    provinceRow.append(sd)
                    provinceRow.append(continentName)
                    provinceRow.append(countryName)
                    provinceRow.append(provinceName)                            
                    provinceRow.append(cityName)
                    provinceRow.append(currentConfirmedCount)
                    provinceRow.append(confirmedCount)
                    provinceRow.append(suspectedCount)
                    provinceRow.append(curedCount)
                    provinceRow.append(deadCount)
                    provinceRow.append(comment)
                    # logger.info('provinceRow=%r\n',provinceRow)
                    rows.append(provinceRow)
                    provinceRow=[]
        logger.info('len(row)=%r',len(rows))
        name = 'NCP'
        columns = ["update","continentName","countryName","provinceName","cityName","currentConfirmedCount","confirmedCount","suspectedCount","curedCount","deadCount","comment"]
        # SQL = f"""insert into {name} ({','.join(columns)}) values ({','.join(['%s'] * len(columns))});"""
        SQL = f"""
            insert into "{name}" ("{'","'.join(columns)}") values ({','.join(['%s'] * len(columns))})
            ON CONFLICT ON CONSTRAINT ncp_unique 
            DO UPDATE SET 
            "currentConfirmedCount" = EXCLUDED."currentConfirmedCount",
            "confirmedCount" = EXCLUDED."confirmedCount",
            "suspectedCount"= EXCLUDED."suspectedCount",
            "curedCount" = EXCLUDED."curedCount",
            "deadCount" = EXCLUDED."deadCount",
            "comment" = EXCLUDED."comment"               
            ;
        """        
        psql.cursor.executemany(SQL,rows)
        psql.conn.commit()
                  
if __name__ == '__main__':
    parser = argparse.ArgumentParser(prog = 'crawl NCP',description = '爬取新冠肺炎数据,默认爬取当天最新数据')
    parser.add_argument("-a","--all",action="store_true",help='获得网站全部新冠肺炎数据，本地数据将被清除。')
    parser.add_argument("-c","--cvs",help='从指定csv文件中提取数据')
    parser.add_argument("-j","--json",help='从指定json文件中提取数据')
    args = parser.parse_args()        
    params = {'latest': '0'}
    timeout = 9
    dbname = 'COVID-19'
    user='operator'
    password='5302469'
    host='localhost'
    port='2012'
    psql = MyPostgreSQL(dbname=dbname,user=user,password=password,host=host,port=port)    
    if args.all:
        params['latest'] = 0
        SQL = 'DROP TABLE IF EXISTS "NCP";'
        psql.execute(SQL)
        SQL = '''
        CREATE TABLE IF NOT EXISTS "NCP" (
            id                      serial,
            "update"                date not null,
            "continentName"         varchar,
            "countryName"           varchar,
            "provinceName"          varchar,
            "cityName"              varchar,        
            "currentConfirmedCount" integer,
            "confirmedCount"        integer,
            "suspectedCount"        integer,
            "curedCount"            integer,
            "deadCount"             integer,
            "comment"               varchar      
        );
        '''
        # logger.info(SQL)
        psql.execute(SQL)
        SQL = '''
            ALTER TABLE "NCP" 
            ADD CONSTRAINT ncp_unique UNIQUE(
                "update",
                "continentName",
                "countryName",
                "provinceName",
                "cityName"            
            );    
        '''
        # logger.info(SQL)
        psql.execute(SQL)           
    else:
        params['latest'] = 1
    if args.cvs:
        filename = args.cvs
        DXY_csv_to_database(filename)
    if args.json:
        filename = args.json
        with open(filename, 'r') as f:
            data = json.load(f)
            # logger.info('type(data)=%r',type(data))        
    # url = "https://lab.isaaclin.cn/nCoV/api/area"
    # crawl_NCP(url=url,params=params,timeout=timeout)
    # url = "https://lab.isaaclin.cn/nCoV/api/overall"
    # crawl_NCP(url=url,params=params,timeout=timeout)
    # url = 'https://ncov.dxy.cn/ncovh5/view/pneumonia'
    # crawl_NCP_dingxiang(url=url,timeout=timeout)
    crawl_NCP_qq()