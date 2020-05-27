#-------------------------------------------------------------------------------
# Name:        葫芦岛终端工艺报表自动化
# Purpose:     简化报表工艺报表的录入［execel］，加入数据库系统［postgresql］,添加数据分析功能。
#
# Author:      wkx
#
# Created:     06-06-2012
# Copyright:   (c) wkx 2012
# Licence:     <your licence>
#-------------------------------------------------------------------------------
#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import os
import sys
import logging

logger = logging.getLogger("葫芦岛终端工艺报表程序运行日志")
logger.setLevel(logging.DEBUG)
fh = logging.FileHandler('run.log')
fh.setLevel(logging.DEBUG)
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
fh.setFormatter(formatter)
logger.addHandler(fh)
#-------------------------------------------------------------------------------

def getDate(x):
    import string
    from datetime import timedelta
    import datetime
    c__s_date = datetime.date(1899, 12, 31).toordinal() - 1
    #print( x,isinstance(x,float) )
    """
    if not x.isdigit() :
        #print('getDate(',x,')')
        #logger.error('getDate(',x,')')
        return(x)
    """
    try:
        date = float(x)
    except:
        return(x)
    if isinstance(date, float) and date > 1:
        date = int(date)
        d = datetime.date.fromordinal(c__s_date + date)
        return( d.strftime("%Y-%m-%d") )
    return('00000000')
#-------------------------------------------------------------------------------
def addContent(fileName):
    import csv
    message = 'addContent('+fileName+')'
    logger.info(message)
    try:
        with open(fileName, newline='', encoding='utf-8') as f:
            reader = csv.reader(f,delimiter=';')
            gasRecord = []
            title ="JZ20-2天然气分离厂基本生产情况汇报表"
            """
            gasRQ  #日期
            gasJTH  #外供锦天化
            gasJX #外供精细化工
            gasXA #外供新奥燃气
            gasZY #自用气
            gasFK #放空量
            gasWS #总外输气量
            gasCQ #总产气量
            gasJSQ #接收气量
            gasBZ #备注
            """
            i = 0
            for row in reader:
                if i == 1 :
                    #d = getDate(row[0])
                    #gasRecord.append(d)
                    #print("日期",d)
                    gasRQ = row[0]
                if i == 4 :
                    gasWS = row[2]
                if i == 5 :
                    #gasRecord.append(row[2])
                    #print("外供锦天化",row[2])
                    gasJTH = row[2]
                if i == 6 :
                    #gasRecord.append(row[2])
                    #print("外供精细化工",row[2])
                    gasJX = row[2]
                if i == 7 :
                    #gasRecord.append(row[2])
                    #print("自用气",row[2])
                    gasZY = row[2]
                if i == 8 :
                    #gasRecord.insert(3,row[2])
                    #print("外供新奥燃气",row[2])
                    gasXA = row[2]
                if i == 9 :
                    #gasRecord.append(row[2])
                    #print("放空量",row[2])
                    #gasRecord.append(row[5])
                    #print("备注：",row[5])
                    gasFK = row[2]
                    gasBZ = row[5]
                if i == 10:
                    gasCQ = row[2]
                if i == 11 :
                    #gasRecord.insert(len(gasRecord)-1,row[2])
                    #print("接收气量",row[2])
                    gasJSQ = row[2]
                """
                a=0
                for y in row :
                    print('[',i,a,']',y)
                    a += 1
                """
                i += 1
            gasRecord.append(gasRQ)
            gasRecord.append(gasJTH)
            gasRecord.append(gasJX)
            gasRecord.append(gasXA)
            gasRecord.append(gasZY)
            gasRecord.append(gasFK)
            gasRecord.append(gasWS)
            gasRecord.append(gasCQ)
            gasRecord.append(gasJSQ)
            gasRecord.append(gasBZ)
            #print(gasRecord,fileName)
        outFile = r'E:\public\test\葫芦岛终端报表\天然气生产.csv'
        FIELDS = ["日期",\
                  "外供锦天化", "外供精细化工", "外供新奥燃气",\
                  "自用气","放空量",\
                  "总外输气量","总产气量",\
                  "接收气量",\
                  "备注"]
        if not os.path.exists(outFile) :
            f = open(outFile,'w')
            writer = csv.csv.DictWriter(f,FIELDS)
            writer.writeheader()
            f.close()
        with open(outFile,'a') as f:
            writer = csv.csv.DictWriter(f,FIELDS)
            writer.writerow(gasRecord)
    except IOError as err:
        print("I/O error: {0}".format(err))
    except RuntimeError as err :
        message = 'addContent(' + fname + ') run error!'
        logger.error(message)
    finally:
        f.close()

#-------------------------------------------------------------------------------
def prepare():
    import os
    import sys
    from os import listdir
    dir = sys.argv[1]
    #print(dir)
    os.chdir(dir)
    for fname in listdir(dir) :
        try:
            addContent( fname )
        except RuntimeError as err :
            message = 'addContent(' + fname + ') run error!'
            logger.error(message)
            continue

#-------------------------------------------------------------------------------

def main():
    prepare()

if __name__ == '__main__':
    main()



