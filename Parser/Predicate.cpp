#include "Predicate.h"

Predicate::Predicate(string id)
{
    this->id = id;
}

Predicate::~Predicate()
{
    for (int i = 0; i < (int)parameters.size(); i++) {
        delete parameters.at(i);
    }
}

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

void Predicate::SetParameters(vector<Parameter*> parameters)
{
    this->parameters = parameters;
}

string Predicate::GetId() const
{
    return id;
}
