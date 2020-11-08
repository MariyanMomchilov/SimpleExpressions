#ifndef _PARSER
#define _PARSER
#include "Lexer.h"
class Visitor; // TO DO:

class Node
{
public:
    virtual void acceptVisitor(Visitor &v) = 0;
    virtual ~Node() = default;
};

class Expression : public Node
{
private:
    Node *left;
    Node *right;
    TokenType op;

public:
    Expression(Node *l, Node *r, TokenType o);
    void acceptVisitor(Visitor &v) override;
    Node *getLeft();
    Node *getRight();
    TokenType getOp() const;
    ~Expression();
};

class Leaf : public Node
{
private:
    int value;

public:
    Leaf(int val);
    void acceptVisitor(Visitor &v) override;
    int getVal();
    ~Leaf() = default;
};

class Parser
{
public:
    Parser(LexerResult &lr);
    Node *buildAST();

private:
    std::vector<Token> tokens;
    unsigned tIndex;
    Token current() const;
    bool isType(TokenType t) const;
    void next();
    void previous();
    Node *parseOperand();
    Node *parseProduct();
    Node *parseSum();
};

#endif