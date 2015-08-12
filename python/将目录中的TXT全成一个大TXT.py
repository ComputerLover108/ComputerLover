#
#��Ŀ¼�е�TXTȫ��һ����TXT
#coding=gbk
import os
import sys
import glob
def dirTxtToLargeTxt(dir,outputFileName):
    '''��dirĿ¼�¶������е�TXT�ļ�,������д��outputFileName��ȥ'''
    #���dir����Ŀ¼���ش���
    if not os.path.isdir(dir):
        print "����Ĳ����д�%s����һ��Ŀ¼" %dir
        return False
    #list all txt files in dir
    outputFile = open(outputFileName,"a")
    for txtFile in glob.glob(os.path.join(dir,"*.txt")):
        print txtFile
        inputFile = open(txtFile,"rb")
        for line in inputFile:
            outputFile.write(line)
    return True


if __name__ =="__main__":
    if len(sys.argv) < 3:
        print "Usage:%s dir outputFileName" %sys.argv[0]
        sys.exit()
    dirTxtToLargeTxt(sys.argv[1],sys.argv[2])
    

