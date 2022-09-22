#include <iostream>
using namespace std;

bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[][3], char);

int main() {
	//
	//	PLEASE DO NOT CHANGE function main
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);

	while (true) {

		// The first player makes a move
		makeAMove(board, 'X');
		displayBoard(board);

		if (isWon('X', board)) {
			cout << "X player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}

		// The second player makes a move
		makeAMove(board, 'O');
		displayBoard(board);

		if (isWon('O', board)) {
			cout << "O player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
	}

	return 0;
}

bool isWon(char player, char board[][3]) {

	return false;
}

bool isDraw(char board[][3]) {

	return false;
}

void displayBoard(char board[][3]) {
	cout << "   |   |   ";
	cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " | ";
	cout << "___|___|___";
	cout << "   |   |   ";
	cout << " " << board[0][4] << " | " << board[0][5] << " | " << board[0][6] << " | ";
	cout << "___|___|___";
	cout << "   |   |   ";
	cout << " " << board[0][7] << " | " << board[0][8] << " | " << board[0][9] << " | ";
	cout << "   |   |   ";
}

void makeAMove(char board[][3], char player) {

}
