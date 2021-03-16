/*  Defines the Word class
	Fields:
		- word : Skdntring
		- type : String
		- definition : String
	Methods:
		+ getWord() : String
		+ getType()
		+ getDef() : String
		+ printDefinition() : void
*/

#include<iostream>
#include<string>
using namespace std;

class Word {
private:
	string word;
	string type;
	string definition; 
	const static int SIZE = 8;

	string types[SIZE] = { "v", "n", "adv", "adj", "prep", "pn", "n_and_v", "misc" };

public:
	//Setters
	void setWord(string w) {
		word = w;
	}
	void setType(string t) {
		type = t;
	}
	void setDef(string def) {
		definition = def;
	}

	//Getters
	string getWord() {
		word[0] = tolower(word[0]); // just to standardise input so proper nouns don't throw the searches
		return word;
	}

	string getType() {
		// using distance() and find() to locate the index of the item in the types[] array
		int x = distance(types, find(types, types + SIZE, type));

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
			return "Proper Noun (pn.)";
		case 6:
			return "Nound and Verb (n.v.)";
		case 7:
			return "Miscellaneous (misc.)";
		default:
			return "Type not found.";
		}
	}

	string getDef() {
		return definition;
	}

	string capitaliseProperNoun() {
		string word = getWord();
		if (getType() == "Proper Noun (pn.)") { // if word type is proper noun
			for (int i = 0; i < word.size(); i++) { // loop word.size() amount of times
				word[i] = toupper(word[i]); //capitalise
			}
		}
		return word;
	}

	string removeSemicolons() {
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

	void printDefinition() {
		string word = capitaliseProperNoun();
		string def = removeSemicolons();

		cout << word << "\n" << getType() << "\n  " << def << "\n\n";
	}
};