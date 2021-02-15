#pragma once

#include <string>

using namespace std;

class Parameter
{
public:
    Parameter(string id);
    
    string ToString() const;
    
protected:
    string id;
};
