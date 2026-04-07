//Sucessfully tested in Dev-C++ under ISO C++11

#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<random> //create random number
#include<stdexcept> //for 'throw' 
#include<fstream>

class Student //specialization(in problem 1)
{
	private:
		char *id, *name, *schoolName;
		double discountRate;
	public:
		Student():id(nullptr), name(nullptr), schoolName(nullptr), discountRate(1.0) {}
		Student(double _discountRate):id(nullptr), name(nullptr), schoolName(nullptr), discountRate(_discountRate) {}
		~Student() {}
};

template<typename T>
class MyVector //template class
{
	private:
    	T data[100] = {}; //each vector is small that no need to preallocate
    	unsigned size, capacity;
	public:
    	MyVector(): size(0), capacity(100) {}
    	MyVector(const MyVector& x): size(x.size), capacity(x.capacity) //copy constructor for deep copy
		{
        	data = new T[capacity];
        	std::copy(x.data, x.data + size, data);
    	}
		~MyVector() {}
    	void insert(const T& value, unsigned index)
		{
        	if(size >= capacity) std::cout<<"Error: line 37, already full."<<"\t"<<size<<"\t"<<capacity<<std::endl; //throw can be used here
        	if(index > size) std::cout<<"Error: line 38, invalid index."<<"\t"<<size<<"\t"<<index<<std::endl;
        	for(unsigned i=size;i>index;--i) data[i] = data[i-1]; //'std::copy' can be used here
	        data[index] = value;
	        ++size;
	    }
	    void erase(unsigned index)
		{
	        if(index >= size) std::cout<<"Error: line 45, invalid index."<<std::endl;
	        else
			{
	            for(unsigned i=index;i<size-1;++i) data[i] = data[i+1];
	            --size;
	        }
	    }
	    T& operator[](unsigned index)
		{
	        if(index >= size) throw std::out_of_range("Index out of range");
	        return data[index];
	    }
		unsigned getSize() const {return size;} //get the size of the vector
	    unsigned getCapacity() const {return capacity;} //get the capacity of the vector
};

template<typename T>
struct Node
{
    MyVector<T> vec; //'std::unique_ptr' can be used here
    unsigned size;
    Node<T> *prev, *next;
	Node(): size(0), prev(nullptr), next(nullptr), vec() {}
};

template<typename T>
class ListQueue
{
	private:
	    Node<T> *head, *tail; //bidirectional
	    unsigned allSize; //decrease use of ListQueue::size()
	public:
	    ListQueue(): head(nullptr), tail(nullptr), allSize(0) {}
	    ~ListQueue()
		{
	        Node<T> *temp=head;
	        while(temp)
			{
	            Node<T> *next=temp->next;
	            delete temp;
	            temp = next;
	        }
	    }
	    void push_front(const T& value)
		{
	        if(!head || head->size >= 100)
			{
	            Node<T> *newNode=new Node<T>();
	            newNode->vec.insert(value, 0);
	            if(!head) head = tail = newNode;
	            else
				{
	                newNode->next = head;
	                head->prev = newNode;
	                head = newNode;
	            }
	            newNode->size = 1;
	        }
	        else
			{
	            head->vec.insert(value, 0);
	            ++head->size;
	        }
	        ++allSize;
	    }
	    void push_back(const T& value)
		{
	        if(!tail || tail->size >= 100)
			{
	            Node<T> *newNode=new Node<T>();
	            newNode->vec.insert(value, 0);
	            if(!tail) head = tail = newNode;
	            else
				{
	                newNode->prev = tail;
	                tail = newNode;
	            }
	            newNode->size = 1;
	        }
	        else
			{
	            tail->vec.insert(value, tail->size);
	            ++tail->size;
	        }
	        ++allSize;
	    }
	    void pop_back()
		{
	        if(!tail) return;
	        tail->vec.erase(tail->size-1);
	        --tail->size;
	        if(tail->size == 0)
			{
	            Node<T> *temp=tail;
	            tail = tail->prev;
	            if(tail) tail->next = nullptr;
	            delete temp;
	            if(!tail) head = nullptr;
	        }
	        --allSize;
	    }
	    void pop_front()
		{
	        if(!head) return;
	        head->vec.erase(0);
	        --head->size;
	        if(head->size == 0)
			{
	            Node<T>* temp = head;
	            head = head->next;
	            if(head) head->prev = nullptr;
	            delete temp;
	            if(!head) tail = nullptr;
	        }
	        --allSize;
	    }
	    void insert(const T& value, unsigned index)
		{
	        if(!head || index >= size())
			{
	            push_back(value);
	            return;
	        }
	        Node<T> *current=head;
	        unsigned totalSize=0;
	        while(current)
			{
	            totalSize += current->size;
	            unsigned t=current->size; //'current->size' may be changed in process
	            if(index < totalSize)
				{
	                if(current->size >= 100)
					{
	                    Node<T> *newNode=new Node<T>();
	                    unsigned splitIndex=index-(totalSize-current->size);
	                    MyVector<T>& vec=current->vec;
	                    for(unsigned i=splitIndex;i<100;++i)
						{
	                        int m=0;
	                        newNode->vec.insert(vec[i], m++); //'std::memcpy' can be used here
	                        ++newNode->size;
	                    }
	                    for(unsigned i=splitIndex;i<100;++i)
						{
	                        vec.erase(splitIndex);
	                        --current->size;
	                    }
	                    newNode->next = current->next;
	                    if(current->next) current->next->prev = newNode;
	                    current->next = newNode;
	                    newNode->prev = current;
	                    if(tail == current) tail = newNode;
	                }
	                current->vec.insert(value, index-(totalSize-t));
	                ++current->size;
	                ++allSize;
	                return;
	            }
	            current = current->next;
	        }
	    }
	    void erase(unsigned index)
		{
	        if(!head || index >= size()) return;
	        Node<T> *current=head;
	        unsigned totalSize=0;
	        while(current)
			{
	            totalSize += current->size;
	            if (index < totalSize)
				{
	                unsigned targetIndex=index-(totalSize-current->size);
	                current->vec.erase(targetIndex);
	                --current->size;
	                if(current->size == 0)
					{
	                    if(current == head)
						{
	                        head = head->next;
	                        if(head) head->prev = nullptr;
	                    }
	                    else if(current == tail)
						{
	                        tail = tail->prev;
	                        if(tail) tail->next = nullptr;
	                    }
	                    else
						{
	                        current->prev->next = current->next;
	                        current->next->prev = current->prev;
	                    }
	                    delete current;
	                }
	                --allSize;
	                return;
	            }
	            current = current->next;
	        }
	    }
	    unsigned size() const //at least O(n)
		{
	        if(!head) return 0;
	        unsigned totalSize=0;
	        Node<T> *current=head;
	        while(current)
			{
	            totalSize += current->size;
	            current = current->next;
	        }
	        return totalSize;
	    }
	    unsigned getSize() const {return allSize;} //only O(1)
	    T& operator[](unsigned index)
		{
	        if(!head || index >= size()) throw std::out_of_range("Index out of range");
	        Node<T> *current=head;
	        unsigned totalSize=0;
	        while(current)
			{
	            totalSize += current->size;
	            if (index < totalSize) return current->vec[index-(totalSize-current->size)];
	            current = current->next;
	        }
	        throw std::out_of_range("Index out of range");
	    }
	    friend std::ostream& operator<<(std::ostream& out, const ListQueue& queue)
		{
	        Node<T> *current=queue.head;
	        out<<"ListQueue: ";
	        while(current)
			{
	            for(unsigned i=0;i<current->size;++i) out<<current->vec[i]<<" ";
	            current = current->next;
	    	}
			return out;
	    }
	    void print(std::ostream& os) const //print on screen or in file
		{
	        Node<T> *current=head;
	        unsigned nodeCount=0;
	        os<<std::endl<<"ListQueue Status:"<<std::endl;
	        while(current)
			{
	            os<<"\tNode "<<++nodeCount<<": "<<current->size<<std::endl;
	            current = current->next;
	        }
	        os<<"All Nodes: "<<nodeCount<<std::endl<<"All Elements: "<<size()<<std::endl;
	    }
};

void test_file(std::ostream& os) //test function in file
{
	ListQueue<int> *test1=new ListQueue<int>();
	unsigned testTurn=100000;
	std::cout<<std::endl<<"Insert <int> elements at random positions to "<<testTurn<<". Process begins and may require a while of waiting time."<<std::endl;
	std::cout<<"REMIND: RESULT IN FILE -> ListQueue_result.txt"<<std::endl;
	os<<std::endl<<"ListQueue<int>"<<std::endl;
	while(test1->getSize() < testTurn)
	{
        unsigned randomIndex=test1->getSize()==0?0:rand()%test1->getSize(); //always valid index surance
        unsigned randomValue=rand()%1000+1; //assuming range 1-1000 for elements
        if(test1->getSize() % (testTurn / 100) == 0) std::cout<<test1->getSize()/(testTurn/100)<<"% has completed."<<std::endl;
//        os<<std::endl<<std::endl<<"Size: "<<test1->getSize()<<std::endl<<"Index: "<<randomIndex<<std::endl;
        test1->insert(randomValue, randomIndex);
    }
    test1->print(os);
    std::cout<<std::endl<<"Insert process ended."<<std::endl<<std::endl;
    std::cout<<std::endl<<"Delete <int> elements at random positions to 0. Process begins and may require a while of waiting time."<<std::endl;
    while(test1->getSize())
    {
    	unsigned randomIndex=rand()%test1->getSize(); //always valid index surance
    	if(test1->getSize() % (testTurn / 100) == 0) std::cout<<100-test1->getSize()/(testTurn/100)<<"% has completed."<<std::endl;
//        os<<std::endl<<std::endl<<"Size: "<<test1->getSize()<<std::endl<<"Index: "<<randomIndex<<std::endl;
        test1->erase(randomIndex);
	}
	test1->print(os);
	std::cout<<std::endl<<"Delete process ended."<<std::endl<<std::endl;
	delete test1;
	
	ListQueue<double> *test2=new ListQueue<double>();
	testTurn = 100000;
	std::cout<<std::endl<<"Insert <double> elements at random positions to "<<testTurn<<". Process begins and may require a while of waiting time."<<std::endl;
	std::cout<<"REMIND: RESULT IN FILE -> ListQueue_result.txt"<<std::endl;
	os<<std::endl<<"ListQueue<double>"<<std::endl;
	while(test2->getSize() < testTurn)
	{
        unsigned randomIndex=test2->getSize()==0?0:rand()%test2->getSize(); //always valid index surance
        unsigned randomValue=1.0*(rand()%1000+1); //assuming range 1-1000 for elements
        if(test2->getSize() % (testTurn / 100) == 0) std::cout<<test2->getSize()/(testTurn/100)<<"% has completed."<<std::endl;
//        os<<std::endl<<std::endl<<"Size: "<<test2->getSize()<<std::endl<<"Index: "<<randomIndex<<std::endl;
        test2->insert(randomValue, randomIndex);
    }
    std::cout<<test2->getSize()/(testTurn/100)<<"% has completed."<<std::endl;
    test2->print(os);
    std::cout<<std::endl<<"Insert process ended."<<std::endl<<std::endl;
    std::cout<<std::endl<<"Delete <double> elements at random positions to 0. Process begins and may require a while of waiting time."<<std::endl;
    while(test2->getSize())
    {
    	unsigned randomIndex=rand()%test2->getSize(); //always valid index surance
    	if(test2->getSize() % (testTurn / 100) == 0) std::cout<<100-test2->getSize()/(testTurn/100)<<"% has completed."<<std::endl;
//        os<<std::endl<<std::endl<<"Size: "<<test2->getSize()<<std::endl<<"Index: "<<randomIndex<<std::endl;
        test2->erase(randomIndex);
	}
	std::cout<<100-test2->getSize()/(testTurn/100)<<"% has completed."<<std::endl;
	test2->print(os);
	std::cout<<std::endl<<"Delete process ended."<<std::endl<<std::endl;
	delete test2;
	
	ListQueue<Student> *test3=new ListQueue<Student>();
	testTurn = 100000;
	std::cout<<std::endl<<"Insert <Student> elements at random positions to "<<testTurn<<". Process begins and may require a while of waiting time."<<std::endl;
	std::cout<<"REMIND: RESULT IN FILE -> ListQueue_result.txt"<<std::endl;
	os<<std::endl<<"ListQueue<Student>"<<std::endl;
	while(test3->getSize() < testTurn)
	{
        unsigned randomIndex=test3->getSize()==0?0:rand()%test3->getSize(); //always valid index surance
        unsigned randomValue=1.0*(rand()%1000+1); //assuming range 1-1000 for elements
        if(test3->getSize() % (testTurn / 100) == 0) std::cout<<test3->getSize()/(testTurn/100)<<"% has completed."<<std::endl;
//        os<<std::endl<<std::endl<<"Size: "<<test2->getSize()<<std::endl<<"Index: "<<randomIndex<<std::endl;
        Student student(randomValue);
		test3->insert(student, randomIndex);
    }
    std::cout<<test3->getSize()/(testTurn/100)<<"% has completed."<<std::endl;
    test3->print(os);
    std::cout<<std::endl<<"Insert process ended."<<std::endl<<std::endl;
    std::cout<<std::endl<<"Delete <Student> elements at random positions to 0. Process begins and may require a while of waiting time."<<std::endl;
    while(test3->getSize())
    {
    	unsigned randomIndex=rand()%test3->getSize(); //always valid index surance
    	if(test3->getSize() % (testTurn / 100) == 0) std::cout<<100-test3->getSize()/(testTurn/100)<<"% has completed."<<std::endl;
//        os<<std::endl<<std::endl<<"Size: "<<test2->getSize()<<std::endl<<"Index: "<<randomIndex<<std::endl;
        test3->erase(randomIndex);
	}
	std::cout<<100-test3->getSize()/(testTurn/100)<<"% has completed."<<std::endl;
	test3->print(os);
	std::cout<<std::endl<<"Delete process ended."<<std::endl<<std::endl;
	delete test3;
	std::cout<<std::endl<<"REMIND: RESULT IN FILE -> ListQueue_result.txt"<<std::endl;
}

void test_screen(std::ostream& os) //test function on screen
{
	os<<std::endl<<"Test(On Screen) Begins Now!"<<std::endl;
	ListQueue<int> test1;
    for(int i=1;i<=10;++i) test1.push_back(i);
    test1.pop_front();
    test1.push_front(5);
    test1.pop_back();
    test1.push_back(11);
    test1.insert(20, 5);
    os<<test1[5]<<std::endl;
    test1.erase(4);
    os<<test1<<std::endl;
    test1.print(os);
    os<<std::endl<<"Test(On Screen) Ends Now!"<<std::endl;
}

int main()
{
    std::ofstream fout("ListQueue_result.txt");
	test_file(fout);
	test_screen(std::cout);
    return 0;
}

//Sucessfully tested in Dev-C++ under ISO C++11
