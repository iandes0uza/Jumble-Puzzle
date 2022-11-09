#include <string>
#include <iostream>
#include <ctime>
#include "jumble_20iagd.cpp"
using namespace std;

void showJumble(const charArrayPtr* jumble, const int size) {
	int i, j;
	cout << "\n  ";
	for (i = 0; i < size; i++)
		if (i < 10)
			cout << " " << i << " ";
		else
			cout << i << " ";
	cout << endl;
	for (i = 0; i < size; i++) {
		if (i < 10)
			cout << " " << i << " ";
		else
			cout << i << " ";
		for (j = 0; j < size; j++)
			cout << jumble[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
}

void playGame() {
	string toHide;
	string difficulty;
	int guessRow, guessCol;
	int start, finish;
	char guessDirection;

	cout << "Provide a string to hide in the puzzle, all lower case: ";
	cin >> toHide;
	cout << "\nChoose your difficulty level: \"easy\", \"medium\" or \"hard\": ";
	cin >> difficulty;

	JumblePuzzle* jp;
	try {
		jp = new JumblePuzzle(toHide, difficulty);
	} catch (BadJumbleException& e) {
		cerr << e.what();
		return;
	}
	
	showJumble(jp->getJumble(), jp->getSize());

}

int main() 
{
	playGame();
	return 0;
}
