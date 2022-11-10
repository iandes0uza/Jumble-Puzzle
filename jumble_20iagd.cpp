#include <string.h>
#include <string>
#include <iostream>
#include <ctime>
#include <cctype>
#include "jumble_20iagd.h"
using namespace std;


JumblePuzzle::JumblePuzzle(const string& hide, const string& diff)
{

    LOWER_LIMIT = 3;
    UPPER_LIMIT = 10;
    size = hide.length();
    //save word size in local int variable to help with validating, would rather not typecast hide.length()
    int word_size = size;
    if (size < LOWER_LIMIT || size > UPPER_LIMIT) 
        throw BadJumbleException("Invalid word length, please refer to game details.\n");
    if (diff == "easy") size *= 2;
    else if (diff == "medium") size *= 3;
    else if (diff == "hard") size *= 4;
    else throw BadJumbleException("Invalid difficulty, must be \"Easy\", \"Medium\", \"Hard\"\n");
    jumblePuzzle = new char* [size];

    //create puzzle board
    for (int x = 0; x < size; x++) jumblePuzzle[x] = new char [size];

    //fill the board with random letters
    for (int x = 0; x < size; x++) for (int y = 0; y < size; y++) jumblePuzzle[x][y] = (char) alphabet[rand()%25];

    //generate random location for hidden word
	srand((unsigned) time(NULL));
    rowPos = rand() % size;
    colPos = rand() % size;

    //save row and column for hints
    int row = rowPos;
    int col = colPos;

    //save the first letter
    jumblePuzzle[rowPos][colPos] = hide[0];

    //randomly chooses a direction to place the word in
    direction = dir[rand()%4];

    //check directions for room. If no space, reversed direction will fit. Break loop once corrected
    if (direction == 'n') if ((row - (word_size - 1)) < 0) direction = 's';
    else if (direction == 'e') if ((col + (word_size - 1)) > size-1) direction = 'w';
    else if (direction == 's') if ((row + (word_size - 1)) > size-1) direction = 'n';
    else{ if ((col - (word_size - 1)) < 0) direction = 'e';}

    //debug
    //printf("Size: %d, Word Size: %d, rowPos: %d, colPos: %d, dir: %c\n", size, hide.length(), rowPos, colPos, dirPicked);

    //places word in desired direction
    for (int x = 1; x < word_size; x++)
    {
        //move position in desired direction
        if (direction == 'n') row--;
        else if (direction == 'e') col++;
        else if (direction == 's') row++;
        else col--;

        //place word
        jumblePuzzle[row][col] = hide[x];

    }

    //debug
    //printf("Size: %d, Word Size: %d, rowPos: %d, colPos: %d, dir: %c", size, hide.length(), rowPos, colPos, dirPicked);
}

JumblePuzzle::JumblePuzzle(JumblePuzzle& puzzle)
{
    *this = puzzle;
}

JumblePuzzle::~JumblePuzzle() 
{
    
}

int JumblePuzzle::getSize() const
{
    return size;
}

int JumblePuzzle::getRowPos() const
{
    return rowPos;
}

int JumblePuzzle::getColPos() const
{
    return colPos;
}

char JumblePuzzle::getDirection() const
{
    return direction;
}

charArrayPtr* JumblePuzzle::getJumble() const
{

    //initialize the new jumblePuzzle
    charArrayPtr* newPuzzle = new char* [size];
    for (int i = 0; i < size; i++) newPuzzle[i] = new char [size];

    //replace contents
    for (int i = 0; i < size; i++) for (int j = 0; j < size; j++) newPuzzle[i][j] = jumblePuzzle[i][j];
    return newPuzzle;
}

JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& puzzle) 
{
    if(this != &puzzle) 
    {
        size = puzzle.getSize();
		jumblePuzzle = puzzle.getJumble();
		rowPos = puzzle.getRowPos();
		colPos = puzzle.getColPos();
		direction = puzzle.getDirection(); 
	}
	return *this;
}

BadJumbleException::BadJumbleException(const string& m) : message(m){ }
string BadJumbleException::what() const { return message; }