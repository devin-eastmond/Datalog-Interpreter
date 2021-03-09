#pragma once

#include <string>
#include <vector>

using namespace std;

class Tuple
{
private:
    vector<string> attributeNames;
    
    bool operator< (const Tuple & other) const {
        return (sizeof(attributeNames) < sizeof(other.GetAttributeNames()));
    }
    
public:
    vector<string> GetAttributeNames() const;
    void AddAttributeName(string attributeName);
};
