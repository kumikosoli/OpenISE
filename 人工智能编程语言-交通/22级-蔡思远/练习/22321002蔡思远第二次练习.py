def counts(string):
    nl = 0
    nd = 0
    ns = 0
    for char in string:
        if char.isalpha():
            nl += 1
        elif char.isdigit():
            nd += 1
        else:
            ns += 1
    return nl,nd,ns
a = input("请输入一个字符串")
l,d,s = counts(a)
print('该字符串中包含%d个字母 %d个数字 %d个其他符号'%(l,d,s))

a = input("请输入第一个字符串")
b = input("请输入第二个字符串")
print(a.index(b))


month = ['January','February','March','April','May','June','July','August','September','October','November','December']
a = int(input("请输入月份数字"))
print(month[a-1])


province = {'11':'北京市','12':'天津市','13':'河北省','14':'山西省','15':'内蒙古自治区','22':'吉林省', '23':'黑龙江省','31':'上海市',  '32':'江苏省','33':'浙江省','35':'福建省','36':'江西省', '37':'山东省','41':'河南省','42':'湖北省','44':'广东省','45':'广西壮族自治区','46':'海南省', '50':'重庆市','51':'四川省','53':'云南省','54':'西藏自治区','61':'陕西省','62':'甘肃省', '63':'青海省','65':'新疆维吾尔自治区','71':'台湾省','81':'香港','82':'澳门'}
a = input("请输入你的身份证号码")
b = a[:2]
print(province[b])

dict = {'python':95,'java':99,'c':100}
dict['Go'] = 90
print(dict)
dict['c'] = 96
print(dict)


s1 = {1,2,1,3,4,5,6,7}
s2 = {1,2,3,8,9,7,10}
print("两个集合的差集为",s2 - s1)
print("两个集合的并集为",s1|s2)
print("两个集合的交集为",s1&s2)

import copy
a = [1, 2, 3, [4, 5, 6]]
d = a
b = copy.deepcopy(a)
c = copy.copy(a)
b[3][0] = 10
print(a)
b[3] = 10
print(a)
c[3][0] = 10
print(a)
d[0] = 10
print(a)


