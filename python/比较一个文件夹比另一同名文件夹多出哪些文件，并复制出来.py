#ȽһļбһͬļжЩļƳ

# coding=gbk
'''
Created on 2011-1-7
@author: HH
'''
  
import os,ConfigParser

'''
ݹгĳĿ¼µļList
'''
def listDir (fileList,path):
    files=os.listdir(path)
    for i in  files:
        file_path=path+"\\"+i
        if os.path.isfile(file_path):
            fileList.append(file_path)
    for i in files:
        file_path=path+"\\"+i
        if os.path.isdir(file_path):
            #fileList.append(file_path)
            listDir(fileList,file_path)
    return fileList

'''
Listдļ
'''
def writeListToFile(list,path):
    strs="\n".join(list)
    f=open(path,'wb')
    f.write(strs)
    f.close()

'''
ļݲList
'''
def readFileToList(path):
    lists=[]
    f=open(path,'rb')
    lines=f.readlines()
    for line in lines:
        lists.append(line.strip())
    f.close()
    return lists

'''
Ƚļ--Setʽ
'''
def compList(list1,list2):
    return list(set(list1)-set(list2))

'''
Listļָλ
'''
def copyFiles(fileList,targetDir):
    for file in fileList:
        targetPath=os.path.join(targetDir,os.path.dirname(file))
        targetFile=os.path.join(targetDir,file)
        if not os.path.exists(targetPath):
            os.makedirs(targetPath)
        if not os.path.exists(targetFile) or (os.path.exists(targetFile) and os.path.getsize(targetFile)!=os.path.getsize(file)):
            print "ڸļ"+file
            open(targetFile,'wb').write(open(file,'rb').read())
        else:
            print "ļѴڣƣ"


if __name__ == '__main__':
    path=".svn"
    #ȡԴĿ¼
    
    txtFile="1.txt"
    #Ŀ¼ṹĿļ
    
    tdir="cpfile"
    #ƵĿĿ¼
    
    cfFile="config.ini";
    #ļļ
    fileList=[]
    
    #ȡļ
    if(os.path.exists(cfFile)):
        cf=ConfigParser.ConfigParser()
        cf.read(cfFile)
        
        path=cf.get("main", "sourceDir")
        txtFile=cf.get("main","txtFile")
        tdir=cf.get("main","targetDir")
    else:
        print "ļڣ"
        raw_input("\n س ˳\n")
        exit()
    
    if(os.path.exists(txtFile)):
        #ļڣͶȡȽ
        list1=readFileToList(txtFile)
        print "ڶȡļб"
        fileList=listDir (fileList,path)
        print "ڱȽļ"
        list_res=compList(fileList,list1)
        
        if len(list_res)>0:
            print "ԭĿ¼вڵļ\n"
            print "\n".join(list_res)
            print "\nļ"+str(len(list_res))+"\n"
            if raw_input("\nǷļy/n")!='n':
                copyFiles(list_res,tdir)
        else:
            print "ûвͬļ"
    else:
        #ļڣ򵼳ļ
        print "ڶȡļб"
        fileList=listDir (fileList,path)
        writeListToFile(fileList,txtFile)
        print "ѱ浽ļ"+txtFile
        
    raw_input("\n س ˳\n")

[] ļconfig.ini

#ļconfig.ini
[main]
sourceDir=wwwroot
txtFile=1.txt
targetDir=cp

