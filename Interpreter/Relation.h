#pragma once

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
    
public:
    Relation(string name, Header* header, set<Tuple*> tuples);
    ~Relation();
    
    Relation* Select(int index, string value);
    Relation* Select(int index1, int index2);
    Relation* Project(vector<string> columnsToKeep);
    Relation* Rename(vector<string> columnNames);
};
