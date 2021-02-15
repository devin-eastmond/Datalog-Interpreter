#pragma once

#include "Automaton.h"

class UndefinedAutomaton: public Automaton
{
public:
    UndefinedAutomaton(int tokenType): Automaton(tokenType) {}
    
    int Start(const string& input);
    
private:
    bool IsInvalidString(const string& input);
    
    bool IsInvalidComment(const string& input);
};
