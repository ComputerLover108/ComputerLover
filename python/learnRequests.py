
import requests
from lxml import etree
import re

url = 'http://keet.dididown.co/'


def getURL(url, aim=None):
    xpath = '//a'
    r = requests.get(url)
    r.encoding = 'utf8'
    tree = etree.HTML(r.text)
    results = tree.xpath(xpath)
    urls = []
    if aim:
        urls = [r.url + x.get('href') for x in results if x.text == aim]
    if not aim:
        for x in results:
            print(x.get('href'),x.text)
    return urls

if __name__ == '__main__':
    # url = 'http://keet.dididown.co/'
    # aim = '图文欣賞'
    url = 'http://www.27270.com/'
    url = 'http://www.mm131.com/'
    urls = getURL(url)
    for url in urls:
        print(url)
