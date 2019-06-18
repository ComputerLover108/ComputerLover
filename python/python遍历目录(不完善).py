#pythonĿ¼()

import os,sys

while 1:
	if sys.argv[1].startswith('--'):
		filePath = sys.argv[1][2:]
		break
	print 'has error!please input dir!'
	exit()
	
	
def listdir(dir,filePath):
	file = open(filePath,'a+')
	file.write('\n[' + dir + ']\n\n')
	fielnum = 0
	list = os.listdir(dir)
	dirlist = [];
	for line in list:
		filepath = os.path.join(dir,line)
		if os.path.isfile(filepath):
			file.write(filepath + '\n')
		else:
			dirlist.append(filepath)
	file.close()
	for dir in dirlist:
		listdir(dir,filePath)
	print 'end!' 
listdir(filePath,'a.txt')

