#coding=utf-8

import os
import time

source_dir = r'D:\共享文件（王全）'
target_dir = r'\\中控2\重要文件夹'

pair = os.path.split(source_dir)
print(pair)

backupFile = pair[1] + time.strftime('%Y-%m-%d') + '.7z'
print(backupFile)

compress_command = '7za '
if not os.path.exists(backupFile):
	option = ' a '
else :
	option = ' u '	


command = compress_command + option + backupFile + ' ' + source_dir
#print(command)

#if os.system(command) == 0 :
#	print('Successful backup to', target)
#else :
#	print('Backup FAILED')