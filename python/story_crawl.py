import requests
# from multiprocessing import Pool,cpu_count
import multiprocessing
from bs4 import BeautifulSoup
import re
import time
import os
import random
import logging
import argparse
from requests.exceptions import ReadTimeout,HTTPError,RequestException

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
user_agent_list = [
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77 Safari/537.36',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.132 Safari/537.36',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:73.0) Gecko/20100101 Firefox/73.0',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_3) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/13.0.5 Safari/605.1.15',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36 Edge/16.16299',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:63.0) Gecko/20100101 Firefox/63.0',
    'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.4150.1 Iron Safari/537.36',
    'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.108 Mobile Safari/537.36',
    'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.81 Safari/537.36 Maxthon/5.3.8.2000',
    'Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:68.9) Gecko/20100101 Goanna/4.4 Firefox/68.9 PaleMoon/28.8.4'
]
headers = {'User-Agent': random.choice(user_agent_list)}
timeout = random.randint(1,60)

def page_crawling(url,params,i):
    headers = {'User-Agent': random.choice(user_agent_list)}
    timeout = random.randint(1,60)      
    if i> 1 :
        params['page'] = i
        # logger.info('url={} page={}'.format(url,params['page']))
    try: 
        response = requests.get(url=url,params=params,headers=headers,timeout=timeout)
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
            # logger.info(curl)
            crawling(curl)
        timedelay = random.randint(3,60)
        logger.info('time delay {}'.format(timedelay))
        time.sleep(30)
    except ReadTimeout:
        logger.info('%r timeout',url)
    except HTTPError:
        logger.info('%r httperror',url)
    except RequestException:
        logger.info('%r reqerror',url)    

def crawling(url):
    pattern='<span id="subject_tpc">(?P<title>.*)</span>'
    try:
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
        

        location='../story'
        if not os.path.exists(location):
            os.mkdir(location)
        filename = title+'.md'
        filename = re.sub('[\\\\/:*?\"<>|]','',filename)
        filename = os.path.join(location,filename)
        filename = os.path.abspath(filename)      
        if os.path.exists(filename):
            return
        with open(filename,'w+',encoding='utf8') as f:
            f.write(content)
            f.flush()
            # logger.info(filename) 
        timedelay = random.randint(1,9)
        time.sleep(timedelay)
    except ReadTimeout:
        logger.info('%r timeout',url)
    except HTTPError:
        logger.info('%r httperror',url)
    except RequestException:
        logger.info('%r reqerror',url)    

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog = 'story_crawl',description = '小说爬取')
    parser.add_argument('url', help='input a url')
    args = parser.parse_args()
    if args.url:
        url = args.url
        # logger.info(url) 
        params = {'fid':17,'type':2}
        response = requests.get(url=url,params=params,timeout=timeout)
        child_urls = re.findall(r'html_data\/\d+\/\d+\/\d+\.html',response.text)
        pages = re.search(r'Pages: +\d+\/(?P<page_count>\d+)',response.text)             
        page_count=int(pages.group('page_count'))
        NUMBER_OF_PROCESSES = multiprocessing.cpu_count()
        pool = multiprocessing.Pool(NUMBER_OF_PROCESSES)
        page_range = [ x for x in range(1,page_count+1)]
        random.shuffle(page_range)
        # logger.info('page range: {}'.format(page_range))
        multi_res = [pool.apply(page_crawling,args=(url,params,i))for i in page_range]
        pool.close()
        pool.join() 
  


