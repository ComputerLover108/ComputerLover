@echo off
path d:\backup\mytools;%path%;
d:
cd d:\������(��ȫ��
xcopy /y \\jz20-2-sc\2010�����ͳ������ͼ\2011�����ͳ������ͼ.xls              		d:\������(��ȫ��
xcopy /y \\Jz202-dd\ͨ��15���Ӽ�¼����\2011�����θ�ƽ̨������ͳ��.xls           		d:\������(��ȫ�� 
xcopy /y \\Jz202-dd\ͨ��15���Ӽ�¼����\�½��ļ���\�������ݶ�̬������(2010).xls  		d:\������(��ȫ��
xcopy /y \\Jz202-dd\ͨ��15���Ӽ�¼����\ѭ��ˮ������������ͳ�Ʊ�.xls             		d:\������(��ȫ��
xcopy /y \\Jz202-dd\��ȫ�ı�������dd�ϣ�\��������\JZ20-2���볧�����������������ͳ��10.02.xls 	d:\������(��ȫ��

e:
cd e:\backup
 7za u \\�п�2\��Ҫ�ļ���\���ձ�����.7z d:\������(��ȫ��
 if not exist ���ձ�����%date:~0,-4%.rar goto backup else goto update

 :update
 echo ÿ����±���
 rar u e:\backup\���ձ�����%date:~0,-4%.rar 	d:\������(��ȫ��


 :backup
 echo ÿ�챸��
 rar a e:\backup\���ձ�����%date:~0,-4%.rar 	d:\������(��ȫ��

xcopy /y e:\backup\���ձ�����%date:~0,-4%.rar \\10.30.29.52\��Ҫ�ļ���\
set /y day=%date:~2,2%
if day==1 goto monthEndBackup
:monthEndBackup
echo �³�����
7za a     e:\backup\���ձ�����%date:~0,-4%.7z d:\������(��ȫ��
xcopy /y  e:\backup\���ձ�����%date:~0,-4%.7z \\10.30.29.52\��Ҫ�ļ���\

exit
