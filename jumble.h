#pragma once
#include <string>
using namespace std;

typedef char* charArrayPtr;

class JumblePuzzle
{
    public:
            //************************* INITIALIZATION *************************
            JumblePuzzle();
            JumblePuzzle(string hide, string diff);
            JumblePuzzle(JumblePuzzle& puzzle);

            //************************** GET FUNCTIONS **************************
            charArrayPtr* getJumble();
            int getRowPos();
            int getColPos();
            string getDirection();
            int getSize();

            //*********************** OPERATOR OVERLOADER ***********************
            JumblePuzzle operator=(const JumblePuzzle puzzle);

    private:
            //************************** PRIVATE VARIABLES **************************
            int size;
            int rowPos;
            int colPos;
            char* dir;
            charArrayPtr* jumblePuzzle;

            //************************** PRIVATE FUNCTIONS **************************
            char genDirection();

            
};

//Exception class for JumblePuzzle
class BadJumbleException
{
    public:
            BadJumbleException(const string& message);
            string what();

    private:
            string message;
};