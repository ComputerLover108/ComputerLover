import requests
from bs4 import BeautifulSoup
import re
import time
import os
import logging

# 通过下面的方式进行简单配置输出方式与日志级别
logging.basicConfig(filename='story_crawl.log', level=logging.DEBUG)

# 自定义headers请求
ua = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_0) ' \
     'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77' \
     ' Safari/537.36'
headers = {'User-Agent': ua}
timeout = 6

def crawling(url):
    pattern='<span id="subject_tpc">(?P<title>.*)</span>'
    response = requests.get(url, headers=headers,timeout=timeout)
    
    # result = chardet.detect(response.content)
    # logging.debug(result)
    # logging.debug(response.status_code, response.reason)
    html = response.content.decode(response.apparent_encoding)
    # title = re.search(pattern,html).group('title')
    soup = BeautifulSoup(html,features="lxml")
    # logging.debug(soup.original_encoding)
    # title = soup.title.text
    title=soup.find(id='subject_tpc').text
    # logging.debug(title)
    content = soup.find(id='read_tpc').text
    # logging.debug(content)
    location='../story'
    if not os.path.exists(location):
        os.mkdir(location)
    filename = title+'.md'
    filename = os.path.join(location,filename)   
    if os.path.exists(filename):
        return
    # logging.debug(filename)
    print(filename)
    with open(filename,'w+',encoding='utf8') as f:
        f.write(content)
        f.flush()

if __name__ == "__main__":
    
    params = {'fid':17,'type':2}
    response = requests.get(url=url,params=params,timeout=timeout)
    # logging.debug(response.status_code,response.reason)
    # html_data/17/2002/4617751.html
    child_urls = re.findall(r'html_data\/\d+\/\d+\/\d+\.html',response.text)
    pages = re.search(r'Pages: +\d+\/(?P<page_count>\d+)',response.text)             
    # logging.debug(pages)
    # logging.debug(pages.group('page_count'))
    page_count=int(pages.group('page_count'))
    for i in range(1,page_count+1)[::-1]:
        if i> 1 :
            params['page'] = i 
            # logging.debug(params)
        response = requests.get(url=url,params=params,timeout=timeout)
        html = response.content.decode(response.apparent_encoding)
        # logging.debug(url,params,i)
        # logging.debug(response.status_code,response.reason)
        pattern = '(read.php\?tid=\d+&fpage=\d+)'
        # logging.debug(pattern)
        # logging.debug(html)
        child_urls = re.findall(pattern,html)
        if child_urls==[]:
            pattern = '(html_data\/\d+\/\d+\/\d+\.html)'
            child_urls = re.findall(pattern,html)
        # logging.debug(child_urls)
        for child_url in child_urls:
            curl=url.replace('thread.php','')+child_url
            logging.debug(curl)
            crawling(curl)
        time.sleep(9)


