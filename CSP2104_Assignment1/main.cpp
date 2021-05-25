#include"Dictionary_Part02.h"
using namespace std;

int main() {
	//Use constructor to call loadDictionary on parameter filename
	Dictionary_Part02 dict("dictionary2021.txt");
	vector<Word> noun_list;

	const char EXIT = 'x';
	cout << "Welcome to Dictionary Part 1!\n";
	char user_comm = '0';
	//menu loops until user enters 'x'
	while (user_comm != EXIT) {

		string response;
		//menu options
		cout << "Enter '1' to Find a word.\n";
		cout << "Enter '2' to List all word(s) that contain more than three 'z''s.\n";
		cout << "Enter '3' to List all word(s) that contain a 'q' that is not followed by a 'u'.\n";
		cout << "Enter '4' to List all word(s) that are both a Noun and a Verb.\n";
		cout << "Enter '5' to List all word(s) that are palindromes.\n";
		cout << "Enter '6' to Find all anagrams of a target word\n";
		cout << "Enter '7' to play the Word Guessing Game!\n";
		cout << "Enter " << EXIT << " to exit the program...\n";
		cin >> response;
		// To prevent cin buffer issues and unintentional input, take a string as cin and test it for length
		// If the user puts a space in the input or it's too long, be mean to them
		while (response.length() > 1) { //only allow input length of 1
			cout << "Invalid input.  Please enter a single value corresponding to a menu item.\n";
			cin >> response;
		}

		user_comm = tolower(response[0]); // take only the first char of response as input - user is warned
		cin.ignore(10000, '\n'); // this will clear the cin buffer so that the next getline will work

		switch (user_comm) {
		case '1':
		{ //Need scope when intialising a variable in a switch
			string userWrd = "";
			cout << "Please enter a word...\n";
			getline(cin, userWrd);
			dict.binFindWord(userWrd); // call binFindWord()
			break;
		}
		case '2':
			dict.threeZs();
			break;
		case '3':
			dict.qButNoU();
			break;
		case '4':
			dict.listAllVerbNouns();
			break;
		case '5':
			dict.listAllPalindromes();
			break;
		case '6': 
		{
			string userWrd = "";
			cout << "Please enter a word...\n";
			getline(cin, userWrd);
			dict.getAnagrams(userWrd);
			break;
		}
		case '7':
		{
			//We only need to fill this list once per run
			if (noun_list.empty()) {
				noun_list = dict.fillNounVector();
			}
			dict.guessingGame(noun_list);
			break;
		}
		case EXIT:
			cout << "Exiting...\n";
			break;
		default:
			cout << "Selection not recognised. Please enter a valid selection.\n";
			break;
		}
	}
}

