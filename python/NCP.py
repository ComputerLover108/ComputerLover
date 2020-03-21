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
from bs4 import BeautifulSoup
import re

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



ua = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_0) ' \
     'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77' \
     ' Safari/537.36'
headers = {'User-Agent': ua}

user_agent_list = [
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77 Safari/537.36',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.132 Safari/537.36',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:73.0) Gecko/20100101 Firefox/73.0',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_3) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/13.0.5 Safari/605.1.15',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36 Edge/16.16299',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:63.0) Gecko/20100101 Firefox/63.0'
]

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
# def fun():
#     th=threading.Thread(target=cxk)
#     th.setDaemon(True)#守护线程
#     th.start()
    # showinfo(title='提示', message='后台数据统计已开始\n请稍等，完成后将会有提示！')

class Crawler:
    def __init__(self):
        self.session = requests.session()
        self.crawl_timestamp = int()

    def run(self):
        while True:
            self.crawler()
            time.sleep(60)

    def crawler(self):
        while True:
            self.session.headers.update(
                {
                    'user-agent': random.choice(user_agent_list)
                }
            )
            self.crawl_timestamp = int(time.time() * 1000)
            try:
                r = self.session.get(url='https://ncov.dxy.cn/ncovh5/view/pneumonia')
            except requests.exceptions.ChunkedEncodingError:
                continue
            soup = BeautifulSoup(r.content, 'lxml')

            # overall_information = re.search(r'(\{"id".*\}\})\}', str(soup.find('script', attrs={'id': 'getStatisticsService'})))
            # if overall_information:
            #     self.overall_parser(overall_information=overall_information)

            # area_information = re.search(r'\[(.*)\]', str(soup.find('script', attrs={'id': 'getAreaStat'})))
            # if area_information:
            #     self.area_parser(area_information=area_information)

            # abroad_information = re.search(r'\[(.*)\]', str(soup.find('script', attrs={'id': 'getListByCountryTypeService2true'})))
            # if abroad_information:
            #     self.abroad_parser(abroad_information=abroad_information)

            # news_chinese = re.search(r'\[(.*?)\]', str(soup.find('script', attrs={'id': 'getTimelineServiceundefined'})))
            # if news_chinese:
            #     self.news_parser(news=news_chinese)

            # news_english = re.search(r'\[(.*?)\]', str(soup.find('script', attrs={'id': 'getTimelineService2'})))
            # if news_english:
            #     self.news_parser(news=news_english)

            # rumors = re.search(r'\[(.*?)\]', str(soup.find('script', attrs={'id': 'getIndexRumorList'})))
            # if rumors:
            #     self.rumor_parser(rumors=rumors)

            # if not overall_information or \
            #         not area_information or \
            #         not abroad_information or \
            #         not news_chinese or \
            #         not news_english or \
            #         not rumors:
            #     time.sleep(3)
            #     continue

            # break

        logger.info('Successfully crawled.')

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
    parser.add_argument("-a","--all", help='获得网站全部新冠肺炎数据，本地数据将被清除。')
    parser.add_argument("-c","--cvs",help='从指定csv文件中提取数据')
    parser.add_argument("-j","--json",help='从指定json文件中提取数据')
    args = parser.parse_args()        
    params = {'latest': '0'}
    timeout = 9
    dbname = 'HLD'
    user='operator'
    password='5302469'
    host='192.168.0.111'
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
    url = "https://lab.isaaclin.cn/nCoV/api/area"
    crawl_NCP(url=url,params=params,timeout=timeout)
    url = "https://lab.isaaclin.cn/nCoV/api/overall"
    crawl_NCP(url=url,params=params,timeout=timeout)
    url = 'https://ncov.dxy.cn/ncovh5/view/pneumonia'
    crawl_NCP_dingxiang(url=url,timeout=timeout)