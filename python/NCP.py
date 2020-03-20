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
            # logger.info('record[{}]={}'.format(v,dt))
            d = datetime.datetime.fromtimestamp(dt/1000.0,tz=None)
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
            # logger.info('row={}'.format(row))
            rows.append(row)
            # psql.execute(SQL,row)
            # psql.cursor.execute(SQL,row)
            # psql.conn.commit()
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
        print(msg)
    # logger.info(type(records))

    
# def fun():
#     th=threading.Thread(target=cxk)
#     th.setDaemon(True)#守护线程
#     th.start()
    # showinfo(title='提示', message='后台数据统计已开始\n请稍等，完成后将会有提示！')
    
if __name__ == '__main__':
    parser = argparse.ArgumentParser(prog = 'crawl NCP',description = '爬取新冠肺炎数据,默认爬取当天最新数据')
    parser.add_argument("-a","--all", help='获得网站全部新冠肺炎数据，本地数据将被清除。',action="store_true")
    args = parser.parse_args()        
    params = {'latest': '0'}
    timeout = 9
    dbname = 'HLD'
    user='operator'
    password='5302469'
    host='192.168.0.122'
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
    url = "https://lab.isaaclin.cn/nCoV/api/area"
    crawl_NCP(url=url,params=params,timeout=timeout)
    url = "https://lab.isaaclin.cn/nCoV/api/overall"
    crawl_NCP(url=url,params=params,timeout=timeout)

