Attribute VB_Name = "ģ��1"
'����������ȥ��ɾ���ߣ��»���
Sub ȥ��ɾ�����»���()
    On Error Resume Next
    Application.DisplayAlerts = False
    For Each sh In Sheets
        For Each myshape In sh.Shapes
                Debug.Print myshape.Name
                myshape.TextFrame2.TextRange.Font.Strikethrough = msoFals
                myshape.TextFrame2.TextRange.Font.UnderlineStyle = msoNoUnderline
        Next
    Next sh
End Sub


