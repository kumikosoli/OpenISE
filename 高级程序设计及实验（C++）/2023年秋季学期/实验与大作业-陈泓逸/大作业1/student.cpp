#include<iostream>
#include<cassert> //not used in this code
#include<iomanip>
using namespace std;

class Student //create class Student
{
	private:
		static const int maxCourses=3;
		int id;
		int count_course; //course number
		double grades[maxCourses]; //scores
		std::string name;
		std::string courseNames[maxCourses];
	public:
		Student() {} //default constructor
		Student(int _id, double _grades[], string _name, string _courseNames[], int _count_course) //constructor with parameters
		{
			id = _id;
			name = _name;
			count_course = _count_course; 
			for(int i=0;i<count_course;i++)
			{
				grades[i] = _grades[i];
				courseNames[i] = _courseNames[i];
			}
		}
		Student(const Student& p) //copy constructor(deep copy)
		{
			id = p.id;
			name = p.name;
			for(int i=0;i<maxCourses;i++)
			{
				grades[i] = p.grades[i];
				courseNames[i] = p.courseNames[i];
			}
		}
		~Student() {} //destructor
		void set_id(int _id) {id = _id;} //functions below are as required
		void set_name(string _name) {name = _name;}
		int get_id() const {return id;}
		string get_name() const {return name;}
		string get_course(int i) const {return courseNames[i];}
		bool AddCourse(const std::string& courseName, double grade)
		{
			if(count_course >= 3) return 0; //if out of range
			courseNames[count_course] = courseName;
			grades[count_course] = grade;
			count_course++;
			return 1;
		}
		void SetGrade(const string& courseName, double grade)
		{
			for(int i=0;i<=2;i++)
			{
				if(courseNames[i] == courseName) grades[i] = grade;
			}
		}
		double GetGrade(const string& courseName) const
		{
			for(int i=0;i<=2;i++)
			{
				if(courseNames[i] == courseName) return grades[i];
			}
		}
		double GetAverageGrade() const
		{
			int i=0;
			double aver=0.0;
			for(i=0;i<count_course;i++) aver += grades[i];
			return aver/(i+1);
		}
		void ShowGrades() const
		{
			for(int i=0;i<count_course;i++) cout<<grades[i]<<" ";
			cout<<endl;
		}
		friend class StudentClass; //declare StudentClass as a friend class
};

class StudentClass
{
	private:
		static const int maxStudent=20;
		static int studentCount;
		string code;
		Student* students[maxStudent];
	public:
		StudentClass() {StudentClass::studentCount++;}
		StudentClass(const string& _code, Student* _students[], const int& num)
		{	
			StudentClass::studentCount = num;
			//cout<<StudentClass::studentCount<<endl;
			//for(int i=0;i<StudentClass::studentCount;i++) delete[](students[i]);
			for(int i=0;i<StudentClass::studentCount;i++) students[i] = new Student(*_students[i]);
			
		}
		StudentClass(const StudentClass& p)
		{
			//for(int i=0;i<StudentClass::studentCount;i++) delete[](students[i]);
			for(int i=0;i<StudentClass::studentCount;i++) students[i] = new Student(*p.students[i]);
			StudentClass::studentCount++;
		}
		~StudentClass()
		{
			//for(int i=0;i<StudentClass::studentCount;i++) delete[](students[i]);
			//StudentClass::studentCount = 0;
		}
		bool AddStudent(const Student* student)
		{
			if(StudentClass::studentCount >= maxStudent) return 0;
			students[StudentClass::studentCount] = new Student(*student);
			StudentClass::studentCount++;
			return 1;
		}
		void ShowStudent(int _id) const
		{
			for(int i=0;i<StudentClass::studentCount;i++)
			{
				if(students[i]->id == _id)
				{
					cout<<students[i]->name<<endl;
					break;
				}
			}
		}
		void ShowStudentByIdOrder(bool (*compare)(int a,int b)) //function pointer for ascending or decending
		{
			int a;
			for(int i=0;i<StudentClass::studentCount-1;i++)
			{
				a = i;
				for(int j=i+1;j<StudentClass::studentCount;j++)
				{
					if(!(*compare)(students[a]->id, students[j]->id)) a = j;
				}
				//int temp=students[a]->id;				not only to exchange id
				//students[a]->id = students[i]->id;
				//students[i]->id = temp;
				Student* temp=students[a];
				students[a] = students[i];
				students[i] = temp;
			}
			cout<<setw(6)<<"id"<<setw(6)<<"name"<<setw(14)<<"courses"<<endl; //formatted output
			for(int i=0;i<StudentClass::studentCount;i++)
			{
				cout<<setw(6)<<students[i]->get_id()<<setw(6)<<students[i]->get_name();
				for(int j=0;j<StudentClass::studentCount;j++) cout<<setw(6)<<students[i]->GetGrade(students[i]->get_course(j));
				cout<<endl;
			}
		}
		static void showStudentCount() {cout<<StudentClass::studentCount<<endl;}
};

bool ascending(int a, int b) {return a<b;}

bool decending(int a, int b) {return a>b;}

int StudentClass::studentCount=0; //assignment of static variable

int main() //test (may not cover all functions by accident)
{
	string course_name[3]={"Robotics", "C++", "Math"}, class_name="class one";
	double grade_wang[3]={89.5, 78.5,90.5};
	double grade_li[3]={84.5, 93.5, 75.5};
	double grade_zhao[3]={63.5, 99.5, 86.5};
	Student student1(1, grade_wang, "Wang", course_name, sizeof(grade_wang)/sizeof(double));
	Student student2(2, grade_li, "Li", course_name, sizeof(grade_li)/sizeof(double));
	Student student3(3, grade_wang, "Zhao", course_name, sizeof(grade_zhao)/sizeof(double));
	Student* students[3]={&student1, &student2, &student3};
	StudentClass class1(class_name, students, 3);
	cout<<setw(6)<<"id"<<setw(6)<<"name"<<setw(14)<<"courses"<<endl;
	for(int i=0;i<sizeof(grade_wang)/sizeof(double);i++)
	{
		cout<<setw(6)<<students[i]->get_id()<<setw(6)<<students[i]->get_name();
		for(int j=0;j<sizeof(grade_wang)/sizeof(double);j++) cout<<setw(6)<<students[i]->GetGrade(students[i]->get_course(j));
		cout<<endl;
	}
	student1.SetGrade(course_name[0], 88.5);
	cout<<endl<<"student1.GetGrade(course_name[0]) = "<<student1.GetGrade(course_name[0])<<endl;
	cout<<endl<<"student1.GetAverageGrade() = "<<student1.GetAverageGrade()<<endl;
	cout<<endl<<"student1.ShowGrades(): ";
	student1.ShowGrades();
	cout<<endl<<"class1.ShowStudent(2): ";
	class1.ShowStudent(2);
	cout<<endl<<"class1.ShowStudentByIdOrder(by decending): "<<endl;
	class1.ShowStudentByIdOrder(&decending);
	cout<<endl<<"StudentClass::showStudentCount(): ";
	StudentClass::showStudentCount();
	return 0;
}
