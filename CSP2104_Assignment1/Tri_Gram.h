#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
#include<random>
#include<fstream>
#include"Dictionary_Part02.h"
using namespace std;

class Tri_Gram {
private:
	const static int VALUES = 27;
	int tri_gram[VALUES][VALUES][VALUES] = { 0 }; //27 with spaces 
	// trigram[0][0][0] = 1 means the number of occurances of AAA is 1
	// trigram[0][0][0]++; adds one to that
public:
	Tri_Gram(string);
	void load_3D_Array(string);
	void complete_Trigram(string);
	void generate_Fake_Word(int, Dictionary_Part02);
};

//Constructor that calls load_3D_Array()
Tri_Gram::Tri_Gram(string filename) {
	load_3D_Array(filename);
}

//------------------------- HELPER FUNCTIONS ----------------------------//

/*  Function Name: return_Index
	Input: char
	Output: int
	Summary: Robbed from the venerable Martin Masek.  Only difference here is
	I return 0 for all cases that aren't valid lowercase letters. Thus,
	every non-alphabetic character is treated as a space. Risky business.
	Written by: Samuel Warner
	Date Created: 23/05/2021
*/
// Valid ACSII Range { 32, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 
// 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122 };
int return_Index(char letter) {
	int code = int(letter);
	int index = 0;
	if ((code >= 97) && (code <= 122))
		index = code - (int)'a' + 1; //whack 96 off it
	return index;
}
/*	Function Name: to_Char
	Input: int
	Output: Char
	Summary: Converts an int to a char unless that int doesn't fall in the
	specified range.
	Written by: Samuel Warner
	Date Created: 23/05/2021
 */
char to_Char(int code) {
	char letter;
	if (code == 0) {
		letter = ' ';
	}
	else {
		letter = char(code + (int)'a' - 1);
	}
	return letter;
}


/*  Function Name: sort_By_Val
	Input: pair<char, int>, pair<char, int>
	Output:bool
	Summary: Returns true if element a is greater then element b.  To be used in the
	algorithm module's sort() function.  Adapted from:
	Singh, M. (May, 2017). Sorting Vector of Pairs in C++.  Taken from:
	https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-1-sort-by-first-and-second/
*/

bool sort_By_Val(const pair<char, int>& a, const pair<char, int>& b) {
	return(a.second > b.second);
}
/* I don't like this
void sorted_Trigram_Vector(int x, int y, vector<pair<char, int>> &arr, int tri_gram[27][27][27]) {
	for (int z = 1; z < VALUES; z++) {
		char a = to_Char(z);
		int b = tri_gram[x][y][z];
		//make pair allows us to push_back pairs
		results.push_back(make_pair(a, b));
	}
	//lets sort this baby
	sort(results.begin(), results.end(), sort_By_Val);
}
*/
//-------------------------------- CLASS FUNCTIONS -------------------------------------//

/*  Function Name: load_3D_Array
	Input: string
	Output: none
	Summary: Reads a .txt file line by line. Parses the line in chunks of three characters
	and records the instance of that combination in the class attribute tri_Gram.
	Written by: Samuel Warner
	Date Created: 23/05/2021
*/
void Tri_Gram::load_3D_Array(string filename) {

	string line;
	int index1, index2, index3;
	ifstream txt_file(filename);

	//Check if file is readable
	if (txt_file.is_open()) {
		cout << "Loading Tri-Grams...\n";
		while (!txt_file.eof()) {
			getline(txt_file, line);
			//Lets go through the line (-2 so we don't get index range error)
			if (line.length() != 0) {
				for (int i = 0; i <= line.length() - 2; i++) {
					//if it isn't an allowable value, make it a space
					index1 = return_Index(tolower(line[i]));
					index2 = return_Index(tolower(line[i + 1]));
					index3 = return_Index(tolower(line[i + 2]));
					//this is a tri-gram
					tri_gram[index1][index2][index3]++;
				}
			}
		}
		cout << "File loaded successfully" << endl;
	}
}
/*  Function Name: complete_Trigram
	Input: string
	Output: none
	Summary: Takes two chars as the user entry (in string format) and uses
	the class atribute tri_Gram to return the 3 most likely letters to appear
	after that letter.  The user is stunned, and rapturous.
	Written by: Samuel Warner
	Date Created: 24/05/2021
*/
void Tri_Gram::complete_Trigram(string filename) {
	// Using a vector of pairs here instead of a map. Why? We are not too concerned 
	// that it will violate the unique keys rule, and it is sortable by value
	vector<pair<char, int>> results;
	string response;
	cout << "\nEnter first two letters of the Tri-Gram:" << endl;
	cin >> response;
	//input validation
	while (response.length() > 2) {
		cout << "Please enter two letters only." << endl;
		cin >> response;
	}
	int x = return_Index(response[0]);
	int y = return_Index(response[1]);
	//gonna skip the space for this one. VALUES is our class constant
	for (int z = 1; z < VALUES; z++) {
		char a = to_Char(z);
		int b = tri_gram[x][y][z];
		//make pair allows us to push_back pairs
		results.push_back(make_pair(a, b));
	}
	//lets sort this baby
	sort(results.begin(), results.end(), sort_By_Val);
	//Find out how many results we can print
	int limit = 0;
	for (const auto& it : results) {
		if (limit <= 3) {
			if ((limit == 0) && (it.second == 0)) {
				cout << "\nThere are no instances of tri-grams featuring " <<
					response[0] << response[1] << " in " << filename << "." << endl;
				break;
			}
			else if ((limit == 1) && (it.second == 0)) {
				cout << "\nThere is only one instance of a tri-gram featuring " <<
					response[0] << response[1] << " in " << filename << ":" << endl;
				break;
			}
			else if ((limit == 2) && (it.second == 0)) {
				cout << "\nThere are only 2 instances of tri-grams featuring " <<
					response[0] << response[1] << " in " << filename << ":" << endl;
				break;
			}
			else if (limit >= 3) {
				cout << "\nThe top 3 tri-grams featuring " <<
					response[0] << response[1] << " in " << filename << " are: " << endl;
				break;
			}
			limit++;
		}
	}
	//print out results
	for (const auto& it : results) {
		if (limit > 0) {
			cout << response[0] << response[1] << it.first << endl;
			limit--;
		}
	}
}

/*  Function Name: generate_Fake_Word
	Input: none
	Output: none
	Summary: Use the tri-gram table to generate 10 fake words, of a length
	Written by: Samuel Warner
	Date Created: 24/05/2021
*/
void Tri_Gram::generate_Fake_Word(int num_words, Dictionary_Part02 dict) {
	vector<string> fake_words;
	for (int n = 0; n < num_words; n++) {
		string fake_word = "";
		//vector of possible chars to complete trigram
		vector<pair<char, int>> results;
		//set up random number generator
		random_device rd;  //Will be used to obtain a seed for the random number engine
		mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		// "Produces random integer values i, uniformly distributed on the closed interval [a, b], 
		// that is, distributed according to the discrete probability function."
		//https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
		// various RNGs
		uniform_int_distribution<> distrib(1, 26);
		uniform_int_distribution<> dist_word_length(3, 10);
		uniform_int_distribution<> dist_0_2(0, 2);
		uniform_int_distribution<> dist_0_1(0, 1);

		int rand1 = distrib(gen);
		int rand2 = distrib(gen);
		//first, we will get a fairly common random combo with a space to start with to begin our word
		while (tri_gram[0][rand1][rand2] < 20) {
			rand1 = distrib(gen);
			rand2 = distrib(gen);
		}
		//push them to the fakeword string
		fake_word.push_back(to_Char(rand1));
		fake_word.push_back(to_Char(rand2));
		int i = 0;
		while (i < dist_word_length(gen)) {
			results.clear();
			// x and y are the last two values
			int x = return_Index(fake_word[fake_word.length() - 2]);
			int y = return_Index(fake_word[fake_word.length() - 1]);
			//populate the vector with key value pairs
			for (int z = 1; z < VALUES; z++) {
				char a = to_Char(z);
				int b = tri_gram[x][y][z];
				results.push_back(make_pair(a, b));
			}
			//Results is now a sorted key/value vector of the completing chars, 
			//in order of most likely to least:
			//'[{'e' : 1300},
			//  {'r' : 400},
			//  {   ...   }]
			sort(results.begin(), results.end(), sort_By_Val);
			//just take the a if there are no results or only one result
			// results[x].second returns the value
			if ((results[0].second == 0) || (results[1].second == 0)) {
				rand1 = 1;
				fake_word.push_back(results[rand1].first);
			}//if there are only two results
			else if (results[2].second == 0) {
				rand1 = dist_0_1(gen);
				fake_word.push_back(results[rand1].first);
			}
			else {// there are three or more results so we choose between them
				//get random num between 0 and 2	
				rand1 = dist_0_2(gen);
				fake_word.push_back(results[rand1].first);
				//cout << fake_word << endl;
				i++;
			}
		}
		// check if the word is in the dictionary.  Discard if it is
		if (dict.in_Dictionary(fake_word)) {
			cout << "Word in dictionary" << endl;
			n--;
		}
		else
		{
			fake_words.push_back(fake_word);
		}
	}
	cout << endl;
	//print all the words
	for (string fkword : fake_words) {
		cout << fkword << endl;
	}
	cout << endl;
}


