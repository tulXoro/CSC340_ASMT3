#include <string>
#include <iterator>
#include <map>
using namespace std;

class Dictionary {
	private:
	multimap<string, string> dictionary;
	public:
	Dictionary();
	~Dictionary();
	void load(string);
	Dictionary();
		
};

void Dictionary::load(string filename) {
	// reads file and stores it into dictionary
}