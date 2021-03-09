#pragma once

#include "Parameter.h"

class Expression: public Parameter
{
private:
    Parameter* leftExpression;
    Parameter* rightExpression;
    string operatorChar;
    
public:
    Expression(string id = ""): Parameter(id) {}
    ~Expression();
    
    string ToString() const;
    
    Parameter* GetLeftExpression() const;
    void SetLeftExpression(Parameter* leftExpression);
    
    Parameter* GetRightExpression() const;
    void SetRightExpression(Parameter* rightExpression);
    
    string GetOperatorChar() const;
    void SetOperatorChar(string operatorChar);
    
};
