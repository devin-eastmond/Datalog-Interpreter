#include "DatalogProgram.h"

DatalogProgram::~DatalogProgram()
{
    for (int i = 0; i < (int)schemes.size(); i++) {
        delete schemes.at(i);
    }
    for (int i = 0; i < (int)facts.size(); i++) {
        delete facts.at(i);
    }
    for (int i = 0; i < (int)rules.size(); i++) {
        delete rules.at(i);
    }
    for (int i = 0; i < (int)queries.size(); i++) {
        delete queries.at(i);
    }
}

string DatalogProgram::ToString() const
{
    string objectString = "Schemes(" + to_string(schemes.size()) + "):\n";
    for (int i = 0; i < (int)schemes.size(); i++) {
        objectString += "  " + schemes.at(i)->ToString() + "\n";
    }
    
    objectString += "Facts(" + to_string(facts.size()) + "):\n";
    for (int i = 0; i < (int)facts.size(); i++) {
        objectString += "  " + facts.at(i)->ToString() + ".\n";
    }
    
    objectString += "Rules(" + to_string(rules.size()) + "):\n";
    for (int i = 0; i < (int)rules.size(); i++) {
        objectString += "  " + rules.at(i)->ToString() + ".\n";
    }
    
    objectString += "Queries(" + to_string(queries.size()) + "):\n";
    for (int i = 0; i < (int)queries.size(); i++) {
        objectString += "  " + queries.at(i)->ToString() + "?\n";
    }
    
    objectString += "Domain(" + to_string(domain.size()) + "):\n";
    for (set<string>::iterator it = domain.begin(); it != domain.end(); it++) {
        objectString += "  \'" + *it + "\'\n";
    }
    
    return objectString;
}

void DatalogProgram::AddScheme(Predicate* scheme)
{
    schemes.push_back(scheme);
}

void DatalogProgram::AddFact(Predicate* fact)
{
    facts.push_back(fact);
    vector<Parameter*> factParameters = fact->GetParameters();
    for (int i = 0; i < (int)factParameters.size(); i++) {
        string parameter = factParameters.at(i)->ToString();
        domain.insert(parameter.substr(1, parameter.size() - 2));
    }
}

void DatalogProgram::AddRule(Rule* rule)
{
    rules.push_back(rule);
}

void DatalogProgram::AddQuery(Predicate* query)
{
    queries.push_back(query);
}
