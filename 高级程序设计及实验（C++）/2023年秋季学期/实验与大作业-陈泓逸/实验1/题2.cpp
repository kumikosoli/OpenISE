#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

class Patient
{
	private:
		char name[20]={'\0'};
		int heart_rate,blood_oxygen_content;
	public:
		Patient();
		~Patient();
		int set_up();
		int get_heart_rate();
		static void sort_by_heart_rate();
};

Patient::Patient():heart_rate(0),blood_oxygen_content(0){}

Patient::~Patient(){}

int Patient::set_up()
{
	cout<<"请输入病人的姓名："<<endl;
	gets(name);
	cout<<"请输入病人的心率："<<endl;
	cin>>heart_rate;
	cout<<"请输入病人的血氧："<<endl;
	cin>>blood_oxygen_content;
	char c=getchar();
	if(heart_rate<60 || heart_rate>100 || blood_oxygen_content<65 || blood_oxygen_content>100) return 0;
	else return 1;
}

int Patient::get_heart_rate()
{
	return heart_rate;
}

Patient p1,p2,p3,p4;
int a[2][4]={{1,2,3,4},{0,0,0,0}};

void Patient::sort_by_heart_rate()
{
	int i,j;
	for(i=0;i<=3;i++)
	{
		for(j=3;j>i;j--)
		{
			if(a[1][j]>a[1][j-1])
			{
				int b=a[1][j-1];
				a[1][j-1]=a[1][j];
				a[1][j]=b;
				b=a[0][j-1];
				a[0][j-1]=a[0][j];
				a[0][j]=b;
			}
		}
	}
	for(i=0;i<=3;i++)
	{
		switch(a[0][i])
		{
			case 1: puts(p1.name);
					cout<<p1.heart_rate<<" "<<p1.blood_oxygen_content<<endl;
					break;
			case 2: puts(p2.name);
					cout<<p2.heart_rate<<" "<<p2.blood_oxygen_content<<endl;
					break;
			case 3: puts(p3.name);
					cout<<p3.heart_rate<<" "<<p3.blood_oxygen_content<<endl;
					break;
			case 4: puts(p4.name);
					cout<<p4.heart_rate<<" "<<p4.blood_oxygen_content<<endl;
					break;
		}
	}
}

int main()
{
	int x1=0,x2=0,x3=0,x4=0;
	while(!x1 || !x2 || !x3 || !x4)
	{
		cout<<"请分别输入四位病人的姓名、心率和血氧："<<endl;
		x1=p1.set_up();
		x2=p2.set_up();
		x3=p3.set_up();
		x4=p4.set_up();
		if(!x1 || !x2 || !x3 || !x4) cout<<"输入错误，请重新输入"<<endl; 
	}
	a[1][0]=p1.get_heart_rate();
	a[1][1]=p2.get_heart_rate();
	a[1][2]=p3.get_heart_rate();
	a[1][3]=p4.get_heart_rate();
	Patient::sort_by_heart_rate();
	return 0;
}
