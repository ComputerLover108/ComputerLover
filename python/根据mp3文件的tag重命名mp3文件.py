#根据mp3文件的tag重命名mp3文件

#!/usr/bin/python
# -*- coding: utf-8 -*-

#此脚本用于将所在文件夹的mp3文件依据其mp3id进行重命名
#请将此脚本放在要重命名的mp3文件所在的文件夹运行即可
#时间：2010/12/16
#作者：lrhehe

import os,sys

nowpath=os.getcwd()
files=os.listdir(nowpath)

def rename(old,new):
    print 'begin to rename',old,new
    new2=''
    for i in range(0,len(new)):
        a=new[i]
        if a!=u'\x00':
            new2+=a
    if new2!=old and new2:
        os.rename(old,new2)
        print 'rename',old,'to',new2


for name in files:
    if os.path.isfile(name) and len(name)>20:
        #len(name)限定仅限于文件名长度超过20的，如果想要用此方法重命名原有的mp3文件，那么
        #可将此限定去掉，不过最好保证要改名的文件有规范的mp3id
        print name       
        f=open(name,'r')
        f.seek(-128,2)
        if f.read(3)=='TAG':
            temp=f.read(21)
            temp=unicode(temp,'gbk','ignore')
            f.close()
            temp= temp+'.mp3'
            rename(name,temp)

