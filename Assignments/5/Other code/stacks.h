#ifndef STACKS_H
#define STACKS_H

const int MAXSIZE = 500;

template <class typeName>
class stack
{
public:
	stack(){ index = 0; }
	bool push(typeName item);
	bool pop(typeName &item);
	bool peak(typeName &item);
	bool pop();
	bool empty();  //make the stack empty
	bool full();
	void initialize(){ index = 0; };
private:
	typeName arr[MAXSIZE];
	int index;
};

template <class typeName>
bool stack<typeName>::empty()
{
	bool check = false;
	if (index == 0)
		check = true;
	return check;
}

template <class typeName>
bool stack<typeName>::full()
{
	bool check = false;
	if (index == MAXSIZE)
		check = true;
	return check;

}

template <class typeName>
bool stack<typeName>::push(typeName item)
{
	bool check = true;
	if (full())
		check = false;
	else
	{
		arr[index] = item;
		index++;
	}
	return check;
}

template <class typeName>
bool stack<typeName>::pop(typeName &item)
{
	bool check = true;
	if (empty())
		check = false;
	else
	{
		item = arr[index - 1];
		index--;
	}
	return check;
}

template <class typeName>
bool stack<typeName>::peak(typeName &item)
{
	bool check = true;
	if (empty())
		check = false;
	else
	{
		item = arr[index - 1];
	}
	return check;
}
template <class typeName>
bool stack<typeName>::pop()
{
	bool check = true;
	if (empty)
		check = false;
	else
	{
		currSize--;
	}
	return check;
}

#endif