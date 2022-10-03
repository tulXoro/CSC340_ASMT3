#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;
bool isvalidcc(const string&);
int DoubleSum(const string&);
int OddNumber(const string&);
int getDigits(int numbers);

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
	
	//Start of what each credit card number is provided by
		//if (number[0] == '4' || number[0] == '5' || number[0] == '4' ||
		//	number[0] == '6' || number[0, 2] == '37') {

	int sum1;
	sum1 = DoubleSum(number);
	int sum2;
	sum2 = OddNumber(number);
	int MainSum;
	MainSum = sum1 + sum2;
	if (MainSum % 10 == 0)
		return true;

	//end of addition of sums
	else return false;
	

//End of in between 13 and 16
	return true;
}

//Does the whole taking two digits and splitting them into 1
int getDigits(int numbers) {
	if (numbers > 9) {
		int Numero = numbers % 10;
		numbers = numbers / 10;
		Numero += numbers;
	}
	else 
return numbers;
}

//Creates the Double Sum
int DoubleSum(string& number){
	int sum = 0;
	int SizeUp;
	SizeUp = number.size();
	for (int i = SizeUp - 2; i > 0; i -= 2) {
		int Digits;
		Digits = number[i] - '0';
		sum = getDigits(Digits * 2) + sum;
	}
	return sum;
}

// Grabs the odd number sums
int OddNumber(string& number) {
	int sum = 0;
	int SizeUp;
	SizeUp = number.length();
	for (int i = SizeUp - 1; i > 0; i -= 2) {
		int Digits;
		Digits = number[i] - '0';
		sum = Digits + sum;
	}
	return sum;



}

