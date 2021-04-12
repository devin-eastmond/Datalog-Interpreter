#pragma once

#include <vector>
#include "Relation.h"

using namespace std;

class Database
{
private:
    vector<Relation*> relations;
    
public:
    ~Database();
    
    void AddRelation(Relation* relation);
    vector<Relation*> GetRelations() const;
    Relation* GetRelation(string name) const;
    int GetNumTuples() const;
    
    void AddTupleToRelation(string name, vector<string> attributeNames);
    
    string ToString() const;
};
