print("要求1：")
str = input('''请输入班级内的学生及相关成绩分数，格式如下：
”学生姓名,高数成绩,英语成绩,大物成绩;SanZhang,70,80,61;SiLi,86,77,81;WuWang,88,90,77;MingLi,60,77,81;MiWang,71,70,60;HaiLi,88,78,89;HeWang,70,90,80;LiWang,67,71,70”
''')
print("要求2：")
str1 = str[0:19]
str2 = str[20:37]
str3 = str[38:51]
str4 = str[52:67]
str5 = str[68:83]
str6 = str[84:99]
str7 = str[100:114]
str8 = str[115:130]
str9 = str[131:146]
inf = [str1,str2,str3,str4,str5,str6,str7,str8,str9]
print(inf)

print("要求3：")
inf[0] = [str1]
inf[1] = [str2]
inf[2] = [str3]
inf[3] = [str4]
inf[4] = [str5]
inf[5] = [str6]
inf[6] = [str7]
inf[7] = [str8]
inf[8] = [str9]
print(inf)

print("要求4：")
strn = str[0:4]
strm = str[5:9]
stre = str[10:14]
strp = str[15:19]
SZn = str[20:28]
SLn = str[38:42]
WWn = str[52:58]
MLn = str[68:74]
MWn = str[84:90]
HLn = str[100:105]
HWn = str[115:121]
LWn = str[131:137]
SZm = int(str2[9:11])
SZe = int(str2[12:14])
SZp = int(str2[15:17])
SLm = int(str3[5:7])
SLe = int(str3[8:10])
SLp = int(str3[11:13])
WWm = int(str4[7:9])
WWe = int(str4[10:12])
WWp = int(str4[13:15])
MLm = int(str5[7:9])
MLe = int(str5[10:12])
MLp = int(str5[13:15])
MWm = int(str6[7:9])
MWe = int(str6[10:12])
MWp = int(str6[13:15])
HLm = int(str7[6:8])
HLe = int(str7[9:11])
HLp = int(str7[12:14])
HWm = int(str8[7:9])
HWe = int(str8[10:12])
HWp = int(str8[13:15])
LWm = int(str9[7:9])
LWe = int(str9[10:12])
LWp = int(str9[13:15])
d1 = {strn:SZn,strm:SZm,stre:SZe,strp:SZp}
d2 = {strn:SLn,strm:SLm,stre:SLe,strp:SLp}
d3 = {strn:WWn,strm:WWm,stre:WWe,strp:WWp}
d4 = {strn:MLn,strm:MLm,stre:MLe,strp:MLp}
d5 = {strn:MWn,strm:MWm,stre:MWe,strp:MWp}
d6 = {strn:HLn,strm:HLm,stre:HLe,strp:HLp}
d7 = {strn:HWn,strm:HWm,stre:HWe,strp:HWp}
d8 = {strn:LWn,strm:LWm,stre:LWe,strp:LWp}
inf[0] = d1
inf[1] = d2
inf[2] = d3
inf[3] = d4
inf[4] = d5
inf[5] = d6
inf[6] = d7
inf[7] = d8
del inf[8]
print(inf)

print("要求5：")
t1 = SZm + SZe + SZp
t2 = SLm + SLe + SLp
t3 = WWm + WWe + WWp
t4 = MLm + MLe + MLp
t5 = MWm + MWe + MWp
t6 = HLm + HLe + HLp
t7 = HWm + HWe + HWp
t8 = LWm + LWe + LWp
print("总分从高到低的学生名单如下:")
arr = [t1,t2,t3,t4,t5,t6,t7,t8]  #以下为经典的冒泡排序。设置成绩数组arr与名字数组arrn一一对应
arrn = [SZn,SLn,WWn,MLn,MWn,HLn,HWn,LWn]
for i in range(7):
    for j in range(7 - i):
        if arr[j] < arr[j+1]:
            t = arr[j]
            arr[j] = arr[j+1]
            arr[j+1] = t
            s = arrn[j]  #成绩数组进行调换顺序时，名字数组与其一齐调换顺序
            arrn[j] = arrn[j + 1]
            arrn[j + 1] = s
for q in range(7):
    print(arrn[q],end=" ")  #输出名字数组
print(arrn[7])
print("总分从低到高的学生名单如下:")
arr = [t1,t2,t3,t4,t5,t6,t7,t8]
arrn = [SZn,SLn,WWn,MLn,MWn,HLn,HWn,LWn]
for i in range(7):
    for j in range(7 - i):
        if arr[j] > arr[j+1]:
            t = arr[j]
            arr[j] = arr[j+1]
            arr[j+1] = t
            s = arrn[j]
            arrn[j] = arrn[j + 1]
            arrn[j + 1] = s
for q in range(7):
    print(arrn[q],end=" ")
print(arrn[7])
print("高数课成绩从高到低的学生名单如下:")
m1 = SZm
m2 = SLm
m3 = WWm
m4 = MLm
m5 = MWm
m6 = HLm
m7 = HWm
m8 = LWm
arr = [m1,m2,m3,m4,m5,m6,m7,m8]
arrn = [SZn,SLn,WWn,MLn,MWn,HLn,HWn,LWn]
for i in range(7):
    for j in range(7 - i):
        if arr[j] < arr[j+1]:
            t = arr[j]
            arr[j] = arr[j+1]
            arr[j+1] = t
            s = arrn[j]
            arrn[j] = arrn[j + 1]
            arrn[j + 1] = s
for q in range(8):
    print(arrn[q],end=" ")