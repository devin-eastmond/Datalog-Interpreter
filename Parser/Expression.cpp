#include "Expression.h"

Expression::~Expression()
{
    delete leftExpression;
    delete rightExpression;
}

string Expression::ToString() const
{
    string objectString = "(" + leftExpression->ToString() + operatorChar + rightExpression->ToString() + ")";
    
    return objectString;
}

Parameter* Expression::GetLeftExpression() const
{
    return leftExpression;
}

void Expression::SetLeftExpression(Parameter* leftExpression)
{
    this->leftExpression = leftExpression;
}

Parameter* Expression::GetRightExpression() const
{
    return rightExpression;
}

void Expression::SetRightExpression(Parameter* rightExpression)
{
    this->rightExpression = rightExpression;
}

string Expression::GetOperatorChar() const
{
    return operatorChar;
}

void Expression::SetOperatorChar(string operatorChar)
{
    this->operatorChar = operatorChar;
}
