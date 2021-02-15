#pragma once

#include <vector>
#include "Predicate.h"

using namespace std;

class Rule
{
private:
    Predicate* headPredicate;
    vector<Predicate*> predicateList;
    
public:
    string ToString() const;
    
    Predicate* GetHeadPredicate() const;
    void SetHeadPredicate(Predicate* headPredicate);
    
    vector<Predicate*> GetPredicateList() const;
    void AddPredicate(Predicate* predicate);
};
