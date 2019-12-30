// Assignment 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include<string>
using namespace std;

template <class T>
class List;

template <class T>
class Node
{
	friend class List<T>;
	T data;
	Node* next;
	Node()
	{
		next = nullptr;
	}
	Node(T& d, Node<T>* ptr = nullptr)
	{
		data = d;
		next = ptr;
	}
};

template <class T>
class List
{
	Node<T>* head, *tail;

	class ListIterator
	{
		Node<T>* iptr;
	
	public:
		
		ListIterator(Node<T>* ptr = nullptr)
		{
			iptr = ptr;
		}

		ListIterator& operator ++(int d) //post increment
		{
			if (iptr)
				iptr = iptr->next;
			return *this;
		}

		ListIterator operator ++() //prefix
		{
			if (iptr)
			{
				ListIterator temp = *this;
				iptr = iptr->next;
				return temp;
			}
		} 

		bool operator == (const ListIterator& i)const
		{
			return(i.iptr == iptr);
		}

		bool operator != (const ListIterator& i) const
		{
			return !(i.iptr == iptr);
		}

		T &operator *()
		{
			return iptr->data;
		}

	};

public:
	typedef ListIterator Iterator;
	List()
	{
		head = nullptr;
		tail = nullptr;
	}

	~List()
	{
		Node<T>* ptr = head;
		{
			while (head != nullptr)
			{
				head = head->next;
				delete ptr;
				ptr = head;
			}
		}
		ptr = head = tail = nullptr;
		
	}

	Iterator begin()
	{
		Iterator I(head);
		return I;
	}

	Iterator end()
	{
		Iterator I(tail);
		return I;
	}

	bool isEmpty()
	{
		if (head == nullptr)
			return true;
		return false;
	}

	void addToStart(T& val)
	{
		if (head == nullptr)
		{
			head = new Node<T>(val);
			tail = head;
		}

		else
			head = new Node<T>(val, head);
	}

	void addToEnd(T& val)
	{
		if (head == nullptr)
			head = tail = new Node<T>(val);
		else
			tail = tail->next = new Node<T>(val);
	}

	void removeFromStart()
	{
		Node<T>* ptr = head;
		head = head->next;
		ptr->next = nullptr;
		delete ptr;
	}

	T& getTop()
	{
		return head->data;
	}
};

template <class T>
class Stack
{
	List<T>* stacklist;
public:
	Stack()
	{
		stacklist = new List<T>();
	}

	~Stack()
	{
		delete stacklist;
		stacklist = nullptr;
	}

	bool isEmpty()
	{
		return stacklist->isEmpty();
	}
	
	void push(T& val)
	{
		stacklist->addToStart(val);
	}

	void pop()
	{
		if (!(isEmpty()))
		{
			stacklist->removeFromStart();
		}
		else
			cout << "Stack Empty! \n";
	}

	T topElement()
	{
		if (!(isEmpty()))
			return stacklist->getTop();
		else
			return -1;
	}
};

template<class T>
class InfluenceNetwork
{
	List<T>** arr;
	int arrsize;
public:
	InfluenceNetwork(int s)
	{
		arrsize = s;
		arr = new List<T> * [s];
		for (int i = 0; i < s; i++)
		{
			arr[i] = new List<T>;
		}
	}

	~InfluenceNetwork()
	{
		for (int i = 0; i < arrsize; i++)
		{
			delete arr[i];
			arr[i] = nullptr;
		}
		delete[]arr;
		arr = nullptr;
	}

	void addToList(int index, int val)	//uses the function of the List addToEnd because index - 1 is  list pointer
	{
		arr[index - 1]->addToEnd(val);
	}

	void CalculateInfluence()const
	{
		cout << "\nThe results are as follows: \n";
		cout << "\nTotal People in the Network: " << arrsize << endl;;
		int maxinfluence = 0;
		List<T>* maxinfluenceid = new List<T>();	//new linked list for the case where several people influence the same no of people//
		List<int>::Iterator iptr;
		for (int i = 0; i < arrsize; i++)
		{
			iptr = arr[i]->begin();		//gives iptr the start of the linked list beginning of the list pointer contained by **arr indexes//
			Stack<int> stack;			//creates a Stack for each list pointer//
			int count = 0;				//counts the no of people influenced by each index//
			bool* checkarr = new bool[arrsize];		//creates a new bool array for each index//
			for (int i = 0; i < arrsize; i++)		//sets 0 value for all the bool array indeces//
				checkarr[i] = 0;

			while (iptr != nullptr)		//gives stack the ids of people it directly influences
			{
				stack.push(*iptr);
				checkarr[*iptr - 1] = 1;
				iptr++;
				count++;
			}
			while (!(stack.isEmpty()))	//calculates indirect influences//
			{
				int id = stack.topElement();	//gives id of the topmost id//
				List<int>::Iterator tempitr = arr[id - 1]->begin();  //new iterator for the list pointer of that arr index
				stack.pop(); // removes the topmost element//
				while (tempitr != nullptr)
				{
					if (checkarr[*tempitr - 1] == false && (*tempitr - 1 != i)) // checks if the element is not previously stored and also that it is not the element itself//
					{
						stack.push(*tempitr);
						checkarr[*tempitr - 1] = 1;
						count++;
					}
					tempitr++;
				}
			}

			//showing people influenced by each user//
			cout << endl << i + 1 << " influences " << count << " people: ";
			for (int j = 0; j < arrsize; j++)
				if (checkarr[j] == 1)
					cout << j + 1 << " ";

			//calculating the maximum people influenced by an individual//
			if (i == 0)	//simply adds influened people in the first go//
			{
				maxinfluenceid->addToEnd(i);
				maxinfluence = count;
			}

			else if (i > 0)
			{
				if (count > maxinfluence)	//checks if previously stored maxinfluence is less than this new count//
				{
					delete maxinfluenceid; // deletes the previous maximum influence members array and creates a new one//
					maxinfluenceid = new List<T>;
					maxinfluenceid->addToEnd(i); //new list contains the new max influence no of people//
					maxinfluence = count; //max influence updated//
				}
				else if (count == maxinfluence) //simply adds another id if the maxinfluence is same for them//
					maxinfluenceid->addToEnd(i);
			}
		}

		//printing who has the max influence/

		if (maxinfluence == 0)
			cout << endl << endl << "Nobody influences anybody. \n";
		else
		{
			iptr = maxinfluenceid->begin();
			cout << endl << endl;
			for (iptr; iptr != nullptr; iptr++)
				cout << *iptr + 1 << " ";
			cout << "influence(s) the most people: " << maxinfluence << endl;
		}
	}

	void InputFromFile(string filename, InfluenceNetwork &i)
	{
		ifstream fin;
		int index = 0;
		int  x = 0;

		fin.open(filename);
		if (fin.is_open())
		{
			fin >> index;
			string str;
			while (!(fin.eof()))
			{
				fin >> index; //inputs the id of the user//
				fin.ignore(3); //ignores the space, then coma and then another space//
				getline(fin, str);
				if (str[0] != NULL) //checks if that user has no influence member at all//
				{
					int y = 0;
					int j = 0;
					while (str[j] != NULL)  //loop to convert all the chars to integers//
					{
						x = 0;
						for (int i = y; str[i] != ',' && str[y] != NULL; i++, y++)
							x = x * 10 + (str[i] - '0');
						j = y;
						y += 2;
						i.addToList(index, x); //adds that particular influence id to the user id//
					}
				}
			}
			i.CalculateInfluence();
			fin.close();
		}
	}
};

int main()
{
	string filename;
	cout << "Enter the name of the file: \n";
	getline(cin, filename);
	ifstream fin;
	int s;
	fin.open(filename);
	if (fin.is_open())
	{
		fin >> s;
		InfluenceNetwork<int>i(s);
		cout << "\nInfluence Network has been created. \n";
		fin.close();
		i.InputFromFile(filename, i);
	}
	else
		cout << "File not found!\n";

	system("pause");
}
