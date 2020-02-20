# import requests
# import json 

# # url = "https://ncov.dxy.cn/ncovh5/view/pneumonia?scene=2&clicktime=1579579384&enterid=1579579384&from=timeline&isappinstalled=0"
# url = "https://lab.isaaclin.cn/nCoV/api/area?latest=1"
# r = requests.get(url=url)    # 最基本的GET请求
# print(r.status_code, r.reason)
# print('GET请求', r.text)

# 自定义headers请求
# ua = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_0) ' \
#      'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77' \
#      ' Safari/537.36'
# headers = {'User-Agent': ua}
# response = requests.get(url=url, headers=headers)
# json_reads = json.loads(response.text)
# ALL=json_reads["results"]
# print(ALL)

import requests
import json
import time, datetime
import xlwt
import threading
import os
import psycopg2
import csv
from io import StringIO

ua = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_0) ' \
     'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77' \
     ' Safari/537.36'
headers = {'User-Agent': ua}
params={'latest': '0'}




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
    
    def execute(self,SQL):
        try:
            self.cursor.execute(SQL)
        except Exception as e:
            print(e)
            self.conn.rollback()
            self.cursor.execute(SQL)
        self.conn.commit()

def DBSave(records,f):
    SQL = '''
    CREATE TABLE IF NOT EXISTS NCP (
        "currentConfirmedCount"  integer,
        "confirmedCount"  integer,
        "suspectedCount"  integer,
        "curedCount"  integer,
        "deadCount"  integer,
        "seriousCount"  integer,
        "currentConfirmedIncr"  integer,
        "confirmedIncr"  integer,
        "suspectedIncr"  integer,
        "curedIncr"  integer,
        "deadIncr"  integer,
        "seriousIncr"  integer,
        "generalRemark" varchar,
        "abroadRemark" varchar,
        "remark1" varchar,
        "remark2" varchar,
        "remark3" varchar,
        "remark4" varchar,
        "remark5" varchar,
        "note1" varchar,
        "note2" varchar,
        "note3" varchar,
        "updateTime" timestamp
    );
    '''
    psql = MyPostgreSQL(dbname='HLD',user='operator',password='5302469',host='127.0.0.1',port='2012')
    psql.execute(SQL)
    fieldnames = records[0].keys()
    print(SQL)    
    print(fieldnames)
    # psql.cursor.copy_from(f, "NCP",
    #             columns=fieldnames, 
    #             sep=',', null='\\N', size=16384)

def cxk():
    url = "https://lab.isaaclin.cn/nCoV/api/overall"
    response = requests.get(url,headers=headers,params=params,timeout=2)
    json_reads = json.loads(response.text)
    records=json_reads["results"]
    filename = 'NCP.json'
    with open(filename,'w') as f:
        json.dump(records,f,ensure_ascii=False)
    # print(type(records))
    filename = 'NCP.csv'
    with open(filename, 'w', newline='') as csvfile:
        fieldnames = records[0].keys()
        print(fieldnames)
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        for record in records:
            writer.writerow(record)

    DBSave(records,csvfile)
    

    newTime = datetime.datetime.fromtimestamp(records[0]["updateTime"]/1000.0).strftime("%Y-%m-%d-%H")
 
    print(newTime+"统计完成")

    #创建工作博
    # wb  =xlwt.Workbook(encoding='utf-8')
 
 
    # #括号内参数为表名 ws 为各省份表
    # ws = wb.add_sheet('%s时新型肺炎统计表'%newTime)
 
    # #括号内参数为表名 wk 为各市区表
    # wk = wb.add_sheet('%s时新型肺炎各省份统计表'%newTime)
 
    # provinceName=[]#省份
    # cityName=[]#下属城市
    # confirmedCount=[]#确诊人数
    # suspectedCount=[]#疑似病例
    # curedCount=[]#治愈人数
    # deadCount=[]#死亡人数
 
    # ws.write(0,0,label = '国家')
    # ws.write(0,1,label = '省份')
    # ws.write(0,2,label = '死亡人数')
    # ws.write(0,3,label = '治愈人数')
    # ws.write(0,4,label = '确诊人数')
    # ws.write(0,5,label = '疑似人数')
 
    # wk.write(0,0,label = '省份')
    # wk.write(0,1,label = '下属城市')
    # wk.write(0,2,label = '死亡人数')
    # wk.write(0,3,label = '治愈人数')
    # wk.write(0,4,label = '确诊人数')
    # wk.write(0,5,label = '疑似人数')
    # k=1
    # l=1
 
    # for i in ALL:
    # #     print(i["provinceName"]+": "+"死亡人数："+str(i["deadCount"])+" 治愈人数："+str(i["curedCount"])+" 确诊人数："+str(i["confirmedCount"])+" 疑似人数："+str(i["suspectedCount"]))
    #     ws.write(k,0,label = i["country"])
    #     ws.write(k,1,label = i["provinceName"])
    #     ws.write(k,2,label = i["deadCount"])
    #     ws.write(k,3,label = i["curedCount"])
    #     ws.write(k,4,label = i["confirmedCount"])
    #     ws.write(k,5,label = i["suspectedCount"])
    #     if i["country"]=="中国":
    #         for j in i["cities"]:
    #             wk.write(l,0,label = i["provinceName"])
    #             wk.write(l,1,label = j["cityName"])
    #             wk.write(l,2,label = j["deadCount"])
    #             wk.write(l,3,label = j["curedCount"])
    #             wk.write(l,4,label = j["confirmedCount"])
    #             wk.write(l,5,label = j["suspectedCount"])
    #             l+=1
    # #             print(j["cityName"]+":\n 死亡人数："+str(j["deadCount"])+" 治愈人数："+str(j["curedCount"])+" 确诊人数："+str(j["confirmedCount"])+" 疑似人数："+str(j["suspectedCount"]))
    #     k+=1
    # #     print('\n')
    # wb.save('新型肺炎%s时统计表.xls'%newTime)
    # showinfo(title='成功', message='今日数据统计完成！') 
    
# def fun():
#     th=threading.Thread(target=cxk)
#     th.setDaemon(True)#守护线程
#     th.start()
    # showinfo(title='提示', message='后台数据统计已开始\n请稍等，完成后将会有提示！')
    
if __name__ == '__main__':
    cxk()
