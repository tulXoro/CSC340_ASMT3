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
	cout << "-------------" << endl;
	cout << "| " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |" << endl;
	cout << "-------------" << endl;
	cout << "| " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |" << endl;
	cout << "-------------" << endl;
	cout << "| " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |" << endl;
	cout << "-------------" << endl;
}

void makeAMove(char board[][3], char player) {
	cout << "Enter a row (0, 1, 2) for player " << player << ": ";
	int row;
	cin >> row;
	cout << "Enter a column (0, 1, 2) for player " << player << ": ";
	int column;
	cin >> column;
	
	if (board[row][column]!=' ') {
		cout << "This cell is already occupied. Please try again." << endl;
		makeAMove(board, player);
	} else {
		board[row][column] = player;
	}
}
