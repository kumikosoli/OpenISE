//Sucessfully tested in Dev-C++ under ISO C++11

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<algorithm>
#include<set>
#include<functional> //functions as parameters 
using namespace std;

struct StudentInfo
{
    int id, schoolYear;
    string name, sex, birthday, birthplace;
};

struct CourseInfo
{
    int id, score;
	double credits;
    string course;
};

set<int> studentIds;
map<int, StudentInfo> studentMap;
multimap<int, CourseInfo> courseMap;

void LoadStudentInfo(const string& filename) //get student information
{
    ifstream file(filename);
    if(!file.is_open())
	{
        cerr<<"Error opening file: "<<filename<<endl;
        return;
    }
    string line;
    while(getline(file, line))
	{
        if(line[0] == '#') continue;
        istringstream ss(line);
        StudentInfo info;
        ss>>info.id>>info.name>>info.sex>>info.birthday>>info.schoolYear>>info.birthplace;
        studentMap[info.id] = info;
    }
    file.close();
}

void LoadCourseInfo(const string& filename) //get course information
{
    ifstream file(filename);
    if(!file.is_open())
	{
        cerr<<"Error opening file: "<<filename<<endl;
        return;
    }
    string line;
    while(getline(file, line))
	{
        if(line[0] == '#') continue;
        istringstream ss(line);
        CourseInfo info;
        ss>>info.id;
        string courseName;
        while(ss>>courseName)
        {
        	if(!isalpha(courseName[0])) break;
        	info.course += " " + courseName; //course name includes space
		}
		info.course.erase(0, 1);
		info.credits = stod(courseName);
		ss>>info.score;
        courseMap.insert({info.id, info});
    }
    file.close();
}

void PrintStudentCourses(int studentId, ostream& os) //"os" can be "cout" or "fout"
{
    if(studentMap.find(studentId) != studentMap.end())
	{
        const auto& student=studentMap[studentId];
        os<<"Student ID: "<<student.id<<endl<<"Name: "<<student.name<<endl<<"Sex: "<<
		    student.sex<<endl<<"Birthday: "<<student.birthday<<endl<<"School Year: "<<
			student.schoolYear<<endl<<"Birthplace: "<<student.birthplace<<endl;
        auto range=courseMap.equal_range(studentId);
        for(auto it=range.first;it!=range.second;++it)
            os<<"\tCourse: "<<it->second.course<<endl<<"\tCredits: "<<it->second.credits<<
			    endl<<"\tScore: "<<it->second.score<<endl<<endl;
    }
	else os<<"No student found with ID "<<studentId<<endl;
}

void SortByName(ostream& os)
{
    vector<pair<int, StudentInfo>> students(studentMap.begin(), studentMap.end());
    sort(students.begin(), students.end(), [](const pair<int, StudentInfo>& a, const pair<int, StudentInfo>& b) {return a.second.name < b.second.name;});
    for(const auto& student: students) PrintStudentCourses(student.first, os);
}

void SortByTotalScore(ostream& os)
{
	vector<pair<int, StudentInfo>> students; //contain students' information
	for(const auto& pair1: studentMap)
	{
		int allScore=0;
		for(const auto& pair2: courseMap) //calculate all scores of each student for comparison
			if(pair2.first == pair1.first) allScore += pair2.second.score;
		students.push_back(make_pair(allScore, pair1.second));
	}
	sort(students.begin(), students.end(), [](const pair<int, StudentInfo>& a, const pair<int, StudentInfo>& b) {return a.first > b.first;});
    for(const auto& student: students) PrintStudentCourses(student.second.id, os);
}

void SortByScore(const string& courseName, ostream& os) //declare target course
{
	vector<pair<int, StudentInfo>> students;
	for(const auto& pair1: studentMap)
	{
		int oneScore=0;
		for(const auto& pair2: courseMap)
			if(pair2.first == pair1.first && pair2.second.course == courseName)
				oneScore += pair2.second.score;
		students.push_back(make_pair(oneScore, pair1.second));
	}
	sort(students.begin(), students.end(), [](const pair<int, StudentInfo>& a, const pair<int, StudentInfo>& b) {return a.first > b.first;});
    for(const auto& student: students) PrintStudentCourses(student.second.id, os);
}

void QueryByScoreRange(const string& courseName, int low, int high, ostream& os, int judge=0) //declare lower-bound and upper-bound
{
    studentIds.clear();
    for(const auto& pair: courseMap)
        if(pair.second.course == courseName && pair.second.score >= low && pair.second.score <= high)
            studentIds.insert(pair.first);
    if(judge) return;
    for(int id: studentIds)
    	if(studentMap[id].schoolYear == 2020) PrintStudentCourses(id, os);
}

void QueryBySex(const string& sex, ostream& os, int judge=0)
{
    studentIds.clear();
    for(const auto& pair: studentMap)
        if(pair.second.sex == sex) studentIds.insert(pair.first);
    if(judge) return;
    for(int id: studentIds) PrintStudentCourses(id, os);
}

void CalculateAverage(double low, ostream& os, int judge=0)
{
	studentIds.clear();
	for(const auto& pair1: studentMap)
	{
		double averageValue=0.0;
		int averageCount=0;
		for(const auto& pair2: courseMap)
		{
			if(pair2.first == pair1.first)
			{
				averageValue += pair2.second.score * 1.0;
				++averageCount;
			}
		}
		if(averageValue / averageCount >= low) studentIds.insert(pair1.first);
	}
	if(judge) return;
	if(!studentIds.empty()) for(int id: studentIds) PrintStudentCourses(id, os);
	else os<<"No Student Qualified."<<endl;
}

void CalculateCredit(int low, ostream& os)
{
	set<int> studentIds;
	for(const auto& pair1: studentMap)
	{
		int allCredit=0;
		for(const auto& pair2: courseMap)
			if(pair2.first == pair1.first) allCredit += pair2.second.credits;
		if(allCredit >= low) studentIds.insert(pair1.first);
	}
	if(!studentIds.empty()) for(int id: studentIds) PrintStudentCourses(id, os);
	else os<<"No Student Qualified."<<endl;
}

void DeleteByCondition(function<bool(const StudentInfo&, const CourseInfo&)> condition, ostream& os) //customized condition function
{
    vector<int> toDelete;
    for(const auto& pair: courseMap)
	{
        const auto& student=studentMap[pair.first];
        const auto& course=pair.second;
        if(condition(student, course)) toDelete.push_back(pair.first);
    }
    for(int id: toDelete)
	{
        studentMap.erase(id);
        courseMap.erase(id);
    }
    if(!studentMap.empty()) for(const auto& pair: studentMap) PrintStudentCourses(pair.first, os);
}

void Test() //write in file
{
    ofstream resultFile("StudenInfo_StudentCourse_result.txt");
    cout<<endl<<"REMIND: RESULT IN FILE -> StudentInfo_StudentCourse_result.txt"<<endl;
    resultFile<<endl<<"Show Information of Student In Condition Below:"<<endl;
    resultFile<<"(school year == 2020, chosen course == C Programming Language, score == [0,60])"<<endl<<endl;
    QueryByScoreRange("C Programming Language", 0, 60, resultFile);
	resultFile<<endl<<"Show Information of Student In Condition Below:"<<endl;
    resultFile<<"(average score of all courses >= 80.0)"<<endl<<endl;
    CalculateAverage(80.0, resultFile);
    resultFile<<endl<<"Show Information of Student In Condition Below:"<<endl;
    resultFile<<"(gain credits >= 20)"<<endl<<endl;
	CalculateCredit(20, resultFile);
    resultFile.close();
}

bool DeleteMale(const StudentInfo& si, const CourseInfo& ci) {return si.sex == string("Male");}

void OtherFun() //show on screen
{
	LoadStudentInfo("StudentInfo.txt");
    LoadCourseInfo("StudentCourse.txt");
	cout<<endl<<"Other Functions' Test Begins Now!"<<endl<<endl;
	cout<<endl<<"Sort All Students By Total Score:"<<endl<<endl;
	SortByTotalScore(cout);
	cout<<endl<<"Sort All Students By Name:"<<endl<<endl;
	SortByName(cout);
	cout<<endl<<"Find All Male Students:"<<endl<<endl;
	QueryBySex("Male", cout);
	cout<<endl<<"Delete All Male Students:"<<endl<<endl;
	DeleteByCondition(DeleteMale, cout);
	cout<<endl<<"Other Functions' Test Ends Now!"<<endl<<endl;
}

int main()
{
    OtherFun();
	Test();
    return 0;
}

//Sucessfully tested in Dev-C++ under ISO C++11
