#Ӳвļ

#coding:cp936
'''
ߣС
'''
import os
#浱ǰеĴ
def existdisk():
	curdisks = []
	allDisks = ['C:', 'D:', 'E:', 'F:', 'G:', 'H:', 'I:', 'J:', 'K:', \
			    'L:', 'M:', 'N:', 'O:', 'P:', 'Q:', 'R:', 'S:', 'T:', \
                'U:', 'V:', 'W:', 'X:', 'Y:', 'Z:', 'A:', 'B:']
	for disk in allDisks:
		if os.path.exists(disk):
			curdisks.append(disk)
			
	return curdisks

#Ŀ¼квҵַ
def SearchDirFile(path, src):
	if not os.path.exists(path):
		print "%s ·" % path
	for root , dirs, files in os.walk(path, True):
		if - 1 != root.find(src):   #·ǷҪҵַ
			print root  
		for item in files:
			 path = os.path.join(root, item)
			 if - 1 != path.find(src):         #ļбǷҪҵַ
			 	print path

			 	
			 	
#ļҪҵַ
def SearchFile(path, src):	
	if not os.path.exists(path):
		print "%s ·" % path
	for root, dirs, files in os.walk(path, True):
		for item in files:
			path = os.path.join(root, item)
			
			try:
				f = open(path, 'r')
				for eachline in f.readlines():
					if - 1 != eachline.find(src):    #ıǷҪҵַ
						print path
						f.close()
						break
			except:
				pass
	
	
#ҵǰдĿ¼ǷҪҵַ
def   SearchAllDirFile(src):	
	curdisks = existdisk()
	for disk in curdisks:
		disk = disk + '\\'
		SearchDirFile(disk, src)
	print ""
	
#ҵǰдĿ¼ļǷҪҵַ
def   SearchALLFile(src):			
	curdisks = existdisk()
	for disk in curdisks:
		disk = disk + "\\"
		SearchFile(disk, src)
	print ""
	
	
SearchALLFile('suixin@codemate.cn')

