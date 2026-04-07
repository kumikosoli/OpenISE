# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


def print_Hello(name):
     # Use a breakpoint in the code line below to debug your script.
    print(f'Hello, {name}')  # Press Ctrl+F8 to toggle the breakpoint.



if __name__ == '__main__':
    print_Hello('Python')


for i in range(1,6):
    print (i)

x =input("请输入分隔符")
print(1,2,3,4,5, sep=x)
#
a = 1
b = 1.1
c = True
d = 'ABC'
print("变量1=",a, "数据类型=",type(a), "地址=",id(a))
print("变量1=",b, "数据类型=",type(b), "地址=",id(b))
print("变量1=",c, "数据类型=",type(c), "地址=",id(c))
print("变量1=",d, "数据类型=",type(d), "地址=",id(d))

import math
aa = float(input())
aaa = math.floor(aa)
aaaa = aa - aaa
print (aaa, aaaa)


cc = float(input("请输入数字1"))
dd = float(input("请输入数字2"))
if a>b:
    print((cc),">",(dd))
elif b>a:
    print((cc),"<",(dd))
else:
    print((cc),"=",(dd))


if type(a) == type(b):
    print("数据类型相同")
else:
    print("数据类型不同")