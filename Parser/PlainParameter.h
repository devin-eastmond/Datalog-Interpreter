#pragma once

#include "Parameter.h"

class PlainParameter: public Parameter
{
public:
    PlainParameter(string id = ""): Parameter(id) {}
};
