@echo off

color 0

title 设置上网环境

echo ☆☆☆☆请选择上网环境☆☆☆☆

echo.

echo 静态IP设置=======》按1键回车

echo 动态DHCP设置=======》按2键回车

set/p n=

if /i "%n%" equ "1" goto one

if /i "%n%" equ "2" goto two

:one

echo 您选择了静态IP设置

echo 正在设置,请稍后......

netsh interface ipv4 set address name="WLAN" source=static addr=192.168.16.169 mask=255.255.255.0 gateway=192.168.16.1 gwmetric=0 >nul

echo 正在添加本机主DNS...

netsh interface ipv4 set dnsservers name="WLAN" static 208.67.222.222

echo 正在添加备用DNS...

netsh interface ipv4 add dnsservers name="WLAN" 9.9.9.9

goto end

:two

echo 您选择了动态DHCP设置

echo 正在设置,请稍后......

netsh interface ipv4 set address name="无线网络连接" source=dhcp

echo 正在添加本机主DNS...

netsh interface ipv4 set dnsservers name="无线网络连接" source=dhcp

goto end

:end

color 2

echo ☆☆☆☆☆☆☆☆本机当前IP配置如下☆☆☆☆☆☆☆☆☆☆☆☆
ipconfig /all