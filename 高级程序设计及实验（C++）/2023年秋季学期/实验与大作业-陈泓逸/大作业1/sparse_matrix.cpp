#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstdlib>
using namespace std;

struct NonzeroElement //create struct NonzeroElement(based on chain-list with a head node, more flexible in add/remove)
{
	int row, column, value;
	NonzeroElement *next; //pointer *next
};

class SparseMatrix //create class SparseMatrix
{
	private:
		int row_n, column_n;
		NonzeroElement *data;
	public:
		SparseMatrix():row_n(0), column_n(0) //default constructor
		{
			data = new NonzeroElement();
			data->row = -1;
			data->column = -1;
			data->value = 0;
			data->next = NULL;
		}
		SparseMatrix(int _row_n, int _column_n, NonzeroElement* _data):row_n(_row_n), column_n(_column_n), data(_data) {} //constructor with parameters
		SparseMatrix(const SparseMatrix& p):row_n(p.get_row()), column_n(p.get_column()) //copy constructor(deep copy)
		{
			data = new NonzeroElement();
			data->row = -1;
			data->column = -1;
			data->value = 0;
			data->next = NULL;
			NonzeroElement *s=data, *t=p.get_data()->next;
			while(t) //use of chain-list makes codes lengthy and not so elegant
			{
				NonzeroElement *q=new NonzeroElement();
				q->row = t->row;
				q->column = t->column;
				q->value = t->value;
				q->next = NULL;
				s->next = q;
				s = s->next;
				t = t->next;
				data->value++;
			}
		}
		~SparseMatrix() //destructor
		{
			NonzeroElement *p=data, *q=p->next;
			while(q)
			{
				delete p;
				p = q;
				q = q->next;
			}
		}
		int get_row() const {return row_n;} //functions below are as required
		int get_column() const {return column_n;}
		NonzeroElement* get_data() const {return data;}
		SparseMatrix& add(const SparseMatrix& a)
		{
			NonzeroElement *p=data, *q=p->next, *u=a.get_data()->next; 
			while(u) //no more notes on pointers
			{
				if(u->row < q->row)
				{
					NonzeroElement *s=new NonzeroElement();
					s->row = u->row;
					s->column = u->column;
					s->value = u->value;
					p->next = s;
					s->next = q;
					p = p->next;
					u = u->next;
				}
				else if(u->row > q->row)
				{
					while(1)
					{
						if(!q->next)
						{
							NonzeroElement *s=new NonzeroElement();
							s->row = u->row;
							s->column = u->column;
							s->value = u->value;
							q->next = s;
							p = q;
							q = q->next;
							u = u->next;
							break;
						}
						else
						{
							p = q;
							q = q->next;
							if(!(u->row > q->row)) break;
						}
					}
				}
				else if(u->column < q->column)
				{
					NonzeroElement *s=new NonzeroElement();
					s->row = u->row;
					s->column = u->column;
					s->value = u->value;
					p->next = s;
					s->next = q;
					p = p->next;
					u = u->next;
				}
				else if(u->column > q->column)
				{
					while(1)
					{
						if(!q->next)
						{
							NonzeroElement *s=new NonzeroElement();
							s->row = u->row;
							s->column = u->column;
							s->value = u->value;
							q->next = s;
							p = q;
							q = q->next;
							u = u->next;
							break;
						}
						else
						{
							p = q;
							q = q->next;
							if(!(u->column > q->column) || !(u->row > q->row)) break;
						}
					}
				}
				else
				{
					q->value += u->value;
					p = p->next;
					q = q->next;
					u = u->next;
				}
			}
			return *this;
		}
		SparseMatrix& subtract(const SparseMatrix& a) //another possible way is a function named 'nevigate', like add(nevigate(a))
		{
			NonzeroElement *p=data, *q=p->next, *u=a.get_data()->next; 
			while(u)
			{
				if(u->row < q->row)
				{
					NonzeroElement *s=new NonzeroElement();
					s->row = u->row;
					s->column = u->column;
					s->value = -(u->value);
					p->next = s;
					s->next = q;
					p = p->next;
					u = u->next;
				}
				else if(u->row > q->row)
				{
					while(1)
					{
						if(!q->next)
						{
							NonzeroElement *s=new NonzeroElement();
							s->row = u->row;
							s->column = u->column;
							s->value = -(u->value);
							q->next = s;
							p = q;
							q = q->next;
							u = u->next;
							break;
						}
						else
						{
							p = q;
							q = q->next;
							if(!(u->row > q->row)) break;
						}
					}
				}
				else if(u->column < q->column)
				{
					NonzeroElement *s=new NonzeroElement();
					s->row = u->row;
					s->column = u->column;
					s->value = -(u->value);
					p->next = s;
					s->next = q;
					p = p->next;
					u = u->next;
				}
				else if(u->column > q->column)
				{
					while(1)
					{
						if(!q->next)
						{
							NonzeroElement *s=new NonzeroElement();
							s->row = u->row;
							s->column = u->column;
							s->value = -(u->value);
							q->next = s;
							p = q;
							q = q->next;
							u = u->next;
							break;
						}
						else
						{
							p = q;
							q = q->next;
							if(!(u->column > q->column) || !(u->row > q->row)) break;
						}
					}
				}
				else
				{
					q->value += u->value;
					p = p->next;
					q = q->next;
					u = u->next;
				}
			}
			return *this;
		}
		void show() const
		{
			NonzeroElement *p=data->next;
			for(int i=1;i<=row_n;i++)
			{
				for(int j=1;j<=column_n;j++)
				{
					
					if(p)
					{
						if(i == p->row && j == p->column)
						{
							cout<<setw(5)<<p->value; //formatted output
							p = p->next;
						}
						else cout<<setw(5)<<"0";
					}
					else cout<<setw(5)<<"0";
				}
				cout<<endl;
			}
		}
		friend SparseMatrix operator+(const SparseMatrix& a, const SparseMatrix& b) //overload operator
		{
			SparseMatrix c(a);
			return c.add(b);
		}
		friend SparseMatrix operator-(const SparseMatrix& a, const SparseMatrix& b)
		{
			SparseMatrix c(a);
			return c.subtract(b);
		}
		friend ostream& operator<<(std::ostream& os, const SparseMatrix& a)
		{
			NonzeroElement *p=a.get_data()->next;
			for(int i=1;i<=a.get_row();i++)
			{
				for(int j=1;j<=a.get_column();j++)
				{
					
					if(p)
					{
						if(i == p->row && j == p->column)
						{
							cout<<setw(5)<<p->value;
							p = p->next;
						}
						else cout<<setw(5)<<"0";
					}
					else cout<<setw(5)<<"0";
				}
				cout<<endl;
			}
			return os;
		}
		int get_v(int _row, int _column)
		{
			NonzeroElement* p=data->next;
			while(p->row < _row)
			{
				if(!p) return -1;
				else p = p->next;
			}
			if(p->row > _row) return 0;
			while(p->column < _column)
			{
				if(!p) return -1;
				else p = p->next;
			}
			if(p->column > _column) return 0;
			else return p->value;
		}
		void set_v(int _row, int _column, int _value)
		{
			if(_row > row_n || _column > column_n) return;
			NonzeroElement *p=data, *q=p->next;
			if(!_value)
			{
				while(q && !(q->row == _row && q->column == _column))
				{
					p = q;
					q = q->next;
				}
				if(q)
				{
					p->next = q->next;
					delete q;
				}
				return;
			}
			while(q->row < _row)
			{
				if(!q) break;
				else
				{
					p = q;
					q = q->next;
				}
			}
			if(q && q->row > _row || !q)
			{
				NonzeroElement* r=new NonzeroElement();
				r->row = _row;
				r->column = _column;
				r->value = _value;
				r->next = q;
				p->next = r;
				data->value++;
			}
			while(q->column < _column)
			{
				if(!q) break;
				else
				{
					p = q;
					q = q->next;
				}
			}
			if(q && q->column > _column || !q)
			{
				NonzeroElement* r=new NonzeroElement();
				r->row = _row;
				r->column = _column;
				r->value = _value;
				r->next = q;
				p->next = r;
				data->value++;
			}
			else q->value = _value;
		}
};

void init_matrix(NonzeroElement*& data1, NonzeroElement*& data2, const int& n, const int& m) //initialize NonzeroElement *data of matrix
{
	data1 = new NonzeroElement();
	data1->row = -1;
	data1->column = -1;
	data1->value = 1;
	data1->next = NULL;
	data2 = new NonzeroElement();
	data2->row = -1;
	data2->column = -1;
	data2->value = 1;
	data2->next = NULL;
	int a, b;
	cout<<"input the number of non-zero elements of a new matrix A ";
	cout<<"("<<n<<" rows and "<<m<<" columns): ";
	cin>>a;
	cout<<"input the number of non-zero elements of a new matrix B ";
	cout<<"("<<n<<" rows and "<<m<<" columns): ";
	cin>>b;
	cout<<endl<<"input the non-zero elements of matrix in row and column order ";
	cout<<"as the particular form below:"<<endl;
	cout<<"row column value"<<endl<<endl;
	cout<<"now input all non-zero elements of matrix A ";
	cout<<"("<<n<<" rows and "<<m<<" columns) in turn:"<<endl;
	NonzeroElement *p, *q=data1;
	for(int i=1;i<=a;i++) //non-automatic initialization
	{
		int x, y, z;
		p=new NonzeroElement();
		cin>>x>>y>>z;
		p->row = x;
		p->column = y;
		p->value = z;
		p->next = NULL;
		q->next = p;
		q = p;
		data1->value++;
	}
	cout<<"now input all non-zero elements of matrix B ";
	cout<<"("<<n<<" rows and "<<m<<" columns) in turn:"<<endl;
	q = data2;
	for(int i=1;i<=b;i++)
	{
		int x, y, z;
		p=new NonzeroElement();
		cin>>x>>y>>z;
		p->row = x;
		p->column = y;
		p->value = z;
		p->next = NULL;
		q->next = p;
		q = p;
		data2->value++;
	}
}

int main() //test(may not cover all functions by accident)
{
	int n, m;
	cout<<"input the number of row of matrix: ";
	cin>>n;
	cout<<"input the number of column of matrix: ";
	cin>>m;
	NonzeroElement *data1, *data2;
	init_matrix(data1, data2, n, m);
	SparseMatrix A(n, m, data1), B(n, m, data2);
	cout<<endl<<"matrix A:"<<endl;
	A.show();
	cout<<endl<<"matrix B:"<<endl;
	B.show();
	SparseMatrix C(A), D(B);
	cout<<endl<<"matrix C (copy from matrix A):"<<endl;
	C.show();
	cout<<endl<<"matrix D (copy from matrix B):"<<endl;
	D.show();
	C.add(B);
	cout<<endl<<"matrix C added by matrix B:"<<endl;
	C.show();
	D.subtract(A);
	cout<<endl<<"matrix D subtracted by matrix A:"<<endl;
	D.show();
	cout<<"cout<< C + D :"<<endl;
	cout<<C + D<<endl;
	return 0;
}
