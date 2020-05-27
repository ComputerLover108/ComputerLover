'Dim dir As String
'pathName = "E:\public\test\报表共享(王全）\2012年基本日报"

Private Sub 遍历文件(pathName As String)
    Dim afileSystem, afolderPath, afolders, afiles
    Set afileSystem = CreateObject("scripting.filesystemobject")
    Set afolderPath = afileSystem.getfolder(pathName)      '文件路径
    Set afolders = afolderPath.subfolders     '子文件夹集定义
      
    For Each afolder In afolders    '遍历文件夹中的子文件夹
        Set afiles = afolder.Files     '文件集定义
          
        For Each afile In afiles      '遍历每个子文件夹中的文件
            If Right(afile.Name, 3) = "xls" Then     '选择扩展名为*.xls的文件
              
                Set fs = CreateObject("scripting.filesystemobject")
                absName = fs.GetAbsolutePathName(afile.Name)
                wb = Workbooks.Open(absName)
                cvsName = fs.GetBaseName(afile.Name)
              
            End If
        Next
    Next
End Sub