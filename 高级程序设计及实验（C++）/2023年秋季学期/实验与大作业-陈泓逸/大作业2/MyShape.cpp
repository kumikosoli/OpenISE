//Successfully test on Dev-C++ under standard of ISO C++11

#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

class Point //define Point
{
	private:
		double x, y; //x-coordinate and y-coordinate
	public:
		Point(): x(0.0), y(0.0) {} //default constructor
		Point(double a, double b): x(a), y(b) {} //constructor with parameters
		Point(const Point& a): x(a.get_x()), y(a.get_y()) {} //copy constructor
		~Point() {} //destructor
		double get_x() const {return x;} //get x-coordinate
		double get_y() const {return y;} //get y-coordinate
		void move(double x_offset, double y_offset) {x += x_offset; y += y_offset;} //translate x_offset in x_axis and y_offset in y_axis
		void print() const {cout<<fixed<<setprecision(1)<<"Point:"<<endl<<"("<<x<<","<<y<<")"<<endl<<endl;} //print Point(x,y)
};

class Edge //define Edge
{
	private:
		Point p1, p2; //an edge determined by two points
	public:
		Edge(): p1(), p2() {} //default constructor
		Edge(const Point& p3, const Point& p4): p1(p3), p2(p4) {} //constructor with parameters
		Edge(const Edge& e): p1(e.get_p1()), p2(e.get_p2()) {} //copy constructor
		~Edge() {} //destructor
		Point get_p1() const {return p1;} //get point1
		Point get_p2() const {return p2;} //get point2
		double length() const //calculate edge's length
		{
			double x1=p1.get_x(), x2=p2.get_x(), y1=p1.get_y(), y2=p2.get_y();
			return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		}
		void print() const //print edge's information
		{
			cout<<"Edge:"<<endl;
			cout<<"p1: "; p1.print();
			cout<<"p2: "; p2.print();
			cout<<fixed<<setprecision(1)<<"length: "<<length()<<endl<<endl;
		}
		void move(double a, double b) {p1.move(a, b); p2.move(a, b);} //translate a in x-axis and b in y-axis
};

class Shape //define Shape(base class)
{
	private:
		static constexpr const int unknown_value=-1; //unknown value(constexpr: compile-time initialization)
	public:
		Shape() {} //default constructor
		~Shape() {} //destructor
		static double print_unknown_value() {return Shape::unknown_value;} //print unknown value
		double virtual circumference() const = 0; //calculate circumference
		double virtual area() const = 0; //calculate area
		void virtual print() const = 0; //print information
		void virtual move(double, double) = 0; //translate in x-axis and y-axis
		//bool virtual is_valid() {} = 0; //judgement
};

int point_count=0, edge_count=0, circle_count=0, polygon_count=0, number_count=0; //record number

class UnknownShape: public Shape //define UnknownShape(derived class, used after two shapes '&' or '|')
{
	private:
		static constexpr const double unknown_value_all=-1.0; //unknown value
		int unknown; //unknown(a variable to make it a specific object)
	public:
		UnknownShape(): unknown(-1) {} //default constructor
		~UnknownShape() {} //destructor
		static double print_unknown_value_all() {return UnknownShape::unknown_value_all;} //print unknown value
		double virtual circumference() const override {return UnknownShape::print_unknown_value();} //calculate circumference(unknown value)
		double virtual area() const override {return UnknownShape::print_unknown_value();} //calculate area(unknown value)
		void virtual print() const override //print UnknownShape's information
		{
			cout<<"UnknownShape: "<<endl;
			cout<<fixed<<setprecision(2)<<"circumference: "<<UnknownShape::print_unknown_value()<<endl;
			cout<<fixed<<setprecision(2)<<"area: "<<UnknownShape::print_unknown_value()<<endl<<endl;
		}
		void virtual move(double a, double b) {cout<<"unknown moving process "<<UnknownShape::print_unknown_value()<<endl<<endl;} //translate UnknownShape in x-axis and y-axis
};

class Circle: public Shape //define Circle(derived class)
{
	private:
		Point center; //center
		double radius; //radius
	public:
		Circle(): center(), radius(1.0) {} //default constructor
		Circle(const Point& a, const double b): center(a), radius(b) {} //constructor with parameters
		Circle(const Circle& a): center(a.get_center()), radius(a.get_radius()) {} //copy constructor
		~Circle() {} //destructor
		Point get_center() const {return center;} //get center
		double get_radius() const {return radius;} //get radius
		double virtual circumference() const override {return 3.14 * 2 * radius;} //calculate circumference
		double virtual area() const override {return 3.14 * radius * radius;} //calculate area
		void virtual print() const override //print Circle's information
		{
			cout<<"Circle: "<<endl;
			cout<<"center: "; center.print();
			cout<<fixed<<setprecision(2)<<"radius: "<<radius<<endl;
			cout<<fixed<<setprecision(2)<<"circumference: "<<circumference()<<endl;
			cout<<fixed<<setprecision(2)<<"area: "<<area()<<endl<<endl;
		}
		void virtual move(double a, double b) override {center.move(a, b);} //translate a in x-axis and b in y-axis
		UnknownShape operator&(Shape* a); //operator &(intersection)
		UnknownShape operator|(Shape* a); //operator |(union)
};

class Polygon: public Shape //dedfine Polygon
{
	private:
		vector<Edge*> edges; //a polygon consisted of a series edges
	public:
		Polygon() {} //default constructor
		Polygon(const vector<Edge*> v): edges(v) {} //constructor with parameters
		Polygon(const Polygon& p): edges(p.get_edges()) {} //copy constructor
		~Polygon() {for(int i=0;i<edges.size();++i) delete edges[i];} //destuctor(delete 'new' pointers)
		vector<Edge*> get_edges() const {return edges;} //get edges
		double virtual circumference() const override //calculate circumference
		{
			double length_all=0;
			int i=0;
			while(i < edges.size()) length_all += edges[i++]->length();
			return length_all;
		}
		double virtual area() const override {return Shape::print_unknown_value();} //calculate area
		void virtual print() const override //print Polygon's information
		{
			cout<<"Polygon: "<<endl;
			cout<<"edges: "<<endl;
			int i=0;
			while(i < edges.size()) edges[i++]->print();
			cout<<fixed<<setprecision(2)<<"circumference: "<<circumference()<<endl;
			cout<<fixed<<setprecision(2)<<"area(unknown value): "<<area()<<endl<<endl;
		}
		void virtual move(double a, double b) override //translate a in x-axis and b in y-axis
		{
			int i=0;
			while(i < edges.size()) edges[i++]->move(a, b);
		}
		UnknownShape operator&(Shape* a) //operator &(intersection)
		{
			UnknownShape u1;
			Circle *c1=dynamic_cast<Circle*>(a); //whether Circle or not
			if(c1) return u1;
			UnknownShape u2;
			Polygon *p1=dynamic_cast<Polygon*>(a); //whether Polygon or not
			if(p1) return u2;
		}
		UnknownShape operator|(Shape* a) //operator |(union)
		{
			UnknownShape u1;
			Circle *c1=dynamic_cast<Circle*>(a);
			if(c1) return u1;
			UnknownShape u2;
			Polygon *p1=dynamic_cast<Polygon*>(a);
			if(p1) return u2;
		}
};

class ShapeFile //define ShapeFile
{
	private:
		vector<Shape*> shapes; //record Circle and Polygon
		vector<Point*> points; //record Point(not a derived class)
	public:
		ShapeFile() {} //default constructor
		~ShapeFile() //destructor
		{
			for(int i=0;i<shapes.size();++i) delete shapes[i]; //delete 'new' pointers
			for(int i=0;i<points.size();++i) delete points[i];
		}
		vector<Shape*> get_shapes() {return shapes;} //get shapes
		void string_handle(string& str) //to remove useless chars until only valid components of numbers(still string) remain
		{
			number_count = 0; //record how many 'numbers' in string
			int index=1;
			while(index != -1)
			{
				index=str.find_first_not_of(",.-0123456789");
				if(index == -1) break;
				str.replace(index, 1, "");
			}
			index = 1;
			while(index != -1)
			{
				index=str.find_first_of(",");
				if(index == -1) break;
				str.replace(index, 1, " "); //only 'numbers'(still string, such as "1 2.0 -3.5") and spaces remain after two replacements
				++number_count;
			}
			++number_count; //used later as iterator in transform from string to int or double
		}
		void read_file(char* a) //read from "shapes.txt"
		{
			ifstream fin;
			ofstream fout;
			fin.open(a, ios::in); //read-only
			if(!fin) //if error
			{
				cout<<"ERROR!"<<endl;
				return;
			}
			char buf[200]={'\n'}; //record one line
			while(fin.getline(buf, sizeof(buf))) //end when reach the bottom of file
			{
				string str1(buf); //transform from char[] to string
				int index1=str1.find("Circle"); //search for key word "Circle"
				if(index1 != -1) //is Circle
				{
					int number_point=0;
					double number_radius=0.0;
					string_handle(str1); //preproccess
					stringstream ss;
					ss.str(str1);
					ss>>number_point>>number_radius; //point's no. and radius value
					Circle *c=new Circle(*points[number_point],number_radius); //'new' a Circle
					Shape *s=NULL;
					shapes.push_back(s);
					shapes.back() = c; //pointer of base class point to derived class
					++circle_count;
//					int a=str[index1+14]-48; //old thoughts below
//					string num[100]=str.substr(index1+17);
//					char *num_=(char*)str.data();
//					double b;
//					sscanf(num_, "%f", &b);
//					Circle *c=new Circle(*points[a],b);
//					Shape *s=NULL;
//					shapes.push_back(s);
//					shapes.back() = c;
//					++circle_count;
				}
				index1 = str1.find("Polygon"); //search for key word "Polygon"
				if(index1 != -1) //is Polygon
				{
					string_handle(str1); //proccess is the same and quite clear
					int number_arr[number_count+1]={0};
					vector<Edge*> edge_vector;
					stringstream ss;
					ss.str(str1);
					for(int i=0;i<number_count;++i) ss>>number_arr[i];
					for(int i=0;i<number_count;++i)
					{
						if(i == number_count-1)
						{
							Edge *e=new Edge(*points[i],*points[0]);
							edge_vector.push_back(e);
							continue;
						}
						Edge *e=new Edge(*points[i],*points[i+1]);
						edge_vector.push_back(e);
					}
					Polygon *plg=new Polygon(edge_vector);
					Shape *s=NULL;
					shapes.push_back(s);
					shapes.back() = plg;
					++polygon_count;
//					vector<Edge*> edge_vector; //old thoughts below
//					int index2=str.find_first_of("0123456789"), index3=str.find(',');
//					string num[100]=str.substr(index2,index3-1);
//					char *num_=(char*)str.data();
//					int x, y;
//					sscanf(num_, "%d", &x);
//					while(index2 != -1)
//					{
//						string num1[100]=str.substr(index2,index3-1);
//						str = str.substr(index3+1);
//						char *num1_=(char*)str.data();
//						int a, b, index4=str.find_first_of("0123456789"), index5=str.find(',');
//						if(index4 != -1)
//						{
//							string num2[100]=str.substr(index4,index5-1);
//							char *num2_=(char*)str.data();
//							sscanf(num2_, "%d", &b);
//						}
//						else break;
//						sscanf(num1_, "%d", &a);
//						Edge e(*points[a],*points[b]);
//						edge_vector.push_back(&e);
//					}
//					int index4=str.find_first_of("0123456789"), index5=str.find(',');
//					num[100]=str.substr(index4,index5-1);
//					num_=(char*)str.data();
//					sscanf(num_, "%d", &y);
//					Edge e(*points[x],*points[y]);
//					edge_vector.push_back(&e);
//					Polygon *plg=new Polygon(edge_vector);
//					Shape *s=NULL;
//					shapes.push_back(s);
//					shapes.back() = plg;
//					++polygon_count;
				}
				index1 = str1.find("Point"); //search for key word "Point"
				if(index1 != -1) //is Point(must search at last)
				{
					int index2=str1.find_first_of(":");
					double number_arr[3]={0};
					str1 = str1.substr(index2 + 1); //proccess is the same and quite clear
					string_handle(str1);
					stringstream ss;
					ss.str(str1);
					for(int i=0;i<number_count;++i) ss>>number_arr[i];
					Point *p=new Point(number_arr[0],number_arr[1]);
					points.push_back(p);
					++point_count;
//					double a=(double)(str[index1+1]-48); //old thoughts below
//					int index2=str.find(',');
//					if(index2 != -1)
//					{
//						double b=(double)(str[index2+2]-48);
//						Point *p=new Point(a,b);
//						points.push_back(p);
//						++point_count;
//					}
				}
			}
		}
//		void write_file() //write in "shapes_output.txt"
//		{
//			
//		}
		void print() const //print all information
		{
			cout<<"Points:"<<endl;
			for(int i=0;i<point_count;++i) points[i]->print();
			cout<<"Shapes:"<<endl;
			for(int i=0;i<circle_count+polygon_count;++i)
			{
				Circle *c1=dynamic_cast<Circle*>(shapes[i]);
				if(c1)
				{
					c1->print();
					continue;
				}
				Polygon *p1=dynamic_cast<Polygon*>(shapes[i]);
				if(p1)
				{
					p1->print();
					continue;
				}
			}
		}
};

UnknownShape Circle::operator&(Shape* a) //the same
{
	UnknownShape u1;
	Circle *c1=dynamic_cast<Circle*>(a);
	if(c1) return u1;
	UnknownShape u2;
	Polygon *p1=dynamic_cast<Polygon*>(a);
	if(p1) return u2;
}

UnknownShape Circle::operator|(Shape* a) //the same
{
	UnknownShape u1;
	Circle *c1=dynamic_cast<Circle*>(a);
	if(c1) return u1;
	UnknownShape u2;
	Polygon *p1=dynamic_cast<Polygon*>(a);
	if(p1) return u2;
}

int main()
{
//	Point p1(0.0,0.0), p2(1.0,0.0), p3(1.0,1.0), p4(0.0,1.0); //old test
//	Edge e1(p1,p2), e2(p2,p3), e3(p3,p4), e4(p4,p1);
//	Edge* edges[4]={&e1,&e2,&e3,&e4};
//	vector<Edge*> edge_vec(edges,edges+4);
//	Polygon pg1(edge_vec);
//	pg1.print();
//	Circle c1(p1,3.0);
//	UnknownShape u1=c1|(&pg1);
//	u1.print();
	char a[100]={"shapes.txt"}; //test
	ShapeFile sfile;
	sfile.read_file(a);
	sfile.print();
	return 0;
}

//Successfully test on Dev-C++ under standard of ISO C++11
