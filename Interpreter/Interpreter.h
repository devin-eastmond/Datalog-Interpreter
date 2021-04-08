#pragma once

#include <algorithm>
#include "Database.h"
#include "../Parser/DatalogProgram.h"

class Interpreter
{
private:
    Database* database;
    
    void EvaluateSchemes(vector<Predicate*> schemes);
    void EvaluateFacts(vector<Predicate*> facts);
    void EvaluateRules(vector<Rule*> rules);
    void EvaluateQueries(vector<Predicate*> queries);
    
    Relation* EvaluatePredicate(Predicate* predicate);
    
    vector<string> GetAttributeNamesFromParameters(vector<Parameter*> parameters) const;
    bool IsVariable(string attribute) const;
    
    void QueryEvaluationOutput(Predicate* query, Relation* relation);
    
public:
    Interpreter();
    ~Interpreter();
    
    void Run(DatalogProgram* datalogProgram);
};
