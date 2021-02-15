#pragma once

#include "Automaton.h"

class IdentifierAutomaton: public Automaton
{
public:
    IdentifierAutomaton(int tokenType): Automaton(tokenType) {}
    
    int Start(const string& input);
};
