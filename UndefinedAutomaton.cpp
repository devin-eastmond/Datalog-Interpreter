#include "UndefinedAutomaton.h"


int UndefinedAutomaton::Start(const string& input)
{
    inputRead = 0;
    if ((input.at(0) == '\'' && IsInvalidString(input)) ||
        (input.at(0) == '#' && input.at(1) == '|' && IsInvalidComment(input))
    ) {
        inputRead = (int)input.size();
    }
    
    return inputRead;
}

bool UndefinedAutomaton::IsInvalidString(const string& input)
{
    newLines = 0;
    bool isString = false;
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
            }
        } else {
            isApostrophe = false;
        }
    }
    
    return !isString;
}

bool UndefinedAutomaton::IsInvalidComment(const string& input)
{
    newLines = 0;
    bool endCommentFound = false;
    for (int i = 2; i < (int)input.size(); i++) {
        if (input.at(i) == '\n') {
            newLines++;
        }
        if (input.at(i) == '#' && input.at(i - 1) == '|') {
            endCommentFound = true;
            break;
        }
    }
    
    return !endCommentFound;
}
