#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from email.parser import Parser
from email.header import decode_header
from email.utils import parseaddr
import email
import os
import poplib
import getpass
import re
import logging
logging.basicConfig(level=logging.DEBUG,
                format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                filename='fetchMail.log',
                filemode='w')

def getHost(email):
    if re.match('.+@gmail.com',email):
        host='pop.googlemail.com'
    return host

#获得邮件方法附件
def getEmailAttachment(path,msg):
    for part in msg.walk():
        if part.get_content_maintype() == 'multipart':
            continue
        if part.get('Content-Disposition') is None:
            continue        
        # if not part.is_multipart():   
        filename = part.get_filename()
        #是否有附件
        if filename:
            data = part.get_payload(decode=True)
            #保存附件
            savefile(filename, data, path) 

#保存文件方法（都是保存在指定的根目录下）
def savefile(filename, data, path):
    if not os.path.exists(path):
        os.mkdir(path)
    filepath = os.path.join(path,filename)
    logInfo='下载附件{}'.format(filepath)
    logging.debug(logInfo)
    with open(filepath, 'wb') as f:
        f.write(data)
    f.close()

def guess_charset(msg):
    charset = msg.get_charset()
    if charset is None:
        content_type = msg.get('Content-Type', '').lower()
        pos = content_type.find('charset=')
        if pos >= 0:
            charset = content_type[pos + 8:].strip()
    return charset

def decode_str(s):
    value, charset = decode_header(s)[0]
    if charset:
        value = value.decode(charset)
    return value                 

def print_info(path,msg, indent=0):
    if indent == 0:
        for header in ['From', 'To', 'Subject']:
            value = msg.get(header, '')
            if value:
                if header=='Subject':
                    value = decode_str(value)
                else:
                    hdr, addr = parseaddr(value)
                    name = decode_str(hdr)
                    value = u'%s <%s>' % (name, addr)
            # logging.debug('%s%s: %s' % ('  ' * indent, header, value))
    if (msg.is_multipart()):
        parts = msg.get_payload()
        for n, part in enumerate(parts):
            # logging.debug('%spart %s' % ('  ' * indent, n))
            # logging.debug('%s--------------------' % ('  ' * indent))
            print_info(path,part, indent + 1)
    else:
        content_type = msg.get_content_type()
        filename = msg.get_filename()
        if content_type=='text/plain' or content_type=='text/html':
            content = msg.get_payload(decode=True)
            charset = guess_charset(msg)
            if charset:
                content = content.decode(charset)
            # logging.debug('%sText: %s' % ('  ' * indent, content + '...'))
        else:
            data = msg.get_payload(decode=True)
            savefile(filename,data,path)
            # logging.debug('获得邮件附件' ,filename)

email = input('Email: ')
pop3_server = getHost(email)
if pop3_server:
    password = getpass.getpass('Password: ')
# 连接到POP3服务器:
server = poplib.POP3_SSL(pop3_server)
# # 可以打开或关闭调试信息:
# server.set_debuglevel(1)
# # 可选:打印POP3服务器的欢迎文字:
# logging.debug(server.getwelcome().decode('utf-8'))
# # 身份认证:
try:
    server.apop(email,password)
    logging.debug('Attempting APOP authentication Success!')
except poplib.error_proto:
    try:
        server.user(email)
        server.pass_(password)
        logging.debug('Loging Sucess!')
    except poplib.error_proto as e:
        logging.debug('Login fialed:',e)

# # stat()返回邮件数量和占用空间:
logging.debug('Messages: %s. Size: %s' % server.stat())

# list()返回所有邮件的编号:
resp, mails, octets = server.list()
# 可以查看返回的列表类似[b'1 82923', b'2 2184', ...]
# # 获取最新一封邮件, 注意索引号从1开始:

count = len(mails)
logging.debug('获得邮件数：{}'.format(count))
for i in range(1,count):
    resp, lines, octets = server.retr(i)
    # # # lines存储了邮件的原始文本的每一行,
    # # # 可以获得整个邮件的原始文本:
    # msg_content = b'\n'.join(lines).decode('utf-8')
    msg_content = b'\n'.join(lines).decode() 
    # # # 稍后解析出邮件:
    msg = Parser().parsestr(msg_content)
    path=os.path.normcase('e:/public/jiankong')
    getEmailAttachment(path,msg)
    # 可以根据邮件索引号直接从服务器删除邮件:
    # server.dele(i)
    # 关闭连接:
server.quit()