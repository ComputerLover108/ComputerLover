Attribute VB_Name = "模块1"
'所有艺术字去除删除线，下划线
Sub 去除删除线下划线()
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


