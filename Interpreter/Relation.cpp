#include "Relation.h"

Relation::Relation(string name, Header* header, set<Tuple*> tuples)
{
    this->name = name;
    this->header = header;
    this->tuples = tuples;
}

void Relation::Select()
{
    
}

Relation* Relation::Project(vector<string> columnsToKeep)
{
    vector<Tuple*> newTuples;
    for (int i = 0; i < (int)tuples.size(); i++) {
        newTuples.push_back(new Tuple());
    }
    
    vector<string> headerAttributes = header->GetAttributes();
    for (int i = 0; i < (int)columnsToKeep.size(); i++) {
        for (int j = 0; j < (int)headerAttributes.size(); i++) {
            if (columnsToKeep.at(i) == headerAttributes.at(j)) {
                set<Tuple*>::iterator it;
                int index = 0;
                for (it = tuples.begin(); it != tuples.end(); it++) {
                    Tuple* tuple = *it;
                    newTuples.at(index)->AddAttributeName(tuple->GetAttributeNames().at(j));
                    index++;
                }
                goto header_found;
            }
        }
        throw 1;
        header_found:;
    }
    
    set<Tuple*> tupleSet;
    for (int i = 0; i < (int)newTuples.size(); i++) {
        tupleSet.insert(newTuples.at(i));
    }
    
    return new Relation(name, new Header(columnsToKeep), tupleSet);
}

Relation* Relation::Rename(vector<string> columnNames)
{
    return new Relation(name, new Header(columnNames), tuples);
}