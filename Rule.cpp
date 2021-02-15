#include "Rule.h"

string Rule::ToString() const
{
    string objectString = headPredicate->ToString() + " :- ";
    objectString += predicateList.at(0)->ToString();
    for (int i = 1; i < (int)predicateList.size(); i++) {
        objectString += "," + predicateList.at(i)->ToString();
    }
    
    return objectString;
}

Predicate* Rule::GetHeadPredicate() const
{
    return headPredicate;
}

void Rule::SetHeadPredicate(Predicate *headPredicate)
{
    this->headPredicate = headPredicate;
}

vector<Predicate*> Rule::GetPredicateList() const
{
    return predicateList;
}

void Rule::AddPredicate(Predicate *predicate)
{
    predicateList.push_back(predicate);
}
