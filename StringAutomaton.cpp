#include "StringAutomaton.h"

int StringAutomaton::Start(const string &input)
{
    bool isString = false;
    inputRead = 0;
    newLines = 0;
    if (input.at(0) == '\'') {
        bool isApostrophe = false;
        for (int i = 1; i < (int)input.size() && !isString; i++) {
            if (input.at(i) == '\n') {
                newLines++;
            }
            if (input.at(i) == '\'') {
                bool nextCharIsQuote = ((unsigned)(i + 1) != input.size() && input.at(i+1) == '\'');
                if (nextCharIsQuote && !isApostrophe) {
                    isApostrophe = true;
                } else if (nextCharIsQuote && isApostrophe) {
                    isApostrophe = false;
                } else if (!nextCharIsQuote && !isApostrophe) {
                    isString = true;
                    inputRead = i + 1;
                }
            } else {
                isApostrophe = false;
            }
        }
    }
    
    return inputRead;
}
