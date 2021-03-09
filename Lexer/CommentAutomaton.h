#pragma once

#include "Automaton.h"

class CommentAutomaton: public Automaton
{
public:
    CommentAutomaton(int tokenType): Automaton(tokenType) {}
    
    int Start(const string& input);
};
