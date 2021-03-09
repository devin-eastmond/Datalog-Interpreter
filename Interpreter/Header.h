#pragma once

#include <string>
#include <vector>

using namespace std;

class Header
{
private:
    vector<string> attributeNames;
    
public:
    Header(vector<string> attributeNames);
    
    void AddAttribute(string attribute);
    vector<string> GetAttributes() const;
};
