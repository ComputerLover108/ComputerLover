#遍历文件


import os
def searchdir(arg,dirname,names):
  for filespath in names:
    open ('c:\\test.txt','a').write('%s\r\n'%(os.path.join(dirname,filespath))) 
if __name__=="__main__":
  paths="g:\\"
  os.path.walk(paths,searchdir,())
  

[代码] 做了修改，添加了文件属性

# -*- coding: cp936 -*-
import os,time
#将文件属性中的时间改为‘2011-1-12 00：00：00格式’
def formattime(localtime):
  endtime=time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(localtime))
  return endtime

def searchdir(arg,dirname,names):
  for filespath in names:
    #得到文件路径
    fullpath=os.path.join(dirname,filespath)
    #得到文件属性
    statinfo=os.stat(fullpath)
    #文件大小
    sizefile=statinfo.st_size
    #创建时间
    creattime=formattime(statinfo.st_ctime)
    #修改时间
    maketime=formattime(statinfo.st_mtime)
    #浏览时间
    readtime=formattime(statinfo.st_atime)
    #判断是文件夹还是文件
    if os.path.isdir(fullpath):
      filestat='DIR'
    else:
      filestat='FILE'
  
    open ('c:\\test.txt','a').write('【%s】路径：%s  文件大小(B)：%s  创建时间：%s  修改时间：%s  浏览时间：%s\r\n'%(filestat,fullpath,sizefile,creattime,maketime,readtime)) 

if __name__=="__main__":
  paths="g:\\"
  os.path.walk(paths,searchdir,())
  

