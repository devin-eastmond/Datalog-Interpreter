#pragma once

#include "Automaton.h"

class StringAutomaton: public Automaton
{
public:
    StringAutomaton(int tokenType): Automaton(tokenType) {}
    
    int Start(const string& input);
};
