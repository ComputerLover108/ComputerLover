#�����ļ�


import os
def searchdir(arg,dirname,names):
  for filespath in names:
    open ('c:\\test.txt','a').write('%s\r\n'%(os.path.join(dirname,filespath))) 
if __name__=="__main__":
  paths="g:\\"
  os.path.walk(paths,searchdir,())
  

[����] �����޸ģ�������ļ�����

# -*- coding: cp936 -*-
import os,time
#���ļ������е�ʱ���Ϊ��2011-1-12 00��00��00��ʽ��
def formattime(localtime):
  endtime=time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(localtime))
  return endtime

def searchdir(arg,dirname,names):
  for filespath in names:
    #�õ��ļ�·��
    fullpath=os.path.join(dirname,filespath)
    #�õ��ļ�����
    statinfo=os.stat(fullpath)
    #�ļ���С
    sizefile=statinfo.st_size
    #����ʱ��
    creattime=formattime(statinfo.st_ctime)
    #�޸�ʱ��
    maketime=formattime(statinfo.st_mtime)
    #���ʱ��
    readtime=formattime(statinfo.st_atime)
    #�ж����ļ��л����ļ�
    if os.path.isdir(fullpath):
      filestat='DIR'
    else:
      filestat='FILE'
  
    open ('c:\\test.txt','a').write('��%s��·����%s  �ļ���С(B)��%s  ����ʱ�䣺%s  �޸�ʱ�䣺%s  ���ʱ�䣺%s\r\n'%(filestat,fullpath,sizefile,creattime,maketime,readtime)) 

if __name__=="__main__":
  paths="g:\\"
  os.path.walk(paths,searchdir,())
  

