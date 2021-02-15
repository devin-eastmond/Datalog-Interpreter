#include "Parameter.h"

Parameter::Parameter(string id)
{
    this->id = id;
}

string Parameter::ToString() const
{
    return id;
}
