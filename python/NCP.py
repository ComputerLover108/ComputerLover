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

def DBSave(records):
    # psql = MyPostgreSQL(dbname='HLD',user='operator',password='5302469',host='127.0.0.1',port='2012')  
    SQL = '''
    CREATE TABLE IF NOT EXISTS "NCP" (
        id serial,
        "updateTime" timestamp ,
        "continentName" varchar ,
        "countryName" varchar ,
        "provinceName" varchar,
        "cityName" varchar,        
        "currentConfirmedCount"  integer,
        "confirmedCount"  integer,
        "suspectedCount"  integer,
        "curedCount"  integer,
        "deadCount"  integer,
        "comment" varchar       
    );
    '''
    logger.info(SQL)
    psql.execute(SQL)    
    # logger.info(records)
    # """简单实用，属于游标的对象方法"""
    name = 'NCP'
    columns = ["updateTime","continentName","countryName","provinceName","cityName","currentConfirmedCount","confirmedCount","suspectedCount","curedCount","deadCount","comment"]
    # SQL = f"""insert into {name} ({','.join(columns)}) values ({','.join(['%s'] * len(columns))});"""
    # logger.info(SQL)
    # logger.info('type(records)={}'.format(type(records)))
    rows = []
    # logger.info('columns={}'.format(columns))
    SQL = f"""insert into "{name}" ("{'","'.join(columns)}") values ({','.join(['%s'] * len(columns))}) ;"""
    logger.info(SQL)
    for record in records:       
        row = []
        citys = []
        for v in columns:           
            if v in record:
                if v =='updateTime':
                    dt = record[v]
                    # logger.info('record[{}]={}'.format(v,dt))
                    d = datetime.datetime.fromtimestamp(dt/1000.0,tz=None)
                    sd = d.strftime("%Y-%m-%d %H:%M:%S")
                    record[v] = sd
                    # logger.info('sd={} record[{}]={}'.format(sd,v,record[v]))
                continentName = record["continentName"] if "continentName" in record else None
                countryName = record["countryName"] if "countryName" in record else None
                provinceName = record["provinceName"] if "provinceName" in record else None
                # logger.info('cityRow[]='.format(cityRow))                 
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
                            comment = record['comment'] if "comment" in record else None
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
                row.append(record[v])
            else:
                row.append(None)
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
    json_reads = json.loads(response.text)
    records=json_reads["results"]
    # filename = 'NCP.json'
    # with open(filename,'w') as f:
    #     json.dump(records,f,ensure_ascii=False)
    # logger.info(type(records))
    DBSave(records)

    
# def fun():
#     th=threading.Thread(target=cxk)
#     th.setDaemon(True)#守护线程
#     th.start()
    # showinfo(title='提示', message='后台数据统计已开始\n请稍等，完成后将会有提示！')
    
if __name__ == '__main__':
    parser = argparse.ArgumentParser(prog = 'crawl NCP',description = '爬取新冠肺炎数据,默认爬取当天最新数据')
    parser.add_argument('-a','--all', help='获得网站全部新冠肺炎数据，本地数据将被清除。')
    args = parser.parse_args()    
    url = "https://lab.isaaclin.cn/nCoV/api/area"    
    params = {'latest': '0'}
    timeout = 9
    psql = MyPostgreSQL(dbname='HLD',user='operator',password='5302469',host='127.0.0.1',port='2012')    
    if args.all:
        params['latest'] = 0
        SQL = 'DROP TABLE IF EXISTS "NCP";'
        psql.execute(SQL) 
    else:
        params['latest'] = 1
    crawl_NCP(url=url,params=params,timeout=timeout)

