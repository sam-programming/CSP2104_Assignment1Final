/*	Class: Dictionary_Part01
	Written by: Samuel Warner
	Date Created: 5/03/2021
	Summary:
	The Dictionary_Part01 class has one attribute - a vector of Word objects called dictionary.
	It has two constructors - one without parameters, and one that takes a string filename and

	uses it to call the loadDictionary() method.  The loadDictionary(string) method reads the
	given .txt file and converts its contents to Word objects, which it adds to the vector to
	form a complete dictionary.  It also contains a search function - binFindWord(string) - that
	uses the binary search method to quickly find a target word and call its printDefinition()
	method. Then their are two novel methods: one - threeZs- that finds all words that have more
	than 3 'z's; and another - qButNotU() - that finds all words that contain that char 'q' that
	is not immediately followed by the char 'u'.
*/
#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include"Word.h"

using namespace std;

//Declaration section
class Dictionary_Part01 {
protected:
	//dynamic STL container for dictionary
	vector<Word> dictionary;
public:
	//constructors
	Dictionary_Part01(string);
	Dictionary_Part01();
	//methods

	void printWordVector(vector<Word>);

	void loadDictionary(string);
	void binFindWord(string);
	void threeZs();
	void qButNoU();


};
//Implementation section

/*  Function Name: Dictionary_Part01
	Input: String filename
	Output: None
	Summary: Constructor overload that calls loadDictionary()
	Written by: Samuel Warner
	Date Created: 10/03/2021

*/
Dictionary_Part01::Dictionary_Part01(string filename) {
	loadDictionary(filename);
}

/*  Function Name: Dictionary_Part01

	Input: None
	Output: None
	Summary: Empty Constructor
	Written by: Samuel Warner
	Date Created: 10/03/2021
*/
Dictionary_Part01::Dictionary_Part01() {}

/*  Function Name: printWordVector
	Input: vector<Word>
	Output: None
	Summary: Uses a range loop to iterate through a vector and cout its contents
	Written by: Samuel Warner
	Date Created: 20/04/2021
*/
void Dictionary_Part01::printWordVector(vector<Word> words) {
	for (Word wrd : words) {
		cout << wrd.getWord() << endl;
	}
}

/*  Function Name: loadDictionary
	Input: String filename
	Output: None
	Summary: Attempts to read a .txt file. Creates word objects from the lines of the file,
	and pushes them into the vector<word> dictionary.
	Written by: Samuel Warner
	Date Created: 10/03/2021

*/
void Dictionary_Part01::loadDictionary(string filename) {
	Word entry;
	string line, word, type;

	cout << "Attempting to read text file... \n";
	ifstream dict_file(filename);

	//Check if file is readable
	if (dict_file.is_open()) {
		cout << "Loading " << filename << "...\n";
		//string delimiter = " ";
		while (!dict_file.eof()) {
			//first line contains word and type delimited by " "
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
			//line after definition is blank, so use getline again to iterate over it before exiting the loop
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

/*  Function Name: binFindWord

	Input: string word
	Output: None
	Summary: Searches for the target word.  Uses a binary search function.  Compared to a linear
	search, which has a max time complexity of O(n), binary search has a max time complexity of
	log2(n). For a dictionary of 106,184 words, that equates to maximum iterations of linear: 106,184
	(for the last word in the dictionary); maximum iterations for binary: 17.
	Written by: Samuel Warner
	Date Created: 10/03/2021

*/
void Dictionary_Part01::binFindWord(string word) {
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
		//NEED TO FIND AND REPLACE THE DASH BECAUSE IT IS FUCKING WITH THE SEACH
		if (comp == 0) {
			dictionary[mid].printDefinition();
			cout << "Word found in " << iterations << " iterations\n\n";
			return;
		}
		else if (comp < 0)
			right = mid - 1; //shift the right border to 1 less than mid		
		else
			left = mid + 1; //shift the left border to 1 more than mid		
	}
	cout << "Word not found.\n";
}

/*  Function Name: threeZs

	Input: None
	Output: None
	Summary: Iterates through each word in the dictionary and prints the word(s) that
	contain more than 3 'z's.
	Written by: Samuel Warner
	Date Created: 10/03/2021
*/

void Dictionary_Part01::threeZs() {
	vector<Word> results; // place the results into a vector 
	int index;
	const char CHAR = 'z';

	for (Word wrd : dictionary) {
		index = wrd.getWord().find(CHAR); //if word contains a z
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
	printWordVector(results);
	cout << endl;
	return;
}

/*  Function Name: qButNoU

	Input: None
	Output: None
	Summary: Iterates through each word in the dictionary and prints the word(s) that contain a 'q'
	but not a a proceeding 'u'.
	Written by: Samuel Warner
	Date Created: 10/03/2021

*/
void Dictionary_Part01::qButNoU() {
	vector<Word> results;
	const char CHAR_1 = 'q';
	const char CHAR_2 = 'u';

	for (Word wrd : dictionary) {
		string word = wrd.getWord();
		int index = word.find(CHAR_1); // find 'q'
		if (index != string::npos) {   // if 'q' is found
			if (word[index + 1] != CHAR_2) // is 'u' at index +1?
				results.push_back(wrd);  // add word to vector
		}
	}
	cout << "Words that contain a 'q' that is not followed by a 'u' are:\n";
	printWordVector(results);
	cout << endl;
}



=======
void Dictionary_Part01::guessingGame() {
	// this can be permanent in dictionary part 2 and accessed by reference
	vector<Word> nouns;
	//fill noun vector
	for (Word wrd : dictionary) {
		if (wrd.getType() == "Noun (n.)") {
			nouns.push_back(wrd);
		}
	}
	bool play_again = true;
	int score = 0;
	while (play_again == true) {
		int guesses = 3;
		int letters_revealed = 0;
		string guess;
		string again;
		string placeholder;
		bool correct = false;
		//generate random number
		//randomises the seed because why have an actual random number
		srand(time(0) * 473 - 18); 
		int random = rand() % nouns.size();
		cout << "Num: " << random << endl;
		string word = nouns[random].getWord();
		cout << "Guess the word!\n";
		cout << "Definition: ";
		cout << nouns[random].getDef() << endl;
		for (int x = 0; x < word.size(); x++) {
			placeholder.push_back('_');
		}

		while (guesses != 0) {
			cout << "You have " << guesses << " remaining guesses...\n";
			cout << placeholder << " " << placeholder.size() << " letters" << endl;
			//validate this input
			getline(cin, guess);
			if (guess == word) {				
				correct = true;
				break;
			}
			else {
				cout << "Incorrect.\n";
				guesses -= 1;
				placeholder[letters_revealed] = word[letters_revealed];
				letters_revealed += 1;
			}
		}
		if (correct == true) {
			score += 1;
			cout << "Correct!\n";
			cout << "Your score is " << score << endl;;
		}
		else {
			if (score > 0) {
				score -= 1;
			}
			cout << "The word is " << word << endl;
			cout << "Incorrect\n";
			cout << "Your score is " << score << endl;
		}
		cout << "Would you like to play again? 'Y' for Yes, 'N' for No.\n";
		//validate this input
		getline(cin, again);
		if (toupper(again[0]) == 'Y')		{
			play_again = true;
		} 
		else if (toupper(again[0]) == 'N')
		{ 
			play_again = false; 
		}	
	}
}

