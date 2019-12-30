#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>


#include "stacks.h"
#include "myconsole.h"
#include "mygraphics.h"
#include "avl.h"
#include <conio.h>

using namespace std;


int main()
{
	SetWindowTitle("My AVL TREE");
	bool found = false;
	avltree<int> tree;
	int check = 0, item = 0;
	while (!found)
	{
		PlaceCursor(0, 0);
		system("COLOR F9");
		cout << "Press 1 to insert an item in the tree." << endl;
		cout << "Press 2 to delete an item from the tree." << endl;
		cout << "Press 3 to delete the tree." << endl;
		cout << "Press 4 to display the tree." << endl;
		cout << "Press 5 to print in ascending order" << endl;
		cout << "Press 6 to print in descending order" << endl;
		cout << "Press 7 to copy the first tree and print it" << endl;
		cout << "Press 8 to exit" << endl;
		cin >> check;
		ClearScreen();
		PlaceCursor(0, 0);
		if(check == 1)
		{
			cout << "Key that you want to insert in the tree:";
			cin >> item;
			tree.insert(item);
		}
		else if (check == 2)
		{
			cout << "Key that you want to delete from the tree:";
			cin >> item;
			tree.deleteKey(item);
		}
		else if (check == 3)
			tree.deleteTree();
		else if (check == 4)
		{
			cout << "Press an key to view tree and after viewing press any key again to go back to menu:";
			_getch();
			tree.printTree(); 
			//cout << "Press an key to continue:"; -> if we insert this ,it distorts the tree
			_getch();

		}
		else if (check == 5)
		{
			tree.printAscending();
			PlaceCursor(20, 20);
			cout << "Press an key to continue:" << endl;
			_getch();
		}
		else if (check == 6)
		{
			tree.printDescending();
			PlaceCursor(20, 20);
			cout << "Press an key to continue:" << endl;
			_getch();
		}
		else if (check == 7)
		{
			avltree<int> tree2(tree);
			cout << "Press an key to view tree and after viewing press any key again to go back to menu:";
			_getch();
			tree2.printTree();
			_getch();
		}
		else if (check == 8)
			found = true;
		ClearScreen();
	}

