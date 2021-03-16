#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"Word.cpp"
using namespace std;

class Dictionary_Part01 {
private:
	vector<Word> dictionary;
public:
	// loads the dictionary file into the dictionary vector
	void loadDictionary(string filename) {

		Word entry;
		string line;
		string word;
		string type;
		string definition;

		cout << "Attempting to read text file... \n";
		ifstream dict_file(filename);

		//Check if file is readable
		if (dict_file.is_open()) {
			cout << "Loading " << filename << "...\n";
			//string delimiter = " ";
			while (!dict_file.eof()) {
				//first line contains word and type: post [n_and_v] delimited by " "
				getline(dict_file, line);
				// word will be from substring 0 to delimiter " ".  find() should find the first instance
				// of delimiter " "
				entry.setWord(line.substr(0, line.find(" ")));
				// type will be from substring "[" to "]", using find() again
				type = line.substr(line.find("[") + 1, line.find("]"));
				type.pop_back();
				entry.setType(type);
				// delimiter for all definitions is '\n' (automatic for getline), delimiter between definitions is ';'
				getline(dict_file, line);
				entry.setDef(line);
				//new line here to iterate over the blank line
				getline(dict_file, line);
				// add the Word object to the word vector
				dictionary.push_back(entry);
			}
			cout << "File Loaded Successfully.\n\n";
		}
		else {
			cout << "File not found";
		}
	}
	//Finds a word in a dictionary, if it is in the dictionary
	void findWord(string word) {
		for (Word wrd : dictionary) {
			if (wrd.getWord() == word) {
				wrd.printDefinition();
				return;
			}
		}
		cout << "Word not found.\n";
	}

	// Binary search function - will increase the efficiency of the algorithm by log2N
	void binFindWord(string word) {
		// make the word lowercase in case input is funky but spelling is right
		for (int i = 0; i < word.size(); i++) 
			word[i] = tolower(word[i]);
		
		int left = 0;
		int right = dictionary.size() - 1;
		int mid = 0;
		int iterations = 0;

		while (left <= right) { // while doesn't equal right
			iterations++;
			mid = floor((left + right) / 2); // find the middle as an integer
			// .compare() method will compare two strings and return 0 if they match,
			// < 0 if string 1 is alphabetically lower, > 0 if alphabetically higher
			int comp = word.compare(dictionary[mid].getWord());
			if(comp == 0) {
				dictionary[mid].printDefinition();
				cout << "Word found in " << iterations << " iterations\n\n";
				return;
			}
			else if (comp < 0) {
				right = mid - 1; //shift the right border to 1 less than mid
			}
			else {
				left = mid + 1; //shift the left border to 1 more than mid
			}
		}
		cout << "Word not found.\n";
	}

	//Replaces a word at the destination using address of operator
	//Not required for assignment
	void replace(string oldWord, string newWord) {
		for (Word& wrd : dictionary) {
			if (wrd.getWord() == oldWord) {
				wrd.setWord(newWord);
				return;
			}
		}
		cout << "Word not found\n";
		return;
	}

	// Iterates through each word in the dictionary and prints the word(s) that contain more than 3 'z's		
	void threeZs() {
		vector<Word> results;
		int index;
		const char CHAR = 'z';

		for (Word wrd : dictionary) {
			index = wrd.getWord().find(CHAR);
			if (index != string::npos) {
				int zs = 0; // keep count of 'z's
				string word = wrd.getWord();
				for (int i = 0; i < word.size(); i++) { //iterate over each charater in word
					if (word[i] == CHAR) {
						zs++; // count the 'z's
					}
				}
				if (zs > 3) {
					results.push_back(wrd); //if word has 3 or more 'z's, add to vector
				}
			}
		}
		cout << "Word(s) that contain more than three 'z''s are:\n";
		for (Word wrd : results) { //print words in vector			
			cout << wrd.getWord() << "\n";
		}
		cout << endl;
		return;
	}

	// Iterates through each word in the dictionary and prints the word(s) that contain a 'q' but not a a proceeding 'u'
	void qButNoU() {
		vector<Word> results;
		const char CHAR_1 = 'q';
		const char CHAR_2 = 'u';

		for (Word wrd : dictionary) {
			string word = wrd.getWord();
			int index = word.find(CHAR_1);
			if (index != string::npos) {
				if(word[index+1] != CHAR_2)
					results.push_back(wrd);
			}
		}
		cout << "Words that contain a 'q' that is not followed by a 'u' are:\n";
		for (Word wrd : results) {
			cout << wrd.getWord() << "\n";
		}
		cout << endl;
	}
};

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