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
    """��÷������������ʼ��Ĵ�С"""
    try:
        s = smtplib.SMTP(server)     #���ӵ�������
        code = s.ehlo()[0]      #���ط�����������
        usesesmtp = 1
        if not (200 <= code <=299):         #��200��299֮�䶼����ȷ�ķ���ֵ
            usesesntp = 0
            code = s.helo()[0]
            if not (200 <= code <=299):
                raise SMTPHeloError(code,resp)
        if usesesmtp and s.has_extn('size'):         #��÷������������ʼ��Ĵ�С
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
    """ʹ��SSL��ȫ�׽ײ��TLS��ȫ���������ʼ����䣬ȷ�������ڴ����еİ�ȫ"""
    try:
        s = smtplib.SMTP(server)     #���ӵ�������
        code = s.ehlo()[0]      #���ط�����������
        usesesmtp = 1
        if not (200 <= code <=299):         #��200��299֮�䶼����ȷ�ķ���ֵ
            usesesntp = 0
            code = s.helo()[0]
            if not (200 <= code <=299):
                raise SMTPHeloError(code,resp)
        if usesesmtp and s.has_extn('starttls'):         #�鿴�������Ƿ�֧��TLS
            print "Negotiating TLS......"
            s.starttls()
            code = s.ehlo()[0]
            if not (200 <= code <=299):             #��֧��TLS�ķ��������Ƿ����ӻػ��ɹ�
                print "Couldn't EHLO after STARTTLS."
                sys.exit(5)
            print "Using TLS connection."
        else:
            print "Server does not suport TLS; using normal connection."
        s.sendmail(fromaddr,toaddr,message)         #�������TLS�ɹ���ʹ�ü��ܴ��䣻������TLS������ʹ����ͨ�Ĵ���
    except(socket.gaierror,socket.error,socket.herror,smtplib.SMTPException),e:
        print "***Your message may not have been sent!"
        print e
        sys.exit(1)
    else:
        print "***Message successful sent to %d recipient(s)" % len(toaddr)

def auth_login():
    """�������ʼ�ʱ����������Ҫ��֤���������û������뷽�ɷ����ʼ�"""
    sys.stdout.write("Enter username: ")
    username = sys.stdin.readline().strip()
    password = getpass("Enter password: ")
    try:
        s = smtplib.SMTP(server)     #���ӵ�������
        code = s.ehlo()[0]      #���ط�����������
        usesesmtp = 1
        if not (200 <= code <=299):         #��200��299֮�䶼����ȷ�ķ���ֵ
            usesesntp = 0
            code = s.helo()[0]
            if not (200 <= code <=299):
                raise SMTPHeloError(code,resp)
        if usesesmtp and s.has_extn('auth'):         #�鿴�������Ƿ�֧����֤
            print "Using Authentication connect."
            try:
                s.login(username,password)
            except smtplib.SMTPException,e:
                print "Authentication failed:",e
                sys.exit(1)
        else:
            print "Server does not suport Authentication; using normal connect."
        s.sendmail(fromaddr,toaddr,message)         #���֧����֤�������û������������֤����֧����ʹ����ͨ��ʽ���д���
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