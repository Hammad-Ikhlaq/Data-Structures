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
			d = s[strptr - 1];
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
template<typename T>
struct AVLnode
{
	T data;
	AVLnode* left;
	AVLnode*right;
	int height;
};

template<typename T>
class AVL
{
private:
	AVLnode<typename T>*root;

public:
	AVL()
	{
		root = nullptr;
	}
	~AVL()
	{
		DestroyTree(root);
	}
	int	geth(AVLnode<typename T>*n)
	{
		if (n == nullptr)
		{
			return 0;
		}
		return n->height;
	}
	int max(int a, int b)
	{
		if (a > b)
		{
			return a;
		}
		return b;
	}
	void RotatetoRight(AVLnode<typename T>*&X)
	{
		AVLnode<typename T>*Y = X->left;
		X->left = Y->right;
		Y->right = X;
		X->height = 1 + max(geth(X->left), geth(X->right));
		Y->height = 1 + max(geth(Y->left), geth(Y->right));
		X = Y;		//maintaining tree
	}
	void RotatetoLeft(AVLnode<typename T>*&X)
	{
		AVLnode<typename T>*Y = X->right;
		X->right = Y->left;
		Y->left = X;
		X->height = 1 + max(geth(X->left), geth(X->right));
		Y->height = 1 + max(geth(Y->left), geth(Y->right));
		X = Y;		//maintaining tree
	}
	void DRotatetoRight(AVLnode<typename T>*&X)
	{
		RotatetoLeft(X->left);
		RotatetoRight(X);
	}
	void DRotatetoLeft(AVLnode<typename T>*&X)
	{
		RotatetoRight(X->right);
		RotatetoLeft(X);
	}
	AVLnode<typename T>*Search(AVLnode<typename T>*root, T d)
	{
		while (root != nullptr || root->data != d)
		{
			if (root->data > d)
			{
				root = root->left;
			}
			else
			{
				root = root->right;
			}
		}
		return root;
	}
	bool Insert(AVLnode<typename T>*&r, T d)
	{
		Stack <AVLnode<typename T>*> record;
		AVLnode < typename T>*curr = r;
		if (r==nullptr)
		{
			curr = new AVLnode<typename T>;
			curr->data = d;
			curr->left = curr->right = nullptr;
			curr->height = 1;
			return true;
		}

		while ((curr->data != d) || (curr != nullptr))	//finding the insertion position
		{
			record.push(curr);
			if (curr->data > d)
			{
				curr = curr->left;
			}
			else
			{
				curr = curr->right;
			}
		}
		if (curr == nullptr)
		{
			curr = new AVLnode<typename T>;
			curr->data = d;
			curr->left = curr->right = nullptr;
			curr->height = 1;
			while (curr->data != root->data)	//it is to check the balancing of the whole tree
			{
				record.pop(curr);
				if (geth(curr->left) - geth(curr->right) == 2)
				{
					if (curr->left->data > d)	//case 1
					{
						RotatetoRight(curr);
					}
					else
					{
						DRotatetoRight(curr);//case 3
					}
				}
				if (geth(curr->left) - geth(curr->right) == -2)
				{
					if (curr->left->data > d)	//case 2
					{
						RotatetoLeft(curr);
					}
					else						//case 4
					{
						DRotatetoLeft(curr);
					}
				}
			}
			return true;
		}
		if (r->data == d)
		{
			return false;
		}

	}
	bool Remove(AVLnode<typename T>*&r, T d)
	{
		if (r != nullptr)
		{
			AVLnode<typename T>*curr = r;
			Stack <AVLnode<typename T>*> record;
			while (curr != nullptr || curr->data != d)
			{
				record.push(curr);//memorizing the path
				if (curr->data > d)
				{
					curr = curr->left;
				}
				if (curr->data < d)
				{
					curr = curr->right;
				}
			}
			if (curr == nullptr)
			{
				return false;
			}
			if (curr->data == d)
			{
				if (curr->left == nullptr&& curr->right == nullptr)// case for leaf node
				{
					delete curr;
					curr = nullptr;
					return true;
				}
				AVLnode<typename T>*temp = curr;
				if (curr->left != nullptr&&curr->right == nullptr)// case for node with one child
				{
					curr = curr->left;
					delete temp;
					return true; //check it
				}
				if (curr->left == nullptr&&curr->right != nullptr)// case for node with one child
				{
					curr = curr->right;
					delete temp;
					return true;
				}
				else// case for node with both child
				{
					curr->data = removePredecessor(curr);
					return true;
				}
				while (!(record.IsEmpty()))
				{
					AVLnode < typename T>*curr2;
					AVLnode<typename T>*y;
					record.pop(curr2);
					if ((geth(curr2->left) - geth(curr2->right) == 2) || (geth(curr2->left) - geth(curr2->right) == -2))//identifying x
					{
						if ((geth(curr2->left) > geth(curr2->right)))//dealing y as a left child
						{
							y = curr2->left;
							if (0 == (geth(y->left) - geth(y->right)))//case 1
							{
								if (y->right->data>d)
								{
									RotatetoLeft(y);
								}
								else
								{
									DRotatetoLeft(y);
								}
							}
							else if ((geth(curr2->left) - geth(curr2->right) + 1) == (geth(y->left) - geth(y->right)))//plus 1 is for condition before deletion //case 2
							{
								if (y->right->data>d)
								{
									RotatetoLeft(y);
								}
								else
								{
									DRotatetoLeft(y);
								}
							}
							else if ((geth(curr2->left) - geth(curr2->right) + 1) == (-1 * (geth(y->left) - geth(y->right))))//plus 1 is for condition before deletion //case 3
							{
								if (y->right->data>d)
								{
									RotatetoLeft(y);
								}
								else
								{
									DRotatetoLeft(y);
								}
							}
						}
						else
						{
							y = curr2->right;
							if (0 == (geth(y->left) - geth(y->right)))//case 1
							{
								if (y->left->data>d)
								{
									RotatetoRight(y);
								}
								else
								{
									DRotatetoRight(y);
								}
							}
							else if ((geth(curr2->left) - geth(curr2->right) + 1) == (geth(y->left) - geth(y->right)))//plus 1 is for condition before deletion //case 2
							{
								if (y->left->data>d)
								{
									RotatetoRight(y);
								}
								else
								{
									DRotatetoRight(y);
								}
							}
							else if ((geth(curr2->left) - geth(curr2->right) + 1) == (-1 * (geth(y->left) - geth(y->right))))//plus 1 is for condition before deletion //case 3
							{
								if (y->left->data>d)
								{
									RotatetoRight(y);
								}
								else
								{
									DRotatetoRight(y);
								}
							}
						}
					}

				}
			}
		}
	}
	T removePredecessor(AVLnode<typename T>*r)
	{
		AVLnode<typename T>*par = r;
		AVLnode<typename T>*curr = r->left;
		bool flag = false;
		while (curr->right != nullptr)
		{
			par = curr;
			curr = curr->right;
			flag = true;
		}
		return curr->data;
	}

	void DestroyTree(AVLnode<typename T>*r)
	{
		AVLnode<typename T>*curr=r;
		AVLnode<typename T>*temp;
		Stack<AVLnode<typename T>*> record;
		while (r!=null)//while root is not null
		{
			record.push(r)
			curr = curr->left;
			while (curr != nullptr)//while left child is not null
			{
				record.push(temp)
					curr = curr->left;
			}
			record.pop(temp);
			delete curr;
			if (curr->right != nullptr)
			{
				record.push(temp)
					curr = curr->left;
			}
			record.pop(temp);
			delete curr;
		}


	}
	AVLnode<typename T>*Search(T d)
	{
		return Search(root, d);
	}
	bool Insert(T d)
	{
		return Insert(root, d);
	}
	bool Remove(T d)
	{
		return Remove(root, d);
	}
	void Inorder()
	{
		Inorder(root);
	}
	void Preorder()
	{
		Preorder(root);
	}
	void Postorder()
	{
		Postorder(root);
	}
	void Inorder(AVLnode<typename T>*r)
	{
		if (r != nullptr)
		{
			Inorder(r->left);
			cout << r->data << "  ";
			Inorder(r->right);
		}
	}
	void Preorder(AVLnode<typename T>*r)
	{
		if (r != nullptr)
		{
			cout << r->data << "  ";
			Inorder(r->left);
			Inorder(r->right);
		}
	}
	void Postorder(AVLnode<typename T>*r)
	{
		if (r != nullptr)
		{
			Inorder(r->left);
			Inorder(r->right);
			cout << r->data << "  ";
		}
	}
};

int main()
{
	int choice, n;
	AVL<int> B;
	while (true)
	{

		cout << "What do you want to do\n1)Insert a value\n2)Remove a value\n3)Search a value\n4)Print the tree in infix order\n5)Print the tree in prefix order\n6)Print the tree in postfix order\n";
		cin >> choice;
		if (choice == 1)
		{
			cout << "\nWrite the data of the inserted child\n";
			cin >> n;
			B.Insert(n);
		}
		else if (choice == 2)
		{
			cout << "\nWrite the data you want to delete\n";
			cin >> n;
			if (B.Remove(n))
			{
				cout << n << " has been removed from the tree\n";
			}
			else
			{
				cout << "The data you entered is not in the tree\n";
			}
		}
		else if (choice == 3)
		{
			cout << "\nWrite the data you want to search\n";
			cin >> n;
			if (B.Search(n) != nullptr)
			{
				cout << n << " is in the tree\n";
			}
			else
			{
				cout << "The data you entered is not in the tree\n";
			}
		}
		else if (choice == 4)
		{
			B.Inorder();
			cout << endl;
		}
		else if (choice == 5)
		{
			B.Preorder();
			cout << endl;
		}
		else if (choice == 6)
		{
			B.Postorder();
			cout << endl;
		}

	}

	system("pause");
	return 0;
}