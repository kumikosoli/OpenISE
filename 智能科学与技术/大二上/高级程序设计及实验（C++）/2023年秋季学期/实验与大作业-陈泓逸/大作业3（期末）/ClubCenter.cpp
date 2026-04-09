//Sucessfully tested in Dev-C++ under ISO C++11

#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<vector>
#include<memory>
using namespace std;

class Person //define Person
{
	protected: //more convinient when derived
    	string id_, name_;
    	bool isPerson_; //judgement of Person or Student
	public:
		Person(): isPerson_(true) {}
    	Person(const string& id, const string& name) : id_(id), name_(name), isPerson_(true) {}
    	~Person() {}
		string getName() const {return name_;}
    	string getId() const {return id_;}
    	bool getPerson() const {return isPerson_;}
};

class Student: public Person //define Student, derived from Person
{
	private:
    	string schoolName_;
    	double discountRate_;
	public:
		Student() {isPerson_ = false;} //convinience mentioned before
    	Student(const string& id, const string& name, const string& schoolName, double discountRate): Person(id, name), schoolName_(schoolName), discountRate_(discountRate) {isPerson_ = false;}
		~Student() {}
		string getSchoolName() const {return schoolName_;}
    	double getDiscountRate() const {return discountRate_;}
};

class Date //define Date
{
	private:
    	int year_, month_, day_;
	public:
		Date() {}
    	Date(int year, int month, int day): year_(year), month_(month), day_(day) {}
		~Date() {}
		string getDate() const {return to_string(year_) + "." + to_string(month_) + "." + to_string(day_);} //replaceable by diplayDate()
};

class Activity //define Activity
{
	private:
    	Date date_;
    	string place_, activity_;
    	set<shared_ptr<Person>> members_; //use shared_ptr
	public:
		Activity() {}
    	Activity(const Date& date, const string& place, const string& activity): date_(date), place_(place), activity_(activity) {}
    	~Activity() {}
		void addMember(const shared_ptr<Person>& member) {members_.insert(member);}
    	void displayActivity(ostream& os) const
		{
        	os<<"Activity: "<<activity_<<endl;
			os<<"Place: "<<place_<<endl;
			os<<"Date: "<<date_.getDate()<<endl;
        	os<<"Members:"<<endl;
        	for(const auto& member : members_)
			{
				os<<" / "<<member->getName()<<"  "<<member->getId();
				if(member->getPerson() == false) //Student then
				{
					Student *student=static_cast<Student*>(&*member); //*member is an object
					os<<"  "<<student->getSchoolName()<<"  "<<student->getDiscountRate();
				}
				os<<endl;
			}
        	os<<endl;
    	}
};

class Club //define Club
{
	protected:
    	string name_;
    	set<shared_ptr<Person>> members_;
    	set<shared_ptr<Activity>> activities_;	
	public:
		Club() {}
    	Club(const string& name): name_(name) {}
    	~Club() {}
    	void virtual displayMembers(ostream&) const = 0;
    	void virtual displayActivities(ostream&) const = 0;
    	void virtual addMember(const shared_ptr<Person>&) = 0;
    	void virtual addActivity(const shared_ptr<Activity>&) = 0;
};

class SportsClub: public Club //define SportsClub, derived from Club
{
	private:
    	string coach_;
    	enum {Running, Swimming, Boxing, Fencing} interest_;
	public:
		SportsClub() {} 
    	SportsClub(const string& name, const string& coach): Club(name), coach_(coach) {}
    	~SportsClub() {}
		void virtual displayMembers(ostream& os) const override
		{
        	os<<endl<<"Sports Club: "<<name_<<endl;
			os<<"Coach: "<<coach_<<endl;
			os<<"Members:"<<endl;
        	for(const auto& member : members_)
			{
				os<<" / "<<member->getName()<<"  "<<member->getId();
				if(member->getPerson() == false)
				{
					Student *student=static_cast<Student*>(&*member);
					os<<"  "<<student->getSchoolName()<<"  "<<student->getDiscountRate();
				}
				os<<endl;
			}
        	os<<endl;
    	}
    	void virtual displayActivities(ostream& os) const override
		{
			os<<endl<<"Sports Club: "<<name_<<endl;
        	os<<"Activities:"<<endl;
        	for(const auto& activity : activities_) activity->displayActivity(os);
        	os<<endl;
    	}
    	void virtual addMember(const shared_ptr<Person>& member) override {members_.insert(member);}
    	void virtual addActivity(const shared_ptr<Activity>& activity) override {activities_.insert(activity);}
};

class MusicClub: public Club //define MusicClub, derived from Club
{
	private:
    	enum {Piano, Violin, Drum, Harp} instrument_;
	public:
		MusicClub() {}
    	MusicClub(const string& name): Club(name) {}
		~MusicClub() {}
		void virtual displayMembers(ostream& os) const override
		{
        	os<<endl<<"Music Club: "<<name_<<endl;
			os<<"Members:"<<endl;
        	for(const auto& member : members_)
			{
				os<<" / "<<member->getName()<<"  "<<member->getId();
				if(member->getPerson() == false)
				{
					Student *student=static_cast<Student*>(&*member);
					os<<"  "<<student->getSchoolName()<<"  "<<student->getDiscountRate();
				}
				os<<endl;
			}
        	os<<endl;
    	}
    	void virtual displayActivities(ostream& os) const override
		{
			os<<endl<<"Music Club: "<<name_<<endl;
        	os<<"Activities:"<<endl;
        	for(const auto& activity : activities_) activity->displayActivity(os);
        	os<<endl;
    	}
    	void virtual addMember(const shared_ptr<Person>& member) override {members_.insert(member);}
    	void virtual addActivity(const shared_ptr<Activity>& activity) override {activities_.insert(activity);}
};

class ClubCenter //define ClubCenter
{
	private:
    	vector<shared_ptr<Club>> clubs_;
	public:
		ClubCenter() {}
		~ClubCenter() {}
    	void addClub(const shared_ptr<Club>& club) {clubs_.push_back(club);}
    	void displayClubs(ostream& os) const
		{
        	for(const auto& club : clubs_)
			{
            	club->displayMembers(os);
            	club->displayActivities(os);
        	}
    	}
};

int main() //test
{
    ClubCenter clubCenter;
    ofstream fout("ClubCenter_result.txt");
    auto sportsClub1 = make_shared<SportsClub>("International Sports Club", "Jason");
    auto sportsClub2 = make_shared<SportsClub>("National Sports Club", "Mike");
    auto musicClub1 = make_shared<MusicClub>("International Music Club");
    auto musicClub2 = make_shared<MusicClub>("National Music Club");
    clubCenter.addClub(sportsClub1); clubCenter.addClub(sportsClub2);
    clubCenter.addClub(musicClub1); clubCenter.addClub(musicClub2);
    auto person1 = make_shared<Person>("001", "Smith");
    auto person2 = make_shared<Person>("002", "Oliver");
    auto person3 = make_shared<Person>("003", "Blake");
    auto person4 = make_shared<Person>("004", "Trump");
    auto student1 = make_shared<Student>("005", "Amy", "SYSU", 0.5);
    auto student2 = make_shared<Student>("006", "Pitt", "MBZU", 1.5);
	auto student3 = make_shared<Student>("007", "Drict", "HKU", 2.5);
	auto student4 = make_shared<Student>("008", "Lam", "CMU", 3.5);
	auto student5 = make_shared<Student>("009", "Elliot", "MIT", 4.5);
	auto student6 = make_shared<Student>("010", "Fred", "UCL", 5.5);
	auto student7 = make_shared<Student>("011", "Qwaintt", "CUHK", 6.5);
	auto student8 = make_shared<Student>("012", "Urquhart", "BBGU", 7.5);
    auto activity1 = make_shared<Activity>(Date(2023,12,15), "Sports Center", "International Badminton Match");
    auto activity2 = make_shared<Activity>(Date(2023,12,18), "Athletic Feild", "International Track And Field Events");
	auto activity3 = make_shared<Activity>(Date(2024,1,4), "Sports Center", "National Tabel Tennis Match");
    auto activity4 = make_shared<Activity>(Date(2024,1,2), "Mountain Park", "National Jogging In The Mountain Game");
	auto activity5 = make_shared<Activity>(Date(2024,1,9), "Great Hall", "International Musician Meeting");
    auto activity6 = make_shared<Activity>(Date(2024,1,6), "Concert Hall", "International Piano Concert");
	auto activity7 = make_shared<Activity>(Date(2023,12,22), "South Grassland", "National Outdoor Art Show");
    auto activity8 = make_shared<Activity>(Date(2024,1,11), "Meeting Room", "National Introductions With Instruments");
	activity1->addMember(person3); activity2->addMember(person1);
	activity3->addMember(person2); activity4->addMember(person4);
	activity5->addMember(person1); activity6->addMember(person4);
	activity7->addMember(person2); activity8->addMember(person3);
    sportsClub1->addMember(person1);
    sportsClub1->addMember(student1); sportsClub1->addMember(student2);
    sportsClub1->addActivity(activity1); sportsClub1->addActivity(activity2);
	sportsClub2->addMember(person2);
    sportsClub2->addMember(student3); sportsClub2->addMember(student4);
    sportsClub2->addActivity(activity3); sportsClub2->addActivity(activity4);
    musicClub1->addMember(person3);
    musicClub1->addMember(student5); musicClub1->addMember(student6);
	musicClub1->addActivity(activity5); musicClub1->addActivity(activity6);
	musicClub2->addMember(person4);
    musicClub2->addMember(student7); musicClub2->addMember(student8);
	musicClub2->addActivity(activity7); musicClub2->addActivity(activity8);
    clubCenter.displayClubs(cout);
    cout<<endl<<"REMIND: RESULT IN FILE -> ClubCenter_result.txt"<<endl;
    return 0;
}

//Sucessfully tested in Dev-C++ under ISO C++11
