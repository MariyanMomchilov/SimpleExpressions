#include "Parser.h"
#include <cassert>
#include "ASTVisitors.h"

Expression::Expression(Node *l, Node *r, TokenType o) : left(l), right(r), op(o) {}

void Expression::acceptVisitor(Visitor &v) { v.visit(this); }

Node *Expression::getLeft() { return left; }

Node *Expression::getRight() { return right; }

TokenType Expression::getOp() const { return op; }

Expression::~Expression()
{
    delete left;
    delete right;
}

Leaf::Leaf(int val) : value(val) {}
void Leaf::acceptVisitor(Visitor &v) { v.visit(this); }
int Leaf::getVal() { return value; }

Parser::Parser(LexerResult &lr) : tokens(lr.tokens), tIndex(0) {}

inline Token Parser::current() const
{
    return tokens[tIndex];
}

inline void Parser::next()
{
    tIndex++;
}

inline void Parser::previous()
{
    tIndex--;
}

inline bool Parser::isType(TokenType t) const
{
    return tokens[tIndex].type == t;
}

Node *Parser::buildAST()
{
    return parseSum();
}

Node *Parser::parseOperand()
{
    Token crr = current();
    if (crr.type == TokenType::Number)
    {
        next();
        return new Leaf{crr.value};
    }
    else if (crr.type == TokenType::LeftPar)
    {
        next();
        Node *expr = parseSum();
        assert(current().type == TokenType::RightPar && expr != nullptr);
        next();
        return expr;
    }
    assert(false);
    return nullptr;
}

Node *Parser::parseProduct()
{
    Node *operand = parseOperand();

    Node *right;
    TokenType type;
    while (isType(TokenType::MultiplyOp) || isType(TokenType::DivideOp) || isType(TokenType::ModuloOp))
    {
        type = current().type;
        next();
        right = parseOperand();
        assert(right != nullptr);
        operand = new Expression(operand, right, type);
    }
    return operand;
}

Node *Parser::parseSum()
{
    Node *product = parseProduct();
    Node *nextProduct;
    TokenType type;
    while (isType(TokenType::Plus) || isType(TokenType::Minus))
    {
        type = current().type;
        next();
        nextProduct = parseProduct();
        assert(nextProduct != nullptr);
        product = new Expression(product, nextProduct, type);
    }
    return product;
}