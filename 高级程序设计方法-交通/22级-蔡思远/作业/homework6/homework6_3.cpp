#include <iostream>
#include <string>
using namespace std;

struct Person {
    std::string name;
    int score;
};

class ScoreMap {
public:    
    ScoreMap() : size_(0), capacity_(10) {   //默认构造函数
        ptr_ = new Person[capacity_];   //分配内存
    }
    
    ScoreMap(int capacity) : size_(0), capacity_(capacity) {   //有参构造函数
        ptr_ = new Person[capacity];   //分配内存
    }
    
    ScoreMap(const ScoreMap& other) {   //拷贝构造函数
        size_ = other.size_;
        capacity_ = other.capacity_;
        ptr_ = new Person[capacity_];   //分配内存
        for (int i = 0; i < size_; i++) {
            ptr_[i] = other.ptr_[i];
        }
    }
    
    ~ScoreMap() {   //析构函数
        delete[] ptr_;
    }

    
    ScoreMap& operator=(const ScoreMap& other) {   //重载赋值运算符
    
        delete[] ptr_;   //释放原有内存
        
        size_ = other.size_;
        capacity_ = other.capacity_;
        ptr_ = new Person[capacity_];
        for (int i = 0; i < size_; i++) {   //将新内容进行复制
            ptr_[i] = other.ptr_[i];
        }
        
		return *this;   //将函数自身的引用作为返回值
    }
    

private:    
    Person* ptr_;   //记录Person数组的首指针
    int size_;   //数组长度
    int capacity_;   //数组容量
};

int main() {
    


}
