#include <iostream>
#include "hashtable.h"
#include "passserver.h"

using namespace std;
using namespace cop4530;
void Menu()
{
	cout << "\n\n";
	cout << "l - Load From File" << endl;
	cout << "a - Add User" << endl;
	cout << "r - Remove User" << endl;
	cout << "c - Change User Password" << endl;
	cout << "f - Find User" << endl;
	cout << "d - Dump HashTable" << endl;
	cout << "s - HashTable Size" << endl;
	cout << "w - Write to Password File" << endl;
	cout << "x - Exit program" << endl;
	cout << "\nEnter choice : ";
}

//main routine
int main()
{
	string filename{};//change this to empty if you wish to change filename via the menu
	string outfilename{};

	//size 2 initialization to test my rehash() and resizeServer() subsequently
	//feel free to initialize it with the default size PassServer myserver;
	PassServer myserver(2);
	//myserver.load(filename.c_str());
	//cout << "*****Dump test on PassServer myserver obj - encrypted *********" << endl;
	//myserver.dump();
	//if (myserver.write_to_file(outfilename.c_str()))
		//cout << "Written to file successfully" << endl;

	/********************Menu implementation*************************/
	/* Written by Gokhan Unal on 4/2/2024, no reference; below is my work. */

	string user_menu_choice{};
	string user_input{};
	string username{};
	string password{};
	string o_password{};
	string n_password{};
	do 
	{
		Menu();
		cin >> user_menu_choice;
		//load from file
		if (user_menu_choice == "l")
		{
			cout << "Enter the filename you wish to load from" << endl;
			cin >> user_input;
			if(myserver.load(user_input.c_str()))
			{
				cout << "File loaded successfully!" << endl;
			}
			else
			{
				cout << "****Cannot open file: " << user_input << endl;
			}
		}
		//add user
		else if (user_menu_choice == "a")
		{
			cout << "Enter the username for the user you want to add: ";
			cin >> username;
			cout << "Enter the password for the user you want to add: ";
			cin >> password;
			if (myserver.addUser(make_pair(username, password)))
			{
				cout << "User with username ' " << username << " ' successfully added." << endl;
			}
			else
			{
				cout << "****Cannot add the user; returning to main menu." << endl;
			}
		}
		//remove user
		else if (user_menu_choice == "r")
		{	
			cout << "Enter the username you wish to remove from the list: ";
			cin >> username;
			if (myserver.removeUser(username))
			{
				cout << "User " << username << " removed successfully." << endl;
			}
			else
			{
				cout << "****Cannot remove the user; returning to main menu." << endl;
			}
		}
		//change user password
		else if (user_menu_choice == "c")
		{
			cout << "Enter the username you wish to change password for: ";
			cin >> username;
			cout << "Enter your old password: ";
			cin >> o_password;
			cout << "Enter the new password you wish to save: ";
			cin >> n_password;
			//create the appropriate pair
			pair<string, string> mypair(username, o_password);
			//if successfully changed or not; let the user know
			if (myserver.changePassword(mypair, n_password))
			{
				cout << "Password changed successfully!" << endl;
			}
			else
			{
				cout << "****Cannot change the password; returning to main menu." << endl;
			}
		}
		//find user
		else if (user_menu_choice == "f")
		{
			cout << "Enter the user name you wish to check for: ";
			cin >> username;
			//if found or not; let the user know with the searched username printed
			if(myserver.find(username))
			{
				cout << "User with username ' " << username << " ' found in the list!" << endl;
			}
			else
			{
				cout << "****User with username ' " << username << " ' NOT found in the list!";
				cout << endl;
			}
		}
		//dump the table
		else if(user_menu_choice == "d")
		{
			myserver.dump();
		}
		//hash table size
		else if (user_menu_choice == "s")
		{
			cout << "Hash Table size: " << myserver.size() << endl;
		}
		//write to file
		else if (user_menu_choice == "w")
		{
			string newoutfilename{};
			cout << "Enter the filename you wish to output the list: ";
			cin >> newoutfilename;
			if (myserver.write_to_file(newoutfilename.c_str()))
			{
				cout << "Written to file " << newoutfilename << " successfully!" << endl;
			}
			else
			{
				cout << "****Couldn't write to file. returning to main menu" << endl;
			}
		}

	} while (user_menu_choice != "x");

	cout << "Exited the program, have a good rest of your day!" << endl;

	return 0;
}

