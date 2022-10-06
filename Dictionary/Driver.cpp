#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <memory>

using namespace std;

multimap<string, string> read_file(string&, unsigned int&);
void queryInput(const multimap<string,string>&, const vector<string>&, unsigned int&);

void callHelp();

int main() {

	// C:/Users/MickeyMouse/AbsolutePath/DB/Data.CS.SFSU.txt
	unique_ptr<string> fileName(new string("Data.CS.SFSU.txt"));

	unsigned int count = 0;

	multimap <string, string> dictionary = read_file(*fileName, count);

	fileName.reset();
	fileName = nullptr;

	cout << "====== DICTIONARY 340 C++ ======" << endl;
	cout << "------ Keywords: " << count << " ------" << endl;
	cout << "------ Definitions: " << dictionary.size() << " ------" << endl;

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
		queryInput(dictionary, args, count);
		


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

void queryInput(const multimap<string, string>& dictionary, const vector<string>& args, unsigned int& count) {

	// Control functions
	if (args.empty()) {
		callHelp();
		return;
	}
	if(args.at(0) == "!q") {
		count = 0;
		return;
	}
	if (args.at(0) == "!help") {
		callHelp();
		return;
	}

	auto itr = dictionary.find(args.at(0));

	if (itr == dictionary.end()) {
		cout << "\t|" << endl;
		cout << "\t <NOT FOUND> To be considered for the next release. Thank you." << endl;
		cout << "\t|" << endl;
		callHelp();
		return;
	}

	cout << "\t|" << endl;
	for (; itr != dictionary.end(); ++itr) {
		if (itr->first == args.at(0)) {
			cout << "\t " << itr->second << endl;

		}
	}
	cout << "\t|" << endl;
	
}

void callHelp() {
	cout << "\t|" << endl;
	cout << "\t PARAMETER HOW-TO, please enter:" << endl;
	cout << "\t 1. A search key -then 2. An optional part of speech -then" << endl;
	cout << "\t 3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
	cout << "\t|" << endl;
}
