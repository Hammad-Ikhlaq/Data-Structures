#include <iostream>
#include <string>
using namespace std;

bool stats = true;	//	Set it false if you dont to print pool and files each time


template<class T>
class List;
class File;


template <class T>	//Class Template of Node
class Node {
	T* data;
	Node<T>* next;
public:
	Node();
	Node(T* d, Node<T>* n);
	~Node();
	friend class FileSystem;
	friend class List<T>;
};


template <class T>	//Class Template of List
class List{
	Node<T>* head, * tail;
	int size;
public:
	List();
	void insertAtEnd(T* n);
	void insertAtEnd(Node<T>* n);
	void print();
	Node<File>* find(string fname);
	~List();
	friend class FileSystem;
};

class Block {
	int start_sector_ID, total_sectors;
public:
	Block();
	Block(int start, int total);
	friend ostream& operator << (ostream& out, Block& b);
	friend class FileSystem;
};


class File {
	string name;
	int size;
	List<Block> blockList;
public:
	File();
	File(string n, int s);
	friend ostream& operator << (ostream& out, File& b);
	friend class List<File>;
	friend class FileSystem;
};

class FileSystem {
	List<Block> pool;
	List<File> files;
	char* disk;
	int numOfSectors, sizeOfSectors, numOfSectorsInPool;
public:
	FileSystem(int num, int size) {
		Block *b = new Block(0, num);
		pool.insertAtEnd(b);
		numOfSectorsInPool = numOfSectors = num;
		sizeOfSectors = size;
		disk = new char[num * size];
	}

	bool saveFile(string fname, const char* fcontent, int fsize) {
		int sectorsRequired = fsize / sizeOfSectors;
		if (fsize % sizeOfSectors != 0)
			++sectorsRequired;

		if (files.find(fname) != nullptr)
			return false;
		if (sectorsRequired > numOfSectorsInPool)
			return false;

		File *newFile = new File(fname, fsize);
		Node<Block>* blockAllocated = nullptr;
		int j = 0, x = 0, y = 0;
		int t = sectorsRequired;
		while (t > 0) {
			
			blockAllocated = allocateBlock(t);	//	Returns address of a block allocated
			x = blockAllocated->data->start_sector_ID;
			y = blockAllocated->data->total_sectors;
			newFile->blockList.insertAtEnd(blockAllocated);	//	Adds that allocated block to the file's blocklist
			for (int i = x * sizeOfSectors; i < ((x + y) * sizeOfSectors) && j < fsize; i++, j++)
				disk[i] = fcontent[j];
		}
		numOfSectorsInPool -= sectorsRequired;
		files.insertAtEnd(newFile);
		return true;
	}

	bool deleteFile(string fname) {
		Node<Block>* temp = removeFile(fname);
		if (temp == nullptr)
			return false;
		Node<Block>* b = nullptr;
		while (temp != nullptr) {
			b = temp;
			temp = temp->next;
			numOfSectorsInPool += b->data->total_sectors;
			deallocateBlock(b);
		}
		return true;
	}

	void readFile(string fname) {
		Node<File>* f = files.find(fname);
		if (f != nullptr) {
			Node<Block>* temp = f->data->blockList.head;
			int j = 0, x = 0, y = 0;
			cout << "\n" << f->data->name << ": ";
			while (temp!=nullptr) {
				x = temp->data->start_sector_ID;
				y = temp->data->total_sectors;
				for (int i = x * sizeOfSectors; i < ((x + y) * sizeOfSectors) && j < f->data->size; i++, j++)
					cout << disk[i];
				temp = temp->next;
			}
			cout << "\n\n";
		}
		else {
			cout << "\nFile Does Not Exist!\n\n";
		}
	}


	//	Returns the address of a node containing a block containing sectors from the pool; if first block has less number of sectors than required,
	//	it returns its address while unlinking it from pool, otherwise it creates a new node containing a block containing required sectors and returns
	//	its address while updating the block in the pool
	Node<Block>* allocateBlock(int& n)
	{
		Node<Block>* temp = nullptr;
		if (pool.head->data->total_sectors <= n) {
			temp = pool.head;
			pool.head = pool.head->next;
			pool.size--;
			if (pool.size == 0)
				pool.tail = nullptr;
			n -= temp->data->total_sectors;
		}
		else {
			Block* b = new Block(pool.head->data->start_sector_ID, n);
			temp = new Node<Block>(b, nullptr);
			pool.head->data->start_sector_ID += n;
			pool.head->data->total_sectors -= n;
			n = 0;
		}
		return temp;
	}


	//	Takes a Node containing block containing sectors to be deallocated and linked back to the pool in sorted order and does that by the following cases mentioned in the function
	void deallocateBlock(Node<Block>* n)
	{

		Node<Block>* temp = pool.head;
		if (temp == nullptr) {	//	Case1: if pool is empty, then just adds it to the pool
			pool.head = pool.tail = n;
			++pool.size;
		}
		else if (n->data->start_sector_ID + n->data->total_sectors < temp->data->start_sector_ID) {	//	Case2: if it does not not need to merge with the very first block of pool, then just inserts it at the start
			n->next = pool.head;
			pool.head = n;
			pool.size++;
		}
		else if (n->data->start_sector_ID + n->data->total_sectors == temp->data->start_sector_ID) {	//	Case3: if it needs to be merged with the very first block of pool, then deletes it after updating the block in the pool (merges it)
			pool.head->data->start_sector_ID = n->data->start_sector_ID;
			pool.head->data->total_sectors += n->data->total_sectors;
			delete n;
		}
		else {
			while (temp != nullptr) {
				if (n) {
					if (temp->next && temp->data->start_sector_ID + temp->data->total_sectors == n->data->start_sector_ID &&
						n->data->start_sector_ID + n->data->total_sectors == temp->next->data->start_sector_ID) {	//	Case4: if it and the current and next block of pool, all 3 needs to be merged, then deletes it and the next block of pool after updating the current one (merges all 3)
						temp->data->total_sectors += (n->data->total_sectors + temp->next->data->total_sectors);
						if (temp->next == pool.tail) {
							temp->next = nullptr;
							delete pool.tail;
							pool.tail = temp;
						}
						else {
							Node<Block>* b = temp->next->next;
							delete n;
							delete temp->next;
							temp->next = b;
						}
						return;
					}
					else if (temp->data->start_sector_ID + temp->data->total_sectors == n->data->start_sector_ID) { 	//	Case5: if it needs to be merged with the current block of pool, deletes it after updating the sectors of current block
						temp->data->total_sectors += n->data->total_sectors;
						delete n;
						return;
					}
					else if (temp->next && n->data->start_sector_ID + n->data->total_sectors == temp->next->data->start_sector_ID) {	//	Case6: if it needs to be merged with the next block of pool, deletes it after updating the sectors of the next block
						temp->next->data->start_sector_ID = n->data->start_sector_ID;
						temp->next->data->total_sectors += n->data->total_sectors;
						delete n;
						return;
					}
					else if (temp->next && n->data->start_sector_ID + n->data->total_sectors < temp->next->data->start_sector_ID) {	//	Case7: if it needs to be put before the next block of pool, links it in the pool as such
						n->next = temp->next;
						temp->next = n;
						pool.size++;
						return;
					}
					else if (temp == pool.tail) {	//	Case8: if it needs to be put after the last block of pool list, does that and moves the tail to it
						pool.tail->next = n;
						pool.tail = pool.tail->next;
						pool.tail->next = nullptr;
						return;
					}
				}
				temp = temp->next;
			}
		}
	}


	//	Finds the file named as in fname and if found, deletes the Node containing file and returns the address of its blocklist for deallocation
	
	Node<Block>* removeFile(string fname)
	{
		Node<Block>* b = nullptr;
		if (files.head != nullptr) {
			Node<File>* temp = files.head;
			if (temp->data->name == fname) {
				files.head = files.head->next;
				b = temp->data->blockList.head;
				temp->data->blockList.head = temp->data->blockList.tail = nullptr;
				temp->data->blockList.size = 0;
				delete temp;
				files.size--;
				if (files.size == 0)
					files.head = files.tail = nullptr;
			}
			else {
				while (temp->next != nullptr) {
					if (temp->next->data->name == fname) {
						Node<File>* temp2 = temp->next;
						temp->next = temp->next->next;
						b = temp2->data->blockList.head;
						temp2->data->blockList.head = temp2->data->blockList.tail = nullptr;
						temp2->data->blockList.size = 0;
						if (temp2 == files.tail)
							files.tail = temp;
						delete temp2;
						files.size--;
						if (files.size == 0)
							files.head = files.tail = nullptr;
						return b;
					}
					temp = temp->next;
				}
			}
		}
		return b;
	}


	//	Prints Disk Information
	void printStats() {
		cout << "Pool: ";
		pool.print();
		cout << "\nFiles: ";
		files.print();
		cout << endl;
	}

	bool findFile(string name) {
		return files.find(name);
	}

	~FileSystem() {
		if (disk != nullptr)
			delete[] disk;
	}
};


ostream& operator << (ostream& out, Block& b);

ostream& operator << (ostream& out, File& b);


//Inputs Number of Sectors from User and Returns it
int inputNum() {
	int a = 0;
	bool flag = false;
	while (!flag) {
		cout << "\nEnter Number of Sectors: ";
		cin >> a;
		if (cin) {
			if (a < 1)
				cout << "Invalid Number!\n";
			else
				flag = true;
		}
		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid Input!\n";
		}
	}
	return a;
}

//Inputs Size of Sectors from User and Returns it
int inputSize() {
	int b = 0;
	bool flag = false;
	while (!flag) {
		cout << "Enter the size for each sector: ";
		cin >> b;
		if (cin) {
			if (b < 1)
				cout << "Invalid Size!\n";
			else
				flag = true;
		}
		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid Input!\n";
		}
	}
	return b;
}

//Inputs Choice for Action from User and Returns it
int inputChoice() {
	int n = 0;
	bool flag = false;
	while (!flag) {
		cout << "Enter 1 to Add a New File\n";
		cout << "Enter 2 to Read a New File\n";
		cout << "Enter 3 to Delete a New File\n";
		cout << "Enter 0 to Quit\n";
		cout << "Choice: ";
		cin >> n;
		if (cin) {
			if (n < 0 || n > 3)
				cout << "Invalid Choice!\n";
			else
				flag = true;
		}
		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid Input!\n";
		}
	}
	return n;
}

//Driver Function Creates and Manage File System
void driver() {
	cout << "Welcome to File Allocation Table (FAT) File System!\n";
	int a = inputNum(), b = inputSize();
	cout << endl;
	FileSystem f(a, b);
	int n = 0;
	char temp[16300];
	string name;
	while (n != -1) {
		if (stats)
			f.printStats();
		n = inputChoice();
		if (n != 0) {
			cout << "Enter Filename: ";
			cin.ignore();
			cin.getline(temp, 256, '\n');
			name = temp;
			if (n == 1) {
				if (!f.findFile(name)) {
					cout << "Enter its Content: ";
					cin.getline(temp, 2047, '\n');
					int i = 0;
					for (i; temp[i] != '\0'; i++);
					if (f.saveFile(name, temp, i))
						cout << "\nFile Saved Successfully!\n\n";
					else
						cout << "\nNot Enough Space!\n\n";
				}
				else
					cout << "\nFile Name Already Exists!\n\n";
			}
			else if (n == 2) {
				f.readFile(name);
			}
			else if (n == 3) {
				if (f.deleteFile(name))
					cout << "\nFile Deleted Successfully!\n\n";
				else
					cout << "\nFile Does Not Exist!\n\n";
			}
		}
		else
			n = -1;
	}
}




int main()
{
	driver();
    cout << endl;
	return 0;
}




//								Node functions implementation
template <class T>
Node<T>::Node() : data(nullptr), next(nullptr) {}

template <class T>
Node<T>::Node(T* d, Node<T>* n) : data(d), next(n) {}

template<class T>
Node<T>::~Node()
{
	if (data)
		delete data;
}



//								List functions implementation
template<class T>
List<T>::List() {
	head = tail = nullptr;
	size = 0;
}

template<class T>
void List<T>::print()
{
	Node<T>* temp = head;
	while (temp != nullptr) {
		cout << *(temp->data) << " ";
		temp = temp->next;
	}
	if (head == nullptr)
		cout << "Empty";
	cout << endl;
}

template<class T>
void List<T>::insertAtEnd(T* n) {
	if (head != nullptr) {
		tail->next = new Node<T>(n, nullptr);
		tail = tail->next;
	}
	else {
		head = tail = new Node<T>(n, nullptr);
	}
}

template<class T>
void List<T>::insertAtEnd(Node<T>* n)
{
	if (head != nullptr) {
		tail->next = n;
		tail = tail->next;
	}
	else {
		head = tail = n;
	}
}


//	Returns the address of the node containing a file named as in fname
template<class T>
Node<File>* List<T>::find(string fname)
{
	if (head != nullptr) {
		Node<File>* temp = head;
		while (temp != nullptr) {
			if (temp->data->name == fname)
				return temp;
			temp = temp->next;
		}
	}
	return nullptr;
}

template<class T>
List<T>::~List() {
	Node<T>* temp = nullptr;
	while (head != nullptr) {
		temp = head;
		head = head->next;
		delete temp;
	}
}



//								Block functions implementation
Block::Block() {
	start_sector_ID = -1;
	total_sectors = 0;
}

Block::Block(int start, int total) {
	start_sector_ID = start;
	total_sectors = total;
}





//								File functions implementation
File::File() {
	size = 0;
}

File::File(string n, int s) {
	name = n;
	size = s;
}

ostream& operator<<(ostream& out, Block& b)
{
	out << b.start_sector_ID << "," << b.total_sectors;
	return out;
}

ostream& operator<<(ostream& out, File& b)
{
	out << b.name << "," << b.size;
	return out;
}
