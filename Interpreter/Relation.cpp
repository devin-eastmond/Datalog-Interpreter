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

Relation* Relation::Join(Relation *r2)
{
    Relation* joinedRelation = Union(r2);
    if (joinedRelation != NULL) {
        return joinedRelation;
    }
    
    Relation* r1 = this;
    
    // Combine header
    vector<string> r1Attributes = r1->GetHeader()->GetAttributes();
    vector<string> attributeNames = r1Attributes;
    vector<string> r2Attributes = r2->GetHeader()->GetAttributes();
    for (int i = 0; i < (int)r2Attributes.size(); i++) {
        if (!count(attributeNames.begin(), attributeNames.end(), r2Attributes.at(i))) {
            attributeNames.push_back(r2Attributes.at(i));
        }
    }
    
    Header* h = new Header(attributeNames);
    joinedRelation = new Relation(r1->GetName(), h);
    set<Tuple*> tuples1 = r1->GetTuples();
    set<Tuple*> tuples2 = r2->GetTuples();
    
    // Combine tuples
    set<Tuple*>::iterator it1;
    set<Tuple*>::iterator it2;
    for (it1 = tuples1.begin(); it1 != tuples1.end(); it1++) {
        Tuple* t1 = *it1;
        for (it2 = tuples2.begin(); it2 != tuples2.end(); it2++) {
            Tuple* t2 = *it2;
            if (TuplesCanJoin(t1, t2, r1->GetHeader(), r2->GetHeader())) {
                vector<string> attributes = t1->GetAttributeNames();
                vector<string> t2Values = t2->GetAttributeNames();
                for (int i = 0; i < (int)r2Attributes.size(); i++) {
                    if (!count(r1Attributes.begin(), r1Attributes.end(), r2Attributes.at(i))) {
                        attributes.push_back(t2Values.at(i));
                    }
                }
                joinedRelation->AddTuple(new Tuple(attributes));
            }
        }
    }
    
    return joinedRelation;
}

Relation* Relation::Union(Relation *r2)
{
    Relation* r1 = this;
    vector<string> h1 = r1->GetHeader()->GetAttributes();
    vector<string> h2 = r2->GetHeader()->GetAttributes();
    bool matchingHeaders = true;
    if (h1.size() == h2.size()) {
        for (int i = 0; i < (int)h1.size(); i++) {
            if (h1.at(i) != h2.at(i)) {
                matchingHeaders = false;
                break;
            }
        }
    } else {
        matchingHeaders = false;
    }
    if (matchingHeaders) {
        Relation* joinedRelation = new Relation(r1->GetName(), r1->GetHeader());
        //Relation* joinedRelation = r1;
        
        set<Tuple*> tuples1 = r1->GetTuples();
        set<Tuple*> tuples2 = r2->GetTuples();
        set<Tuple*>::iterator it1;
        for (it1 = tuples1.begin(); it1 != tuples1.end(); it1++) {
            Tuple* tuple = *it1;
            joinedRelation->AddTuple(tuple);
            r1->AddTuple(tuple);
        }
        set<Tuple*>::iterator it2;
        for (it2 = tuples2.begin(); it2 != tuples2.end(); it2++) {
            Tuple* tuple = *it2;
            joinedRelation->AddTuple(tuple);
            r1->AddTuple(tuple);
        }
        
        return joinedRelation;
    } else {
        return NULL;
    }
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

bool Relation::TuplesCanJoin(Tuple* t1, Tuple* t2, Header* h1, Header* h2) const
{
    vector<string> t1Values = t1->GetAttributeNames();
    vector<string> t2Values = t2->GetAttributeNames();
    vector<string> h1Values = h1->GetAttributes();
    vector<string> h2Values = h2->GetAttributes();
    
    for (int i = 0; i < (int)t1Values.size(); i++) {
        for (int j = 0; j < (int)t2Values.size(); j++) {
            if (h1Values.at(i) == h2Values.at(j) && t1Values.at(i) != t2Values.at(j)) {
                return false;
            }
        }
    }
    
    return true;
}
