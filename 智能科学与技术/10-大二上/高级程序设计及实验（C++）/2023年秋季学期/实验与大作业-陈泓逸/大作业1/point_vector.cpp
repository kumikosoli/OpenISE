#include<iostream>
#include<cassert> //used here
using namespace std;

struct Point //create struct Point
{
	int x, y;
	Point(int x=0, int y=0):x(x), y(y) {}
	void print() {cout<<"("<<x<<","<<y<<")"<<endl;}
};

class PointVector //create class PointVector
{
	private:
		Point *data;
		unsigned size, capacity;
	public:
		PointVector():data(NULL), size(0), capacity(1) {data = new Point[1];} //default constructor(initial value of capacity cannot be zero instead of at least one)
		PointVector(const PointVector& p) //copy constructor(deep copy)
		{
			size = p.get_size();
			capacity = p.get_capacity();
			data = new Point[capacity];
			memcpy(data, p.get_data(), get_size_all()); //memory copy(it's said on web that std::copy will be safer)
		}
		~PointVector() {delete[] data;} //destructor
		Point* operator[](int index) //overload operator
		{
			assert(index >= 0 && index < size);
			return &data[index];
		}
		PointVector& operator=(const PointVector& p)
		{
			if(this == &p) return *this; //not doing repeated work
			delete[] data;
			size = p.get_size();
			capacity = p.get_capacity();
			data = new Point[capacity];
			memcpy(data, p.get_data(), get_size_all());
			return *this;
		}
		friend PointVector operator+(const PointVector& a, const PointVector& b)
		{
			assert(a.get_size() == b.get_size()); //only two vectors of the same dimention can be added
			PointVector c(a);
			for(unsigned i=0;i<a.get_size();i++)
			{
				c.data[i].x += b.get_data()[i].x;
				c.data[i].y += b.get_data()[i].y;
			}
			return c;
		}
		friend ostream& operator<<(ostream& os, const PointVector& a)
		{
			for(unsigned i=0;i<a.get_size();i++) a.get_data()[i].print(); //calling Point.print()
			return os;
		}
		unsigned get_size() const {return size;} //functions below are as required
		unsigned get_capacity() const {return capacity;}
		Point* get_data() const {return data;}
		int get_size_all() const {return size * sizeof(Point);}
		void clear()
		{
			delete[] data;
			data = new Point[1]; //remaining attention
			size = 0;
			capacity = 1;
		}
		void push_back(const Point& a)
		{
			if(size == capacity)
			{
				capacity = capacity * 1.3 + 1; //advance capacity allocation
				Point *_data=new Point[capacity];
				memcpy(_data, data, get_size_all()); //copy existed data
				delete[] data;
				data = _data;
				data[size].x = a.x;
				data[size++].y = a.y;
			}
			else
			{
				data[size].x = a.x;
				data[size++].y = a.y;
			}
		}
		void pop_back()
		{
			assert(size > 0);
			//delete &data[size-1];
			size--;
		}
		Point& at(unsigned index)
		{
			assert(index >=0 && index < size); //remind of range
			return data[index];
		}
		bool empty() {return (size <= 0) ? 1 : 0;} //'true' means indeed empty
		Point& front()
		{
			assert(size > 0);
			return data[0];
		}
		Point& back()
		{
			assert(size > 0);
			return data[size-1];
		}
		bool insert(unsigned pos, const Point& p)
		{
			//assert(pos >= 0 && pos < size);
			if(pos < 0 || pos >= size) return 0;
			if(size == capacity)
			{
				capacity *= 1.3;
				Point *_data=new Point[capacity];
				memcpy(_data, data, get_size_all());
				delete[] data;
				data = _data;
			}
			memcpy(&data[pos+1], &data[pos], (size - pos + 1) * sizeof(Point));
			data[pos].x = p.x;
			data[pos].y = p.y;
			size++;
			return 1;
		}
		bool erase(unsigned pos)
		{
			//assert(pos >= 0 && pos < size);
			if(pos < 0 || pos >= size) return 0;
			//delete &data[pos];
			memcpy(&data[pos], &data[pos+1], (size - pos - 1) * sizeof(Point));
			size--;
			return 1;
		}
};

int main() //test(as document's required, may not cover all functions by accident)
{
	PointVector pv;
	if(pv.empty()) cout<<"empty point vector!"<<endl;
	for(int i=0;i<20;i++)
	{
		pv.push_back(Point(i, i));
		cout<<"size="<<pv.get_size()<<", capacity="<<pv.get_capacity()<<endl;
	}
	pv.front().print();
	pv.back().print();
	PointVector pv1(pv);
	cout<<pv1<<endl;
	PointVector pv2=pv1;
	for(unsigned j=0;j<pv2.get_size();j++) cout<<pv2.at(j).x<<" "<<pv2.at(j).y<<endl;
	pv.insert(0, Point(100, 100));
	cout<<pv<<endl;
	pv.erase(pv.get_size() / 2);
	cout<<pv<<endl;
	cout<<pv1 + pv2<<endl;
	return 0;
}
