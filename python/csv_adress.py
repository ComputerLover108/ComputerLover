#-------------------------------------------------------------------------------
# Name:        模块1
# Purpose:
#
# Author:      wkx9dragon
#
# Created:     26-06-2012
# Copyright:   (c) wkx9dragon 2012
# Licence:     <your licence>
#-------------------------------------------------------------------------------
#!/usr/bin/env python

def main():
    import csv
    import sys
    name = argv[1]
    #name = r'D:\BACKUP\重要文件\工作\jz202天然气分离厂（老厂）\葫芦岛终端生产日报1.csv'
    with open(name,'r') as file:
        reader = csv.reader(file)
        row = 1
        for record in reader:
            col = 1
            for item in record:
                print('R',row,'C',col,item)
                col += 1
            row +=1
    file.close()

if __name__ == '__main__':
    main()
