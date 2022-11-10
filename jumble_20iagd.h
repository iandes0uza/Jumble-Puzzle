#pragma once
#include <string>
using namespace std;


typedef char* charArrayPtr;

class JumblePuzzle
{
    public:
            //*************************** DESTRUCTOR ***************************
            ~JumblePuzzle();

            //************************* INITIALIZATION *************************
            JumblePuzzle(const string& hide, const string& diff);
            JumblePuzzle(JumblePuzzle& puzzle);

            //************************** GET FUNCTIONS **************************
            charArrayPtr* getJumble() const;
            int getRowPos() const;
            int getColPos() const;
            char getDirection() const;
            int getSize() const;

            //*********************** OPERATOR OVERLOADER ***********************
            JumblePuzzle& operator=(const JumblePuzzle& puzzle);

    private:
            //************************** PRIVATE VARIABLES **************************
            int size;
            int rowPos;
            int colPos;
            char direction;
            int LOWER_LIMIT;
            int UPPER_LIMIT;
            charArrayPtr* jumblePuzzle;
            const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
            const char* dir = "nesw";

            //************************** PRIVATE FUNCTIONS **************************
            //char genDirection();

            
};

//Exception class for JumblePuzzle
class BadJumbleException
{
    public:
            BadJumbleException(const string& message);
            string what() const;

    private:
            string message;
};