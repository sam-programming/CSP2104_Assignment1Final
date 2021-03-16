#include"Dictionary_Part01.h"
using namespace std;

int main() {
	Dictionary_Part01 dict;
	dict.loadDictionary("dictionary2021.txt");
	const char EXIT = 'x';
	cout << "Welcome to Dictionary Part 1!\n";

	char user_comm = '0';
	// Menu loops until user enters 'x'
	while (user_comm != EXIT) {

		string response;
		cout << "Enter '1' to Find a word.\n";
		cout << "Enter '2' to List all word(s) that contain more than three 'z''s.\n";
		cout << "Enter '3' to List all word(s) that contain a 'q' that is not followed by a 'u'.\n";
		cout << "Enter " << EXIT << " to exit the program...\n";
		cin >> response;
		// To prevent cin buffer issues and unintentional input, take a string as cin and test it for length
		// If the user puts a space in the input
		while (response.length() > 1) {
			cout << "Invalid input.  Please enter a single value corresponding to a menu item.\n";
			cin >> response;
		}
		user_comm = tolower(response[0]);
		cin.ignore(10000, '\n'); // this will clear the cin buffer so that the next getline will work

		switch (user_comm) {
		case '1':
		{ //Need braces when intialising a variable in a switch
			string userWrd = "";
			cout << "Please enter a word...\n\n";
			getline(cin, userWrd);
			dict.binFindWord(userWrd);
			break;
		}
		case '2':
			dict.threeZs();
			break;
		case '3':
			dict.qButNoU();
			break;
		case EXIT:
			cout << "Exiting...\n";
			break;
		default:
			cout << "Selection not recognised. Please enter a valid selection.\n";
			break;
		}
	}
}

