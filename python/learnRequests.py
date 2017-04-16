
import requests
from lxml import etree

url = 'http://keet.dididown.co/'
r = requests.get(url)
tree = etree.HTML(r.text)

print(r.status_code)    # 获取返回状态
print(r.url)
print(r.encoding)
r.encoding='utf-8'
print(r.text)   #打印解码后的返回数据
print(tree)