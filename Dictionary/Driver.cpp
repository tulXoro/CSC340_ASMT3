#include <algorithm>
#include <complex>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <memory>
#include <unordered_map>

using namespace std;

multimap<string, string> read_file(string&, unsigned int&);
void query_input(const multimap<string,string>&, const vector<string>&, unsigned int&);

void validate(const string&, const unsigned int&);
void output(const multimap<string, string>&, const string&, const bool&);
void call_help();

int main() {

	// C:/Users/MickeyMouse/AbsolutePath/DB/Data.CS.SFSU.txt
	string fileName = "Data.CS.SFSU.txt";

	unsigned int count = 0;

	const multimap <string, string> dictionary = read_file(fileName, count);

	cout << "\n====== DICTIONARY 340 C++ ======" << endl;
	cout << "------ Keywords: " << count << endl;
	cout << "------ Definitions: " << dictionary.size() << "\n" << endl;

	count = 1;
	

	do {
		cout << "Search [" << count << "]: ";

		// Handle user input
		string input;
		getline(cin, input);
		transform(input.begin(), input.end(), input.begin(), tolower);

		// convert string to vector
		stringstream ss(input);
		vector<string> args((istream_iterator<string>(ss)),
			istream_iterator<string>());

		// handle input
		query_input(dictionary, args, count);
		


	} while (count++);

	cout << "\n====== THANK YOU ======" << endl;


	return 0;
}


/*
 * This function reads a file and returns a multimap of the words and their definitions
 */
multimap<string, string> read_file(string& input, unsigned int& count) {
	cout << "! Opening data file... " << input << endl;
	fstream file;
	// try to open the file until it is successful
	while (!file.is_open()) {
		file.open(input, ios::in);
		if (!file.is_open()) {
			cout << "<!>ERROR<!> ===> File could not be opened." << endl;
			cout << "<!>ERROR<!> ===> Provided file path: " << input << endl;
			cout << "<!>Enter the CORRECT data file path: ";
			cin >> input;
		}
	}

	cout << "! Loading data..." << endl;

	multimap<string, string> dictionary = {};

	// read line by line
	string line;
	while (getline(file, line)) {
		string word;
		string definition;
		++count;

		auto it = line.begin();

		// grab word
		while (*it != '|') {
			word += *it;
			++it;
		}

		++it;

		// grab definition
		for (; it != line.end(); ++it) {

			if (*it == '|') {
				dictionary.insert(pair<string, string>(word, definition));
				definition = "";
				continue;
			}
			else if (it + 1 == line.end()) {
				dictionary.insert(pair<string, string>(word, definition));
				break;
			}
			else {
				definition += *it;
			}
		}
		
	}
	cout << "! Loading completed..." << endl;

	cout << "! Closing data file... " << input << endl;

	file.close();

	return dictionary;
}

void query_input(const multimap<string, string>& dictionary, const vector<string>& args, unsigned int& count) {

	// Control functions
	if (args.empty()) {
		call_help();
		return;
	}
	if(args.at(0) == "!q") {
		count = 0;
		return;
	}
	if (args.at(0) == "!help" || args.at(0) == "!h" || args.size() > 4) {
		call_help();
		return;
	}

	// validate args
	for (unsigned int i=1; i<args.size(); i++) {
		validate(args.at(i), i);
	}

	// handle args

	// check if string "reverse" is in args vector
	bool reverse = false;
	if (find(args.begin(), args.end(), "reverse") != args.end()) {
		reverse = true;
	}

	// check if string "distinct" is in args vector
	bool distinct = false;
	if (find(args.begin(), args.end(), "reverse") != args.end()) {
		reverse = true;
	}

	bool pos = false;
	if (args.size() >= 2) {
		if (args.at(1) == "noun") pos = true;
		else if (args.at(1) == "verb") pos = true;
		else if (args.at(1) == "adjective") pos = true;
		else if (args.at(1) == "adverb") pos = true;
		else if (args.at(1) == "pronoun") pos = true;
		else if (args.at(1) == "preposition") pos = true;
		else if (args.at(1) == "conjunction") pos = true;
		else if (args.at(1) == "interjection") pos = true;
	}

	if (!pos && !distinct) {
		output(dictionary, args.at(0), reverse);
		return;
	}

	// create a dictionary that is distinct
	multimap<string, string> dictionaryClone;
	unordered_map<string, bool> duplicates;

	const char* temp = args.at(0).c_str();
	auto itr = dictionary.find(args.at(0));

	for(; itr!=dictionary.end(); itr++) {
		if(itr->first == args.at(0)) {
			// if distinct, and distinct is in dup map, skip
			if (distinct && duplicates.at(itr->second) == true) continue;

			// for pos check if the first word is equal to pos
			istringstream iss{ itr->second };
			string partOfSpeech;
			iss >> partOfSpeech;
			if(pos && partOfSpeech==args.at(1)) {
				dictionaryClone.emplace(itr->first, itr->second);
			} else if(!pos && distinct){
				dictionaryClone.emplace(itr->first, itr->second);
			}

			duplicates.emplace(itr->second, true);


		}
		
	}

	output(dictionaryClone, args.at(0), reverse);

}

void call_help() {
	cout << "\t|" << endl;
	cout << "\t PARAMETER HOW-TO, please enter:" << endl;
	cout << "\t 1. A search key -then 2. An optional part of speech -then" << endl;
	cout << "\t 3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
	cout << "\t|" << endl;
}

void output(const multimap<string, string>& map, const string& word, const bool& reversed) {

	auto itr = map.find(word);

	if (itr == map.end()) {
		cout << "\t|" << endl;
		cout << "\t <NOT FOUND> To be considered for the next release. Thank you." << endl;
		cout << "\t|" << endl;
		call_help();
		return;
	}

	if(reversed) {
		auto itr = map.rbegin();

		cout << "\t|" << endl;
		for (; itr != map.rend(); ++itr) {
			if (itr->first == word) {
				cout << "\t " << itr->second << endl;

			}
		}
		cout << "\t|" << endl;

	} else {

		cout << "\t|" << endl;
		for (; itr != map.end(); ++itr) {
			if (itr->first == word) {
				cout << "\t " << itr->second << endl;

			}
		}
		cout << "\t|" << endl;
	}
}

void validate(const string& arg, const unsigned int& index) {
	string result = "\t|\n";

	bool pos = false;
	bool distinct = false;
	bool reverse = false;

	switch(index) {
	case 1:
		if (arg == "noun") pos = true;
		else if (arg == "verb") pos = true;
		else if (arg == "adjective") pos = true;
		else if (arg == "adverb") pos = true;
		else if (arg == "pronoun") pos = true;
		else if (arg == "preposition") pos = true;
		else if (arg == "conjunction") pos = true;
		else if (arg == "interjection") pos = true;

		if (!pos)
			result += "\t <The entered 2nd parameter " + arg + " is NOT a part of speech.>";

		// check if arg is distinct
		if (arg == "distinct") distinct = true;

		if (!distinct)
			result += "\n\t <The entered 2nd parameter " + arg + " is NOT 'distinct'.>";

		// check if arg is reverse
		if (arg == "reverse") reverse = true;

		if (!reverse)
			result += "\n\t <The entered 2nd parameter " + arg + " is NOT 'reverse'.>";

		result += "\n\t <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'\n\t|\n";

		if (!pos && !distinct && !reverse) cout << result;
		return;
	case 2:
		if (arg == "distinct") distinct = true;

		if (!distinct)
			result += "\t <The entered 3rd parameter " + arg + " is NOT 'distinct'.>";

		// check if arg is reverse
		if (arg == "reverse") reverse = true;

		if (!reverse)
			result += "\n\t <The entered 3rd parameter " + arg + " is NOT 'reverse'.>";

		result += "\n\t <The 3rd parameter should be 'distinct' or 'reverse'\n\t|\n";

		if (!distinct && !reverse) cout << result;
		return;
	case 3:
		if (arg == "reverse") reverse = true;

		if (!reverse)
			result += "\t <The entered 4th parameter " + arg + " is NOT 'reverse'.>";

		result += "\n\t <The 4th parameter should be 'reverse'.>\n\t|\n";

		if (!reverse) cout << result;
		return;
	default:
		cout << "Error, should not have reached this point";
		return;
	}
}