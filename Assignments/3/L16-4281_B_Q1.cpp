#include<iostream>
using namespace std;
template<typename type>
class Stack
{
	type*s;
	int size;
	int strptr;				//index at which insersion will take place
public:
	Stack(int n = 10)		//default and parameterize constructor
	{
		size = n;
		s = new type[n];
		strptr = 0;
	}
	bool push(type d)
	{
		if (!IsFull())
		{
			s[strptr] = d;
			strptr++;
			return true;
		}
		return false;
	}
	bool pop(type&d)
	{
		if (!IsEmpty())
		{
			strptr--;
			d = s[strptr];
			return true;
		}
		return false;
	}
	bool top(type&d)
	{
		if (!IsEmpty())
		{
			d = s[strptr-1];
			return true;
		}
		return false;
	}
	bool IsFull()
	{
		if (size == strptr)
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
		if (strptr == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
struct cellNum
{
	int row;
	int col;
};
bool CheckCell(int*sol ,int currRow, int currCol)
{
	int prev = currRow-1;
	int dist = 1;
	while (prev != -1)
	{
		if ((currCol == (sol[prev] - 1)) || (currCol == (sol[prev] - 1) + dist) || (currCol == (sol[prev] - 1) - dist))
		{
			return false; //you cannot place the queen at this position
		}
		dist++;
		prev--;
	}
	return true;
}
void print(int*sol,int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << sol[i] << " ";
	}
	cout << endl;
}
void NQueen(int n)
{
	Stack<cellNum> Queens;
	int*sol = new int[n];		//allocating rows for puzzle
	int i = 0;					//stoing row number - 1 or queen number - 1
	int j = 0;					//stoing column number
	int solutionNo = 0;
	sol[i] = j + 1;					//placing the first queen

	cellNum first;				//storing queen position in cell number
	first.row = i;
	first.col = j;

	Queens.push(first);			//pushing queen's position in stack
	cellNum temp;				//a temp is used to get the row and column of the previous inserted queen
	Queens.top(temp);
	i++;
	int flag = 0;
	while ((i == 1&&j!=n-1)||flag==0)
	{

		while (i != n||flag==0)			//while the last queen is not placed
		{
			if (flag == 2)
			{
				break;
			}
			while ((!CheckCell(sol, i, j)) || j == n)	//checking that if the next queen is below the previous or in the diagonal
			{							//entering the loop means that you cannot place the queen here
				if (j + 1 >= n)		//checking if the queen has reached the end of the column
				{
					Queens.pop(temp);		//removing the previous queen
					i = temp.row;		//moving to the next column of the previous queen
					j = temp.col + 1;		//moving to the next column of the previous queen
					if (i == 0 && j == n)	//checking if the first queen has been poped from last column
					{
						flag = 2;			//it will break both loops
					}
					break;		//breaking the loop
				}
				j++;				//moving to the next column
			}
			if (CheckCell(sol, i, j) && j < n) //checking that if the next queen is below the previous or in the diagonal
			{
				cellNum next;				//storing queen position in cell number
				next.row = i;
				next.col = j;
				Queens.push(next);			//pushing queen's position in stack
				sol[i] = j + 1;					//placing the next queen
				i++;						//moving towards next queen
				j = 0;						//starting from the first column of next row
				if (i == n)					//if the last queen has been placed
				{
					solutionNo++;			//solution counter
					cout << "Solution number " << solutionNo << ":\t";
					print(sol, n);
				}
			}
		}
		Queens.pop(temp);		//removing the previous queen
		i = temp.row;		//moving to the next column of the previous queen
		j = temp.col + 1;		//moving to the next column of the previous queen
		if (i==0&&j==n)			//checking if the first queen has been poped from last column
		{
			flag = 2;		//it will break both loops
		}
	}
}
int main()
{
	NQueen(8);
	system("pause");
	return 0;
}