#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cmath>
#include<list>

using namespace std;

//struct of points
struct Point
{
	float x, y;
};
class HeapItem
{
public:
	float distance;
	int G1, G2;//group no's

	//default constructor
	HeapItem()
	{
		distance = 0;
		G1 = 0;
		G2 = 0;
	}
	//parametrized constructors
	HeapItem(float d, int g1, int g2)
	{
		distance = d;
		G1 = g1;
		G2 = g2;
	}
	//destructors
	~HeapItem()
	{}
	//friend void CreateGroups(string fileName);
};

class MinHeap
{
public:
	vector<HeapItem> heap;

	//default constructor
	MinHeap()
	{}
	//parametrized constructor
	MinHeap(int s)
	{
		heap.resize(s);
	}
	//Insert Function
	void insert(HeapItem h)
	{
		heap.push_back(h);//pushing heapItem in the Minheap
		ReheapUp(0, heap.size()-1);//Sorting heap from end to top
	}
	//Function to sort heap from end to top
	void ReheapUp(int r, int i)
	{
		int parent = 0;
		if (r < i)
		{
			parent = (i - 1) / 2;//finding parent
		}
		if (heap[parent].distance > heap[i].distance)//comparing distances
		{
			MySwap(heap, parent, i);//swapping parent
			ReheapUp(r, parent);//sorting heap
		}
	}
	//Function to swap to heap objects
	void MySwap(vector<HeapItem> &a, int p, int in)
	{
		HeapItem t;//creating temporary heapitem
		t.distance = a[p].distance;//swapping distance
		t.G1 = a[p].G1;//swapping group1
		t.G2 = a[p].G2;//swapping group2
		a[p].distance = a[in].distance;//swapping distance
		a[p].G1 = a[in].G1;//swapping group1
		a[p].G2 = a[in].G2;//swapping group2
		a[in].distance = t.distance;//swapping distance
		a[in].G1 = t.G1;//swapping group1
		a[in].G2 = t.G2;//swapping group2
	}
	//Function to get the Minimum heap item
	void getMin(HeapItem &h)
	{
		h.distance = heap[0].distance;//storing distance in passed object
		h.G1 = heap[0].G1;//storing group1 in passed object
		h.G2 = heap[0].G2;//storing group2 in passed object
	}
	//Function to delete Minimum heap item
	void deleteMin()
	{
		MySwap(heap, 0, heap.size()-1);//swapping minimum item with last item
		heap.pop_back();//removing the last item
		ReheapDown(0, (heap.size() / 2) - 1);//sorting heap from top to bottom
	}
	//Function to sort heap from top to bottom
	void ReheapDown(int node, int last)
	{
		int min, lc = (2 * node) + 1, rc = (2 * node) + 2;//calculating the index of left and right child
		if (node <= last)//min node is less than or equal to last index
		{
			if (node == last)//min node is equal to last index
			{
				min = lc;//min is equal to left child
			}
			else//min node is less than to last index
			{
				if (heap[lc].distance > heap[rc].distance)//comparing the distances of left and right child
				{
					min = rc;//min is equal to right child
				}
				else
				{
					min = lc;//min is equal to left child
				}
			}
			if (heap[node].distance > heap[min].distance)//comparing the distances of first and min node
			{
				MySwap(heap, node, min);//swapping the items of first and min node
				ReheapDown(min, last);//sorting heap from top to bottom
			}
		}
	}
	//Funtion to check  whether the heap is empty or not
	bool isEmpty() const
	{
		if (heap.size() == 0)//if size zero than empty
			return true;
		else//not empty
			return false;
	}
	//Destructor
	~MinHeap()
	{}
	//friend void CreateGroups(string fileName);
};

//Funtion to update matrix
void CreatingMatrix(MinHeap &heap1, vector<vector<int>> &mat, HeapItem &item)
{
	int r = 0, c = 0;
	for (int i = 0; i < heap1.heap.size(); i++)//loop to traverse from the heap
	{
		r = heap1.heap[i].G1 - 1;//initializing row for matrix
		c = heap1.heap[i].G2 - 1;//initializing col for matrix
		if (r != item.G2 - 1 || c != item.G2 - 1)
		{
			mat[r][c] = i;//storing the heap index in the matrix
		}
	}
}
//Fubntion to create groups
void CreateGroups(string fileName)
{
	char buff[5];
	int N = 0, M = 0, tGroup = 0;
	float dis = 0;
	Point p;
	vector<Point> v;//vector of points
	MinHeap h;//heap object
	HeapItem hItem;//heapitem object
	vector<vector<int>> matrix;//2D matrix
	vector<list<int>> l;//vector of link list
	ifstream fin;
	fin.open(fileName);
	if (fin.is_open())
	{
		//Inputting N and M
		fin.getline(buff, 5, '#');//getting the number of points
		N=atoi(buff);//storing the number of points
		fin.getline(buff, 5, '\n');//getting the number of groups
		M = atoi(buff);//storing the number of groups
		if (M == 0)//if number of groups are zero
		{
			cout << "Invalid Group No's 0!" << endl;//printing error message
			return;
		}
		if (N == 0)//if number of points are zero
		{
			cout << "Invalid Points No's 0!" << endl;//printing error message
			return;
		}
		if (M > N)//if number of groups are greater then total points
		{
			cout << "Number of groups are Greater than Total Points!" << endl;//printing error message
			return;
		}
		//inputing points
		while (!fin.eof())//loop until end of file
		{
			fin >> p.x;//get x point
			fin.ignore();
			fin >> p.y;//get y point
			v.push_back(p);//push the point in vector
		}
		tGroup = N;
		//creating heap
		for (int i = 0; i < v.size(); i++)//loop till the end of vector
		{
			for (int j = i+1; j < v.size(); j++)//loop till the end of vector
			{
				dis = sqrt(pow((v[j].x - v[i].x), 2) + pow((v[j].y - v[i].y), 2));//calculating distance
				hItem.distance = dis;//storing distance in heapitem
				hItem.G1 = i + 1;//storing goup1 in heapitem
				hItem.G2 = j + 1;//storing group2 in heapitem
				h.insert(hItem);//inserting heapitem in heap
			}
		}
		//initializing matrix and vector of link list
		matrix.resize(N);//declaring matrix of size n
		l.resize(N);//declaring vector of size n
		for (int k = 0; k < matrix.size(); k++)//loop till the size of matrix
		{
			matrix[k].resize(N);//declaring the 2D matrix
			l[k].push_back(k);//intializing the list of vector
		}
		//declaring matrix
		CreatingMatrix(h, matrix, hItem);
		//making groups
		while (tGroup!=M)//loop till total groups are not equal to required groups 
		{
			h.getMin(hItem);//getting minimum heap item
			h.deleteMin();//deleting the minimum item
			CreatingMatrix(h, matrix, hItem);//updating matrix
			if (l[hItem.G1 - 1].size() != 0 && l[hItem.G2 - 1].size() != 0)//checking in the vector whether the groups are already crated or not
			{
				l[hItem.G1 - 1].merge(l[hItem.G2 - 1]);//merging the groups
				for (int j = hItem.G2; j < N; j++)//loop till the number of points
				{
					int g2 = h.heap[matrix[hItem.G1 - 1][j]].G2;//storing group 2
					float min = sqrt(pow((v[g2 - 1].x - v[hItem.G1 - 1].x), 2) + pow((v[g2 - 1].y - v[hItem.G1 - 1].y), 2));//calculating distance
					list<int>::iterator ite = l[hItem.G1 - 1].begin();
					for (ite = l[hItem.G1 - 1].begin(); ite != l[hItem.G1 - 1].end(); ite++)//loop till the end of list
					{
						dis = sqrt(pow((v[g2 - 1].x - v[*ite].x), 2) + pow((v[g2 - 1].y - v[*ite].y), 2));//calculating distance
						if (dis < min)//checking the minimum distance
							min = dis;//storing the minimum distance
					}
					h.heap[matrix[hItem.G1 - 1][j]].distance = min;//updating the distance in heap 
				}
				tGroup--;//decrementing total groups
			}
			
		}
		//Printing groups
		int count = 1;
		for (int i = 0; i < l.size(); i++)//loop till the size of vector
		{
			list<int>::iterator ite = l[i].begin();
			if (l[i].size() != 0)//checking if there is a group or not
			{
				cout << "Group " << count << ": ";
				for (ite = l[i].begin(); ite != l[i].end(); ite++)//loop till the end of the list
				{
					cout << "(" << v[*ite].x << "," << v[*ite].y << ")  ";//printing the points in the groups
				}
				count++;
				cout << endl;
			}
		}
			for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout<<matrix[i][j]<<"\t";
		}
		cout<<endl;
	}
	}
	else
	{
		cout << "Could not open file!" << endl;
	}

}
int main()
{
	CreateGroups("p.txt");
	system("pause");
	return 0;
}