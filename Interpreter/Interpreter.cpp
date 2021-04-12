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
    
    vector<Rule*> rules = datalogProgram->GetRules();
    EvaluateRules(rules);
    
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

void Interpreter::EvaluateRules(vector<Rule*> rules)
{
    int numTuples = 0;
    do {
        numTuples = database->GetNumTuples();
        for (int i = 0; i < (int)rules.size(); i++) {
            cout << rules.at(i)->ToString() << "." << endl;
            
            // 1. Evaluate predicates on right-hand side of rule
            vector<Relation*> evaluatedPredicates;
            vector<Predicate*> predicateList = rules.at(i)->GetPredicateList();
            for (int j = 0; j < (int)predicateList.size(); j++) {
                evaluatedPredicates.push_back(EvaluatePredicate(predicateList.at(j)));
            }
            
            // 2. Join the relations that result
            Relation* joinedRelation = evaluatedPredicates.at(0);
            if (evaluatedPredicates.size() > 1) {
                for (int j = 1; j < (int)evaluatedPredicates.size(); j++) {
                    joinedRelation = joinedRelation->Join(evaluatedPredicates.at(j));
                }
            }
            
            // 3. Project columns that appear in head predicate
            vector<Parameter*> headPredicateParameters = rules.at(i)->GetHeadPredicate()->GetParameters();
            vector<string> headPredicateColumns;
            for (int j = 0; j < (int)headPredicateParameters.size(); j++) {
                headPredicateColumns.push_back(headPredicateParameters.at(j)->ToString());
            }
            joinedRelation = joinedRelation->Project(headPredicateColumns);
            
            // 4. Rename the relation to make it union-compatible
            Relation* databaseRelation = database->GetRelation(rules.at(i)->GetHeadPredicate()->GetId());
            joinedRelation = joinedRelation->Rename(databaseRelation->GetHeader()->GetAttributes());
            
            // 5. Union with the relation in the database
            //joinedRelation = joinedRelation->Union(databaseRelation);
            databaseRelation->Join(joinedRelation);
            
            cout << joinedRelation->ToString() << endl;
        }
    } while(numTuples != database->GetNumTuples());
}

void Interpreter::EvaluateQueries(vector<Predicate*> queries)
{
    // Iterate through queries
    for (int i = 0; i < (int)queries.size(); i++) {
        Relation* relation = EvaluatePredicate(queries.at(i));
        QueryEvaluationOutput(queries.at(i), relation);
    }
}

Relation* Interpreter::EvaluatePredicate(Predicate* predicate)
{
    string name = predicate->GetId();
    Relation* relation = database->GetRelation(name);
    
    vector<string> attributes = GetAttributeNamesFromParameters(predicate->GetParameters());
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
    
    return relation;
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
