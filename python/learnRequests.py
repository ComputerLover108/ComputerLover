
import requests
from lxml import etree

url = 'http://keet.dididown.co/'
# xpath = '/html/body/div[last()]/table[last()]/tr/td/text()'
xpath = '//a'
r = requests.get(url)
r.encoding = 'utf8'
tree = etree.HTML(r.text)
# print(tree)
results = tree.xpath(xpath)
print(results)
for x in results:
    print(x.attrib, x.text)
# proxies = [line.strip() for line in results]
# print(tree)
# print(results)
# print(proxies)

# print(r.status_code)    # 获取返回状态
# print(r.url)
# print(r.encoding)


# print(r.text)  # 打印解码后的返回数据
# print(tree)
# page = etree.HTML(html.lower().decode('utf-8'))

# hrefs = page.xpath(u"//a")

# for href in hrefs:

#  　　print(href.attrib)
