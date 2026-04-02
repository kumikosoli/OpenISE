//Successfully test on Dev-C++ under standard of ISO C++11

#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<map>
#include<set>
using namespace std;

typedef vector<string>::size_type line_number;
typedef pair<string,int> PAIR; //map's pair

bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {return lhs.second > rhs.second;}
struct CmpByValue //ascend sort(used in algorithm: sort())
{
  bool operator()(const PAIR& lhs, const PAIR& rhs) {return lhs.second > rhs.second;}
};

class FileQuery //define FileQuery
{
	private:
		vector<string*> sentences; //record full text
		map<string,set<line_number>*> word_map; //record occurance line no. of each word
		map<string,long long unsigned int*> word_occur; //record occurance time of each word
	public:
		FileQuery() {} //default constructor
		FileQuery(char* a) {read_file(a);} //constructor with parameters(read file directly)
		~FileQuery() //destructor
		{
			for(int i=0;i<sentences.size();++i) delete sentences[i]; //one iterator form
			for(const auto& word_lines:word_map) //another iterator form
			{
				set<line_number> *line=word_lines.second;
				delete line;
			}
			for(const auto& word_occurs:word_occur)
			{
				long long unsigned int *occur=word_occurs.second; //mind the type of "occur"
				delete occur;
			}
		}
		void handle_file(string& str) //preproccess
		{
			int index=1;
			while(index != -1) //only words(char) and spaces remain after loop
			{
				index = str.find_first_of(",.:;!-");
				if(index == -1) break;
				str.replace(index, 1, "");
			}
			transform(str.begin(), str.end(), str.begin(), ::tolower); //convert uppercase letters to lowercase letters
		}
		void create_map(string& str) //create word_map and word_occur
		{
			istringstream line(str);
			string word;
			while(line>>word) //for each word
			{
				auto &lines1=word_map[word];
				auto &lines2=word_occur[word]; 
				if(!lines1) lines1 = new set<line_number>;
				if(!lines2) lines2 = new long long unsigned int(0);
				lines1->insert(sentences.size()-1);
				++(*lines2);
			}
		}
		void read_file(char* a) //read file "poem.txt"(familiar proccesses in "MyShape.cpp")
		{
			ifstream fin;
			ofstream fout;
			fin.open(a, ios::in);
			if(!fin)
			{
				cout<<"ERROR!"<<endl;
				return;
			}
			char buf[1000]={'\n'};
			while(fin.getline(buf, sizeof(buf)))
			{
				string *s=new string(buf);
				handle_file(*s);
				sentences.push_back(s);
				create_map(*s);
			}
		}
		void print_sentence() {for(auto i=sentences.begin();i!=sentences.end();++i) cout<<**i<<endl;} //mind the "**i". "i" presents an iterator which is &(string&)
		void print_sentence(const vector<string>& str_vec) {for(auto i=str_vec.begin();i!=str_vec.end();++i) cout<<*i<<endl;} //mind the "*i". "i" presents an iterator which is &string
		void print_ascend()
		{
			vector<string> str_vec; //copy, which is actually transformation from string* to string
			for(int i=0;i<sentences.size();++i) str_vec.push_back(*sentences[i]); //mind "*sentences[i]". "sentences[i]" presents &string
			sort(str_vec.begin(), str_vec.end()); //mind this. if call "sort(sentences.begin(), sentences.end());", the full test("sentences") will be sorted by the order of its("sentences") element's(string) address(string&) which is unexpected(see notes at line 88)
			print_sentence(str_vec); //then have correct result(call the overload function)
		}
		void print_word() {for(map<string,set<line_number>*>::iterator it=word_map.begin();it!=word_map.end();++it) cout<<it->first<<": "<<*word_occur[it->first]<<endl;} //mind "*word_occur[it->first]"(see notes at line 93). "map<string,set<line_number>*>::iterator" is real form of "auto" here
		void print_top(int n)
		{
			map<string,int> map_num;
			for(auto i=word_map.begin();i!=word_map.end();++i) map_num.insert(pair<string, int>(i->first, i->second->size()));
			vector<PAIR> map_vec(map_num.begin(),map_num.end()); //vector<PAIR> map_vec(word_occur.begin(),word_occur.end()); (a matter of int/long long unsigned int)
			sort(map_vec.begin(), map_vec.end(), CmpByValue()); //ascend sort
			for(int i=0;i<n;++i)
			{
				string word=map_vec[i].first;
				cout<<word<<": "<<*word_occur[word]<<endl;
				for(auto j=word_map[word]->begin();j!=word_map[word]->end();++j) //print as: "{front_word word next_word}" (if front_word or next_word exist)
				{
					int index=1, index2=1;
					string str=*sentences[*j];
					while(index != -1) //such a complex proccess will be much more comprehensible if a simply concrete example is given
					{
						index = str.find(word+" ");
						if(index == -1) break;
						cout<<"{";
						if(index)
						{
							index2 = str.rfind(" ", index-2);
							cout<<str.substr(index2+1, index-1-index2-1)<<" ";
						}
						cout<<str.substr(index, word.size())<<" ";
						if(index+word.size() < str.size())
						{
							index2 = str.find(" ", index+word.size()+1);
							cout<<str.substr(index+word.size()+1, index2-1-index-word.size());
						}
						cout<<"}"<<endl;
						str = str.substr(index+word.size()+1);
					}
				}
				cout<<endl;
			}
		}
		void find_word(const string& a)
		{
			if(word_map.find(a) == word_map.end()) //if error
			{
				cout<<"The word \""<<a<<"\" doesn't exist."<<endl;
				return;
			}
			cout<<"The word \""<<a<<"\" occurs "<<*word_occur[a]<<" times. Information is shown below."<<endl;
			for(auto i=word_map[a]->begin();i!=word_map[a]->end();++i) cout<<" line "<<*i+1<<":\t"<<*sentences[*i]<<endl; //occur lines
		}
		void replace_word(const string& old_word, const string& new_word)
		{
			if(word_map.find(old_word) == word_map.end()) //if error
			{
				cout<<"The word \""<<old_word<<"\" doesn't exist."<<endl;
				return;
			}
			for(int i=0;i<sentences.size();++i)
			{
				int index=1;
				while(index != -1) //such a complex proccess will be much more comprehensible if a simply concrete example is given
				{
					index = sentences[i]->find(old_word);
					if(index == -1) break;
					if(!index) sentences[i]->replace(index, old_word.size(), new_word);
					else
					{
						index = sentences[i]->find(" "+old_word+" ");
						if(index == -1) break;
						sentences[i]->replace(index+1, old_word.size(), new_word);
					}
				}
			}
			cout<<"Replace completed!"<<endl;
		}
};

void test_function(FileQuery& fq) //test
{
	cout<<"Test begins now!"<<endl<<endl;
	cout<<endl<<"Call function: void PrintSentences()"<<endl;
	fq.print_sentence();
	cout<<endl<<"Call function: void PrintWordCount()"<<endl;
	fq.print_word();
	cout<<endl<<"Call function: void PrintTopWordContect(int n=2)"<<endl;
	fq.print_top(2);
	cout<<endl<<"Call function: void PrintTopWordContect(int n=3)"<<endl;
	fq.print_top(3);
	cout<<endl<<"Call function: void PrintTopWordContect(int n=4)"<<endl;
	fq.print_top(4);
	cout<<endl<<"Call function: void Find(const std::string& word=captain)"<<endl;
	fq.find_word("captain");
	cout<<endl<<"Call function: void Find(const std::string& word=the)"<<endl;
	fq.find_word("the");
	cout<<endl<<"Call function: void Find(const std::string& word=error)"<<endl;
	fq.find_word("error");
	cout<<endl<<"Call function: void Replace(const std::string& old=the, const std::string& new=a)"<<endl;
	fq.replace_word("the", "a");
	cout<<endl<<"Call function: void Replace(const std::string& old=is, const std::string& new=are)"<<endl;
	fq.replace_word("is", "are");
	cout<<endl<<"Call function: void Replace(const std::string& old=error, const std::string& new=default)"<<endl;
	fq.replace_word("error", "default");
	cout<<endl<<"Call function: void PrintSentencesAscend()"<<endl;
	fq.print_ascend();
	cout<<endl<<endl<<"Test ends now!"<<endl;
}

int main()
{
	char a[100]={"poem.txt"};
	FileQuery fq(a);
	test_function(fq);
	return 0;
}

//Successfully test on Dev-C++ under standard of ISO C++11
