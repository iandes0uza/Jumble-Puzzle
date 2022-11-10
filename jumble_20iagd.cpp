#include <string.h>
#include <string>
#include <iostream>
#include <ctime>
#include <cctype>
#include "jumble_20iagd.h"
using namespace std;



JumblePuzzle::JumblePuzzle(const string& hide, const string& diff)
{
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

    //hide the first character
	srand((unsigned) time(NULL));
    rowPos = rand() % size;
    colPos = rand() % size;
    jumblePuzzle[rowPos][colPos] = hide[0];

    //randomly chooses a direction to place the word in
    char dirPicked = dir[rand()%4];


    //check directions for room. If no space, reversed direction will fit. Break loop once corrected
    if (dirPicked == 'n') if ((rowPos - (word_size - 1)) < 0) dirPicked = 's';
    else if (dirPicked == 'e') if ((colPos + (word_size - 1)) > size-1) dirPicked = 'w';
    else if (dirPicked == 's') if ((rowPos + (word_size - 1)) > size-1) dirPicked = 'n';
    else{ if ((colPos - (word_size - 1)) < 0) dirPicked = 'e';}

    //debug
    printf("Size: %d, Word Size: %d, rowPos: %d, colPos: %d, dir: %c\n", size, hide.length(), rowPos, colPos, dirPicked);

    //places word in desired direction
    for (int x = 1; x < word_size; x++)
    {
        //move position in desired direction
        if (dirPicked == 'n') rowPos--;
        else if (dirPicked == 'e') colPos++;
        else if (dirPicked == 's') rowPos++;
        else colPos--;

        //place word
        jumblePuzzle[rowPos][colPos] = hide[x];

    }

    //debug
    printf("Size: %d, Word Size: %d, rowPos: %d, colPos: %d, dir: %c", size, hide.length(), rowPos, colPos, dirPicked);
}

int JumblePuzzle::getSize() const
{
    return size;
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

BadJumbleException::BadJumbleException(const string& m) : message(m){ }
string BadJumbleException::what() const { return message; }