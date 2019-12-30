#ifndef AVL_H
#define AVL_H

#include <Windows.h>

const int LEFT = 0;
const int RIGHT = 1;
const int TWO = 2;
template <class type> class avlnode;
template <class type> class avltree;

template <class type>
class avlnode
{
	//methods
	avlnode(){ child[LEFT] = nullptr; child[RIGHT] = nullptr; height = 0; }
	avlnode(type value){ child[LEFT] = nullptr; child[RIGHT] = nullptr; height = 0; data = value; }
	int totalChild(){ int count = 0; if (child[LEFT]) count++; if (child[RIGHT]) count++; return count; }
	int childDirection(){ if (child[LEFT]) return LEFT; if (child[RIGHT])return RIGHT; return -1; }
	int balanceFactor();	//the difference in height of right and left child.  Should be O(1)
	void changeHeight();	//here get the height of left child and right child and take the max.  Should be O(1)
	~avlnode();
	//data members
	type data;
	avlnode *child[TWO];
	int height;

	friend class avltree<type>;
};

template <class type>
class avltree
{
public:
	//constructor
	avltree(){ root = nullptr; }
	avltree(const avltree<type>& tree);
	void printTree();
	bool deleteKey(type item);
	bool insert(type item);
	void createSampleTree(type rootValue, type leftValue, type rightValue);
	void printAscending();
	void printDescending();
	//destructor...you must implement the destructor also
	void deleteTree(); //implemet this too
	~avltree();
private:
	void printDescending(avlnode<type>*curr);
	void printAscending(avlnode<type>*curr);
	void deleteTree(avlnode<type>*& curr); //private method to help deleteTREE 
	avlnode<type>* copyConst(avlnode<type>* curr); //Private method used to help copy constructor
	bool rotateLeft(avlnode<type> *p, avlnode<type>*g, int dirg);
	bool rotateRight(avlnode<type> *p, avlnode<type>*g, int dirg);
	void rotateSingle(stack<avlnode<type>*> &nodeStack, stack<int> &directionStack, avlnode<type> *n, int nChildDirection);
	void rotateDouble(stack<avlnode<type>*> &nodeStack, stack<int> &directionStack, avlnode<type> *n, int nChildDirection);
	void balance(stack <avlnode<type>*> nodeStack, stack <int> directionStack, avlnode<type>*current, int currChildDirection);

	void printPreorder(avlnode<type> *n, int minx, int maxx, int y, int ht);

	bool createRoot(type item);
	bool findInsertionPoint(stack<avlnode<type>*> &nodeStack, stack<int> &directionStack, type value);
	type findHighestKeyOnLeft(avlnode<type> *n);
	avlnode<type>* findNode(type item, stack<avlnode<type>*> &nodeStack, stack<int> &directionStack);
	bool adjustNode(avlnode<type>*n, stack<avlnode<type>*> &nodeStack, stack<int> &directionStack);



private:
	avlnode<type> *root;
};

#include "avl.cpp"

#endif