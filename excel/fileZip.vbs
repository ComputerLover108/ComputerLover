call main() 
Sub main() 
Dim fs '�ļ�ϵͳ�� 
Dim f 'folder 
Dim fc 'files 
Dim s 'string 
Dim ws 'SHELL�� 
Dim subfs 
Dim fi 
'����SHELL�� 
Set ws = CreateObject("WScript.Shell") 
'�����ļ����� 
Set fs = CreateObject("Scripting.FileSystemObject") 
Set f = fs.GetFolder(ws.currentdirectory) 
Handle_files(ws.currentdirectory) 
Set subfs = f.SubFolders 
'����ÿ����Ŀ¼�� 
For Each fi In subfs 
Call ListSub(fi.Path) 
Next 
End Sub 
Sub ListSub(filename) 
On Error Resume Next 
Dim subfs '��Ŀ¼�� 
'���ȴ���ǰĿ¼�� 
Handle_Files(filename) 
'�����ļ����� 
Set fs = CreateObject("Scripting.FileSystemObject") 
Set f = fs.GetFolder(filename) 
Set subfs = f.SubFolders 
For Each fi In subfs 
Call ListSub(fi.Path) 
Next 
End Sub 
'����ÿ��Ŀ¼�µ��ļ��� 
Sub Handle_Files(foldername) 
'�����ļ����� 
Set fs = CreateObject("Scripting.FileSystemObject") 
Set f = fs.GetFolder(foldername) 
Set fc = f.Files 
'����SHELL�� 
Set ws = CreateObject("WScript.Shell") 
'�����ļ����� 
For Each fl In fc 
if ( RegExpTest(".vbs|.rar|.zip",fl.name) = false) then 
'����ѹ���� 
s = "winrar M -ep " & fl.Path & ".rar " & fl.Path 
output s 
ws.Run s, 0, True 
End If 
Next 
End Sub 
sub output(string) 
wscript.echo string 
end sub 
'ʹ��������ʽ�����жϡ� 
Function RegExpTest(patrn, strng) 
Dim regEx, retVal ' Create variable. 
Set regEx = New RegExp ' Create regular expression. 
regEx.Pattern = patrn ' Set pattern. 
regEx.IgnoreCase = False ' Set case sensitivity. 
retVal = regEx.Test(strng) ' Execute the search test. 
If retVal Then 
RegExpTest = true 
Else 
RegExpTest = false 
End If 
End Function 