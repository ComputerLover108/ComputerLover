rem 学习来源：http://www.jb51.net/article/25911.htm
@echo off
color 0a
title windows 2003文件夹权限设置 by ╰☆孤影☆╮
echo.
echo.
echo.
cacls "C:\Windows" /r everyone /e
cacls "C:\Documents and Settings" /r everyone /e
cacls "C:\Documents and Settings\All Users" /r everyone /e
cacls "C:\Documents and Settings\All Users\Documents" /r everyone /e
cacls "C:\Inetpub\wwwroot\aspnet_client" /r everyone /e
cacls "C:\Documents and Settings\All Users\Application Data\Microsoft" /r everyone /e
cacls "C:\Documents and Settings\All Users\Application Data\Microsoft\HTML Help" /r

everyone /e
cacls "C:\Windows" /r "CREATOR OWNER" /e
cacls "C:\Windows\repair" /r "CREATOR OWNER" /e
cacls "C:\Windows\system32" /r "CREATOR OWNER" /e
cacls "C:\Windows\system32\wbem" /r "CREATOR OWNER" /e
cacls "C:\Windows\system32\config" /r "CREATOR OWNER" /e
cacls "C:\Program Files" /r "CREATOR OWNER" /e
cacls "C:\Program Files\WindowsUpdate" /r "CREATOR OWNER" /e
cacls "C:\Documents and Settings\All Users\Documents" /r "CREATOR OWNER" /e
cacls "C:\Documents and Settings\All Users\Application Data" /r "CREATOR OWNER" /e
cacls "C:\Windows" /r "Power Users" /e
cacls "C:\Windows\repair" /r "Power Users" /e
cacls "C:\Windows\system32" /r "Power Users" /e
cacls "C:\Windows\system32\wbem" /r "Power Users" /e
cacls "C:\Windows\system32\config" /r "Power Users" /e
cacls "C:\Program Files" /r "Power Users" /e
cacls "C:\Documents and Settings" /r "Power Users" /e
cacls "C:\Program Files\WindowsUpdate" /r "Power Users" /e
cacls "C:\Documents and Settings\All Users" /r "Power Users" /e
cacls "C:\Documents and Settings\All Users\Documents" /r "Power Users" /e
cacls "C:\Documents and Settings\All Users\Application Data" /r "Power Users" /e
cacls "C:\Documents and Settings\All Users\Application Data\Microsoft" /r "Power Users" /e
cacls "C:\Documents and Settings\All Users\Application Data\Microsoft\HTML Help" /r "Power

Users" /e
cacls "C:\Program Files" /r "TERMINAL SERVER USER" /e
cacls "C:\Documents and Settings\All Users" /r users /e
cacls "C:\Documents and Settings\All Users\Documents" /r users /e
cacls "C:\Documents and Settings\All Users\Application Data" /r users /e
cacls "C:\Documents and Settings" /r users /e
cacls "C:\Windows" /r users /e
cacls "C:\Windows\addins" /r users /e
cacls "C:\Windows\AppPatch" /r users /e
cacls "C:\Windows\Connection Wizard" /r users /e
cacls "C:\Windows\Debug" /r users /e
cacls "C:\Windows\Driver Cache" /r users /e
cacls "C:\Windows\Help" /r users /e
cacls "C:\Windows\IIS Temporary Compressed Files" /r users /e
cacls "C:\Windows\java" /r users /e
cacls "C:\Windows\msagent" /r users /e
cacls "C:\Windows\mui" /r users /e
cacls "C:\Windows\repair" /r users /e
cacls "C:\Windows\Resources" /r users /e
cacls "C:\Windows\security" /r users /e
cacls "C:\Windows\system" /r users /e
cacls "C:\Windows\TAPI" /r users /e
cacls "C:\Windows\twain_32" /r users /e
cacls "C:\Windows\Web" /r users /e
cacls "C:\Windows\system32\3com_dmi" /r users /e
cacls "C:\Windows\system32\administration" /r users /e
cacls "C:\Windows\system32\Cache" /r users /e
cacls "C:\Windows\system32\CatRoot2" /r users /e
cacls "C:\Windows\system32\Com" /r users /e
cacls "C:\Windows\system32\config" /r users /e
cacls "C:\Windows\system32\dhcp" /r users /e
cacls "C:\Windows\system32\drivers" /r users /e
cacls "C:\Windows\system32\export" /r users /e
cacls "C:\Windows\system32\icsxml" /r users /e
cacls "C:\Windows\system32\lls" /r users /e
cacls "C:\Windows\system32\LogFiles" /r users /e
cacls "C:\Windows\system32\MicrosoftPassport" /r users /e
cacls "C:\Windows\system32\mui" /r users /e
cacls "C:\Windows\system32\oobe" /r users /e
cacls "C:\Windows\system32\ShellExt" /r users /e
pause 