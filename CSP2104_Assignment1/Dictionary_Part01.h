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
#include <string>

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
	void findWord(string);
	void threeZs();
	void qButNoU();
	string removeDash(string);//may not need this
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

//Removes dashes from words - they seem to confuse the binary search
string Dictionary_Part01::removeDash(string word) {
	
	int index = word.find("-");
	if (index != string::npos) {
		word.erase(index, 1);
	}
	return word;
}
/*  Function Name: findWord

	Input: string word
	Output: None
	Summary: Sadly, the binary word find is not working. So this is the basic word find.
	Written by: Samuel Warner
	Date Created: 10/03/2021

*/
void Dictionary_Part01::findWord(string word) {
	// make the word lowercase in case input is funky but spelling is right
	for (Word wrd : dictionary) {
		if (wrd.getWord() == word) {
			cout << "Word found." << endl;
			wrd.printDefinition();
			return;
		}		
	}
	cout << "Word not found." << endl;	
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

