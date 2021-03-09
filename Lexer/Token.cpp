#include "Token.h"

const string Token::TOKEN_NAMES[18] = {
    "COMMA",
    "PERIOD",
    "Q_MARK",
    "LEFT_PAREN",
    "RIGHT_PAREN",
    "COLON",
    "COLON_DASH",
    "MULTIPLY",
    "ADD",
    "SCHEMES",
    "FACTS",
    "RULES",
    "QUERIES",
    "ID",
    "STRING",
    "COMMENT",
    "UNDEFINED",
    "EOF"
};

Token::Token(int tokenType, string input, int lineNumber)
{
    this->tokenType = tokenType;
    this->input = input;
    this->lineNumber = lineNumber;
}

void Token::Print()
{
    cout << "(" << TOKEN_NAMES[tokenType] << ",\"" << input << "\"," << lineNumber << ")" << endl;
}

int Token::GetType() const
{
    return tokenType;
}

string Token::GetInput() const
{
    return input;
}

int Token::GetLineNumber() const
{
    return lineNumber;
}
