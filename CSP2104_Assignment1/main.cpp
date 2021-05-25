#include"Dictionary_Part02.h"
#include"Tri_Gram.h";
using namespace std;

int main() {
	//Use constructor to call loadDictionary on parameter filename
	string filename = "dictionary2021.txt";
	Dictionary_Part02 dict(filename);
	vector<Word> noun_list;
	Tri_Gram tri_gram("dictionary2021.txt");

	const char EXIT = 'x';
	cout << "\n\n ---------------------------------------\n";
	cout << " |    Welcome to Dictionary Part 2!    |\n";
	cout << " ---------------------------------------\n";
	char user_comm = '0';
	//menu loops until user enters 'x'
	while (user_comm != EXIT) {
		string response;
		//menu options
		cout << " - Enter '1' to Find a word.\n";
		cout << " - Enter '2' to List all word(s) that contain more than three 'z''s.\n";
		cout << " - Enter '3' to List all word(s) that contain a 'q' that is not followed by a 'u'.\n";
		cout << " - Enter '4' to List all word(s) that are both a Noun and a Verb.\n";
		cout << " - Enter '5' to List all word(s) that are palindromes.\n";
		cout << " - Enter '6' to Find all anagrams of a target word\n";
		cout << " - Enter '7' to play the Word Guessing Game!\n";
		cout << " - Enter '8' to play with Tri-Grams\n";
		cout << " - Enter " << EXIT << " to exit the program...\n";
		cin >> response;
		// To prevent cin buffer issues and unintentional input, take a string as cin and test it for length
		// If the user puts a space in the input or it's too long, be mean to them
		while (response.length() > 1 ) { //only allow input length of 1
			cout << "Invalid input.  Please enter a single value corresponding to a menu item.\n";
			cin >> response;
		}

		user_comm = tolower(response[0]); // take only the first char of response as input - user is warned
		cin.ignore(10000, '\n'); // this will clear the cin buffer so that the next getline will work

		switch (user_comm) {
		case '1':
		{ //Need scope when intialising a variable in a switch
			string userWrd = "";
			bool found;
			cout << "Please enter a word...\n";
			getline(cin, userWrd);
			dict.findWord(userWrd); // call binFindWord()			
			break;
		}
		case '2':
			dict.threeZs();
			break;
		case '3':
			dict.qButNoU();
			break;
		case '4':
			cout << endl;
			dict.listAllVerbNouns();
			cout << endl;
			break;
		case '5':
			cout << endl;
			dict.listAllPalindromes();
			cout << endl;
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
		case '8': {
			char menu_item = '0';
			while (menu_item != '3') {
				string usr_input = "";
				cout << " - Enter '1' to Input two characters and get the three most likely characters to occur after those two characters. " << endl;
				cout << " - Enter '2' to generate a list of 10 fake words, using Tri-Grams, that are not in the dictionary"<< endl;
				cout << " - Enter '3' to return." << endl;
				cin >> usr_input;
				while (usr_input.length() > 1) {
					cout << "Invalid input.  Please enter a single value corresponding to a menu item.\n";
					cin >> usr_input;
				}
				menu_item = usr_input[0];
				if (menu_item == '1') {
					tri_gram.complete_Trigram(filename);
					cout << endl;
				}
				else if (menu_item == '2') {
					tri_gram.generate_Fake_Word(10, dict);
					cout << endl;
				}				
			}
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

