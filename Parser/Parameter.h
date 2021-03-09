#pragma once

#include <string>

using namespace std;

class Parameter
{
public:
    Parameter(string id = "");
    virtual ~Parameter() {}
    virtual string ToString() const;
    
protected:
    string id;
};
