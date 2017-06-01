cd /d D:\public\temp\winiso
dism /Mount-Wim /WimFile:D:\public\temp\winiso\boot.wim /index:2 /MountDir:D:\public\temp\mywin7
rem Dism /Image:D:\public\temp\mywin7 /Add-Driver /Driver:D:\public\temp\amd /Recurse /ForceUnsigned
rem Dism /Image:D:\public\temp\mywin7 /Add-Driver /Driver:D:\public\temp\amd /Recurse 
dism /unmount-wim /mountdir:D:\public\temp\mywin7 /commit

dism /Mount-Wim /WimFile:D:\public\temp\winiso\install.wim /index:4 /MountDir:D:\public\temp\mywin7
rem rem Dism /Image:D:\public\temp\mywin7 /Add-Driver /Driver:D:\public\driver\ab350-game\mb_driver_chipset_am4 /Recurse /ForceUnsigned 
rem Dism /Image:D:\public\temp\mywin7 /Add-Driver /Driver:D:\public\driver\ab350-game\mb_driver_chipset_am4 /Recurse 
dism /unmount-wim /mountdir:D:\public\temp\mywin7 /commit