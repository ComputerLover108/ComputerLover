#!/usr/bin/env python
# -*- coding: utf-8 -*-


import poplib
import email
import logging
import re
import os
import time
import getpass
from email.parser import Parser

logging.basicConfig(
    level=logging.DEBUG,
    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
    filename='fetchMail.log',
    filemode='w+'
)


def getMailServer(emailAddress):
    if re.match('.+@gmail.com', email):
        MailServer = 'pop.googlemail.com'
    return MailServer


def getEmailAttachment(path, msg):
    for part in msg.walk():
        if part.get_content_maintype() == 'multipart':
            continue
        if part.get('Content-Disposition') is None:
            continue
        # if not part.is_multipart():
        filename = part.get_filename()
        # 是否有附件
        if filename:
            data = part.get_payload(decode=True)
            # 保存附件
            saveEmailAttachment(filename, data, path)
    # logging.debug('getEmailAttachment Success!')


def saveEmailAttachment(filename, data, path):
    if not os.path.exists(path):
        os.mkdir(path)
    filepath = os.path.join(path, filename)
    logging.debug('下载附件{}'.format(filepath))
    with open(filepath, 'wb') as f:
        f.write(data)
    f.close()


class SimpleMail(object):

    def __init__(self, email, password):
        mailServer = getMailServer(email)
        self.server = poplib.POP3_SSL(mailServer)
        try:
            self.server.apop(email, password)
            logging.debug('Attempting APOP authentication Success!')
        except poplib.error_proto:
            try:
                self.server.user(email)
                self.server.pass_(password)
                logging.debug('Loging Sucess!')
            except poplib.error_proto as e:
                logging.debug(e)
        logging.debug('SimpleMail construct success!')

    def __del__(self):
        self.server.quit()
        logging.debug('SimpleMail deconstruct success!')

    def getEmail(self):
        resp, mails, octets = self.server.list()
        count = len(mails)
        logging.debug('获得邮件数：{}'.format(count))
        msgs = []
        for i in range(count):
            resp, lines, octets = self.server.retr(i + 1)
            # lines存储了邮件的原始文本的每一行,可以获得整个邮件的原始文本:
            # lines是一个字节列表，
            # b'\n'.join(lines)把lines转换为bytes，decode把bytes转为str
            msg_content = b'\n'.join(lines).decode()
            msg = Parser().parsestr(msg_content)
            msgs.append(msg)
        logging.debug('getEmail Success! It has {} msg'.format(len(msgs)))
        return msgs


if __name__ == "__main__":
    email = input('Email: ')
    password = getpass.getpass('Password: ')
    path = os.path.normcase('e:/public/jiankong')
    for i in range(8):
        x = SimpleMail(email, password)
        msgs = x.getEmail()
        for msg in msgs:
            getEmailAttachment(path, msg)
        time.sleep(9)
