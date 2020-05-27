#coding=utf-8
from datetime import datetime, date, timedelta
def isMonthEnd() :
    today = datetime.today()
    #print(today)
    d = timedelta(days=1)
    tommorrow = today + d
    #print(tommorrow)
    return (tommorrow.day == 1);

import os
import time

source_dir = r'D:\报表共享(王全）'
target_dir = r'\\中控2\重要文件夹'
temp_dir = r'E:\重要文件夹'
#print( os.getcwd() )
os.chdir(temp_dir)
#print( os.getcwd() )
pair = os.path.split(source_dir)
backupFileDaily = pair[1] + time.strftime('%Y-%m-%d') + '.7z'
backupFile = pair[1] + '.7z'
compress_command = '7za '
if not os.path.exists(backupFileDaily):
    option = ' a '
else :
    option = ' u '


command = compress_command + option + backupFileDaily + ' ' + source_dir
#os.system(command)
command = compress_command + ' u ' + target_dir + '\\' + backupFile + ' ' + source_dir
#os.system(command)
backupCommand = 'xcopy /y ' + backupFileDaily + ' ' + target_dir
#os.system(backupCommand)






