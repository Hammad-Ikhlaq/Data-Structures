#include<iostream>
#include<time.h>
using namespace std;

struct player			//the stuture of players playing this game
{
	int id;			//it is used to distinguish players
	player*next;		//current player will know the person to which he has to pass
};

class game					//the class of each game that will take place
{
	player*firstplayer;
public:
	game(int i)			//default and parameterize constructor
	{
		firstplayer = new player;
		firstplayer->id = 1;
		firstplayer->next = firstplayer;
		player*temp = firstplayer;
		for (int a = 0; a < i -1; a++)		//making the whole list of players
		{
			temp->next = new player;		//making a new player
			temp->next->id = a + 2;			//maintaining id
			temp = temp->next;				//move ahead

		}
		temp->next = firstplayer;		//making list circular
	}
	void remove(int i)
	{
		player*curr = firstplayer;
		for (int a = 0; a < i - 1; a++)
		{
			curr = curr->next;			//curr has the address of the player that is before the player who is to remove
		}
		if (curr->next == firstplayer)	//updating the first player id
		{
			firstplayer = firstplayer->next;
		}
		player*temp = curr->next;  //storing the address of the player who is to remove
		curr->next = temp->next;	//updating the pointer of player that is before the player who is to remove
		delete temp;
	}
	void display()			//display the players
	{
		player*temp = firstplayer->next;
		cout<<firstplayer->id<<" ";
		while (temp!=firstplayer)
		{
			cout << temp->id << " ";
			temp = temp->next;
		}
		cout << endl;
	}
	~game()
	{
		player*temp = firstplayer->next;
		while (temp!=firstplayer)
		{
			firstplayer->next = temp->next;
			delete temp;
			temp = firstplayer->next;
		}
		delete firstplayer;

	}
};
int main()
{
	int n,r;
	cout << "Enter the number of players you want to start the game\n";
	cin >> n;
	game test(n);
	for (int i = 0; i < n-1; i++) //n-1 phases
	{
		//test.display();			//to see each step
		srand(unsigned(time(0)));
		r = (rand() % 9 + 1);
		test.remove(r);
	}
	test.display();
	cout << "is the winner\n";
	system("pause");
	return 0;
}