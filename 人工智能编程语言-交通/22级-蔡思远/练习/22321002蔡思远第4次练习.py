class Geese:
    def __init__(self):
        pass

    def fly(self,condition):
        print('飞行状态为:', condition)

if __name__ == '__main__':
    Geese1 = Geese()
    Geese1.fly('平稳')



class fruit:
    def __init__(self,color):
        self.color = color
apple = fruit('red')
orange = fruit('orange')
watermelon = fruit('green')

print(apple.color)
print(orange.color)
print(watermelon.color)



class quadrangle:
    def __init__(self,side1,side2,side3,side4):
        self.side1 = side1
        self.side2 = side2
        self.side3 = side3
        self.side4 = side4
    def perimetrer(self):
        return self.side1+self.side2+self.side3+self.side4
class parallelogram(quadrangle):
    def __init__(self,side1,side2,side3,side4):
        super(parallelogram,self).__init__(side1,side2,side3,side4)
class rectangle(parallelogram):
    def __init__(self,side1,side2):
        self.side1 = side1
        self.side2 = side2

p1 = parallelogram(5,4,7,8)
r1 = rectangle(5,4)
print(p1.perimetrer())




class Animal:
    def __init__(self,color,name,age):
        self.color = color
        self.name = name
        self.age = age
        print('以下为动物的基本信息：')
    def eat(self):
        print("吧唧吧唧")
    def __str__(self):
        print(self.color,self.name,self.age)

if __name__ == '__main__':
    animal = Animal('灰色','无名',3)
    animal.eat()
    animal.__str__()



class car
