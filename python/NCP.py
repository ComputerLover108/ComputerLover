import requests

# 自定义headers请求
ua = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_0) ' \
     'AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77' \
     ' Safari/537.36'
headers = {'User-Agent': ua}

def craw():
    timeout=2
    url = 'https://lab.isaaclin.cn'
    # url = 'https://github.com/BlankerL/DXY-2019-nCoV-Data'
    url = url + '/nCoV/api/overall'
    print(url)
    params = {'latest':'1'}
    response = requests.get(url=url,params=params,timeout=timeout)
    print('带参数的GET请求',response.json())

if __name__ == "__main__":
    craw()