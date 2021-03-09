#include "Automaton.h"

Automaton::Automaton(int tokenType)
{
    this->tokenType = tokenType;
    newLines = 0;
}

Token* Automaton::CreateToken(string input, int lineNumber)
{
    return new Token(tokenType, input, lineNumber);
}

int Automaton::NewLinesRead() const
{
    return newLines;
}

int Automaton::GetTokenType() const
{
    return tokenType;
}
