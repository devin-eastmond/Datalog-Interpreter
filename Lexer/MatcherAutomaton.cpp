#include "MatcherAutomaton.h"

MatcherAutomaton::MatcherAutomaton(string toMatch, int tokenType): Automaton(tokenType)
{
    this->toMatch = toMatch;
}

int MatcherAutomaton::Start(const string& input)
{
    bool isMatch = true;
    inputRead = 0;
    for (int i = 0; i < (int)toMatch.size() && isMatch; i++) {
        if (input[i] != toMatch[i]) {
            isMatch = false;
        }
    }
    if (isMatch) {
        inputRead = (int)toMatch.size();
    }
    
    return inputRead;
}
