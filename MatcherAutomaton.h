#pragma once

#include <string>
#include "Automaton.h"

using namespace std;

class MatcherAutomaton: public Automaton
{
private:
    string toMatch;
    
public:
    MatcherAutomaton(string toMatch, int tokenType);
    
    int Start(const string& input);
};
