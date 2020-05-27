#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2019-06-18 09:24:51
# @Author  : wkx (wkx9dragon@126.com)
# @Link    : ${link}
# @Version : $Id$

import argparse
import codecs
import os
import sys
import chardet

# 解析文件编码格式


def code( path):
    f = open(path, 'rb')
    f_read = f.read()
    f_charInfo = chardet.detect(f_read)
    return f_charInfo


def GetFileExtension(file):
    (filepath, filename) = os.path.split(file)
    (shortname, extension) = os.path.splitext(filename)
    return extension


def GetFileEncodingFormat(file):
    fileHandle = open(file, 'r', errors='ignore')
    fileContext = fileHandle.read()
    return chardet.detect(fileContext.encode())["encoding"]


def CovertFileCodeFormat(file, out_encode):
    try:
        encoding = GetFileEncodingFormat(file)
        extension = GetFileExtension(file)
        if (encoding != out_encode):
            fileHandle = codecs.open(file, 'r', encoding, errors='ignore')
            fileContext = fileHandle.read()
            codecs.open(file, 'w', out_encode,
                        errors='ignore').write(fileContext)
            print("convert:" + file + " sucess")
    except IOError as err:
        print("I/O error: {0}".format(err))


def ProcessDir(dir, out_encode):
    for root, dirs, files in os.walk(dir):
        for file in files:
            filePath = os.path.join(root, file)
            CovertFileCodeFormat(filePath, out_encode)

 # page = page_req.text.encode('iso-8859-1').decode('gbk')


def getListFiles(path):
    assert os.path.isdir(path), '%s not exist.' % path
    ret = []
    for root, dirs, files in os.walk(path):
        # print '%s, %s, %s' % (root, dirs, files)
        for filespath in files:
            ret.append(os.path.join(root, filespath))
    return ret


def main():
    parser = argparse.ArgumentParser(description="查看，转换文件或指定目录下所有文件编码！")
    parser.add_argument("-f","--file",help="input file name")
    parser.add_argument("-d", "--directory",help="input directory name")
    parser.add_argument("--encode",default="UTF-8",help="convert encode")
    parser.add_argument("--verify",type=bool,default=False,help="确认操作")
    args = parser.parse_args()
    files=list()
    if args.file:
        filename = args.file
        files.append(filename)
    if args.directory:
        directory = args.directory
        files=getListFiles(directory)   
    if files:
    	for filename in files:
    		if args.verify:
    			CovertFileCodeFormat(filename,args.encode)
    		else:
    			print(filename,GetFileEncodingFormat(filename))



if __name__ == '__main__':
    main()
