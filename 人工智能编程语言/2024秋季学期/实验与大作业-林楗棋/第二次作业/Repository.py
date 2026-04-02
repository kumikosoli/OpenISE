from pathlib import Path
import pickle

# implement S一串字母
class account:
    def __init__(self, acc_name, password, real_name = None, ID = None):
        self.ID = ID
        self.acc_name = acc_name
        self.password = password
        self.real_name = real_name
        self.rate = rate_your_pwd(password)

    def __str__(self):
        return f"账号{self.acc_name} 是学生{self.real_name}的帐号，学号为{self.ID}"

# 在该文件目录下创建一个accounts文件夹，储存账号和密码
repository = Path("accounts")

def log_in(acc, pwd):
    real_acc = rtn_acc(acc)
    if real_acc.password == pwd:
        return True, real_acc
    return False, False

# 如果有重号，则返回False，否则返回一个account类
def sign_up(acc, pwd):
    if repository.joinpath(acc).exists():
        return False
    else:
        return account(acc, pwd)

# 用于注册重号判别成功后更新信息，@acc是account类， 其他为字符串类型
def update_acc(acc, name, ID):
    acc.real_name = name
    acc.ID = ID
    with open(repository.joinpath(acc.acc_name), 'wb') as f:
        pickle.dump(acc, f)

# 进行密码评分
def rate_your_pwd(pwd):
    sum = 0
    alpha_flag = False
    capital_flag = False
    # 密码长度
    if len(pwd) <= 4:
        sum += 5
    elif len(pwd) <= 7:
        sum += 10
    else:
        sum += 25
    # 检验是否含有英文单词并判断大小写
    if contains(pwd, str.isalpha):
        alpha_flag = True
        if pwd.upper() == pwd or pwd.lower() == pwd:
            sum += 10
        else:
            sum += 20
            capital_flag = True
    # 检查是否有数字
    digit = contains(pwd, str.isdigit)
    if digit >= 2:
        sum += 20
    elif digit == 1:
        sum += 10
    # 检查是否有符号
    symbol = contains(pwd, lambda x: not x.isdigit() and not x.isalpha())
    if symbol >= 2:
        sum += 25
    elif symbol == 1:
        sum += 10
    # 额外奖励
    if capital_flag and digit and symbol:
        sum += 5
    elif alpha_flag and digit and symbol:
        sum += 3
    elif alpha_flag and digit:
        sum += 2
    return sum

# 根据评分规则划分等级
def rtn_level(rate):
    rate = int(rate)
    if rate >= 90:
        return "非常安全"
    elif rate >= 80:
        return  "安全"
    elif rate >=70:
        return "非常强"
    elif rate >= 60:
        return "强"
    elif rate >= 50:
        return "一般"
    elif rate >= 25:
        return "弱"
    else:
        return "非常弱"

# 检查密码复杂度，运用高阶函数，同时判断是否是数字，字母，符号
def contains(pwd, func):
    count = 0
    for i in pwd:
        if func(i):
            count += 1
    return count


def rtn_acc(acc):
    acc_repo = repository.joinpath(acc)
    if acc_repo.exists() and acc_repo.is_file():
        with open(repository.joinpath(acc), 'rb') as f:
            return pickle.load(f)
    return None

