#include <iostream>
#include <windows.h>
using namespace std;

class StringLeaky {
private:
    char *str;
    int len;
    static int lost_memory;   //添加静态成员lost_memory，用于记录泄露的内存大小
public:
    StringLeaky(const char *s) {
	    len = strlen(s);
        str = new char[len + 1];
        strcpy(str, s);
        lost_memory += len;   //累加分配的内存大小，得到泄露的内存
    }
    ~StringLeaky(){   //添加析构函数，防止内存泄漏 
    	delete[]str;
	}
    int GetLen() const { 
	    return len; }
	
	static int get_lost_memory(){
		return lost_memory;
	}
    
};

int StringLeaky::lost_memory = 0;

void EatMemory() {
    StringLeaky str("Hello, I'm from SYSU.");
    cout << "Allocated " << str.GetLen() << " bytes memory, without reclaim." << endl;
}

int main(){
    for (int i = 0; i < 10; i++) {
	    EatMemory();
		Sleep(100);
    }
	
	EatMemory();
    cout << "Total allocated memory: " << StringLeaky::get_lost_memory() << " bytes." << endl;   //输出没有回收的总内存大小 
    cout << "已通过析构函数防止内存泄漏" << endl; 
	return 0;
}



