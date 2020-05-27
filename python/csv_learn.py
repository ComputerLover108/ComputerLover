#-------------------------------------------------------------------------------
# Name:        模块1
# Purpose:
#
# Author:      wkx9dragon
#
# Created:     19-06-2012
# Copyright:   (c) wkx9dragon 2012
# Licence:     <your licence>
#-------------------------------------------------------------------------------
#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import csv
import os
from datetime import timedelta
import datetime
path = r'E:\public\test\葫芦岛终端报表\基本日报\csv'
fileName = r'基本生产日报表2012.5.18_Sheet1.csv'
#-------------------------------------------------------------------------------

def getDate(x):
    c__s_date = datetime.date(1899, 12, 31).toordinal() - 1
    date = float(x)
    if isinstance(date, float) and date > 1:
        date = int(date)
        d = datetime.date.fromordinal(c__s_date + date)
        return d.strftime("%Y-%m-%d")
    else:
        return '00000000'
#-------------------------------------------------------------------------------
def equal_list(x,y):
    if len(x) != len(y) :
        return(False)
    for i in range( len(x) ):
        print(x[i],y[i])
        if x[i] != y[i] :
            return(False)
    return(True)

def getFilesize(file):
    """
        获取要读取文件的大小
    """
    FILE_SIZE = 0
    fstream = open(file,'r')
    fstream.seek(0,os.SEEK_END)
    FILE_SIZE = fstream.tell()
    fstream.close()
    return(FILE_SIZE)

def lineCount( fname ):
    return len(open(fname).readlines())

#-------------------------------------------------------------------------------
def main():
    name = os.path.join(path,fileName)
    with open(name, newline='', encoding='utf-8') as f:
        reader = csv.reader(f,delimiter=';')
        gasRecord = []
        i = 0
        for row in reader:
            if i == 1 :
                d = getDate(row[0])
                gasRecord.append(d)
                #print("日期",d)
            if i == 5 :
                gasRecord.append(row[2])
                #print("外供锦天化",row[2])
            if i == 6 :
                gasRecord.append(row[2])
                #print("外供精细化工",row[2])
            if i == 7 :
                gasRecord.append(row[2])
                #print("自用气",row[2])
            if i == 8 :
                gasRecord.insert(3,row[2])
                #print("外供新奥燃气",row[2])
            if i == 9 :
                gasRecord.append(row[2])
                #print("放空量",row[2])
            if i == 11 :
                gasRecord.append(row[2])
                #print("接收气量",row[2])
            i += 1
        count_1 = float( gasRecord[1] ) + float( gasRecord[2] ) + float( gasRecord[3] )
        count_2 = count_1 + float( gasRecord[4] ) + float( gasRecord[5] )
        gasRecord.insert(len(gasRecord)-1,count_1)
        gasRecord.insert(len(gasRecord)-1,count_2)
        #
        outFile = r'天然气生产.csv'
        FIELDS = [r"日期",r"外供锦天化", r"外供精细化工", r"外供新奥燃气",r"自用气",r"放空量",r"总外输气量",r"总产气量",r"接收气量"]

        if not os.path.exists(outFile) :
            with open(outFile,'w') as fa:
                w = csv.writer(fa)
                w.writerow(FIELDS)
        with open(outFile, 'a') as f:
            writer = csv.writer(f)
            writer.writerow(gasRecord)
        """
        dict_writer = csv.DictWriter(open(outFile, 'a'), fieldnames=FIELDS,delimiter='\t')
        dict_writer.writeheader() # CSV第一行需要自己加入
        dict_writer.writerow(gasRecord) # rows就是表单提交的数据
        """

#-------------------------------------------------------------------------------
if __name__ == '__main__':
    main()
