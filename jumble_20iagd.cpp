#include <string.h>
#include <string>
#include <iostream>
#include <ctime>
using namespace std;


#include "jumble_20iagd.h"

JumblePuzzle::JumblePuzzle(const string& hide, const string& diff)
{
    diff.tolower();
    size = hide.length();
    if (size < LOWER_LIMIT || size > UPPER_LIMIT) 
        throw BadJumbleException("Invalid word length, please refer to game details.\n");
    if (diff == "easy") size *= 2;
    else if (strcmp(diff, "medium") == 0) size *= 3;
    else if (strcmp(diff, "hard") == 0) size *= 4;
    else throw BadJumbleException("Invalid difficulty, must be \"Easy\", \"Medium\", \"Hard\"\n");
    jumblePuzzle = new char* [size];

    //create puzzle board
    for (int x = 0; x < size; x++) jumblePuzzle[x] = new char [size];

    //fill the board with random letters
    for (int x = 0; x < size; x++) for (int y = 0; y < size; y++) jumblePuzzle[x][y] = (char) alphabet[rand()%25];

    //hide the first character
    rowPos = rand() % size;
    colPos = rand() % size;
    jumblePuzzle[rowPos][colPos] = hide[0];

    //prep jumble puzzle for word entry ***************************** test this on the side for effeciency
    // while(true)
    // {
    //     //determine the direction for the hidden word
    //     char dirPicked = dir[rand()%4];

    //     //check directions for room. If no space, reversed direction will fit. Break loop once corrected
    //     if (dirPicked == 'n') 
    //     {
    //         if ((rowPos - (hide.length() - 1)) < 0) dirPicked = 's';
    //         break;
    //     }
    //     if (dirPicked == 'e') 
    //     {
    //         if ((colPos + (hide.length() - 1)) > size) dirPicked = 'w';
    //         break;
    //     }
    //     if (dirPicked == 's') 
    //     {
    //         if ((rowPos + (hide.length() - 1)) > size) dirPicked = 'n';
    //         break;
    //     }
    //     if (dirPicked == 'w') 
    //     {
    //         if ((colPos - (hide.length() - 1)) < 0) dirPicked = 'e';
    //         break;
    //     }
    // }

    //randomly chooses a direction to place the word in
    char dirPicked = dir[rand()%4];

    //check directions for room. If no space, reversed direction will fit. Break loop once corrected
    if (dirPicked == 'n') if ((rowPos - (hide.length() - 1)) < 0) dirPicked = 's';
    else if (dirPicked == 'e') if ((colPos + (hide.length() - 1)) > size) dirPicked = 'w';
    else if (dirPicked == 's') if ((rowPos + (hide.length() - 1)) > size) dirPicked = 'n';
    else if ((colPos - (hide.length() - 1)) < 0) dirPicked = 'e';

    //places word in desired direction
    for (int x = 1; x < hide.length(); x++)
    {
        //move position in desired direction
        if (dirPicked == 'n') rowPos--;
        else if (dirPicked == 'e') colPos++;
        else if (dirPicked == 's') rowPos++;
        else colPos--;

        //place word
        jumblePuzzle[rowPos][colPos] = hide[x];
    }
}