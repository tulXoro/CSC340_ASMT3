#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;

bool isvalidcc(const string&);

int get_part_a(const string&);
int get_part_b(const string&);

int main()
{
	//
	// PLEASE DO NOT CHANGE function main
	//
	vector<string> cardnumbers = {
		 "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
		"4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
		"5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
		"4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
		"5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
		 "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
		"4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
		"5556551555555557", "6011316011016011"
	};

	int i;
	vector<string>::iterator itr;

	for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
		cout << setw(2) << i << " "
			<< setw(17) << *itr
			<< ((isvalidcc(*itr)) ? " is valid" : " is not valid") << endl;
	}

	return 0;
}

bool isvalidcc(const string& number) {

	//start of length of credit card number
	if (number.length() < 13 || number.length() > 16)
		return false;

	int sum = get_part_a(number) + get_part_b(number);
	cout << "sum: " << sum << endl;
	return (sum % 10 == 0);
}

int get_part_a(const string& cc) {
	// double every number from right to left
	int sum = 0;
	string::const_reverse_iterator itr = cc.rbegin();
	itr++;

	while (itr != cc.rend()) {
		int digit = (*itr - '0') * 2;

		if(digit<10) {
			sum += digit;
		} else {
			int first = digit / 10;
			int second = digit% 10;
			sum += first + second;
		}

		if (itr + 1 != cc.rend())
			itr += 2;
		else
			break;
		
	}
	return sum;
}

int get_part_b(const string& cc) {
	// add all odd indices from right to left
	int sum = 0;
	string::const_reverse_iterator itr = cc.rbegin();

	while (itr != cc.rend()) {
		// convert char to int
		sum += (*itr - '0');
		++itr;
		if (itr != cc.rend()) {
			++itr;
		}
	}

	return sum;
}
