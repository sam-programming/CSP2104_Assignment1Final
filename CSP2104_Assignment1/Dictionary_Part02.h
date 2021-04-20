#pragma once
#include<algorithm>
#include "Dictionary_Part01.h"

class Dictionary_Part02 : public Dictionary_Part01 {
public:
	//declaration section	 
	Dictionary_Part02(string);
	void listAllVerbNouns();
	//self explanitory
	void listAllPalindromes();
	void getAnagrams(string);
	//Present the definition of a random noun and the length of that noun and ask 
	// the user to guess that noun, giving three tries.  After the first incorrect guess,
	// reveal the first letter of the word - and so on.	
	void guessingGame();
};

//implementation sections
/*  Function Name: Dictionary_Part02
	Input: string filename
	Output: none
	Summary: Constructor that calls the base class constructor with parameter filename
	Written by: Samuel Warner
	Date Created: 20/04/2021
*/
Dictionary_Part02::Dictionary_Part02(string filename) : Dictionary_Part01(filename) {}

/*  Function Name: listAllVerbNouns
	Input: none
	Output: none
	Summary: Searches the dictionary and lists all words that are both a noun and a verb
	Written by: Samuel Warner
	Date Created: 20/04/2021
*/
void Dictionary_Part02::listAllVerbNouns() {
	vector<Word> verbNouns;
	string type = "NounAndVerb (n.v.)";
	for (Word wrd : dictionary) {
		if (wrd.getType() == type) {
			verbNouns.push_back(wrd);
		}
	}
	printWordVector(verbNouns);
}

/*  Function Name: listAllPalindromes
	Input: none
	Output: none
	Summary: Searches the dictionary and lists all words that are palindromes.
	Written by: Samuel Warner
	Date Created: 20/04/2021
*/
void Dictionary_Part02::listAllPalindromes() {
	vector<Word> palindromes;
	string reverse;
	string word;
	for (Word wrd : dictionary) {
		reverse = "";
		word = wrd.getWord();
		if (word.length() > 1) {
			for (int i = word.length() - 1; i >= 0; i--) {
				reverse.push_back(word[i]);
			}
			if (word == reverse) {
				palindromes.push_back(wrd);
			}
		}
	}
	printWordVector(palindromes);
}

/*  Function Name: getAnagrams
	Input: string word
	Output: none
	Summary: Takes a string as a parameter and searches the dictionary for words that are 
	anagrams of that parameter.  This is achieved by sorting the target word and the words
	to compare it with and then comparing the sorted strings.
	Written by: Samuel Warner
	Date Created: 20/04/2021
*/

void Dictionary_Part02::getAnagrams(string targ) {
	vector<Word> anagrams;
	string word = "";
	string target = targ;
	//use algorithm's sort method to sort the target alphabetically
	sort(target.begin(), target.end());
	for (Word wrd : dictionary) {
		//only proceed if the dictionary entry is the same length of the target
		//also ignore the word if it is the target word
		if (wrd.getWord().length() == target.length() && wrd.getWord() != targ) {
			word = wrd.getWord();
			//sort the word and compare it to the sorted target
			sort(word.begin(), word.end());
			if (word == target) {
				anagrams.push_back(wrd);
			}
		}
	}
	//if there are any results, cout them
	if (anagrams.size() != 0) {
		printWordVector(anagrams);
	} 
	else {
		cout << "No anagrams of " << targ << " found.\n";
	}
}