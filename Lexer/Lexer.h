#pragma once

#include <iostream>
#include <vector>
#include "Automaton.h"
#include "CommentAutomaton.h"
#include "IdentifierAutomaton.h"
#include "MatcherAutomaton.h"
#include "StringAutomaton.h"
#include "Token.h"
#include "UndefinedAutomaton.h"

using namespace std;

class Lexer
{
private:
    vector<Token*> tokens;
    vector<Automaton*> automata;
    
public:
    Lexer();
    ~Lexer();
    
    void Run(string input);
    vector<Token*> GetTokens() const;
    void Print();
};
