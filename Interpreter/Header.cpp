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
