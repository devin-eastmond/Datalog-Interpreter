#pragma once

#include <iostream>
#include <set>
#include <string>
#include "Header.h"
#include "Tuple.h"

using namespace std;

class Relation
{
private:
    string name;
    Header* header;
    set<Tuple*> tuples;
    
    bool TuplesCanJoin(Tuple* t1, Tuple* t2, Header* h1, Header* h2) const;
    
public:
    Relation(string name, Header* header, set<Tuple*> tuples);
    Relation(string name, Header* header);
    ~Relation();
    
    string GetName() const;
    Header* GetHeader() const;
    vector<string> GetHeaderAttributes() const;
    set<Tuple*> GetTuples() const;
    void AddTuple(Tuple* tuple);
    
    Relation* Select(int index, string value);
    Relation* Select(int index1, int index2);
    Relation* Project(vector<string> columnsToKeep);
    Relation* Rename(vector<string> columnNames);
    Relation* Join(Relation* relation2);
    Relation* Union(Relation* relation2);
    
    string ToString() const;
};
