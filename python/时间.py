#-------------------------------------------------------------------------------
# Name:        时间
# Purpose:
#
# Author:      wkx
#
# Created:     24-05-2012
# Copyright:   (c) wkx 2012
# Licence:     <your licence>
#-------------------------------------------------------------------------------
#!/usr/bin/env python

def main():
    pass

from datetime import timedelta, datetime

if __name__ == '__main__':
    main()

def isYearEnd( date ):
    return False

def isQuarterday( date ):
    if date.month == 3 and date.day == 31 :
        return True
    if date.month == 6 and date.day == 30 :
        return True
    if date.month == 9 and date.day == 30 :
        return True
    if date.month == 12 and date.day == 31:
        return True
    return False

def isMonthEnd( date ):
    d=date+timedelta(dates=1)
    if d.day == 1 :
        return True
    return False

