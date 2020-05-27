#!/usr/bin/env python
#-*-coding = UTF-8-*-
#SMTP_email.py
#auth@:xfk
#date@:2012-04-30

import sys
import smtplib
import socket
from getpass import getpass

if len(sys.argv) < 4:
    print "[*]usage:%s server fromaddr toaddr " % sys.argv[0]
    sys.exit(1)

server = sys.argv[1]
fromaddr = sys.argv[2]
toaddr = sys.argv[3]

message = """
TO: %s
From: %s
Subject: Test Message from SMTP_mail.py

Hello ,This a simple SMTP_mail example.
""" % (','.join(toaddr),fromaddr)

def get_size():
    """÷ʼĴС"""
    try:
        s = smtplib.SMTP(server)     #ӵ
        code = s.ehlo()[0]      #ط
        usesesmtp = 1
        if not (200 <= code <=299):         #200299֮䶼ȷķֵ
            usesesntp = 0
            code = s.helo()[0]
            if not (200 <= code <=299):
                raise SMTPHeloError(code,resp)
        if usesesmtp and s.has_extn('size'):         #÷ʼĴС
            print "Maxinum message size is ",s.esmtp_features['size']
            if len(message) > int(s.esmtp_features['size']):
                print "Message too large;aborting."
                sys.exit(2)
        s.sendmail(fromaddr,toaddr,message)
    except(socket.gaierror,socket.error,socket.herror,smtplib.SMTPException),e:
        print "***Your message may not have been sent!"
        print e
        sys.exit(1)
    else:
        print "***Message successful sent to %d recipient(s)" % len(toaddr)

def ssl_tls():
    """ʹSSLȫ׽ײTLSȫʼ䣬ȷڴеİȫ"""
    try:
        s = smtplib.SMTP(server)     #ӵ
        code = s.ehlo()[0]      #ط
        usesesmtp = 1
        if not (200 <= code <=299):         #200299֮䶼ȷķֵ
            usesesntp = 0
            code = s.helo()[0]
            if not (200 <= code <=299):
                raise SMTPHeloError(code,resp)
        if usesesmtp and s.has_extn('starttls'):         #鿴Ƿ֧TLS
            print "Negotiating TLS......"
            s.starttls()
            code = s.ehlo()[0]
            if not (200 <= code <=299):             #֧TLSķǷӻػɹ
                print "Couldn't EHLO after STARTTLS."
                sys.exit(5)
            print "Using TLS connection."
        else:
            print "Server does not suport TLS; using normal connection."
        s.sendmail(fromaddr,toaddr,message)         #TLSɹʹüܴ䣻TLSʹͨĴ
    except(socket.gaierror,socket.error,socket.herror,smtplib.SMTPException),e:
        print "***Your message may not have been sent!"
        print e
        sys.exit(1)
    else:
        print "***Message successful sent to %d recipient(s)" % len(toaddr)

def auth_login():
    """ʼʱҪ֤û뷽ɷʼ"""
    sys.stdout.write("Enter username: ")
    username = sys.stdin.readline().strip()
    password = getpass("Enter password: ")
    try:
        s = smtplib.SMTP(server)     #ӵ
        code = s.ehlo()[0]      #ط
        usesesmtp = 1
        if not (200 <= code <=299):         #200299֮䶼ȷķֵ
            usesesntp = 0
            code = s.helo()[0]
            if not (200 <= code <=299):
                raise SMTPHeloError(code,resp)
        if usesesmtp and s.has_extn('auth'):         #鿴Ƿ֧֤
            print "Using Authentication connect."
            try:
                s.login(username,password)
            except smtplib.SMTPException,e:
                print "Authentication failed:",e
                sys.exit(1)
        else:
            print "Server does not suport Authentication; using normal connect."
        s.sendmail(fromaddr,toaddr,message)         #֧֤û֤֧ʹͨʽд
    except(socket.gaierror,socket.error,socket.herror,smtplib.SMTPException),e:
        print "***Your message may not have been sent!"
        print e
        sys.exit(1)
    else:
        print "***Message successful sent to %d recipient(s)" % len(toaddr)

if __name__ == "__main__":
    get_size()
    ssl_tls()
    auth_login()