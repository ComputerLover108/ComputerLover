#!/usr/bin/env python
#-*-coding = UTF-8-*-
#POP_email.py
#auth@:xfk
#date@:2012-04-30
################################################################
# WARNING: This program deletes mail from the specified mailbox.
#           Do Not point it to any mailbox you are care about!
################################################################

import getpass
import sys
import poplib
import email

if len(sys.argv) < 4:
    print "[*]usage:%s server fromaddr toaddr " % sys.argv[0]
    sys.exit(1)

(host,user,dest) = sys.argv[1:]
passwd = getpass.getpass()
destfd = open(dest,"at")
    
p = poplib.POP3(host)           #ֺ֧ҪAPOP֤APOPʹüܱ뱻ȡ
try:
    print "Attempting APOP authentication..."
    print "Logging on..."
    p.apop(user,passwd)
    print "Success.\n"
except poplib.error_proto:
    print "Attempting standard authentication..."
    try:
        print "Logging on..."
        p.user(user)
        p.pass_(passwd)
        print "Success.\n"
    except poplib.error_proto,e:
        print "Login fialed:",e
        sys.exit(1)
print "*****Scanning INBOX...*****"         #ɨʼ
mail_box_list = p.list()[1]
print "There is %d messages.\n" % len(mail_box_list)

delelist = []           #Ҫɾּ

for item in mail_box_list:
    number,octets = item.split(' ')         #ÿһԪ֮пո
    print "Downloading message %s (%s bytes)..." % (number,octets)
    lines = p.retr(number)[1]           #ʼ
    msg = email.message_from_string("\n".join(lines))           #һʼ
    destfd.write(msg.as_string(unixfrom = 1))           #ʼдĿļ
    destfd.write("\n")
    delelist.append(number)
    print "Done !\n"
destfd.close()

counter = 0
for number in delelist:
    counter = counter + 1
    print "Deleting message %d of %d \r" % (counter,len(delelist))
    p.dele(number)          #ɾʼ

if counter > 0:
    print "Successfully deleted %d message from server.\n" % counter
else:
    print "No messages present to download.\n"

print "Closing connection..."

p.quit()            #Ͽ
print "Done !\n"