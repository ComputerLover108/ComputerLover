#����Ӳ���в����ļ�������

#coding:cp936
'''
���ߣ�С�����
'''
import os
#���浱ǰ�еĴ���
def existdisk():
	curdisks = []
	allDisks = ['C:', 'D:', 'E:', 'F:', 'G:', 'H:', 'I:', 'J:', 'K:', \
			    'L:', 'M:', 'N:', 'O:', 'P:', 'Q:', 'R:', 'S:', 'T:', \
                'U:', 'V:', 'W:', 'X:', 'Y:', 'Z:', 'A:', 'B:']
	for disk in allDisks:
		if os.path.exists(disk):
			curdisks.append(disk)
			
	return curdisks

#Ŀ¼�к��в��ҵ��ַ�
def SearchDirFile(path, src):
	if not os.path.exists(path):
		print "%s ·��������" % path
	for root , dirs, files in os.walk(path, True):
		if - 1 != root.find(src):   #·�������Ƿ����Ҫ���ҵ��ַ�
			print root  
		for item in files:
			 path = os.path.join(root, item)
			 if - 1 != path.find(src):         #�ļ��б����Ƿ���Ҫ���ҵ��ַ�
			 	print path

			 	
			 	
#�����ļ���������Ҫ���ҵ��ַ�
def SearchFile(path, src):	
	if not os.path.exists(path):
		print "%s ·��������" % path
	for root, dirs, files in os.walk(path, True):
		for item in files:
			path = os.path.join(root, item)
			
			try:
				f = open(path, 'r')
				for eachline in f.readlines():
					if - 1 != eachline.find(src):    #�ı��������Ƿ���Ҫ���ҵ��ַ�
						print path
						f.close()
						break
			except:
				pass
	
	
#���ҵ�ǰ���д���Ŀ¼���Ƿ���Ҫ�ҵ��ַ�
def   SearchAllDirFile(src):	
	curdisks = existdisk()
	for disk in curdisks:
		disk = disk + '\\'
		SearchDirFile(disk, src)
	print "�������"
	
#���ҵ�ǰ���д���Ŀ¼�ļ��������Ƿ���Ҫ�ҵ��ַ�
def   SearchALLFile(src):			
	curdisks = existdisk()
	for disk in curdisks:
		disk = disk + "\\"
		SearchFile(disk, src)
	print "�������"
	
	
SearchALLFile('suixin@codemate.cn')

