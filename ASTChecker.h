#ifndef _VISITORS
#define _VISITORS
#include "Parser.h"

class Visitor
{
public:
    virtual void visit(Leaf *node) = 0;
    virtual void visit(Expression *node) = 0;
    ~Visitor() = default;
};

class Printer : public Visitor
{
public:
    char printOp(TokenType t);
    void visit(Leaf *node) override;
    void visit(Expression *node) override;
};

#endif