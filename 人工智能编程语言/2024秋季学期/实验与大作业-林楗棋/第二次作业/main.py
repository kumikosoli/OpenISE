import pickle
import Repository

def print_usage():
    return "欢迎使用账号管理系统：\n1-注册账号\n2-登录\n3-修改密码\nq-退出\n>>> "

while True:
    choice = input(print_usage())
    if choice == '1':
        acc_name = input("请输入账号名：")
        pwd = input("请输入密码：")
        acc = Repository.sign_up(acc_name, pwd)
        if acc:
            name = input("请输入姓名：")
            while name == acc_name:
                name = input("姓名不可与账号相同，请重新输入！\n>>> ")
            ID = input("请输入学号：")
            Repository.update_acc(acc, name, ID)
            print(f"注册成功！账号为{acc.acc_name}，密码为{acc.password}，密码评级为{Repository.rtn_level(acc.rate)}")
        else:
            print("注册失败，账号已存在！")
    elif choice == '2':
        acc = input("请输入账号名：")
        if not Repository.repository.joinpath(acc).exists():
            print("账号不存在，请注册！")
            continue
        pwd = input("请输入密码：")
        result, account = Repository.log_in(acc, pwd)
        if result:
            print(f"登录成功！欢迎您，{account.real_name}！")
            print(f"账号信息：{account}")
        else:
            print("登录失败，账号或密码错误！")
    elif choice == '3':
        acc = input("请输入账号名：")
        pwd = input("请输入旧密码：")
        result, account = Repository.log_in(acc, pwd)
        if result:
            new_pwd = input("请输入新密码：")
            account.password = new_pwd
            account.rate = Repository.rate_your_pwd(new_pwd)
            with open(Repository.repository.joinpath(account.acc_name), 'wb') as f:
                pickle.dump(account, f)
            print(f"修改成功！新密码等级为{Repository.rtn_level(account.rate)}")
        else:
            print("修改失败，账号或密码错误！")

    elif choice == '4':
        for file in Repository.repository.iterdir():
            if file.is_file():
                with open(file, 'rb') as f:
                    account = pickle.load(f)
                    print(f"账号：{account.acc_name}, 姓名：{account.real_name}, 学号：{account.ID}, "
                          f"密码评分：{account.rate},密码：{account.password}")
    elif choice == 'q':
        print("感谢使用账号管理系统，再见！")
        exit(0)
    else:
        print("无效的选项，请重新输入！")
        print_usage()