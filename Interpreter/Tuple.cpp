#include "Tuple.h"

vector<string> Tuple::GetAttributeNames() const
{
    return attributeNames;
}

void Tuple::AddAttributeName(string attributeName)
{
    attributeNames.push_back(attributeName);
}
