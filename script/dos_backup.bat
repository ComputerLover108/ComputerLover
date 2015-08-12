rem ѧϰ��Դ��http://www.jb51.net/article/30200.htm

@echo off 
rem ****************************** 
rem * ��ʱ��ɾ���ļ�Ŀ¼�������� * 
rem ****************************** 
rem ������ʱĿ¼��·�� 
set tempDir=%tmp%\remove_%date:~0,10% 
if not exist %tempDir% md %tempDir% 
rem ���ô������ڵĽű��ļ���·�� 
set scriptFile=%tempDir%\get_date.vbs 
rem ���Ҫ���������� 
set days=%~1 
if "%days%" == "" goto printUsage 
rem ���Ŀ��Ŀ¼��·�� 
set dirPath=%~2 
if "%dirPath%" == "" set dirPath=. 
rem ���Ҫ�������ļ���ʽ 
set fileSpec=%~3 
if "%fileSpec%" == "" set fileSpec=*.* 
rem ���ɼ������ڵĽű��ļ������ɾ���Ľ�ֹ���� 
echo d=date()-%1 > %scriptFile% 
echo s=right("0000" ^& year(d),4) ^& "-" ^& right("00" ^& month(d),2) ^& "-" ^& right("00" ^& day(d),2) >> %scriptFile% 
echo wscript.echo s >> %scriptFile% 
for /f %%i in ('cscript /nologo %scriptFile%') do set lastDate=%%i 
rem ����Ŀ��Ŀ¼���ÿ������ 
for /f "tokens=1,2,3* delims=<> " %%i in ('dir "%dirPath%\%fileSpec%" /a /-c /tc') do call :proc "%%i" "%%j" "%%k" "%%l" 
goto :done 
rem ����Ŀ��Ŀ¼�����Ĺ��� 
:proc 
rem ��ö���Ĵ������ڲ��ж��Ƿ�Ϊ��Ч��ʽ 
set fileDate=%~1 
echo %fileDate% | findstr "[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]" > nul 
if errorlevel 1 goto end 
rem ��ö�������� 
set fileType=%~3 
if "%fileType%" == "" goto end 
rem ��ö�������� 
set fileName=%~4 
if "%fileName%" == "" goto end 
if "%fileName%" == "." goto end 
if "%fileName%" == ".." goto end 
if "%fileName%" == "�ֽ�" goto end 
if "%fileName%" == "�����ֽ�" goto end 
rem �ж϶��������Ƿ�С�ڻ����ɾ���Ľ�ֹ���� 
if "%fileDate:~0,10%" leq "%lastDate%" ( 
echo deleting "%fileName%" ... 
if "%fileType%" == "DIR" ( rd /s /q "%dirPath%\%fileName%" ) else ( del /q /f "%dirPath%\%fileName%" ) 
) 
goto end 
:error 
echo An error occurred during backuping. 
:done 
rd /s /q %tempDir% 
goto end 
:printUsage 
echo Usage: %0 ^<Days^> [Work directory] [Target file specification (can include wildcards)] 
goto end 
:end 