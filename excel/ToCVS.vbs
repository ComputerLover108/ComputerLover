'Dim dir As String
'pathName = "E:\public\test\������(��ȫ��\2012������ձ�"

Private Sub �����ļ�(pathName As String)
    Dim afileSystem, afolderPath, afolders, afiles
    Set afileSystem = CreateObject("scripting.filesystemobject")
    Set afolderPath = afileSystem.getfolder(pathName)      '�ļ�·��
    Set afolders = afolderPath.subfolders     '���ļ��м�����
      
    For Each afolder In afolders    '�����ļ����е����ļ���
        Set afiles = afolder.Files     '�ļ�������
          
        For Each afile In afiles      '����ÿ�����ļ����е��ļ�
            If Right(afile.Name, 3) = "xls" Then     'ѡ����չ��Ϊ*.xls���ļ�
              
                Set fs = CreateObject("scripting.filesystemobject")
                absName = fs.GetAbsolutePathName(afile.Name)
                wb = Workbooks.Open(absName)
                cvsName = fs.GetBaseName(afile.Name)
              
            End If
        Next
    Next
End Sub