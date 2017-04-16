
import requests
 
r = requests.get(url='http://keet.dididown.co/')    # 最基本的GET请求
print(r.status_code)    # 获取返回状态
print(r.url)
print(r.encoding)
r.encoding='utf-8'
print(r.text)   #打印解码后的返回数据