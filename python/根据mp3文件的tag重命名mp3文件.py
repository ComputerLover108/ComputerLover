#����mp3�ļ���tag������mp3�ļ�

#!/usr/bin/python
# -*- coding: utf-8 -*-

#�˽ű����ڽ������ļ��е�mp3�ļ�������mp3id����������
#�뽫�˽ű�����Ҫ��������mp3�ļ����ڵ��ļ������м���
#ʱ�䣺2010/12/16
#���ߣ�lrhehe

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
        #len(name)�޶��������ļ������ȳ���20�ģ������Ҫ�ô˷���������ԭ�е�mp3�ļ�����ô
        #�ɽ����޶�ȥ����������ñ�֤Ҫ�������ļ��й淶��mp3id
        print name       
        f=open(name,'r')
        f.seek(-128,2)
        if f.read(3)=='TAG':
            temp=f.read(21)
            temp=unicode(temp,'gbk','ignore')
            f.close()
            temp= temp+'.mp3'
            rename(name,temp)

