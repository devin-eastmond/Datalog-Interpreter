#include "CommentAutomaton.h"

int CommentAutomaton::Start(const string& input)
{
    inputRead = 0;
    newLines = 0;
    if (input.at(0) == '#') {
        if (input.at(1) == '|') { // Block comment
            bool endCommentFound = false;
            inputRead = 2;
            for (int i = 2; i < (int)input.size(); i++) {
                if (input.at(i) == '\n') {
                    newLines++;
                }
                inputRead++;
                if (input.at(i) == '#' && input.at(i - 1) == '|') {
                    endCommentFound = true;
                    break;
                }
            }
            // Case: '|#' is not found before EOF
            if (!endCommentFound) {
                inputRead = 0;
            }
        } else { // Line comment
            inputRead = 1;
            for (int i = 1; i < (int)input.size(); i++) {
                if (input.at(i) == '\n') {
                    break;
                }
                inputRead++;
            }
        }
    }
    
    return inputRead;
}
