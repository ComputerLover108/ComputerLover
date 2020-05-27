# 中国身份证格式说明
# 中国的18位身份证由于 17位数字加最后一位 校验码生成

# 校验码 | Wikiwand
# ​
# www.wikiwand.com
# 图标

# 1 ~ 3 分别代表 省(直辖市、自治区)/市(自治州)/区县
# 4 代表出生年月日
# 5 代表派出所代码
# 6 代表性别 奇数为男、偶数为女
# 7 为校验码 与前17位计算所得结果对比校验码是否合法
# 如何计算前17位的结果呢?
# 按照中华人民共和国国家标准GB11643-1999规定中华人民共和国公民身份号码校验码的计算方法即为ISO 7064:1983.MOD 11-2校验码计算法 -- 来自维基百科

# 计算步骤

## 计算17位数字各位数字与对应的加权因子的乘积
S = 1 * 7 + 2 * 9 + 3 * 10 + ... 7 * 2

## 计算余数 根据余数查 校验表 得到校验码
index = S mod 11

ckcodes = ('1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2')
code = ckcodes[index]

## 最后比较 校验码 与 最后一位是否相等即可
code 是否等于 最后一位
代码实现

import re

IDCARD_REGEX = '[1-9][0-9]{14}([0-9]{2}[0-9X])?'

def is_valid_idcard(idcard):
    if isinstance(idcard, int):
        idcard = str(idcard)

    if not re.match(IDCARD_REGEX, idcard):
        return False

    items = [int(item) for item in idcard[:-1]]

    ## 加权因子表
    factors = (7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2)

    ## 计算17位数字各位数字与对应的加权因子的乘积
    copulas = sum([a * b for a, b in zip(factors, items)])

    ## 校验码表
    ckcodes = ('1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2')

    return ckcodes[copulas % 11].upper() == idcard[-1].upper()