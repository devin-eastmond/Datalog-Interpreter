#include "IdentifierAutomaton.h"

int IdentifierAutomaton::Start(const string& input)
{
    if (!isalpha(input.at(0))) {
        inputRead = 0;
    } else {
        inputRead = 1;
        for (int i = 1; i < (int)input.size(); i++) {
            if (isalnum(input.at(i))) {
                inputRead++;
            } else {
                break;
            }
        }
    }
    
    return inputRead;
}
