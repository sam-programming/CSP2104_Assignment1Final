/*      
	Written by: Samuel Warner
	Date Created: 23/03/2021
	The Word class has three private attributes: a string word, which is the name of the word; a string type,
	that is the type of word, such as noun, proper noun, verb, etc.; and a string definition - the definition
	of the word.  
	It has a constructor with no parameters that initialises default values for all three attributes, and a 
	constructer with three string parameters corresponding to the three attributes.  It contains getter and
	setter methods for each attribute - setting and returning the attributes corresponding to the methods.
	It contains two auxiliary functions - capitaliseProperNoun and removeSemicolons - that are called in the
	printDefinition() function to capitalise proper nouns if the word type is proper noun, and remove the
	semicolons from the definition that are seperating multiple definitions within the same word.  
	printDefinition() prints out the word, the type (expanded from shorthand), and the definition, all seperated
	by '\n'.
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
	//two methods used in-class
	string capitaliseProperNoun();
	string removeSemicolons();
public:
	//constructors
	Word();
	Word(string, string, string);
	//Methods to set word object attributes
	void setWord(string);
	void setType(string);
	void setDef(string);
	//Methods to retrieve object attributes
	string getWord();
	string getType();
	string getDef();
	// method to cout word information
	void printDefinition();	
};
//Word implementation

//default constructor
Word::Word() {
	word = "default word";
	type = "";
	definition = "This is a default word";
}

//constructor with parameters
Word::Word(string word, string type, string definition) {
	this->word = word;
	this->type = type;
	this->definition = definition;
}

//set object's word attribute to parameter
void Word::setWord(string word) {
	this->word = word;
}
//set object's type attribute to parameter
void Word::setType(string type) {
	this->type = type;
}
//set object's definition attribute to parameter
void Word::setDef(string definition) {
	this->definition = definition;
}

//return word attribute with first letter lowered to standardise words for comparison with user input
string Word::getWord() {
	//use tolower to standardise input (proper nouns are capitalised in the dict file)
	word[0] = tolower(word[0]);
	return word;
}
//type is set as a shorthand - see const string TYPES[] for examples - but should be displayed expanded
//get type identifies the shorthand and returns the corresponding expanded type via switch comparison
string Word::getType() {
	
	const int SIZE = 8;
	const string TYPES[SIZE] = { "v", "n", "adv", "adj", "prep", "pn", "n_and_v", "misc" };
	//using distance() and find() to locate the index of the item in the types[] array
	int x = distance(TYPES, find(TYPES, TYPES + SIZE, type)); 
	//Use switch to return the type corresponding to array index
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
//returns the definition
string Word::getDef() {
	return definition;
}

//tests if a word is of type properNoun.  If it is, capitalise the first letter of the word, as per the brief.
//proper nouns are by default capitalised, however the are made lowercase in getWord() method above to
//standardise user input for comparison
string Word::capitaliseProperNoun() {
	string word = getWord(); 
	string type = "Proper Noun (pn.)";
	if (getType() == type) { // if word type is proper noun
		for (int i = 0; i < word.size(); i++) { // loop word.size() amount of times
			word[i] = toupper(word[i]); //capitalise first letter
		}
	}
	return word;
}

//the definition attribute may contain many definitions, and these are seperated by semicolons
//the removeSemicolons() method removes these semicolons, and in their place inserts a newline '\n'
//it also tidies up some leading whitespace
string Word::removeSemicolons() {
	string def = getDef(); // make copy of definition
	int index = def.find(";"); // get index of semicolon
	while (index != string::npos) { // while a semicolon is not not found
		def.erase(index, 1);	 // delete semicolon so we don't keep finding it, length is 1
		def.insert(index, "\n"); // insert a newline at old semicolon index
		// Delete extra whitespace - some definitions are preceeded by two spaces, some by one
		if (def[index + 1] == ' ' && def[index + 2] == ' ') {
			def.erase(index + 1, 2);
		}
		if (def[index + 1] == ' ') {
			def.erase(index + 1, 1);
		}
		index = def.find(";"); // find the next one
	}
	return def;
}
//calls removeSemicolon and capitaliseProperNoun, and then prints the word, type, and definition
//getType() is explicitly called here - getDef and getWord are called by the two auxiliary methods
void Word::printDefinition() {
	string word = capitaliseProperNoun();
	string def = removeSemicolons();

	cout << word << "\n" << getType() << "\n" << def << "\n\n";
}
