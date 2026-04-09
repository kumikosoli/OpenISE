import os

# 1
file = open(r"空.txt", "w+")
context = "你好\n再见\n拜拜\n好吧"
file.write(context)
file.close()
file = open(r"空.txt", "r")
count = 0
for i in file.readlines():
    count += 1
    if count % 2 == 1:
        print(i.strip())
print(file.read())
print(count)
print(os.path.getsize(r"空.txt"))
file.close()


# 2
os.makedirs(r"practice3")
for i in range(1,101):
    fi=open(r"practice3/file"+str(i)+'.txt','w')
    fi.close()

for i in range(1,101):
    os.renames(r"practice3/file"+str(i)+'.txt',r"practice3/fig"+str(i)+'.jpg')


# 3
p = os.listdir(r"/Users/caisiyuan/Desktop")
print(len(os.listdir(r"/Users/caisiyuan/Desktop")))
for r, d, f in os.walk(r"/Users/caisiyuan/Desktop/dit"):
    print(r, '\n')
    print(d, '\n')
    print(f, '\n')
print("\n")

# 4
def make_shirt(size, text):
    print(f"This T-shirt is size {size}, text: '{text}'.")
make_shirt('Medium', 'AI Programming Language')
make_shirt(size='Large', text='Hello World')
print("\n")

# 5
def show_magicians(magicians):
    for magician in magicians:
        print(magician)
magicians_names = ['David Copperfield', 'Harry Houdini', 'Qian Liu']
show_magicians(magicians_names)


