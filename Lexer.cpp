#include "Lexer.h"

Lexer::Lexer()
{
    automata.push_back(new MatcherAutomaton(",", Token::TYPE_COMMA));
    automata.push_back(new MatcherAutomaton(".", Token::TYPE_PERIOD));
    automata.push_back(new MatcherAutomaton("?", Token::TYPE_Q_MARK));
    automata.push_back(new MatcherAutomaton("(", Token::TYPE_LEFT_PAREN));
    automata.push_back(new MatcherAutomaton(")", Token::TYPE_RIGHT_PAREN));
    automata.push_back(new MatcherAutomaton(":", Token::TYPE_COLON));
    automata.push_back(new MatcherAutomaton(":-", Token::TYPE_COLON_DASH));
    automata.push_back(new MatcherAutomaton("*", Token::TYPE_MULTIPLY));
    automata.push_back(new MatcherAutomaton("+", Token::TYPE_ADD));
    automata.push_back(new MatcherAutomaton("Schemes", Token::TYPE_SCHEMES));
    automata.push_back(new MatcherAutomaton("Facts", Token::TYPE_FACTS));
    automata.push_back(new MatcherAutomaton("Rules", Token::TYPE_RULES));
    automata.push_back(new MatcherAutomaton("Queries", Token::TYPE_QUERIES));
    automata.push_back(new IdentifierAutomaton(Token::TYPE_ID));
    automata.push_back(new StringAutomaton(Token::TYPE_STRING));
    automata.push_back(new CommentAutomaton(Token::TYPE_COMMENT));
    automata.push_back(new UndefinedAutomaton(Token::TYPE_UNDEFINED));
}

Lexer::~Lexer()
{
    //Print();
    for (int i = 0; (unsigned)i < automata.size(); i++) {
        delete automata.at(i);
    }
    /*for (int i = 0; (unsigned)i < tokens.size(); i++) {
        delete tokens.at(i);
    }*/
}

vector<Token*> Lexer::GetTokens() const
{
    return tokens;
}

void Lexer::Run(string input)
{
    int lineNumber = 1;
    while (input.size() > 0) {
        int maxRead = 0;
        Automaton* maxAutomaton = automata.at(0);
        for (int i = 0; (unsigned)i < automata.size(); i++) {
            int inputRead = automata.at(i)->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }
        if (maxRead > 0) {
            if (maxAutomaton->GetTokenType() != Token::TYPE_COMMENT) {
                tokens.push_back(maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber));
            }
            input = input.substr(maxRead, string::npos);
            lineNumber += maxAutomaton->NewLinesRead();
        } else {
            if (input.at(0) == '\n') {
                lineNumber++;
            } else if (input.at(0) != ' ' && input.at(0) != '\t'){ // Case: undefined token
                tokens.push_back(new Token(Token::TYPE_UNDEFINED, input.substr(0, 1), lineNumber));
            }
            input = input.substr(1, string::npos);
        }
    }
    tokens.push_back(new Token(Token::TYPE_EOF,"", lineNumber));
}

void Lexer::Print()
{
    for (int i = 0; (unsigned)i < tokens.size(); i++) {
        tokens.at(i)->Print();
    }
    cout << "Total Tokens = " << tokens.size() << endl;
}
