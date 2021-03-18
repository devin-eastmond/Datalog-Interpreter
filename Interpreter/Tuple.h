#pragma once

#include <string>
#include <vector>

using namespace std;

class Tuple
{
private:
    vector<string> attributeNames;
    
    bool operator< (const Tuple& other) const {
//        for (int i = 0; i < (int)attributeNames.size(); i++) {
//            if (attributeNames.at(i) != other.GetAttributeNames().at(i)) {
//                return attributeNames.at(i) < other.GetAttributeNames().at(i);
//            }
//        }
        return this->attributeNames > other.GetAttributeNames();
    }
    
public:
    Tuple() {}
    Tuple(vector<string> attributeNames);
    
    vector<string> GetAttributeNames() const;
    void AddAttributeName(string attributeName);
    
    string ToString() const;
};
