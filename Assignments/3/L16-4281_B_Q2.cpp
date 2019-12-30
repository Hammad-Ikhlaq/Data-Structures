#include<iostream>
using namespace std;
template<typename type>
class Queue
{
	type*q;
	int front;
	int end;
	int maxsize;
	int size;
public:
	Queue(int s = 10)		//default and parameterize constructor
	{
		maxsize = s;
		q = new type[maxsize];
		front = -1;
		end = 0;
		size = 0;
	}
	bool Enqueue(type d)
	{
		if (!IsFull())
		{
			q[end] = d;
			end++;
			if (end == maxsize)
			{
				end=0;
			}
			size++;
			return true;
		}
		return false;
	}
	bool Dequeue(type&d)
	{
		if (!IsEmpty())
		{
			if (front == maxsize)
			{
				front = -1;
			}
			front++;
			d=q[front];
			size--;
			return true;
		}
		return false;
	}
	bool IsFull()
	{
		if (size == maxsize)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool IsEmpty()
	{
		if (size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
class Set
{
private:
	int*arr;
	int size;
public:
	void print()
	{
		cout << "{";
		for (int i = 0; i<size-1; i++)
			cout << arr[i] << ",";
		cout<<arr[size-1];
		cout << "}";
	}
	Set() //Default constructor
	{
		arr = NULL;
		size = 0;
	}
	~Set()		//Destructor!
	{
		if (arr != NULL)
		{

			delete[]arr;
		}
	}
	Set(int*ptr, int n)			//parameterized constructor
	{
		size = n;
		arr = new int[size];
		for (int i = 0; i<n; i++)
			arr[i] = ptr[i];
	}
	const Set & operator=(const Set & obj)
	{
		if (arr != NULL)
		{
			delete[]arr;
		}
		arr=NULL;
		arr = new int[obj.size];
		size = obj.size;
		for (int i = 0; i < size; i++)
		{
			arr[i] = obj.arr[i];
		}
		return *this;
	}
	Set(const Set & obj) //copy constructor
	{
		arr = new int[obj.size];
		size = obj.size;
		for (int i = 0; i < size; i++)
		{
			arr[i] = obj.arr[i];
		}
	}
	void Add(int obj)
	{
		int* temp;
		temp = new int[size + 1];	//alloting space for new array
		for (int i = 0; i<size; i++)
		{
			temp[i] = arr[i];		//coping array
		}
		temp[size] = obj;			//adding the last element
		arr = temp;
		size = size++;			//increment the size
	}
	void Remove()
	{
		int*temp;					
		temp = new int[size - 1];	//alloting space for new array
		for (int i = 0; i<size-1; i++)
		{
			temp[i] = arr[i];		//coping array
		}
		size = size--;				//decrement the size
		arr = temp;
	}
	int getlast()
	{
		return arr[size - 1];
	}
	void allSubsets(int n)
	{
		int arr[1] = { 1 };
		Set first(arr,1);
		Queue<Set> subsets(pow(2,n)-1);
		subsets.Enqueue(first);
		Set s(first);
		Set r;
		int count =0;		//it is used to count the number of subsets
		while (!subsets.IsEmpty())
		{
			subsets.Dequeue(s);
			s.print();
			cout<<endl;
			count++;
			cout<<endl;
			if (s.getlast() < n)
			{
				r = s;
				r.Remove();
				r.Add(s.getlast() + 1);
				subsets.Enqueue(r);
				s.Add(s.getlast() + 1);
				subsets.Enqueue(s);
			}
		}
		cout<<count<<" subsets are generated"<<endl; // it prints the number of subsets generated
	}
};

int main()
{
	int arr[] = { 1, 2, 3,4,5 };
	Set check(arr, 5);
	check.allSubsets(5);
	cout << endl;
	system("pause");
	return 0;
}