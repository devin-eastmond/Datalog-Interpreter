#include "Interpreter.h"

Interpreter::Interpreter()
{
    database = new Database();
}

Interpreter::~Interpreter()
{
    if (nullptr != database) {
        delete database;
    }
}

void Interpreter::Run(DatalogProgram* datalogProgram)
{
    vector<Predicate*> schemes = datalogProgram->GetSchemes();
    EvaluateSchemes(schemes);
    
    vector<Predicate*> facts = datalogProgram->GetFacts();
    EvaluateFacts(facts);
    
    vector<Predicate*> queries = datalogProgram->GetQueries();
    EvaluateQueries(queries);
    
    //cout << database->ToString() << endl;
}

void Interpreter::EvaluateSchemes(vector<Predicate*> schemes)
{
    for (int i = 0; i < (int)schemes.size(); i++) {
        vector<string> attributeNames = GetAttributeNamesFromParameters(schemes.at(i)->GetParameters());
        
        string name = schemes.at(i)->GetId();
        Header* header = new Header(attributeNames);
        Relation* relation = new Relation(name, header);
        database->AddRelation(relation);
    }
}

void Interpreter::EvaluateFacts(vector<Predicate*> facts)
{
    for (int i = 0; i < (int)facts.size(); i++) {
        vector<string> attributeNames = GetAttributeNamesFromParameters(facts.at(i)->GetParameters());
        string name = facts.at(i)->GetId();
        database->AddTupleToRelation(name, attributeNames);
    }
}

void Interpreter::EvaluateRules(vector<Rule *> rules)
{
    
}

void Interpreter::EvaluateQueries(vector<Predicate*> queries)
{
    // Iterate through queries
    for (int i = 0; i < (int)queries.size(); i++) {
        Predicate* query = queries.at(i);
        string name = query->GetId();
        Relation* relation = database->GetRelation(name);
        
        vector<string> attributes = GetAttributeNamesFromParameters(query->GetParameters());
        vector<string> variables;
        vector<string> variableColumns;
        // Iterate through each attribute of the query
        for (int j = 0; j < (int)attributes.size(); j++) {
            string attribute = attributes.at(j);
            if (IsVariable(attribute)) {
                if (find(variables.begin(), variables.end(), attribute) == variables.end()) {
                    variables.push_back(attribute);
                    variableColumns.push_back(relation->GetHeaderAttributes().at(j));
                }
                // Check the rest of the attributes to find matching variables
                for (int k = j+1; k < (int)attributes.size(); k++) {
                    if (attributes.at(k) == attribute) {
                        relation = relation->Select(j, k);
                    }
                }
            } else {
                relation = relation->Select(j, attribute);
            }
        }
        
        relation = relation->Project(variableColumns);
        relation = relation->Rename(variables);
        QueryEvaluationOutput(query, relation);
    }
}

vector<string> Interpreter::GetAttributeNamesFromParameters(vector<Parameter*> parameters) const
{
    vector<string> attributeNames;
    for (int i = 0; i < (int)parameters.size(); i++) {
        attributeNames.push_back(parameters.at(i)->ToString());
    }
    
    return attributeNames;
}

bool Interpreter::IsVariable(string attribute) const
{
    if (attribute.at(0) != '\'' && attribute.at(attribute.length() - 1) != '\'') {
        return true;
    }
    
    return false;
}

void Interpreter::QueryEvaluationOutput(Predicate* query, Relation* relation)
{
    cout << query->ToString() << "? ";
    int numSolutions = (int)relation->GetTuples().size();
    if (numSolutions == 0) {
        cout << "No" << endl;
        return;
    } else {
        cout << "Yes(" << numSolutions << ")" << endl;
    }
    vector<string> variables = relation->GetHeaderAttributes();
    set<Tuple*> tuples = relation->GetTuples();
    set<Tuple*>::iterator it;
    set<vector<string>>::iterator it2;
    set<vector<string>> sortedTuples;
    for (it = tuples.begin(); it != tuples.end(); it++) {
        Tuple* tuple = *it;
        sortedTuples.insert(tuple->GetAttributeNames());
    }
    for (it2 = sortedTuples.begin(); it2 != sortedTuples.end(); it2++) {
        if (variables.size() != 0) {
            cout << "  ";
        }
        for (int i = 0; i < (int)variables.size(); i++) {
            cout << variables.at(i) << "=" << it2->at(i);
            if (i == (int)variables.size() - 1) {
                cout << endl;
            } else {
                cout << ", ";
            }
        }
    }
}
