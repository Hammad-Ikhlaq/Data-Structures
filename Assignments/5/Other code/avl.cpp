#include <iostream>
#include <math.h>

int const MAXSTRING = 500;

template <class type>
void avltree<type>::printTree()
{
	myRect(0, 0, 800, 500, RGB(255, 255, 255), RGB(255, 255, 255));
	printPreorder(root, 0, 600, 10, 1);

}

//will print in preorder
template <class type>
void avltree<type>::printPreorder(avlnode<type> *n, int minx, int maxx, int y, int ht)
{
	if (!n) return;
	int width = 30;
	int down = 25;
	COLORREF red = RGB(255, 0, 0);
	COLORREF white = RGB(255, 255, 255);
	COLORREF black = RGB(0, 0, 0);
	COLORREF yellow = RGB(0, 255, 255);
	int x = (minx + maxx) / 2;

	if (n->child[LEFT])
		myLine(x, y, (x + minx) / 2, y + down, yellow);
	if (n->child[RIGHT])
		myLine(x, y, (x + maxx) / 2, y + down, yellow);


	char str[MAXSTRING];
	char str1[MAXSTRING];
	_itoa_s(n->data, str, 10);
	_itoa_s(n->height, str1, 10);
	strcat_s(str, "(");			//uncomment this line if you want to print the node data and its height
	strcat_s(str, str1);			//uncomment this line if you want to print the node data and its height
	strcat_s(str, ")");			//uncomment this line if you want to print the node data and its height
	COLORREF colour = black;

	myDrawText(x, y, 20, str, colour, white);

	//recursive
	printPreorder(n->child[LEFT], minx, x, y + down, ht + 1);
	printPreorder(n->child[RIGHT], x, maxx, y + down, ht + 1);
}


template <class type>
bool avltree<type>::createRoot(type item)
{
	root = new avlnode<type>;
	root->data = item;
	root->height = 0;
	return true;
}

template <class type>
bool avltree<type>::findInsertionPoint(stack<avlnode<type>*> &nodeStack, stack<int> &directionStack, type value)
{
	avlnode<type>* curr = root;
	while (curr && curr->data != value)
	{
		nodeStack.push(curr);
		if (curr->data > value)
		{
			directionStack.push(LEFT);
			curr = curr->child[LEFT];
		}
		else{
			directionStack.push(RIGHT);
			curr = curr->child[RIGHT];
		}
	}
	return curr;
	//here find the insertion point and the direction you traversed to reach this point;DONE
}
template <class type>
void avlnode<type>::changeHeight()
{
	if (!child[RIGHT] && !child[LEFT])
		height = 0;
	else if (!child[RIGHT])
		height = child[LEFT]->height + 1;
	else if (!child[LEFT])
		height = child[RIGHT]->height + 1;
	else
		height = max(child[RIGHT]->height, child[LEFT]->height) + 1;
}
template <class type>
int avlnode<type>::balanceFactor()
{
	int balanceFact = 0;
	if (!child[RIGHT] && !child[LEFT])
		balanceFact = 0;
	else if (!child[RIGHT])
		balanceFact = (-1) - child[LEFT]->height;
	else if (!child[LEFT])
		balanceFact = child[RIGHT]->height + 1;
	else
		balanceFact = (child[RIGHT]->height) - (child[LEFT]->height);
	
		return balanceFact;
}
//check the 2 single rotate cases here
template <class type>
void avltree<type>::rotateSingle(stack<avlnode<type>*> &nodeStack, stack<int> &directionStack, avlnode<type> *n, int nChildDirection)
{
	avlnode<type> *parent = NULL;	//parent of n
	int pChildDirection = 0;	//direction (between parent and n)
	nodeStack.pop(parent);		//parent is NULL if stack is empty.  No need to set anything here or check if stack is empty
	directionStack.pop(pChildDirection);
	if (nChildDirection == RIGHT)
		rotateLeft(n, parent, pChildDirection);
	else
		rotateRight(n, parent, pChildDirection);
	}

//check the 2 double rotate cases here
template <class type>
void avltree<type>::rotateDouble(stack<avlnode<type>*> &nodeStack, stack<int> &directionStack, avlnode<type> *n, int nChildDirection)
{
	avlnode<type> *child = n->child[nChildDirection];
	nodeStack.push(n);
	directionStack.push(nChildDirection);
	rotateSingle(nodeStack, directionStack, child, !nChildDirection);
	rotateSingle(nodeStack, directionStack, n, nChildDirection);
}

//current is the node whose balance is out of order
//parent is the parent of current
//don't forget to change heights
//also don't forget to change the root if needed
template <class type>
bool avltree<type>::rotateLeft(avlnode<type> *current, avlnode<type>*parent, int pChildDirection)
{
	if (current->data == root->data && !parent) //incase of root , parent is NULL
	{
		avlnode<type>* temp = root;
		root = root->child[RIGHT];
		if (root->child[LEFT])
			temp->child[RIGHT] = root->child[LEFT];
		else
			temp->child[RIGHT] = NULL;
		root->child[LEFT] = temp;
		temp->changeHeight();
		root->changeHeight();
	}
	else
	{
		avlnode<type>* right = current->child[RIGHT];
		parent->child[pChildDirection] = right;
		avlnode<type>*RL = NULL;
		if (right)
			RL = right->child[LEFT];
		current->child[RIGHT] = RL;
		if (right)
		{
			right->child[LEFT] = current;
		}
		current->changeHeight();
		parent->changeHeight();
	}
	return true;
}


//current is the node whose balance is out of order
//parent is the parent of current
//don't forget to change heights
//also don't forget to change the root if needed
template <class type>
bool avltree<type>::rotateRight(avlnode<type> *current, avlnode<type>*parent, int pChildDirection)
{
	if (current->data == root->data && !parent) //incase of root , parent is NULL
	{
		avlnode<type>* temp = root;
		root = root->child[LEFT];
		if (root->child[RIGHT])
			temp->child[LEFT] = root->child[RIGHT];
		else
			temp->child[LEFT] = NULL;
		root->child[RIGHT] = temp;
		temp->changeHeight();
		root->changeHeight();
	}
	else{
		avlnode<type>* left = current->child[LEFT];
		parent->child[pChildDirection] = left;
		avlnode<type>*LR = NULL;
		if (left)
			LR = left->child[RIGHT];
		current->child[LEFT] = LR;
		if (left)
		{
			left->child[RIGHT] = current;
		}
		current->changeHeight();
		parent->changeHeight();
	}
	return true;
}
template <class type>
bool avltree<type>::insert(type item)
{
	stack <avlnode<type>*> nodeStack;   //both stacks to be filled by findInsertionPoint
	stack <int> directionStack;
	int pChildDirection = 0;
	avlnode<type> *parent = nullptr, *current = nullptr;
	bool done = false;
	//STEP 1:  check if no root exists then create it and exit the function
	if (!root)
	{
		done = createRoot(item);
	}
	else
	{
		//STEP 2: call findInsertionPoint.  If insertionPoint not found exit the function
		bool check = true;
		check = findInsertionPoint(nodeStack, directionStack, item);
		//STEP 3: allocate memory for a new node
		if (!check)
		{
			avlnode<type> *newNode = new avlnode<type>(item);
			done = true;
			nodeStack.pop(parent);
			directionStack.pop(pChildDirection);
			parent->child[pChildDirection] = newNode;
			parent->changeHeight();
			//STEP 4: pop the parent and insert the newNode in its correct place in the tree
			//you can do something like parent->child[pChildDirection] = newNode; 
			//the parent and pChildDirection should be popped from stack

			//STEP 5: now adjust all the heights and perform rotations in all ancestors.  All ancestors are stored on the stack
			current = parent;			//isnertion point is the current node
			int currChildDirection = pChildDirection,balanceFact = 0;
			while (!nodeStack.empty())
			{
				nodeStack.pop(parent);//the parent of current node 
				directionStack.pop(pChildDirection);
				parent->changeHeight();//update height of parent
				balanceFact = parent->balanceFactor();
				if (balanceFact != 0 && balanceFact != -1 && balanceFact != 1 /* check wrong balance factor of parent here */)
				{
					if (currChildDirection == pChildDirection)
						rotateSingle(nodeStack, directionStack, parent, pChildDirection); // parent is passed as it is node out of balance;
					else
						rotateDouble(nodeStack, directionStack, parent, pChildDirection);
					//check if you have to perform single or double rotation
					//call the functions corresponding to single rotation or double rotation. 
					//you need around 4-6 lines of code here
				}
				currChildDirection = pChildDirection;
				current = parent;
			}
		}
	}
	return done;
}


template <class type>
avlnode<type>* avltree<type>::findNode(type item, stack<avlnode<type>*> &nodeStack, stack<int> &directionStack)
{
	avlnode<type>* curr = root;
	while (curr && curr->data!=item)
	{
		nodeStack.push(curr);
		if (item > curr->data)
		{
			directionStack.push(RIGHT);
			curr = curr->child[RIGHT];
		}
		else
		{
			directionStack.push(LEFT);
			curr = curr->child[LEFT];
		}
	}
	//required by deleteKey function
	//return pointer to node to be deleted
	return curr;
}

template <class type>
type avltree<type>::findHighestKeyOnLeft(avlnode<type>*n)
{
	avlnode<type>* temp = n->child[LEFT];
	type val = temp->data;
	bool found = false;
	while (!found && temp)
	{
		if (val < temp->data)
			val = temp->data;
		if (temp->child[RIGHT])
			temp = temp->child[RIGHT];
		else
			found = true;
	}
	return val;
	//return the data as the highest key on the left of n
}

template <class type>
bool avltree<type>::deleteKey(type item)
{
	bool found = false;
	int pChildDirection = 0;
	avlnode<type>*parent = NULL;
	stack <avlnode<type>*> nodeStack;
	stack <int> directionStack;
	avlnode<type> *n = nullptr;
	n = findNode(item, nodeStack, directionStack);
	bool  done = false;
	//STEP 1: call find node to find the node that stores the key to be deleted and store that pointer in n
	//the findNode function should also fill out the ancestor node pointers and the direction variables
	//return false if node is not found

	//STEP 2: check if you are deleting the root and its the only node in the tree
	//deleting root
	if (n)
	{
		if (n == root && n->totalChild() == 0)
		{
			delete root;
			root = NULL;
			done = true;
		}
		//STEP 3: check if n has two child nodes.  Call findHighetKeyOnLeft (saving its key) and call delteKey recursively
		if (n->totalChild() == 2)
		{
			type val = findHighestKeyOnLeft(n);
			deleteKey(val);
			n->data = val;
			n->changeHeight();
			done = true;
		}

		//STEP 4 check if only one child
		//first check the parent and direction in which n is located
		nodeStack.peak(parent);
		directionStack.peak(pChildDirection);
		//STEP 5: deleting node with one child
		if (!done)
		{
			if (parent && n->totalChild() == 1)
			{
				if (n->child[LEFT])
					parent->child[pChildDirection] = n->child[LEFT];
				else
					parent->child[pChildDirection] = n->child[RIGHT];
				parent->changeHeight();
				delete n;
				n = NULL;
			}

			else if (parent)//deleting the leaf
			{
				if (pChildDirection == LEFT)
					parent->child[LEFT] = NULL;
				else
					parent->child[RIGHT] = NULL;
				parent->changeHeight(); //if parent had only one child, the height of the parent would change to 0 making it a leaf node.
				delete n;
				n = NULL;
				//set the correct links of parent to null
				//don't forget to deallocate n
			}
			else if (!parent)  //deleting root with one child
			{
				avlnode<type> *temp = n->child[pChildDirection];
				delete n;
				n = NULL; // to make dispalyTree work properly
				root = temp; // if we just change n here, root will be pointing to garbage value;
				// no need to change height here, the new node will have it's own height, rather than the height of the root.
				//make sure you reset the root here
				//deallocate n
			}
			//STEP 6: update the heights and perform rotations if necessary
			avlnode<type> * current = NULL;
			int currChildDirection = 0;
			while (!nodeStack.empty())
			{
				nodeStack.pop(current);	//parent of deleted node
				directionStack.pop(currChildDirection);
				current->changeHeight();
				if (current->balanceFactor() != 0 && current->balanceFactor() != -1 && current->balanceFactor() != 1)
				{
					balance(nodeStack, directionStack, current, currChildDirection);
					//call the balance method here
				}
			}
		}
		found =  true;
	}
	return found;
}

//this function will balance the current node 
template <class type>
void avltree<type>::balance(stack <avlnode<type>*> nodeStack, stack <int> directionStack, avlnode<type>*current, int currChildDirection)
{
	//these variables would be required.  INITIALIZE THEM YOURSELF
	avlnode<type> *child = NULL, *grandChild = NULL, *parent = NULL;
	int childDir = LEFT, grandChildDir = LEFT, pChildDirection = 0;
	int htChildLeft = -1, htChildRight = -1;
	int htgrandChildLeft = -1, htgrandChildRight = -1;
	parent = current;
	pChildDirection = currChildDirection;
	childDir = !currChildDirection;
	child = parent->child[childDir];
	if (parent->child[LEFT])
		htChildLeft = parent->child[LEFT]->height;
	if (parent->child[RIGHT])
		htChildRight = parent->child[RIGHT]->height;
	if (child->child[RIGHT])
		htgrandChildRight = child->child[RIGHT]->height;
	if (child->child[LEFT])
		htgrandChildLeft = child->child[LEFT]->height;
	if (htgrandChildLeft >= htgrandChildRight)
	{
		grandChild = child->child[LEFT];
		grandChildDir = LEFT;
	}
	else
	{
		grandChild = child->child[RIGHT];
		grandChildDir = RIGHT;
	}
	if (childDir == grandChildDir)
		rotateSingle(nodeStack, directionStack, parent, childDir); // parent is passed as it is node out of balance;
	else
		rotateDouble(nodeStack, directionStack, parent, childDir); 
	parent->changeHeight();
	child->changeHeight();
	grandChild->changeHeight();
	
}
//code will not check that leftVal is less than root and rightVal > rootVal.  But you can print the tree and check it
template <class type>
void avltree<type>::createSampleTree(type rootValue, type leftValue, type rightValue)
{
	root = new avlnode<type>(rootValue);
	root->child[LEFT] = new avlnode<type>(leftValue);
	root->child[RIGHT] = new avlnode<type>(rightValue);

}
template <class type>
avltree<type>::avltree(const avltree<type>& tree)
{
	root  = copyConst(tree.root);
}
template <class type>
avlnode<type>* avltree<type>::copyConst(avlnode<type>* curr)
{
	avlnode<type>* temp = NULL;
	if (curr)
	{
		temp = new avlnode<type>;
		temp->data = curr->data;
		temp->height = curr->height;
		temp->child[LEFT] = copyConst(curr->child[LEFT]);
		temp->child[RIGHT] = copyConst(curr->child[RIGHT]);
	}
	return temp;
}
template <class type>
void avltree<type>::deleteTree()
{
	deleteTree(root);
}
template <class type>
void avltree<type>::deleteTree(avlnode<type>*& curr)
{
	if (curr)
	{
		deleteTree(curr->child[LEFT]);
		deleteTree(curr->child[RIGHT]);
		delete curr;
		curr = NULL;
	}
}
template <class type>
avltree<type>::~avltree()
{
	deleteTree();
}
template<class type>
avlnode<type>::~avlnode()
{
	//no de-allocations, hence empty
}
template<class type>
void avltree<type>::printAscending()
{
	printAscending(root);
}
template<class type>
void avltree<type>::printDescending()
{
	printDescending(root);
}
template<class type>
void avltree<type>::printAscending(avlnode<type>*curr)
{

	if (curr)
	{
		if (curr->child[LEFT])
			printAscending(curr->child[LEFT]); 
		cout << curr->data << endl;
		if (curr->child[RIGHT])
			printAscending(curr->child[RIGHT]);
	}
}
template<class type>
void avltree<type>::printDescending(avlnode<type>*curr)
{
	if (curr)
	{
		if (curr->child[RIGHT])
			printDescending(curr->child[RIGHT]);
		cout << curr->data << endl;
		if (curr->child[LEFT])
			printDescending(curr->child[LEFT]);
	}
}