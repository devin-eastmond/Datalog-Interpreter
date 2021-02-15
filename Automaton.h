#pragma once

#include <vector>
#include "Token.h"

class Automaton
{
protected:
    int inputRead = 0;
    int newLines = 0;
    int tokenType;
    
public:
    Automaton(int tokenType);
    virtual ~Automaton() {}
    
    // Start the automaton and return the number of characters read
    // read == 0 indicates the input was rejected
    // read > 0 indicates the input was accepted
    virtual int Start(const string& input) = 0;
    
    virtual Token* CreateToken(string input, int lineNumber);
    
    virtual int NewLinesRead() const;
    
    int GetTokenType() const;
};
