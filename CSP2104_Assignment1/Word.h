/*  
	Defines the Word class
	Fields:
		- word : String
		- type : String
		- definition : String
	Methods:
		+ getWord() : String
		+ getType()
		+ getDef() : String
		+ capitaliseProperNoun() : void
		+ removeSemicolons() : void
		+ printDefinition() : void
*/

#pragma once
#include<iostream>
#include<string>
using namespace std;

//Declaration Section
class Word {
private:
	//attributes
	string word;
	string type;
	string definition;
public:
	//getters
	void setWord(string);
	void setType(string);
	void setDef(string);
	//setters
	string getWord();
	string getType();
	string getDef();
	//two functions used in-class
	string capitaliseProperNoun();
	string removeSemicolons();
	// function to cout word information
	void printDefinition();	
};
//Word implementation
void Word::setWord(string w) {
	word = w;
}
void Word::setType(string t) {
	type = t;
}
void Word::setDef(string d) {
	definition = d;
}

string Word::getWord() {
	//use tolower to standardise input (proper nouns are capitalised in the dict file)
	word[0] = tolower(word[0]);
	return word;
}

string Word::getType() {
	
	const int SIZE = 8;
	const string TYPES[SIZE] = { "v", "n", "adv", "adj", "prep", "pn", "n_and_v", "misc" };
	//using distance() and find() to locate the index of the item in the types[] array
	int x = distance(TYPES, find(TYPES, TYPES + SIZE, type)); // consider clarifying these vairables
	//int x = 1;
	//Use switch to return the appropriate type when required for printDefinition()
	switch (x) {
	case 0:
		return "Verb (v.)";
	case 1:
		return "Noun (n.)";
	case 2:
		return "Adverb (adv.)";
	case 3:
		return "Adjective (adj.)";
	case 4:
		return "Preposition (prep.)";
	case 5:
		return "ProperNoun (pn.)";
	case 6:
		return "NounAndVerb (n.v.)";
	case 7:
		return "MiscWords (misc.)";
	default:
		return "Type not found.";
	}
}

string Word::getDef() {
	return definition;
}

string Word::capitaliseProperNoun() {
	string word = getWord();
	string type = "Proper Noun (pn.)";
	if (getType() == type) { // if word type is proper noun
		for (int i = 0; i < word.size(); i++) { // loop word.size() amount of times
			word[i] = toupper(word[i]); //capitalise
		}
	}
	return word;
}

string Word::removeSemicolons() {
	string def = getDef(); // make copy of definition
	int index = def.find(";"); // get index of semicolon
	while (index != string::npos) { // while a semicolon is not not found
		def.erase(index, 1);	 // delete semicolon so we don't keep finding it, length is 1
		def.insert(index, "\n"); // insert a newline
		// Delete extra spaces - some definitions are preceeded by two spaces, some by one - for tidiness
		if (def[index + 1] == ' ' && def[index + 2] == ' ') {
			def.erase(index + 1, 1);
		}
		index = def.find(";");
	}
	return def;
}

void Word::printDefinition() {
	string word = capitaliseProperNoun();
	string def = removeSemicolons();

	cout << word << "\n" << getType() << "\n  " << def << "\n\n";
}