#第一题
def get_int_list():
    n = int(input("请输入数组长度: "))
    numbers = []
    for i in range(n):
        numbers.append(int(input()))
    return numbers

def print_odd(list):
    tup = ([],)
    for i in range(len(list)):
        if list[i] % 2 == 1:
            tup[0].append(list[i])
    print(tup[0])

def print_even(list):
    sum = 0
    n = 0
    for i in range(len(list)):
        if list[i] % 2 == 0:
            sum += list[i]
            n += 1
    print(sum/n)

list = get_int_list()
tuple = ()
print_odd(list)
print_even(list)

#第二题
#统计字符串中每个字符出现的次数，并返回字典
def count_characters(s):
    char_count = {}
    for char in s:
        if char in char_count:
            char_count[char] += 1
        else:
            char_count[char] = 1
    return char_count


# 创建一个包含字符串中唯一字符的集合
def get_unique_characters(dictionary):
    only_set = set()
    for char in dictionary:
        if dictionary[char] == 1:
            only_set.update(char)
    return only_set


#将字符串中所有字母变为大写
def convert_to_uppercase(s):
    return s.upper()

#提取子串，输出前5个字符、后5个字符、偶数索引位置的字符
def extract_substrings(s):
    first_5_chars = s[:5]
    last_5_chars = s[-5:]
    even_index_chars = s[::2]
    print("前五个字符：",first_5_chars,"后五个字符：", last_5_chars,"偶数索引字符：", even_index_chars)

#将字符串中的空格替换为','，然后分成两段输出
def replace_and_split(s):
    replaced_str = s.replace(" ", ",")
    split_list = replaced_str.split(",", 1)  # 以","作为间隔分割为两部分
    print(split_list)

# 测试
input_str = "Hello world!"

char_count = count_characters(input_str)
print("字符出现次数：", char_count)

unique_chars = get_unique_characters(char_count)
print("唯一字符集合：", unique_chars)

uppercase_str = convert_to_uppercase(input_str)
print("大写字符串：", uppercase_str)

extract_substrings(input_str)

replace_and_split(input_str)

#第三题
#成绩字典
grade = {
    'SanZhang': [70, 80, 61],
    'SiLi': [86, 77, 81],
    'WuWang': [88, 90, 77],
    'MingLi': [60, 77, 81],
    'MiWang': [71, 70, 60],
    'HaiLi': [88, 78, 89],
    'HeWang': [70, 90, 80],
    'LiWang': [67, 71, 70]
}

#逐个加得总分，储存于列表第四个
def get_total_grade(grade):
    for key, value in grade.items():
        value.append(sum(value))
#由冒泡排序得到第i个成绩的排序，由i可以决定排名哪科
def bubble_sort(grade, k):
    n = len(grade)
    grade = list([key, value[k]]for key, value in grade.items()) #将字典转化为列表，变得有序
    for j in range(n): #使用冒泡遍历
        for i in range(n - j - 1):
            if grade[i][1] > grade[i + 1][1]:
                grade[i], grade[i + 1] = grade[i + 1], grade[i]
    return grade

def bubble_sort_reverse(grade, k):
    n = len(grade)
    grade = list([key, value[k]]for key, value in grade.items()) #将字典转化为列表，变得有序
    for j in range(n): #使用冒泡遍历
        for i in range(n - j - 1):
            if grade[i][1] < grade[i + 1][1]:
                grade[i], grade[i + 1] = grade[i + 1], grade[i]
    return grade
get_total_grade(grade)
#打印由低到高的总分
print("总分由低到高是：",bubble_sort(grade, 3))
#打印由高到低的总分，直接反转列表。
print("总分由高到低是：",bubble_sort_reverse(grade, 3))
#打印高数成绩，由低到高，由反转的冒泡算法得出。高数是第一个成绩，k=0
print("高数成绩由高到低是：",bubble_sort_reverse(grade, 0))
#同理打印出英语和大物成绩
print("英语成绩由高到低是：",bubble_sort_reverse(grade, 1))
print("大物成绩由高到低是：",bubble_sort_reverse(grade, 2))

#第四题
#用于打印该程序的功能
def print_usage():
    print(
        "功能如下：\n"
        f"{'添加货物及价格：'.ljust(10)} add <货物名称> <货物价格>\n"
        f"{'查看货品：'.ljust(10)} check\n"
        f"{'删除货物：'.ljust(10)} delete <货物名称>\n"
        f"{'修改价格：'.ljust(10)} change <货品名称> <货品价格>\n"
        f"{'查看总价格：'.ljust(10)} sum\n"
        f"{'退出：'.ljust(10)} quit\n"
        f"{'帮助：'.ljust(10)} help"
    )

#检查输入长度是否合法
def check_length(arg, i):
    return len(arg) == i

#依次打印字典
def print_list(dictionary):
    for key, value in dictionary.items():
        print("货物：",key, " 价格是：", value)

#计算有几件货物，总价值多少
def sum_list(dictionary):
    i = 0
    sum = 0
    for key, value in dictionary.items():
        sum += int(value)
        i += 1
    return i, sum

def grocery_list(to_buy_list):
    prompt = "欢迎使用货物管理程序>>> "
    cmd = input(prompt).split(" ")
    match cmd[0]: #类似于C语言的switch
        case "add":
            if not check_length(cmd, 3):
                print("参数数量错误")
            if cmd[1] in to_buy_list.keys():
                print("已有相同货物")
                return
            to_buy_list.update({cmd[1]: cmd[2]})
        case "check":
            if not check_length(cmd, 1):
                print("参数数量错误")
            print_list(to_buy_list)
        case "delete":
            if not check_length(cmd, 2):
                print("参数数量错误")
            if not cmd[1] in to_buy_list.keys():
                print("清单中没有这个货物")
            to_buy_list.pop(cmd[1])
        case "change":
            if not check_length(cmd, 3):
                print("参数数量错误")
            if not cmd[1] in to_buy_list.keys():
                print("清单中没有这个货物")
            to_buy_list.update({cmd[1]: cmd[2]})
        case "sum":
            if not check_length(cmd, 1):
                print("参数数量错误")
            i, sum = sum_list(to_buy_list)
            print(i,"件货物共价值",sum,"元")
        case "quit":
            exit(0)
        case "help":
            print_usage()
        case _:
            print("未找到输入的指令")
            print_usage()


#实例
to_buy_list = {}
while True:
    grocery_list(to_buy_list)