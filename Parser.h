#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "DatalogProgram.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include "Token.h"

using namespace std;

class Parser
{
private:
    vector<Token*> tokens;
    int tokenIndex = 0;
    
    void ParseDatalogProgram();
    
    void ParseSchemeList();
    void ParseFactList();
    void ParseRuleList();
    void ParseQueryList();
    
    void ParseScheme();
    void ParseFact();
    void ParseRule();
    void ParseQuery();
    
    void ParseHeadPredicate();
    void ParsePredicate();
    
    void ParsePredicateList();
    void ParseParameterList();
    void ParseStringList();
    void ParseIdList();
    
    void ParseParameter();
    void ParseExpression();
    void ParseOperator();
    
    void ParseTerminal(int token);
    
public:
    ~Parser();
    
    void Parse(vector<Token*> tokens);
};
