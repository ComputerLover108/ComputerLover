@echo off
path d:\backup\mytools;%path%;
d:
cd d:\报表共享(王全）
xcopy /y \\jz20-2-sc\2010年产量统计曲线图\2011年产量统计曲线图.xls              		d:\报表共享(王全）
xcopy /y \\Jz202-dd\通球15分钟记录报表\2011年上游各平台供气量统计.xls           		d:\报表共享(王全） 
xcopy /y \\Jz202-dd\通球15分钟记录报表\新建文件夹\生产数据动态分析表(2010).xls  		d:\报表共享(王全）
xcopy /y \\Jz202-dd\通球15分钟记录报表\循环水蒸发量、排污统计表.xls             		d:\报表共享(王全）
xcopy /y \\Jz202-dd\王全的宝贝（在dd上）\生产报表\JZ20-2分离厂基本生产情况及消耗统计10.02.xls 	d:\报表共享(王全）

e:
cd e:\backup
 7za u \\中控2\重要文件夹\工艺报表共享.7z d:\报表共享(王全）
 if not exist 工艺报表共享%date:~0,-4%.rar goto backup else goto update

 :update
 echo 每天更新备份
 rar u e:\backup\工艺报表共享%date:~0,-4%.rar 	d:\报表共享(王全）


 :backup
 echo 每天备份
 rar a e:\backup\工艺报表共享%date:~0,-4%.rar 	d:\报表共享(王全）

xcopy /y e:\backup\工艺报表共享%date:~0,-4%.rar \\10.30.29.52\重要文件夹\
set /y day=%date:~2,2%
if day==1 goto monthEndBackup
:monthEndBackup
echo 月初备份
7za a     e:\backup\工艺报表共享%date:~0,-4%.7z d:\报表共享(王全）
xcopy /y  e:\backup\工艺报表共享%date:~0,-4%.7z \\10.30.29.52\重要文件夹\

exit
