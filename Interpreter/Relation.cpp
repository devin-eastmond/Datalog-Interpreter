#include "Relation.h"

Relation::Relation(string name, Header* header, set<Tuple*> tuples)
{
    this->name = name;
    this->header = header;
    this->tuples = tuples;
}

Relation::Relation(string name, Header* header)
{
    this->name = name;
    this->header = header;
}

Relation::~Relation()
{
    delete header;
    set<Tuple*>::iterator it;
    for (it = tuples.begin(); it != tuples.end(); it++) {
        delete *it;
    }
}

string Relation::GetName() const
{
    return name;
}

Header* Relation::GetHeader() const
{
    return header;
}

vector<string> Relation::GetHeaderAttributes() const
{
    return header->GetAttributes();
}

set<Tuple*> Relation::GetTuples() const
{
    return tuples;
}

void Relation::AddTuple(Tuple* tuple)
{
    set<Tuple*>::iterator it;
    for (it = tuples.begin(); it != tuples.end(); it++) {
        Tuple* currentTuple = *it;
        if (currentTuple->GetAttributeNames() == tuple->GetAttributeNames()) {
            return;
        }
    }
    tuples.insert(tuple);
}

Relation* Relation::Select(int index, string value)
{
    set<Tuple*>::iterator it;
    set<Tuple*> newTuples;
    for (it = tuples.begin(); it != tuples.end(); it++) {
        Tuple* currentTuple = *it;
        vector<string> attributeNames = currentTuple->GetAttributeNames();
        if (attributeNames.at(index) == value) {
            newTuples.insert(currentTuple);
        }
    }
    
    return new Relation(name, header, newTuples);
}

Relation* Relation::Select(int index1, int index2)
{
    set<Tuple*>::iterator it;
    set<Tuple*> newTuples;
    for (it = tuples.begin(); it != tuples.end(); it++) {
        Tuple* currentTuple = *it;
        vector<string> attributeNames = currentTuple->GetAttributeNames();
        if (attributeNames.at(index1) == attributeNames.at(index2)) {
            newTuples.insert(currentTuple);
        }
    }
    
    return new Relation(name, header, newTuples);
}

Relation* Relation::Project(vector<string> columnsToKeep)
{
    vector<Tuple*> newTuples;
    for (int i = 0; i < (int)tuples.size(); i++) {
        newTuples.push_back(new Tuple());
    }
    
    vector<string> headerAttributes = header->GetAttributes();
    for (int i = 0; i < (int)columnsToKeep.size(); i++) {
        for (int j = 0; j < (int)headerAttributes.size(); j++) {
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

string Relation::ToString() const
{
    string relationString = "Relation " + name + ":\n";
    relationString += header->ToString() + "\n";
    set<Tuple*>::iterator it;
    for (it = tuples.begin(); it != tuples.end(); it++) {
        Tuple* tuple = *it;
        relationString += tuple->ToString() + "\n";
    }
    
    return relationString;
}
