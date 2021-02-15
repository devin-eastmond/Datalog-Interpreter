#include "Predicate.h"

string Predicate::ToString() const
{
    string objectString = id + "(" + parameters.at(0)->ToString();
    for (int i = 1; i < (int)parameters.size(); i++) {
        objectString += "," + parameters.at(i)->ToString();
    }
    objectString += ")";
    
    return objectString;
}

vector<Parameter*> Predicate::GetParameters() const
{
    return parameters;
}

void Predicate::AddParameter(Parameter *parameter)
{
    parameters.push_back(parameter);
}
