#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

multimap<string, string> read_file(string& input, unsigned int& count);

int main(){

	// C:/Users/MickeyMouse/AbsolutePath/DB/Data.CS.SFSU.txt
	auto* fileName = new string("Data.CS.SFSU.txt");

	unsigned int count = 0;

	multimap <string, string> dictionary = read_file(*fileName, count);

	delete fileName;
	fileName = nullptr;



	cout << "====== DICTIONARY 340 C++ ======" << endl;
	cout << "------ Keywords: " << count << " ------" << endl;
	cout << "------ Definitions: " << dictionary.size() << " ------" << endl;

	count = 1;

	string args;

	while(count) {
		cout << "Search [" << count << "]: ";
		cin >> args;
	}

	
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
		for (;it != line.end(); ++it) {

			if (*it == '|') {
				dictionary.insert(pair<string, string>(word, definition));
				continue;
			} else if (it+1 == line.end()) {
				dictionary.insert(pair<string, string>(word, definition));
				break;
			} else {
				definition += *it;
			}
		}
	}
	cout << "! Loading completed..." << endl;

	cout << "! Closing data file... " << input << endl;

	file.close();

	return dictionary;
}
