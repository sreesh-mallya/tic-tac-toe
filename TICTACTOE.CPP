#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <process.h>
#include <ctype.h>
#include <conio.h>
#include <stdio.h>

#define X 'X'
#define O 'O'

char options[][25] = {
						"1. Play",
						"2. Profiles",
						"3. Recent Winners",
						"4. Help",
						"5. Exit"
                     };    // Main menu options

int ctr = -1;     // Just a counter variable
int turns = 0;

class MAIN_MENU
{
	char Select;            // User choice in the main menu
public:
	void splash();          // Display splash screen at runtime
	void MenuDisplay();     // Display main menu
	void play();            // Play the game
	void recent_winners();  // Display game statistics
	void help();            // Display help
	void ExitScreen();      // Display exit screen
}menu, m;


class GAME
{
public:
	char a[3][3];            // The matrix for the game plane
	void ScrInit();
	void ScrDisplay();      // Function for displaying the game plane
	int PatternCheck();     // Checks the pattern to decide winner
}game;

class PLAYER
{
	char x;		            // Player's input
	char profile[30];      // Player profile name
public:
	unsigned int wins, losses, draws;
	void askInput(char);    // Asks choice(where to input X or O)
	void askProfileName();  // Asks player to input profile name
	void displayName();
	void PROFILE();			// Manages profiles
	void Winner();          // Adds winner's name to recent winners
}p1, p2, p3, p4;

void PLAYER :: Winner()
{
	ofstream add;
	add.open("recent_winners.dat", ios::app);
	add << profile << '\n';
	add.close();
}

void PLAYER :: displayName()
{
	cout << profile;
}

void MAIN_MENU :: splash()
{
	clrscr();
	cout << "\n\n\n\n\n\n\t\t\t Created by: \n\t\t\t Aaquib, Ajith,"
		 << "Sreesh \n\n\n\t\t\t";
	cout << "\n\n\t\t\tPress any key to continue . . . ";
	getch();
	clrscr();
	cout << "\n\n\n\n\n\n\n\t\t\t  -----------------------";
	cout << "\n\t\t\t.:|   TIC TAC TOE GAME  |:.";
	cout << "\n\t\t\t  -----------------------";
	cout << "\n\n\n\t\t\tPress any key to continue . . . ";
	getch();
	clrscr();
}

void MAIN_MENU :: MenuDisplay()
{
	clrscr();
	cout << "\n\n\n\n\n\n\n\n\t\t\t\t MAIN MENU \n";
	cout << "\t\t\t\t ~~~~~~~~~\n\n";
	for(int i = 0; i < 5; i++)
	{
		cout << "\t\t\t" << options[i] << endl;
	}

	cout << "\n\n\t\t Select your choice. Example: '1' to play . . . . " ;

	DO_AGAIN:       // 'goto' label

	cin >> Select;
	switch(Select)
	{
		case '1':
			play();
		break;

		case '2':
			p3.PROFILE();
		break;

		case '3':
			recent_winners();
		break;

		case '4':
			help();
		break;

		case '5':
			ExitScreen();
		break;

		default:
		cout << "\n\t\t\t Select any valid option : ";
		goto DO_AGAIN;
	}

}

void MAIN_MENU :: recent_winners()
{
	clrscr();
	cout << "\n\t\t\t\t\t\t RECENT WINNERS";
	cout << "\n\t\t\t\t\t\t ~~~~~~~~~~~~~~";
	int q;
	char con;
	cout << "\n\t\t\t 1. View Recent Winners \n\t\t\t 2. Reset Recent Winners"
		   << "\n\t\t\t 3. Return to Main Menu " << endl;
	cout << "\n\n\t\t\t Select the required option (1-3): ";
	po:
	cin >> q;
	if (q == 1)
	{
		char line[80];
		int l;
		ifstream fout;
		fout.open("recent_winners.dat", ios::in);
		fout.seekg(0, ios::end);
		l = fout.tellg();
		fout.close();
		if (l == 0)		// Checks whether the Profile is empty or not.
		{
			clrscr();
			cout << "\n\t\t\t Currently there are no Recent Winners to be"
				 << "displayed… \n \n \n";
			getch();
			m.recent_winners();
		}
		else if (l != 0)
		{
			clrscr();
			cout << "\n\t\t\t RECENT WINNERS";
			cout << "\n\t\t\t ~~~~~~~~~~~~~~";
			fout.open("recent_winners.dat",ios::in);
			while(!fout.eof())
			{
				cout << endl;
				for(int n = 0; n != 10; n++)
				{
					fout.getline(line, 80);
					cout <<"\n\t\t\t" << line;
					if(n % 5 == 0)
					{
						cout << "\n";
					}
				}
			}
			fout.close();
		}
		getch();
		m.recent_winners();
	}
	else if (q == 2)
	{
		clrscr();
		cout << "\n\t\t\t Are you sure you want to reset Recent Winners (y/n): ";
		cin >> con;
		if (con == 'Y' || con == 'y')
		{
			ofstream fout;
			fout.open("recent_winners.dat", ios::trunc);   // Resets the Profile.
			fout.clear();
			fout.close();
			cout << "\n Recent Winners Reseted...";
			getch();
			m.recent_winners();
		}
		else
			m.recent_winners();
	}
	else if (q == 3)
		menu.MenuDisplay();
	else
	{
		cout << "\n\t\t\t Select a valid option (1-3): ";
		goto po;
	}

	getch();
}

void MAIN_MENU :: ExitScreen()
{
    clrscr();
    char EXIT;
	cout << "\n\n\n\n\n\t\t Are you sure you want to quit? (Type Q to quit) ";
	cin >> EXIT;

    EXIT = toupper(EXIT);

    if(EXIT == 'Q')
	exit(0);
    else
	MenuDisplay();
}

void PLAYER :: askProfileName()
{
	gets(profile);
	ofstream filout;
	filout.open("profiles.txt", ios::app);
	filout << profile << '\n';
	filout.close();
}

void PLAYER :: PROFILE()
{
	clrscr();
	int p;
	char conf;
	cout << "\n\t\t\t\t\t\t PROFILES";
	cout << "\n\t\t\t\t\t\t ~~~~~~~~~";
	cout << "\n\t\t\t 1. View Profiles \n\t\t\t 2. Reset Profiles \n\t\t\t"
		   << "3. Return to Main Menu " << endl;
	cout << "\n\n\t\t\t Select the required option (1-3): ";
	op:
	cin >> p;
	if (p == 1)
	{
		char ar[500];
		int len;
		ifstream filin;
		filin.open("profiles.txt", ios::in);
		filin.seekg(0, ios::end);
		len = filin.tellg();
		filin.close();
		if (len == 0)	// Checks whether the Profile is empty or not.
		{
			clrscr();
			cout << "\n\t\t\t Currently there are no profiles to be displayed"
					   << "\n \n \n";
			getch();
			p3.PROFILE();
		}
		else if (len != 0)
		{
			clrscr();
			filin.open("profiles.txt", ios::in);
			while(!filin.eof())
			{
				filin.getline(ar,500);
				if (filin.eof())
					break;
				cout << "\n\t\t\t" << ar << endl;
			}
			filin.close();
		}
		getch();
		p3.PROFILE();
	}
	else if (p == 2)
	{
		clrscr();
		cout << "\n\t\t\t Are you sure you want to reset Profiles (y/n): ";
		cin >> conf;
		if (conf == 'Y' || conf == 'y')
		{
			ofstream filout;
			filout.open("profiles.txt", ios::trunc);      // Resets the Profile.
			filout.clear();
			filout.close();
			cout << "\n\t\t\t Profiles Reseted…";
			getch();
			p3.PROFILE();
		}
		else
			p3.PROFILE();
	}
	else if (p == 3)
		menu.MenuDisplay();
	else
	{
		cout << "\n\t\t\t Select a valid option (1-3): ";
		goto op;
	}
}


void MAIN_MENU :: help()          // Help file.
{
	char arr[500];
	ifstream load;
	clrscr();
	load.open("help.txt", ios::in);
	while(!load.eof())
	{
		load.getline(arr,500,'$');
		if (load.eof())
			break;
		cout << arr;
	}
	cout << "\n \n";
	getch();
	menu.MenuDisplay();
}

void GAME :: ScrInit()
{
	game.a[0][0] = '0';
	game.a[0][1] = '1';
	game.a[0][2] = '2';
	game.a[1][0] = '3';
	game.a[1][1] = '4';
	game.a[1][2] = '5';
	game.a[2][0] = '6';
	game.a[2][1] = '7';
	game.a[2][2] = '8';
}

void GAME :: ScrDisplay()
{
	clrscr();
	cout << endl;

	cout << "\t\t\t             ___________ " << endl;
	cout << "\t\t\t            |   |   |   |" << endl;
	cout << "\t\t\t            | " << a[0][0] << " | " << a[0][1] << " | " << a[0][2]
     << " |" << endl;
	cout << "\t\t\t            |___|___|___|" << endl;
	cout << "\t\t\t            |   |   |   |" << endl;
	cout << "\t\t\t            | " << a[1][0] << " | " << a[1][1] << " | " << a[1][2]
           << " |" << endl;
	cout << "\t\t\t            |___|___|___|" << endl;
	cout << "\t\t\t            |   |   |   |" << endl;
	cout << "\t\t\t            | " << a[2][0] << " | " << a[2][1] << " | " << a[2][2]
           << " |" << endl;
	cout << "\t\t\t            |___|___|___|" << endl;

	cout << endl;
}

void MAIN_MENU :: play()
{
	clrscr();

	cout << "\n\t\t\t\t\t\t  MAKE A PROFILE";
	cout << "\n\t\t\t\t\t\t ~~~~~~~~~~~~~~~ \n\n";

	cout << "\t\t\tEnter Player1 name : ";
	p1.askProfileName();

	cout << "\t\t\tEnter Player2 name : ";
	p2.askProfileName();

	clrscr();
	int game_over;

	game.ScrInit();

	NEXT_TURN:

	game.ScrDisplay();
	cout << "\t\t\t";
	p1.displayName();
	cout << "'s turn : ";
	p1.askInput(O);
	++turns;
	game_over = game.PatternCheck();

	if(!game_over)
	{
		game.ScrDisplay();
		cout << "\t\t\t";
		p2.displayName();
		cout << "'s turn : ";
		p2.askInput(X);
		++turns;
		game_over = game.PatternCheck();
	}
	if(game_over == 1)
	{
		game.ScrDisplay();
		cout << endl;
		turns = 0;
		cout << "\t\t\t";
		p1.displayName();
		cout << " is the winner!";
		p1.Winner();
		cout << "\n\n\t\t\t Statistics update successful. \n\n";
		getch();
		menu.MenuDisplay();
      }
	if(game_over == 2)
	{
		game.ScrDisplay();
		cout << endl;
		turns = 0;
		cout << "\t\t\t";
		p2.displayName();
		cout << " is the winner!";
		p2.Winner();
		cout << "\n\n\t\t\t Statistics update successful. \n\n";
		getch();
		menu.MenuDisplay();
	}
	if(game_over == -1)
	{
		game.ScrDisplay();
		turns = 0;
		cout << "\n\t\t\t The game is a draw.\n\t\t\t Returning to main menu"
				 << "\n\n";
		getch();
		menu.MenuDisplay();
	}





if(!game_over)
		goto NEXT_TURN;

}

void PLAYER :: askInput(char x_o)
{
	int dummy;
	cin >> dummy;

	while(dummy < 0 || dummy > 8)
	{
	    cout << "\n\n\t\t\t Enter again : ";
	    cin >> dummy;
	}
	x = dummy + '0';

	for(int c = 0; c < 3; c++)
	{
		for(int r = 0; r < 3; r++)
		{
			if(game.a[c][r] == x)
				game.a[c][r] = x_o;
		}
	}
	game.ScrDisplay();

	cout << endl;
}

int GAME :: PatternCheck()
{
	/* Diagonal : */
	/* Player1 winning */

	if(game.a[0][0] == O && game.a[1][1] == O && game.a[2][2] == O)
		return 1;
	if(game.a[0][2] == O && game.a[1][1] == O && game.a[2][0] == O)
		return 1;

	/* Player2 winning */
	if(game.a[0][0] == X && game.a[1][1] == X && game.a[2][2] == X)
		return 2;
	if(game.a[0][2] == X && game.a[1][1] == X && game.a[2][0] == X)
		return 2;

	/* Vertical : */
	/* Player1 winning */
	if(game.a[0][0] == O && game.a[1][0] == O && game.a[2][0] == O)
		return 1;
	if(game.a[0][1] == O && game.a[1][1] == O && game.a[2][1] == O)
		return 1;
	if(game.a[0][2] == O && game.a[1][2] == O && game.a[2][2] == O)
		return 1;

	/* Player2 winning */
	if(game.a[0][0] == X && game.a[1][0] == X && game.a[2][0] == X)
		return 2;
	if(game.a[0][1] == X && game.a[1][1] == X && game.a[2][1] == X)
		return 2;
	if(game.a[0][2] == X && game.a[1][2] == X && game.a[2][2] == X)
		return 2;

	/* Horizontal : */
	/* Player1 winning */
	if(game.a[0][0] == O && game.a[0][1] == O && game.a[0][2] == O)
		return 1;
	if(game.a[1][0] == O && game.a[1][1] == O && game.a[1][2] == O)
		return 1;
	if(game.a[2][0] == O && game.a[2][1] == O && game.a[2][2] == O)
		return 1;

	/* Player2 winning */
	if(game.a[0][0] == X && game.a[0][1] == X && game.a[0][2] == X)
		return 2;
	if(game.a[1][0] == X && game.a[1][1] == X && game.a[1][2] == X)
		return 2;
	if(game.a[2][0] == X && game.a[2][1] == X && game.a[2][2] == X)
		return 2;


	if(turns == 9)
		return -1;

	else
		return 0;
}

int main()
{
    clrscr();
    menu.splash();
    menu.MenuDisplay();
    getch();
    return 0;
}
