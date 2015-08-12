#-------------------------------------------------------------------------------
# Name:        excel
# Purpose:
#
# Author:      ComputerLover
#
# Created:     31-05-2012
# Copyright:   (c) ComputerLover 2012
# Licence:     <your licence>
#-------------------------------------------------------------------------------
#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import os,sys,win32api
from win32com.client import Dispatch

class Excel:
    def __init__(self, filename=None):
        self.xlApp = win32com.client.Dispatch('Excel.Application')
        if filename:
            self.filename=filename
            if os.path.exists(self.filename):
                self.xlBook=self.xlApp.Workbooks.Open(filename)
            else:
                self.xlBook= self.xlApp.Workbooks.Add()
        else:
            self.xlBook= self.xlApp.Workbooks.Add()
            self.filename=Untitle

    def save(self, newfilename=None):
        if newfilename:
            self.filename = newfilename
        self.xlBook.SaveAs(self.filename)

    def close(self):
        self.xlBook.Close(SaveChanges=0)
        del self.xlApp

    def copySheet(self, before):
        "copy sheet"
        shts = self.xlBook.Worksheets
        shts(1).Copy(None,shts(1))

    def newSheet(self,newSheetName):
        sheet=self.xlBook.Worksheets.Add()
        sheet.Name=newSheetName
        sheet.Activate()

    def activateSheet(self,sheetName):
        self.xlBook.Worksheets(sheetName).Activate()

    def activeSheet(self):
        return self.xlApp.ActiveSheet;

    def getCell(self, row, col,sheet=None):
        "Get value of one cell"
        if sheet:
            sht = self.xlBook.Worksheets(sheet)
        else:
            sht=self.xlApp.ActiveSheet
        return sht.Cells(row, col).Value

    def setCell(self, row, col, value,sheet='Sheet1'):
        "set value of one cell"
        if sheet:
             sht = self.xlBook.Worksheets(sheet)
        else:
             sht=self.xlApp.ActiveSheet

        sht.Cells(row, col).Value = value

    def getRange(self, sheet, row1, col1, row2, col2):
          "return a 2d array (i.e. tuple of tuples)"
          sht = self.xlBook.Worksheets(sheet)
          return sht.Range(sht.Cells(row1, col1), sht.Cells(row2, col2)).Value

    def getContiguousRange(self, sheet, row, col):
        """Tracks down and across from top left cell until it
        encounters blank cells; returns the non-blank range.
        Looks at first row and column; blanks at bottom or right
        are OK and return None within the array"""

        sht = self.xlBook.Worksheets(sheet)

        # find the bottom row
        bottom = row
        while sht.Cells(bottom + 1, col).Value not in [None, '']:
            bottom = bottom + 1

        # right column
        right = col
        while sht.Cells(row, right + 1).Value not in [None, '']:
            right = right + 1

        return sht.Range(sht.Cells(row, col), sht.Cells(bottom, right)).Value

def main():
    fileName = r'E:\test\test.xls'
    print(fileName)
    sheet = r'sheet1'
    xls = Excel(fileName)
    print(xls.getCell(5,2) )
    content = xls.getContiguousRange(sheet,1,1)
    print(content)
    xls.close()

if __name__ == '__main__':
    main()

