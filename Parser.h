#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "DatalogProgram.h"
#include "Expression.h"
#include "Parameter.h"
#include "PlainParameter.h"
#include "Predicate.h"
#include "Rule.h"
#include "Token.h"

using namespace std;

class Parser
{
private:
    vector<Token*> tokens;
    int tokenIndex = 0;
    
    DatalogProgram* ParseDatalogProgram();
    
    vector<Predicate*> ParseSchemeList();
    vector<Predicate*> ParseFactList();
    vector<Rule*> ParseRuleList();
    vector<Predicate*> ParseQueryList();
    
    Predicate* ParseScheme();
    Predicate* ParseFact();
    Rule* ParseRule();
    Predicate* ParseQuery();
    
    Predicate* ParseHeadPredicate();
    Predicate* ParsePredicate();
    
    vector<Predicate*> ParsePredicateList();
    vector<Parameter*> ParseParameterList();
    vector<string> ParseStringList();
    vector<string> ParseIdList();
    
    Parameter* ParseParameter();
    Expression* ParseExpression();
    void ParseOperator();
    
    string ParseTerminal(int token);
    
public:
    ~Parser();
    
    DatalogProgram* Parse(vector<Token*> tokens);
};
