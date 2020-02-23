import requests
from multiprocessing import Pool
from bs4 import BeautifulSoup
import re
import time
import os
import random
import logging
import argparse


# 通过下面的方式进行简单配置输出方式与日志级别
# create logger
logger_name = "story_crawl"
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

# create file handler
filename = "story_crawl.log"
fh = logging.FileHandler(filename)
fh.setLevel(logging.INFO)

# create formatter
fmt = "%(message)s %(asctime)-15s %(levelname)s %(filename)s %(lineno)d %(process)d "
formatter = logging.Formatter(fmt)

# add handler and formatter to logger
fh.setFormatter(formatter)
logger.addHandler(fh)

# 自定义headers请求
ua = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_0) ' \
     'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77' \
     ' Safari/537.36'
headers = {'User-Agent': ua}
timeout = random.randint(1,60)

def page_crawling(url,params,i):      
    if i> 1 :
        params['page'] = i
        logger.info('url={} page={}'.format(url,params['page'])) 
    response = requests.get(url=url,params=params,timeout=timeout)
    html = response.content.decode(response.apparent_encoding)
    pattern = '(read.php\?tid=\d+&fpage=\d+)'
    # logger.info(pattern)
    # logger.info(html)
    child_urls = re.findall(pattern,html)
    if child_urls==[]:
        pattern = '(html_data\/\d+\/\d+\/\d+\.html)'
        child_urls = re.findall(pattern,html)
    for child_url in child_urls:
        curl=url.replace('thread.php','')+child_url
        logger.info(curl)
        crawling(curl)
    timedelay = random.randint(3,60)
    logger.info('time delay {}'.format(timedelay))
    time.sleep(30)

def crawling(url):
    pattern='<span id="subject_tpc">(?P<title>.*)</span>'
    response = requests.get(url, headers=headers,timeout=timeout)   
    # result = chardet.detect(response.content)
    # logger.info(result)
    # logger.info(response.status_code, response.reason)
    html = response.content.decode(response.apparent_encoding)
    # title = re.search(pattern,html).group('title')
    soup = BeautifulSoup(html,features="lxml")
    # logger.info(soup.original_encoding)
    # title = soup.title.text
    title=soup.find(id='subject_tpc').text
    # logger.info(title)
    content = soup.find(id='read_tpc').text
    # logger.info(content)
    

    location='..\story'
    if not os.path.exists(location):
        os.mkdir(location)
    filename = title+'.md'
    filename = re.sub('[\\\\/:*?\"<>|]','',filename)
    filename = os.path.join(location,filename)      
    if os.path.exists(filename):
        return
    with open(filename,'w+',encoding='utf8') as f:
        f.write(content)
        f.flush()
        logger.info(filename) 
    timedelay = random.randint(1,9)
    time.sleep(timedelay)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog = 'story_crawl',description = '小说爬取')
    parser.add_argument('url', help='input a url')
    args = parser.parse_args()
    if args.url:
        url = args.url
        logger.info(url) 
        params = {'fid':17,'type':2}
        response = requests.get(url=url,params=params,timeout=timeout)
        child_urls = re.findall(r'html_data\/\d+\/\d+\/\d+\.html',response.text)
        pages = re.search(r'Pages: +\d+\/(?P<page_count>\d+)',response.text)             
        page_count=int(pages.group('page_count'))
        pool = Pool()
        multi_res = [pool.apply_async(page_crawling,args=(url,params,i))for i in range(1,page_count+1)]
        random.shuffle(multi_res)
        for res in multi_res:
            res.get()   


