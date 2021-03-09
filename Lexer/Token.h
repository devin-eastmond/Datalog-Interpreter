#pragma once

#include <iostream>
#include <string>

using namespace std;

class Token
{
public:
    static const int TYPE_COMMA = 0;
    static const int TYPE_PERIOD = 1;
    static const int TYPE_Q_MARK = 2;
    static const int TYPE_LEFT_PAREN = 3;
    static const int TYPE_RIGHT_PAREN = 4;
    static const int TYPE_COLON = 5;
    static const int TYPE_COLON_DASH = 6;
    static const int TYPE_MULTIPLY = 7;
    static const int TYPE_ADD = 8;
    static const int TYPE_SCHEMES = 9;
    static const int TYPE_FACTS = 10;
    static const int TYPE_RULES = 11;
    static const int TYPE_QUERIES = 12;
    static const int TYPE_ID = 13;
    static const int TYPE_STRING = 14;
    static const int TYPE_COMMENT = 15;
    static const int TYPE_UNDEFINED = 16;
    static const int TYPE_EOF = 17;
    
    static const string TOKEN_NAMES[18];
    
    Token(int tokenType, string input, int lineNumber);
    
    void Print();
    
    int GetType() const;
    string GetInput() const;
    int GetLineNumber() const;
    
private:
    int tokenType;
    string input;
    int lineNumber;
};
