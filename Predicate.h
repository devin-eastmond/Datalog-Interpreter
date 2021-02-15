#pragma once

#include <string>
#include <vector>
#include "Parameter.h"

using namespace std;

// This class includes: Schemes, Facts, Queries, and Predicates
class Predicate
{
private:
    string id;
    vector<Parameter*> parameters;
    
public:
    string ToString() const;
    
    vector<Parameter*> GetParameters() const;
    void AddParameter(Parameter* parameter);
    
};
