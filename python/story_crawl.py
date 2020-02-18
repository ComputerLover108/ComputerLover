import requests
from bs4 import BeautifulSoup
import re
import time
import os
# 自定义headers请求
ua = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_0) ' \
     'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77' \
     ' Safari/537.36'
headers = {'User-Agent': ua}
timeout = 2

def crawling(url):
    pattern='<span id="subject_tpc">(?P<title>.*)</span>'
    response = requests.get(url, headers=headers,timeout=timeout)
    
    # result = chardet.detect(response.content)
    # print(result)
    # print(response.status_code, response.reason)
    html = response.content.decode(response.apparent_encoding)
    # title = re.search(pattern,html).group('title')
    soup = BeautifulSoup(html)
    # print(soup.original_encoding)
    # title = soup.title.text
    title=soup.find(id='subject_tpc').text
    # print(title)
    content = soup.find(id='read_tpc').text
    # print(content)
    location='e:/public/temp/story/'
    filename = location+title+'.md'
    with open(filename,'w',encoding='utf8') as f:
        if not os.path.exists(filename):
            f.write(content)
            f.flush()

if __name__ == "__main__":
    url='https://s1.pbnmdssb.top/pw/thread.php'
    params = {'fid':17,'type':2}
    response = requests.get(url=url,params=params,timeout=timeout)
    # print(response.status_code,response.reason)
    # html_data/17/2002/4617751.html
    child_urls = re.findall(r'html_data\/\d+\/\d+\/\d+\.html',response.text)
    pages = re.search(r'Pages: +\d+\/(?P<page_count>\d+)',response.text)             
    # print(pages)
    # print(pages.group('page_count'))
    page_count=int(pages.group('page_count'))
    for i in range(1,page_count)[::-1]:
        if i> 1 :
            params['page'] = i 
            # print(params)
        response = requests.get(url=url,params=params,timeout=timeout)
        child_urls = re.findall(r'html_data\/\d+\/\d+\/\d+\.html',response.text)
        for child_url in child_urls:
            curl=url.replace('thread.php','')+child_url
            # print(curl)
            crawling(curl)
        print(params,i)
        time.sleep(9)


