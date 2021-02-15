#pragma once

#include "Parameter.h"

class Expression: public Parameter
{
public:
    Expression(string id): Parameter(id) {}
};
