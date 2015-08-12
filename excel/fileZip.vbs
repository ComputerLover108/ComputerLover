call main() 
Sub main() 
Dim fs '文件系统。 
Dim f 'folder 
Dim fc 'files 
Dim s 'string 
Dim ws 'SHELL。 
Dim subfs 
Dim fi 
'创建SHELL。 
Set ws = CreateObject("WScript.Shell") 
'创建文件对象。 
Set fs = CreateObject("Scripting.FileSystemObject") 
Set f = fs.GetFolder(ws.currentdirectory) 
Handle_files(ws.currentdirectory) 
Set subfs = f.SubFolders 
'遍历每个子目录。 
For Each fi In subfs 
Call ListSub(fi.Path) 
Next 
End Sub 
Sub ListSub(filename) 
On Error Resume Next 
Dim subfs '子目录。 
'首先处理当前目录。 
Handle_Files(filename) 
'创建文件对象。 
Set fs = CreateObject("Scripting.FileSystemObject") 
Set f = fs.GetFolder(filename) 
Set subfs = f.SubFolders 
For Each fi In subfs 
Call ListSub(fi.Path) 
Next 
End Sub 
'处理每个目录下的文件。 
Sub Handle_Files(foldername) 
'创建文件对象。 
Set fs = CreateObject("Scripting.FileSystemObject") 
Set f = fs.GetFolder(foldername) 
Set fc = f.Files 
'创建SHELL。 
Set ws = CreateObject("WScript.Shell") 
'遍历文件对象。 
For Each fl In fc 
if ( RegExpTest(".vbs|.rar|.zip",fl.name) = false) then 
'进行压缩。 
s = "winrar M -ep " & fl.Path & ".rar " & fl.Path 
output s 
ws.Run s, 0, True 
End If 
Next 
End Sub 
sub output(string) 
wscript.echo string 
end sub 
'使用正则表达式进行判断。 
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