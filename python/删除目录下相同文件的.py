"""
ɾĿ¼ͬļpython(md5)
"""
# -*- coding: UTF-8 -*-
import md5
import os
from time import clock as now
def getmd5(filename):
file_txt = open(filename,'rb').read()
m = md5.new(file_txt)
return m.hexdigest()
def main():
path = raw_input("path: ")
all_md5 = {}
all_size = {}
total_file=0
total_delete=0
start=now()
for file in os.listdir(path):
total_file += 1
real_path=os.path.join(path,file)
if os.path.isfile(real_path) == True:
size = os.stat(real_path).st_size
name_and_md5=[real_path,'']
if size in all_size.keys():
new_md5 = getmd5(real_path)
if all_size[size][1]=='':
all_size[size][1]=getmd5(all_size[size][0])
if new_md5 in all_size[size]:
print 'ɾ',file
total_delete += 1
else:
all_size[size].append(new_md5)
else:
all_size[size]=name_and_md5
end = now()
time_last = end - start
print 'ļ',total_file
print 'ɾ',total_delete
print 'ʱ',time_last,''

if __name__=='__main__':
main() 