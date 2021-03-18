#pragma once

#include "Database.h"
#include "../Parser/DatalogProgram.h"

class Interpreter
{
private:
    Database* database;
    
    void EvaluateSchemes(vector<Predicate*> schemes);
    void EvaluateFacts(vector<Predicate*> facts);
    void EvaluateQueries(vector<Predicate*> queries);
    
    vector<string> GetAttributeNamesFromParameters(vector<Parameter*> parameters) const;
    bool IsVariable(string attribute) const;
    
    void QueryEvaluationOutput(Predicate* query, Relation* relation);
    
public:
    Interpreter();
    ~Interpreter();
    
    void Run(DatalogProgram* datalogProgram);
};
