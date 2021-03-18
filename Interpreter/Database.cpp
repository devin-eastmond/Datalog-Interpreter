#include "Database.h"

Database::~Database()
{
    for (int i = 0; i < (int)relations.size(); i++) {
        delete relations.at(i);
    }
}

void Database::AddRelation(Relation *relation)
{
    relations.push_back(relation);
}

vector<Relation*> Database::GetRelations() const
{
    return relations;
}

Relation* Database::GetRelation(string name) const
{
    for (int i = 0; i < (int)relations.size(); i++) {
        if (relations.at(i)->GetName() == name) {
            return relations.at(i);
        }
    }
    throw 1;
}

void Database::AddTupleToRelation(string name, vector<string> attributeNames)
{
    for (int i = 0; i < (int)relations.size(); i++) {
        if (relations.at(i)->GetName() == name) {
            relations.at(i)->AddTuple(new Tuple(attributeNames));
            
            return;
        }
    }
    throw 1;
}

string Database::ToString() const
{
    string databaseString = "";
    for (int i = 0; i < (int)relations.size(); i++) {
        databaseString += relations.at(i)->ToString();
    }
    
    return databaseString;
}
