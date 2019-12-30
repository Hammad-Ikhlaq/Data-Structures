#include <iostream>

using namespace std;
template <typename T>
class BST;
template < typename T>
class Node { //Node class
	T data;
	Node* right;
	Node* left;
	Node* nextInOrder;
public:
	Node() { //default constructor
		right = nullptr;
		left = nullptr;
		nextInOrder = nullptr;
	}

	friend class BST<T>; //since the data members are private
};
template <typename T>
class BST { //Stackless BST Class
private:
	Node<T>* root;
	bool IsSuccessor;
public:
	BST() { //default constructor
		root = nullptr;
		IsSuccessor = true;
	}
	Node<T>* gettothenumber(Node<T>*curr, Node<T>* temp) { //function to get to a specific node
		if (curr != nullptr) {
			if (temp->data == curr->data) { //if the given data is found in the node
				return temp;
			}
			else if (curr->data > temp->data) { //if data is smaller
				return gettothenumber(curr, temp->right);
			}
			else { //if data is greater
				return gettothenumber(curr, temp->left);
			}
		}
	}
	Node<T>* Rgettothenumber(T d, Node<T>* temp) { //function to get to a specific node with different parameters using nextInOrder
		if (temp->nextInOrder != nullptr) { //if temp is not the greatest value
			if (temp->nextInOrder->data == d) { 
				return temp;
			}
			else {
				temp = Rgettothenumber(d, temp->nextInOrder); //function called to get to the node
			}
		}
		
	}
	void copynext(const BST&obj,Node<T>*curr) { //for copying the nextInOrder list
		if (curr == nullptr) {
			return;
		}
		else {
			Node<T>* temp = gettothenumber(curr, obj.root); //for the tree
			
			Node<T>* temp2 = gettothenumber(temp->nextInOrder, root); //for nextInOrder
			
			curr->nextInOrder = temp2; 
			copynext(obj, curr->left); //recursive call for left node
			copynext(obj, curr->right); //recursive call for right node
		}

	}
	void copy(Node<T>*&temp,Node<T>* temp2) { //wrapper function for copy 
		if (temp2 == nullptr) { 
			temp = nullptr;
			return;
		}
		else {
			temp = new Node<T>;
			temp->data = temp2->data;
			
			copy(temp->left, temp2->left);
			copy(temp->right, temp2->right);
		}
	}
	BST(const BST&obj) { //copy constructor
		if (obj.root == nullptr) {//if the object is empty
			root = nullptr;
		}
		else {
			copy(root, obj.root);

			copynext(obj, root);
			if (obj.IsSuccessor == true) {
				Node<T>* temp = getmax();
				temp->nextInOrder = nullptr;
			}
			else {
				Node<T>* temp = getmin();
				temp->nextInOrder = nullptr;
			}
			IsSuccessor = obj.IsSuccessor; //specifying the value of issuccessor
		}
	}
	BST& operator=(const BST& obj) { //assignment operator
		if (obj.root == nullptr) { //if the object is empty
			root = nullptr;
			return *this;
		}
		copy(root, obj.root);
		
		copynext(obj, root);

		if (obj.IsSuccessor==true) {
			Node<T>* temp = getmax();
			temp->nextInOrder = nullptr;
		}
		else {
			Node<T>* temp = getmin();
			temp->nextInOrder = nullptr;
		}
		IsSuccessor = obj.IsSuccessor; //specifying the value of issuccessor
		return*this;
	}
	
	Node<T>* getmin() { //function for getting the minimum node
		Node <T>* temp = root;
		if (temp != nullptr) {
			while (temp->left != nullptr) {
				temp = temp->left;
			}
			return temp;
		}
		else {
			return root;
		}
	}
	Node<T>* getmax() { //function for getting the maximum node
		Node<T>* temp = root;
		if (temp != nullptr) {
			
			while (temp->right != nullptr) {
				temp = temp->right;
			}
			return temp;
		}
		else {
			return root;
		}
	}
	void reversewrap(Node<T>*temp,Node<T>* curr,Node<T>*prev,Node<T>*next) { //recursive reverse
		if (curr == nullptr) {
			temp = prev;
			return;
		}
		else {
			next = curr->nextInOrder;
			curr->nextInOrder = prev;
			prev = curr;
			curr = next;
			reversewrap(temp, curr, prev, next);
		}
	}
	
	void reverse() { //recursive wrapper reverse
		Node<T>* prev = nullptr;
		Node<T>* next = nullptr;
		if (IsSuccessor == true) { //if issuccessor is true
			Node<T>* temp = getmin();
			Node<T>* curr = temp;
			reversewrap(temp, curr, prev, next);
		}
		else { //if issuccessor is false
			Node<T>* temp = getmax();
			Node<T>* curr = temp;
			reversewrap(temp, curr, prev, next);
		}
		
		IsSuccessor = !IsSuccessor;
	}
	
	bool insert(T d) { //function for inserting data into the tree
		Node<T>* temp = root; //the new node we will make
		Node<T>* parent = root; //keeps track of parent
		Node<T>* successor = getmax(); //temporarily putting the maximum value for successor
		Node<T>* predeccessor = getmin();
		if (IsSuccessor == true) { //if successor is true
			if (temp == nullptr) { //if temp is root and the root is null
				Node<T>* temp2 = new Node<T>;
				temp2->data = d;
				temp2->left = nullptr;
				temp2->right = nullptr;
				temp2->nextInOrder = nullptr;
				root = temp2;
			}

			else { // for any other case
				while (temp != nullptr) { //starting the traversal
					if (temp->data == d) { //if d is already present
						return false;
					}
					else if (temp->data < d) { //if d is greater
						if (temp->data > d && successor->data > temp->data) {
							successor = temp;
						}
						parent = temp;
						temp = temp->right;
					}
					else if (temp->data > d) { //if d is smaller
						if (temp->data > d && successor->data > temp->data) {
							successor = temp;
						}
						parent = temp;
						temp = temp->left;
					}
				}

				if (temp == nullptr) { //the place for the data to be inserted has been found
					Node<T>* temp2 = new Node<T>;
					temp2->left = nullptr;
					temp2->right = nullptr;
					temp2->data = d;
					if (root->left == nullptr && root->right == nullptr) { //if only root is present 
						if (d > root->data) { //if the data is greater than the root data
							temp2->nextInOrder = nullptr;
							root->nextInOrder = temp2;
							root->right = temp2;

						}
						else { //if the smaller than the root data
							root->left = temp2;
							temp2->nextInOrder = root;

						}
					}
					else if (d > root->data) { //if d is greater than root data
						if (d > parent->data) { //if d is greater tha parent data
							if (successor->data > temp2->data) { //if successor is greater than the data
								temp2->nextInOrder = successor;
							}
							else {
								temp2->nextInOrder = nullptr;
							}
							parent->nextInOrder = temp2;
							parent->right = temp2;

						}
						else if (d < parent->data) { //if data is smaller than the parent data
							parent->left = temp2;
							temp2->nextInOrder = parent;
						

							Node<T>* curr = root;
							while (curr->left != nullptr) {
								curr = curr->left;
							}
							while (curr->nextInOrder != parent) {
								curr = curr->nextInOrder;
							}
							if (curr->data != d) {
								curr->nextInOrder = temp2;
							}

						}
					}
					else if (d < root->data) { //if d is less than root data
						if (d < parent->data) { //if d is less than parent data
							parent->left = temp2;
							temp2->nextInOrder = parent;
						
							Node<T>* curr = root;
							while (curr->left != nullptr) {
								curr = curr->left;
							}
							while (curr->nextInOrder != temp2->nextInOrder) {
								curr = curr->nextInOrder;
							}
							if (curr->data != d) {
								curr->nextInOrder = temp2;
							}
						}
					else if (d > parent->data) { //if d is greater than parent data
						parent->right = temp2;
						temp2->nextInOrder = successor;
						if (parent->nextInOrder != nullptr) {
							if (parent->nextInOrder->data == successor->data) {

								parent->nextInOrder = temp2;
							}
						}

					}
				}
				}
			}
		}
		//FOR REVERSE ORDER
		else {
			if (temp == nullptr) { //starting with the traversal
				Node<T>* temp2 = new Node<T>;
				temp2->data = d;
				temp2->left = nullptr;
				temp2->right = nullptr;
				temp2->nextInOrder = nullptr;
				root = temp2;
			}

			else {
				while (temp != nullptr) { //while the place for insertion is not found
					if (temp->data == d) { //if the number is already present
						return false;
					}
					else if (temp->data < d) { //d is greater
						if (temp->data < d && predeccessor->data < temp->data) {
							predeccessor = temp;
						}
						parent = temp;
						temp = temp->right;
					}
					else if (temp->data > d) { //d is smaller
						if (temp->data < d && predeccessor->data < temp->data) {
							predeccessor = temp;
						}
						parent = temp;
						temp = temp->left;
					}
				}

				if (temp == nullptr) { //if the place for insertion has been found
					Node<T>* temp2 = new Node<T>;
					temp2->left = nullptr;
					temp2->right = nullptr;
					temp2->data = d;

					if (root->left == nullptr && root->right == nullptr) { //if there is no node other than root
						if (d > root->data) { //if d is greater than root data
							temp2->nextInOrder = root;
							root->nextInOrder = nullptr;
							root->right = temp2;

						}
						else { //if d is less than root data
							root->left = temp2;
							root->nextInOrder = temp2;

						}
					}
					else if (d > root->data) { // if is greater than root data
						if (d > parent->data) { //if d is greater than parent data
							if (predeccessor->data < temp2->data) { 
								temp2->nextInOrder = predeccessor;
							}
							else {
								temp2->nextInOrder = nullptr;
							}
							temp2->nextInOrder = parent;
							parent->right = temp2;
						}
						
						else if (d < parent->data) { //if data is smaller than parent data
							parent->left = temp2;
							temp2->nextInOrder = parent->nextInOrder;
							parent->nextInOrder = temp2;
							Node<T>* curr = root;
							while (curr->right != nullptr) {
								curr = curr->right;
							}
							while (curr->nextInOrder != temp2->nextInOrder) {
								curr = curr->nextInOrder;
							}
							if (curr->data != d) {
								curr->nextInOrder = temp2;
							}
							
						}
						}
						else if (d < root->data) { //if d is less than root data
							if (d < parent->data) { //if d is smaller than parent data
								parent->left = temp2;
								Node<T>* temp3 = parent->nextInOrder;
								parent->nextInOrder = temp2;
								temp2->nextInOrder = temp3;
								
								
							}
							else if (d > parent->data) { //if d is greater than parent data
								parent->right = temp2;
								temp2->nextInOrder = parent;
								Node<T>* curr = root;
								while (curr->right != nullptr) {
									curr = curr->right;
								}
								while (curr->nextInOrder != parent) {
									curr = curr->nextInOrder;
								}
								if (curr->data != d) {
									curr->nextInOrder = temp2;
								}
							
							}
						}

					
				}

			}
		}
		return true;
	}
	void Print() { //function that prints the tree using nextInOrder list
		if (root == nullptr) { //if the tree is empty
			cout << "The tree is empty." << endl;
			return;
		}
		if (IsSuccessor == true) { //if the tree isn't reversed
			Node<T>* temp = root;
			while (temp->left != nullptr) {
				temp = temp->left;
			}
			while (temp != nullptr) {
				cout << temp->data << " ";
				temp = temp->nextInOrder;
			}
		}
		else { //if the tree is reversed
			Node<T>* temp = root;
			while (temp->right != nullptr) {
				temp = temp->right;
			}
			while (temp != nullptr) {
				cout << temp->data << " ";
				temp = temp->nextInOrder;
			}
		}
	}
	T findmax(Node<T>* t) { //function for finding the maximum data
		while (t->right) {
			t = t->right;
		}
		return t->data;
	}
	Node<T>* getParentNode(Node<T>* temp,Node<T>*r) { //function for getting the parent node
		if (r->left == temp || r->right == temp) {
			return r;
		}
		else {
			if (r->data > temp->data) {
				return getParentNode(temp, r->left);
			}
			else {
				return getParentNode(temp, r->right);
			}
		}

	}
	Node<T>* getparent(T d, Node<T>*temp){ //function for getting the parent node with different parameters
		if (temp != nullptr) {
			if (temp->left != nullptr) {


				if (temp->left->data == d) {
					return temp;
				}
			}
			 else if (temp->right != nullptr) {
				if (temp->right->data == d) {
					return temp;
				}
			}

			else {
				if (temp->data > d) {

					return getparent(d, temp->left);

				}
				else {
					return getparent(d, temp->right);
				}
			}
		}
	}
	void removewrap(T d, Node<T>*&r) { //resursive remove wrap
		if (r == nullptr) { //if node is null
			return;
		}
		
		if (d < r->data) { //if d is smaller than current node
			removewrap(d, r->left);
		}
		else if (d > r->data) { //if d is greater than current node
			removewrap(d, r->right);
		}
		else {
			if (r->left == nullptr && r->right == nullptr) { //if both right left are null
				delete r;
				r = nullptr;
			}
			else if (r->left != nullptr && r->right != nullptr) { //if both right left are not null
				r->data = findmax(r->left);
				removewrap(r->data, r->left);
				
			}

			else { //in any other case
				Node<T>* temp;
				if (r->left != nullptr) {
					temp = r->left;
					delete r;
					r = temp;
									}
				else {
					temp = r->right;
					delete r;
					r = temp;
				}
			}
		}
			
	}
	

	bool numberisthere(T d,Node<T>*temp) { //function to check whether or not the number is there recursively
		if (temp == nullptr) {
			return false;
		}
		if (temp->data == d) {
			return true;
		}
		else {
			if (d > temp->data) {
				return numberisthere(d, temp->right);
			}
			else {
				return numberisthere(d, temp->left);
			}
		}
	}
	void lookforsuccessor(Node<T>*&successor,Node<T>* temp, Node<T>* possible) { //function that looks for successor
		if (temp != nullptr) {
			if (possible == nullptr) {
				return;
			}


			else
				if (possible->data > temp->data && possible->data <= successor->data) {

					successor = possible;
				}
			if (temp->data < possible->data) {
				lookforsuccessor(successor, temp, possible->left);
			}
			else {
				lookforsuccessor(successor, temp, possible->right);
			}
		}
	}
	void lookforpredeccessor(Node<T>*& predeccessor, Node<T>* temp, Node<T>* possible) { //function that looks for predeccessor
		if (possible == nullptr) {
			return;
		}
		
		else
		if (possible->data < temp->data && possible->data > predeccessor->data) {
			predeccessor = possible;
		}
		
			if (temp->data > possible->data) {
				lookforpredeccessor(predeccessor, temp, possible->right);
			}
			else {
				lookforpredeccessor(predeccessor, temp, possible->left);
			}
		
	}
	void setsuccessorswrap(Node<T>*temp) { //wrapper function for setting successors/predeccessors
		Node<T>* successor;
		Node<T>* predeccessor;
		//primarily setting up the value of the successor/predecessor
		if (temp->right != nullptr) { 
			 successor = temp->right;
		}
		else {
			successor = getmax();
		}
		if (temp->left != nullptr) {
			 predeccessor = temp->left;
		}
		else {
			predeccessor = getmin();
		}
	    
			if (IsSuccessor == true) { //if the tree is not reversed
				if (temp==nullptr) { 
					return;
				}
				if (successor != nullptr) { //if successor is not null
					if (temp->data < root->data) {  //if data is less than root data
						Node<T>* temp2 = getParentNode(temp, root);
						if (temp->data > temp2->data) {
							Node<T>*temp3= getParentNode(temp2, root);
							successor = temp3;
						}
						else {
							successor = temp2;
						}
					}
					else if(temp->data>root->data) { //if data is greater than root data
						Node<T>* temp2 = getParentNode(temp, root);
						if (temp->data < temp2->data) {
							successor = temp2;
						}
						else {
							successor = nullptr;
						}
					}
					else {
						successor = root;
					}
				}
				if (temp == root) { //if the given node is root
					Node<T>* possible = temp->right;
					lookforsuccessor(successor, temp, possible);
					temp->nextInOrder = successor;
				}
				else { //in any other case
					lookforsuccessor(successor, temp, temp->right);
					if (successor == getmax()) {
						successor->nextInOrder = nullptr;
					}
					if (temp == getmax()) {
						temp->nextInOrder = nullptr;
					}
					else {
						temp->nextInOrder = successor;
					}
				}
			}
			else { //if the tree is reversed
				if (temp == nullptr ) {
					return;
				}
				if (predeccessor != nullptr) { //if predeccessor is not null
					if (temp->data < root->data) {  //if the data is less than root
						Node<T>* temp2 = getParentNode(temp, root);
						if (temp->data > temp2->data) {
							
							predeccessor = temp2;
						}
						else {
							predeccessor = nullptr;
						}
					}
					else {
						Node<T>* temp2 = getParentNode(temp, root); //getting the parent node
						if (temp->data < temp2->data) {
							Node<T>* temp3 = getParentNode(temp2, root);
							predeccessor = temp3;
						}
						else {
							predeccessor = temp2;
						}
					}
					
				}
				if (temp == root) { // if temp is root
					Node<T>* possible = temp->left;
					lookforpredeccessor(predeccessor, temp, possible);
					temp->nextInOrder = predeccessor;
				}
				else { //otherwise

					lookforpredeccessor(predeccessor, temp, root);
					if (predeccessor == getmin()) {
						predeccessor->nextInOrder = nullptr;
					}
					if (temp ==getmin()) {
						temp->nextInOrder = nullptr;
					}
					else {
						temp->nextInOrder = predeccessor;
					}
				}
			}
		
	}
	Node<T>* getminforroot(Node<T>* temp) {//function to get the minimum for root
		if (temp != nullptr) {
			if (temp->left == nullptr) {
				return temp;
			}
			else {
				return getminforroot(temp->left);
			}
		}
		else {
			return nullptr;
		}
		
	}
	Node<T>* getmaxforroot(Node<T>* temp) { //function to get the maximum for root
		if (temp != nullptr)
		{
			if (temp->right == nullptr) {
				return temp;
			}
			else {
				return getmaxforroot(temp->right);
			}
		}
		else {
			return nullptr;
		}

	}
	void setsuccessors(Node<T>*temp) { //wrapper for setting successors
		
		if (temp == nullptr) { //if temp is null
			return;
		}
		if (temp == root) { //if temp is root
			if (IsSuccessor == true) { 
				if (temp != nullptr) {
					temp->nextInOrder = getminforroot(root->right);
				}
			}
			else {
				if (temp != nullptr) {
					temp->nextInOrder = getmaxforroot(root->left);
				}
			}
		}
		else { //for any other node other than root
			setsuccessorswrap(temp); 
			setsuccessors(temp->left);
			setsuccessors(temp->right);
		}
	}
	Node<T>* getprevforroot(Node<T>*temp) {  //function for getting previous for root
		
		if (temp->nextInOrder == root) {
			return temp;
		}
		else {
			return getprevforroot(temp->nextInOrder);
		}
	}
	Node<T>* getnextforroot(Node<T>* temp) { //function for getting next for root
		if (temp== root->nextInOrder) {
			return temp;
		}
		else {
			return getnextforroot(temp->nextInOrder);
		}
	}
	bool remove(T d) { //wrapper function for remove
		bool x = numberisthere(d, root);
		
		if (d == root->data && (root->left == nullptr && root->right == nullptr)) { //if there is only root and root is the data
			delete root;
			root = nullptr;
			return true;
		}
		if (d != root->data) { //for any other node

			Node<T>* parent = getparent(d, root);

		
		}
		if (x == true) { //if the data is present
			if (IsSuccessor == true) { //if tree is not reversed
				Node<T>* temp = getmin();
				
				if (d == root->data) {
					removewrap(d, root);
					if (root->left == nullptr && root->right == nullptr) { //if root left and root right are null
						return true;
					}
					if (root->left != nullptr) { //if root left is not null
						Node<T>* temp3 = getmaxforroot(root->left); //getting max from root left
						if (root->left == temp3) {  //if the left child of root is temp3
							if (root->left->left != nullptr && root->left->right != nullptr) {
								root->data = root->left->data;
								root->left = temp3->left;
								delete temp3;
							}
						}
						Node<T>* newnextroot = getmaxforroot(root->left);
						if (root->right != nullptr) { //if root right is not null
							Node<T>* temp2 = getminforroot(root->right);
							newnextroot->nextInOrder = root;
							root->nextInOrder = temp2;
						}
						else {
							newnextroot->nextInOrder = root;
						}
					}
					else {
						Node<T>* temp2 = getminforroot(root->right);
						root->nextInOrder = temp2;
					}
				}
				else { // for any other case other than root
					removewrap(d, root);

					if (d < root->data) {
						setsuccessors(root->left);
					}
					else {
						setsuccessors(root->right);
					}
					setsuccessors(root);
				}
			}
			else { //if the tree is reversed
				Node<T>* temp = getmax();
				
				if (d == root->data) { // if the data is root
					removewrap(d, root);
					if (root->left != nullptr) { //if root left is not null
						Node<T>* temp3 = getmaxforroot(root->left);
						if (root->left == temp3) {
							root->data = root->left->data;
							root->left = temp3->left;
							delete temp3;

						}
						Node<T>* newnextroot = getmaxforroot(root->left);
						if (root->right != nullptr) {// if root right is not null
							Node<T>* temp2 = getminforroot(root->right);
							temp2->nextInOrder = root;
							root->nextInOrder = newnextroot;
						}
						else {
							root->nextInOrder = newnextroot;
						}
						
					}
					else {
						Node<T>* temp2 = getminforroot(root->right);
						temp2->nextInOrder = root;

					}
				}
				else { //for any other node
					removewrap(d, root);
					if (d < root->data) {
						setsuccessors(root->left);
					}
					else {
						setsuccessors(root->right);
					}
					setsuccessors(root);
				}
			}
				return true;
		}
		else return false;
	}
	void PrintLH(T L, T H) { //function that prints within a given range
		if (IsSuccessor == true) {
			Node<T>* temp = getmin();
			
			while (temp->data<= H) {
				
				if (temp->data >= L) {
					cout << temp->data << " ";
				}
				temp = temp->nextInOrder;
				if (temp == nullptr) {
					break;
				}
			}
		}
		else { // in case the tree is reversed
			Node<T>* temp =getmax();
			
			while (temp->data >= L) {
				
				if (temp->data <= H) {
					cout << temp->data << " ";
				}
				temp = temp->nextInOrder;
				if (temp == nullptr) {
					break;
				}
			}
		}
	}
	void isleafbalancewrap(Node<T>*temp, int& m, int& n) { //function that checks whether or not the tree leaves are balanced
		if ( temp ==nullptr) {
			if (n > m) {
				m = n;
			}
			
		}
		else {
			n++;
			isleafbalancewrap(temp->left,m,n);
			
			isleafbalancewrap(temp->right, m, n);
		}
	}
	bool isleafbalance() { //wrapper function for checking whether or not the tree leaves are balanced
		int count1 = 0,count2=0, n = 0;
		if (root==nullptr || root->left == nullptr || root->right == nullptr) {
			return true;
		}
		else {
			isleafbalancewrap(root->left, count1, n);
			n = 0;
			isleafbalancewrap(root->right, count2, n);
			if (count1 != count2) {
				return false;
			}
			else return true;
		}
	}
	bool search(T d) { //function that looks for an element in the tree
		Node<T>* temp = root;
		while (temp != nullptr) {
			if (temp->data == d) {
				return true;
			}
			else if (d > temp->data) {
				temp = temp->right;
			}
			else {
				temp = temp->left;
			}
		}
		return false;
	}
	~BST() { //destructor that deletes nextInOrder linklist to delete all of the nodes
		if (root != nullptr) {
			Node<T>* temp = getmin();
			while (temp != nullptr) {
				Node<T>* temp2 = temp->nextInOrder;
				delete temp;
				temp = temp2;
			}
			
		}
		
	}
};


int main() { //main function
	BST<int> tree;
	BST<int>tree2;
	while (1 != 0) {
	
		int key;
		cout << "WELCOME TO LET'S MAKE A TREE!" << endl;
		cout << endl;
		cout << "To perform different functions, choose from the following given options: " << endl;
		cout << endl;
		cout << "Press 1 to insert a number." << endl;
		cout << "Press 2 to remove a number." << endl;
		cout << "Press 3 to search for a number." << endl;
		cout << "Press 4 to make a copy of the tree." << endl;
		cout << "Press 5 to check whether or not the tree leaves are balanced." << endl;
		cout << "Press 6 to reverse the tree." << endl;
		cout << "Press 7 to print the tree." << endl;
		cout << "Press 8 to print elements of the tree within a range." << endl;
		cout << "Press 0 to exit this program." << endl;
		cin >> key;
		if (key == 0) {
			break;
		}
		if (key == 1) {
			system("cls");
			int n;
			cout << "Enter the number: ";
			cin >> n;
			cout << endl;
			bool x = tree.insert(n);
			if (x == true) {
				cout << "The number has been successfully entered!" << endl;
			}
			else if(x==false){
				cout << "The entered number is already present." << endl;
			}
			cout << endl;
			system("pause");
		}
		if (key == 2) {
			system("cls");
			int n;
			cout << "Enter the number: ";
			cin >> n;
			cout << endl;
			bool x = tree.remove(n);
			if (x == true) {
				cout << "The number has been successfully removed!" << endl;
			}
			else {
				cout << "Number not found." << endl;
			}
			cout << endl;
			system("pause");
			
		}
		if (key == 3) {
			system("cls");
			int n;
			cout << "Enter the number: ";
			cin >> n;
			cout << endl;
			bool x = tree.search(n);
			if (x == true) {
				cout << "We found the number!" << endl;
			}
			else {
				cout << "Number not found." << endl;
			}
			cout << endl;
			system("pause");
		}
		if (key == 4) {
			system("cls");
			cout << "Do you want to copy using the assignment operation or copy constructor?" << endl;
			cout << "Press 1 to use assignment operator." << endl;
			cout << "Press 2 to use the copy constructor." << endl;
			int key2;
			cin >> key2;
			system("cls");
			if (key2 == 1) {
				
				tree2 = tree;
			}
			if (key2==2){
				BST<int>tree3(tree);
				cout << "Tree 3: ";
				tree3.Print();
				cout << endl;
			}
			cout << "The tree has been successfully copied!" << endl;
			cout << endl;
			system("pause");
			
		}
		if (key == 5) {
			system("cls");
			bool x = tree.isleafbalance();
			if (x == true) {
				cout << "The leaves are balanced." << endl;
			}
			else {
				cout << "The leaves aren't balanced." << endl;
			 }
			cout << endl;
			system("pause");
			}
		if (key == 6) {
			system("cls");
			tree.reverse();
			cout << "The tree has been successfully reversed!" << endl;
			cout << endl;
			system("pause");
		}
		if (key == 7) {
			system("cls");
			cout << "The tree is: ";
			tree.Print();
			cout << endl;
			cout << "Tree 2 is: ";
			tree2.Print();
			cout << endl;
			system("pause");
		}
		if (key == 8) {
			system("cls");
			int L;
			int H;
			cout << "Enter the start of the range: ";
			cin >> L;
			cout << "Enter the end of the range: ";
			cin >> H;
			system("cls");
			cout << "The numbers within the given range are: " << endl;
			tree.PrintLH(L, H);
			cout << endl;
			system("pause");
		}
		system("cls");
	}
		system("pause");
		return 0;
}
