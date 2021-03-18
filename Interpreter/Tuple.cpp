#include "Tuple.h"

Tuple::Tuple(vector<string> attributeNames)
{
    this->attributeNames = attributeNames;
}

vector<string> Tuple::GetAttributeNames() const
{
    return attributeNames;
}

void Tuple::AddAttributeName(string attributeName)
{
    attributeNames.push_back(attributeName);
}

string Tuple::ToString() const
{
    string tupleString = "{";
    for (int i = 0; i < (int)attributeNames.size(); i++) {
        tupleString += attributeNames.at(i);
        if (i != (int)attributeNames.size() - 1) {
            tupleString += ",";
        }
    }
    tupleString += "}";
    
    return tupleString;
}
