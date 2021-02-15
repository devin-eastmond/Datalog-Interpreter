#include "Parser.h"

Parser::~Parser()
{
    for (int i = 0; (unsigned)i < tokens.size(); i++) {
        delete tokens.at(i);
    }
}

void Parser::Parse(vector<Token*> tokens)
{
    this->tokens = tokens;
    tokenIndex = 0;
    ParseDatalogProgram();
}

// Grammar: datalogProgram -> SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
void Parser::ParseDatalogProgram()
{
    try {
        ParseTerminal(Token::TYPE_SCHEMES);
        ParseTerminal(Token::TYPE_COLON);
        ParseScheme();
        ParseSchemeList();
        
        ParseTerminal(Token::TYPE_FACTS);
        ParseTerminal(Token::TYPE_COLON);
        ParseFactList();
        
        ParseTerminal(Token::TYPE_RULES);
        ParseTerminal(Token::TYPE_COLON);
        ParseRuleList();
        
        ParseTerminal(Token::TYPE_QUERIES);
        ParseTerminal(Token::TYPE_COLON);
        ParseQuery();
        ParseQueryList();
        
        ParseTerminal(Token::TYPE_EOF);
        
        cout << "Success!" << endl;
    } catch(int e) {
        cout << "Failure!" << endl << "  ";
        tokens.at(tokenIndex)->Print();
    }
}

// Grammar: schemeList -> scheme schemeList | lambda
void Parser::ParseSchemeList()
{
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_ID) {
        ParseScheme();
        ParseSchemeList();
    }
}

// Grammar: factList -> fact factList | lambda
void Parser::ParseFactList()
{
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_ID) {
        ParseFact();
        ParseFactList();
    }
}

// Grammar: ruleList -> rule ruleList | lambda
void Parser::ParseRuleList()
{
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_ID) {
        ParseRule();
        ParseRuleList();
    }
}

// Grammar: queryList -> query queryList | lambda
void Parser::ParseQueryList()
{
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_ID) {
        ParseQuery();
        ParseQueryList();
    }
}

// Grammar: scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::ParseScheme()
{
    ParseTerminal(Token::TYPE_ID);
    ParseTerminal(Token::TYPE_LEFT_PAREN);
    ParseTerminal(Token::TYPE_ID);
    ParseIdList();
    ParseTerminal(Token::TYPE_RIGHT_PAREN);
}

// Grammar: fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
void Parser::ParseFact()
{
    ParseTerminal(Token::TYPE_ID);
    ParseTerminal(Token::TYPE_LEFT_PAREN);
    ParseTerminal(Token::TYPE_STRING);
    ParseStringList();
    ParseTerminal(Token::TYPE_RIGHT_PAREN);
    ParseTerminal(Token::TYPE_PERIOD);
}

// Grammar: rule -> headPredicate COLON_DASH predicate predicateList PERIOD
void Parser::ParseRule()
{
    ParseHeadPredicate();
    ParseTerminal(Token::TYPE_COLON_DASH);
    ParsePredicate();
    ParsePredicateList();
    ParseTerminal(Token::TYPE_PERIOD);
}

// Grammar: query -> predicate Q_MARK
void Parser::ParseQuery()
{
    ParsePredicate();
    ParseTerminal(Token::TYPE_Q_MARK);
}

// Grammar: headPredicate -> ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::ParseHeadPredicate()
{
    ParseTerminal(Token::TYPE_ID);
    ParseTerminal(Token::TYPE_LEFT_PAREN);
    ParseTerminal(Token::TYPE_ID);
    ParseIdList();
    ParseTerminal(Token::TYPE_RIGHT_PAREN);
}

// Grammar: predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
void Parser::ParsePredicate()
{
    ParseTerminal(Token::TYPE_ID);
    ParseTerminal(Token::TYPE_LEFT_PAREN);
    ParseParameter();
    ParseParameterList();
    ParseTerminal(Token::TYPE_RIGHT_PAREN);
}

// Grammar: predicateList -> COMMA predicate predicateList | lambda
void Parser::ParsePredicateList()
{
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_COMMA) {
        ParseTerminal(Token::TYPE_COMMA);
        ParsePredicate();
        ParsePredicateList();
    }
}

// Grammar: parameterList -> COMMA parameter parameterList | lambda
void Parser::ParseParameterList()
{
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_COMMA) {
        ParseTerminal(Token::TYPE_COMMA);
        ParseParameter();
        ParseParameterList();
    }
}

// Grammar: stringList -> COMMA STRING stringList | lambda
void Parser::ParseStringList()
{
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_COMMA) {
        ParseTerminal(Token::TYPE_COMMA);
        ParseTerminal(Token::TYPE_STRING);
        ParseStringList();
    }
}

// Grammar: idList -> COMMA ID idList | lambda
void Parser::ParseIdList()
{
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_COMMA) {
        ParseTerminal(Token::TYPE_COMMA);
        ParseTerminal(Token::TYPE_ID);
        ParseIdList();
    }
}

// Grammar: parameter -> STRING | ID | expression
void Parser::ParseParameter()
{
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_STRING) {
        ParseTerminal(Token::TYPE_STRING);
    } else if (tokens.at(tokenIndex)->GetType() == Token::TYPE_ID) {
        ParseTerminal(Token::TYPE_ID);
    } else if (tokens.at(tokenIndex)->GetType() == Token::TYPE_LEFT_PAREN) {
        ParseExpression();
    } else {
        throw 1;
    }
}

// Grammar: expression -> LEFT_PAREN parameter operator parameter RIGHT_PAREN
void Parser::ParseExpression()
{
    ParseTerminal(Token::TYPE_LEFT_PAREN);
    ParseParameter();
    ParseOperator();
    ParseParameter();
    ParseTerminal(Token::TYPE_RIGHT_PAREN);
}

// Grammar: operator -> ADD | MULTIPLY
void Parser::ParseOperator()
{
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_ADD) {
        ParseTerminal(Token::TYPE_ADD);
    } else if (tokens.at(tokenIndex)->GetType() == Token::TYPE_MULTIPLY) {
        ParseTerminal(Token::TYPE_MULTIPLY);
    } else {
        throw 1;
    }
}

void Parser::ParseTerminal(int tokenType)
{
    if (tokens.at(tokenIndex)->GetType() == tokenType) {
        tokenIndex++;
    } else {
        throw 1;
    }
}
