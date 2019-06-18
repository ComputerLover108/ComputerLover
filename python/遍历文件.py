#ļ


import os
def searchdir(arg,dirname,names):
  for filespath in names:
    open ('c:\\test.txt','a').write('%s\r\n'%(os.path.join(dirname,filespath))) 
if __name__=="__main__":
  paths="g:\\"
  os.path.walk(paths,searchdir,())
  

[] ޸ģļ

# -*- coding: cp936 -*-
import os,time
#ļеʱΪ2011-1-12 000000ʽ
def formattime(localtime):
  endtime=time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(localtime))
  return endtime

def searchdir(arg,dirname,names):
  for filespath in names:
    #õļ·
    fullpath=os.path.join(dirname,filespath)
    #õļ
    statinfo=os.stat(fullpath)
    #ļС
    sizefile=statinfo.st_size
    #ʱ
    creattime=formattime(statinfo.st_ctime)
    #޸ʱ
    maketime=formattime(statinfo.st_mtime)
    #ʱ
    readtime=formattime(statinfo.st_atime)
    #жļлļ
    if os.path.isdir(fullpath):
      filestat='DIR'
    else:
      filestat='FILE'
  
    open ('c:\\test.txt','a').write('%s·%s  ļС(B)%s  ʱ䣺%s  ޸ʱ䣺%s  ʱ䣺%s\r\n'%(filestat,fullpath,sizefile,creattime,maketime,readtime)) 

if __name__=="__main__":
  paths="g:\\"
  os.path.walk(paths,searchdir,())
  

