import os
import random
import sys


class Student:
    def __init__(self, student_id, name, gender, class_id, student_number, college):
        self.student_id = student_id
        self.name = name
        self.gender = gender
        self.class_id = class_id
        self.student_number = student_number
        self.college = college

def read_data():
    students = []
    with open('人工智能编程语言学生名单.txt', encoding='UTF-8') as f:
        lines = f.readlines()
        for i, line in enumerate(lines):
            if i == 0:
                continue
            student_info = line.strip().split('\t')
            student = Student(student_info[0], student_info[1], student_info[2], student_info[3], student_info[4], student_info[5])
            students.append(student)
    return students

def find_student(students, student_number):
    for student in students:
        if student.student_number == student_number:
            return student
    return None

def random_call(students, num):
    return random.sample(students, num)

def arrange_exam(students):
    random.shuffle(students)
    with open('考场安排表.txt', 'w', encoding='UTF-8') as f:
        for i, student in enumerate(students, 1):
            f.write(f"考场顺序号：{i}, 姓名：{student.name}, 学号：{student.student_number}\n")

def print_examid(students):
    for i, student in enumerate(students, 1):
        file_path = f'准考证号/{i:02d}.txt'
        with open(file_path, 'w', encoding='UTF-8') as f:
            f.write(f'考场顺序号：{i}\n姓名：{student.name}\n学号：{student.student_id}')

def main():
    students = read_data()
    while True:
        print('要求1：')
        student_number = input('请输入学号: ')
        student = find_student(students, student_number)
        if student:
            print(f'姓名：{student.name}\n'
                  f'性别：{student.gender}\n'
                  f'班级：{student.class_id}\n'
                  f'学院：{student.college}\n')
        else:
            print('没有找到相应的学生。')
        print('要求2：')
        num = int(input('请输入需要回答问题的学生数量: '))
        for student in random_call(students, num):
            print('姓名：',student.name,',','学号：',student.student_number)
        print('要求3：')
        arrange_exam(students)
        print('考场安排表已打印输出')
        print('要求4：')
        print_examid(students)
        print('准考证文件已打印')
        sys.exit()

if __name__ == '__main__':
    main()