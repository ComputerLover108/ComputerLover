import sys
import chilkat

charset = chilkat.CkCharset()

#  Any string argument automatically begins the 30-day trial.
success = charset.UnlockComponent("30-day trial")
if (success != True):
    print charset.lastErrorText()
    sys.exit()

#  Set the "To" and "From" character encodings:
charset.put_FromCharset("shift_JIS")
charset.put_ToCharset("utf-8")

#  To do file-to-file conversion, call ConvertFile.
#  The shift_JIS sample file is downloadable from this URL:
#  http://www.chilkatsoft.com/testData/japanese_shiftJis.txt
success = charset.ConvertFile("japanese_shiftJis.txt","japanese_utf8.txt")
if (success != True):
    print charset.lastErrorText()
else:
    print "Success"