#include "Header.h"

Header::Header(vector<string> attributeNames)
{
    this->attributeNames = attributeNames;
}

void Header::AddAttribute(string attribute)
{
    attributeNames.push_back(attribute);
}

vector<string> Header::GetAttributes() const
{
    return attributeNames;
}

string Header::ToString() const
{
    string headerString = "{";
    for (int i = 0; i < (int)attributeNames.size(); i++) {
        headerString += attributeNames.at(i);
        if (i != (int)attributeNames.size() - 1) {
            headerString += ",";
        }
    }
    headerString += "}";
    
    return headerString;
}
