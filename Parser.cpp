#include "Parser.h"

Parser::~Parser()
{
    for (int i = 0; (unsigned)i < tokens.size(); i++) {
        delete tokens.at(i);
    }
}

DatalogProgram* Parser::Parse(vector<Token*> tokens)
{
    this->tokens = tokens;
    tokenIndex = 0;
    return ParseDatalogProgram();
}

// Grammar: datalogProgram -> SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
DatalogProgram* Parser::ParseDatalogProgram()
{
    DatalogProgram* datalogProgram = new DatalogProgram();
    
    try {
        ParseTerminal(Token::TYPE_SCHEMES);
        ParseTerminal(Token::TYPE_COLON);
        datalogProgram->AddScheme(ParseScheme());
        vector<Predicate*> schemeList = ParseSchemeList();
        for (int i = 0; i < (int)schemeList.size(); i++) {
            datalogProgram->AddScheme(schemeList.at(i));
        }
        
        ParseTerminal(Token::TYPE_FACTS);
        ParseTerminal(Token::TYPE_COLON);
        vector<Predicate*> factList = ParseFactList();
        for (int i = 0; i < (int)factList.size(); i++) {
            datalogProgram->AddFact(factList.at(i));
        }
        
        ParseTerminal(Token::TYPE_RULES);
        ParseTerminal(Token::TYPE_COLON);
        vector<Rule*> ruleList = ParseRuleList();
        for (int i = 0; i < (int)ruleList.size(); i++) {
            datalogProgram->AddRule(ruleList.at(i));
        }
        
        ParseTerminal(Token::TYPE_QUERIES);
        ParseTerminal(Token::TYPE_COLON);
        datalogProgram->AddQuery(ParseQuery());
        vector<Predicate*> queryList = ParseQueryList();
        for (int i = 0; i < (int)queryList.size(); i++) {
            datalogProgram->AddQuery(queryList.at(i));
        }
        
        ParseTerminal(Token::TYPE_EOF);
        
        cout << "Success!" << endl;
        cout << datalogProgram->ToString();
    } catch(int e) {
        cout << "Failure!" << endl << "  ";
        tokens.at(tokenIndex)->Print();
    }
    
    return datalogProgram;
}

// Grammar: schemeList -> scheme schemeList | lambda
vector<Predicate*> Parser::ParseSchemeList()
{
    vector<Predicate*> schemeList;
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_ID) {
        schemeList.push_back(ParseScheme());
        vector<Predicate*> schemeListToAdd = ParseSchemeList();
        schemeList.insert(schemeList.end(), schemeListToAdd.begin(), schemeListToAdd.end());
    }
    
    return schemeList;
}

// Grammar: factList -> fact factList | lambda
vector<Predicate*> Parser::ParseFactList()
{
    vector<Predicate*> factList;
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_ID) {
        factList.push_back(ParseFact());
        vector<Predicate*> factListToAdd = ParseFactList();
        factList.insert(factList.end(), factListToAdd.begin(), factListToAdd.end());
    }
    
    return factList;
}

// Grammar: ruleList -> rule ruleList | lambda
vector<Rule*> Parser::ParseRuleList()
{
    vector<Rule*> ruleList;
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_ID) {
        ruleList.push_back(ParseRule());
        vector<Rule*> ruleListToAdd = ParseRuleList();
        ruleList.insert(ruleList.end(), ruleListToAdd.begin(), ruleListToAdd.end());
    }
    
    return ruleList;
}

// Grammar: queryList -> query queryList | lambda
vector<Predicate*> Parser::ParseQueryList()
{
    vector<Predicate*> queryList;
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_ID) {
        queryList.push_back(ParseQuery());
        vector<Predicate*> queryListToAdd = ParseQueryList();
        queryList.insert(queryList.end(), queryListToAdd.begin(), queryListToAdd.end());
    }
    
    return queryList;
}

// Grammar: scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
Predicate* Parser::ParseScheme()
{
    string id = ParseTerminal(Token::TYPE_ID);
    ParseTerminal(Token::TYPE_LEFT_PAREN);
    PlainParameter* parameter = new PlainParameter(ParseTerminal(Token::TYPE_ID));
    vector<string> idList = ParseIdList();
    ParseTerminal(Token::TYPE_RIGHT_PAREN);
    
    Predicate* scheme = new Predicate(id);
    scheme->AddParameter(parameter);
    for (int i = 0; i < (int)idList.size(); i++) {
        parameter = new PlainParameter(idList.at(i));
        scheme->AddParameter(parameter);
    }
    
    return scheme;
}

// Grammar: fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
Predicate* Parser::ParseFact()
{
    string id = ParseTerminal(Token::TYPE_ID);
    ParseTerminal(Token::TYPE_LEFT_PAREN);
    PlainParameter* parameter = new PlainParameter(ParseTerminal(Token::TYPE_STRING));
    vector<string> stringList = ParseStringList();
    ParseTerminal(Token::TYPE_RIGHT_PAREN);
    ParseTerminal(Token::TYPE_PERIOD);
    
    Predicate* fact = new Predicate(id);
    fact->AddParameter(parameter);
    for (int i = 0; i < (int)stringList.size(); i++) {
        parameter = new PlainParameter(stringList.at(i));
        fact->AddParameter(parameter);
    }
    
    return fact;
}

// Grammar: rule -> headPredicate COLON_DASH predicate predicateList PERIOD
Rule* Parser::ParseRule()
{
    Predicate* headPredicate = ParseHeadPredicate();
    ParseTerminal(Token::TYPE_COLON_DASH);
    Predicate* predicate = ParsePredicate();
    vector<Predicate*> predicateList = ParsePredicateList();
    ParseTerminal(Token::TYPE_PERIOD);
    
    Rule* rule = new Rule();
    rule->SetHeadPredicate(headPredicate);
    rule->AddPredicate(predicate);
    for (int i = 0; i < (int)predicateList.size(); i++) {
        rule->AddPredicate(predicateList.at(i));
    }
    
    return rule;
}

// Grammar: query -> predicate Q_MARK
Predicate* Parser::ParseQuery()
{
    Predicate* predicate = ParsePredicate();
    ParseTerminal(Token::TYPE_Q_MARK);
    
    return predicate;
}

// Grammar: headPredicate -> ID LEFT_PAREN ID idList RIGHT_PAREN
Predicate* Parser::ParseHeadPredicate()
{
    string id = ParseTerminal(Token::TYPE_ID);
    ParseTerminal(Token::TYPE_LEFT_PAREN);
    Parameter* parameter = new Parameter(ParseTerminal(Token::TYPE_ID));
    vector<string> idList = ParseIdList();
    ParseTerminal(Token::TYPE_RIGHT_PAREN);
    
    Predicate* headPredicate = new Predicate(id);
    headPredicate->AddParameter(parameter);
    for (int i = 0; i < (int)idList.size(); i++) {
        parameter = new Parameter(idList.at(i));
        headPredicate->AddParameter(parameter);
    }
    
    return headPredicate;
}

// Grammar: predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
Predicate* Parser::ParsePredicate()
{
    string id = ParseTerminal(Token::TYPE_ID);
    ParseTerminal(Token::TYPE_LEFT_PAREN);
    Parameter* parameter = ParseParameter();
    vector<Parameter*> parameterList = ParseParameterList();
    ParseTerminal(Token::TYPE_RIGHT_PAREN);
    
    Predicate* predicate = new Predicate(id);
    predicate->AddParameter(parameter);
    for (int i = 0; i < (int)parameterList.size(); i++) {
        predicate->AddParameter(parameterList.at(i));
    }
    
    return predicate;
}

// Grammar: predicateList -> COMMA predicate predicateList | lambda
vector<Predicate*> Parser::ParsePredicateList()
{
    vector<Predicate*> predicateList;
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_COMMA) {
        ParseTerminal(Token::TYPE_COMMA);
        predicateList.push_back(ParsePredicate());
        vector<Predicate*> predicateListToAdd = ParsePredicateList();
        predicateList.insert(predicateList.end(), predicateListToAdd.begin(), predicateListToAdd.end());
    }
    
    return predicateList;
}

// Grammar: parameterList -> COMMA parameter parameterList | lambda
vector<Parameter*> Parser::ParseParameterList()
{
    vector<Parameter*> parameterList;
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_COMMA) {
        ParseTerminal(Token::TYPE_COMMA);
        parameterList.push_back(ParseParameter());
        vector<Parameter*> parameterListToAdd = ParseParameterList();
        parameterList.insert(parameterList.end(), parameterListToAdd.begin(), parameterListToAdd.end());
    }
    
    return parameterList;
}

// Grammar: stringList -> COMMA STRING stringList | lambda
vector<string> Parser::ParseStringList()
{
    vector<string> stringList;
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_COMMA) {
        ParseTerminal(Token::TYPE_COMMA);
        stringList.push_back(ParseTerminal(Token::TYPE_STRING));
        vector<string> stringListToAdd = ParseStringList();
        stringList.insert(stringList.end(), stringListToAdd.begin(), stringListToAdd.end());
    }
    
    return stringList;
}

// Grammar: idList -> COMMA ID idList | lambda
vector<string> Parser::ParseIdList()
{
    vector<string> idList;
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_COMMA) {
        ParseTerminal(Token::TYPE_COMMA);
        idList.push_back(ParseTerminal(Token::TYPE_ID));
        vector<string> idListToAdd = ParseIdList();
        idList.insert(idList.end(), idListToAdd.begin(), idListToAdd.end());
    }
    
    return idList;
}

// Grammar: parameter -> STRING | ID | expression
Parameter* Parser::ParseParameter()
{
    if (tokens.at(tokenIndex)->GetType() == Token::TYPE_STRING) {
        return new PlainParameter(ParseTerminal(Token::TYPE_STRING));
    } else if (tokens.at(tokenIndex)->GetType() == Token::TYPE_ID) {
        return new PlainParameter(ParseTerminal(Token::TYPE_ID));
    } else if (tokens.at(tokenIndex)->GetType() == Token::TYPE_LEFT_PAREN) {
        return ParseExpression();
    }
    
    throw 1;
}

// Grammar: expression -> LEFT_PAREN parameter operator parameter RIGHT_PAREN
Expression* Parser::ParseExpression()
{
    // TODO: Expression
    Expression* expression = new Expression("A");
    ParseTerminal(Token::TYPE_LEFT_PAREN);
    ParseParameter();
    ParseOperator();
    ParseParameter();
    ParseTerminal(Token::TYPE_RIGHT_PAREN);
    
    return expression;
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

string Parser::ParseTerminal(int tokenType)
{
    string tokenInput = tokens.at(tokenIndex)->GetInput();
    if (tokens.at(tokenIndex)->GetType() == tokenType) {
        tokenIndex++;
    } else {
        throw 1;
    }
    
    return tokenInput;
}
