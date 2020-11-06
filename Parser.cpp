#include "Parser.h"
#include <cassert>
#include "ASTChecker.h"

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

Node *Parser::buildAST()
{
    return parseSum();
}

Node *Parser::parseNumber()
{
    Token crr = current();
    if (crr.type == TokenType::Number)
    {
        next();
        return new Leaf{crr.value};
    }
    return nullptr;
}

Node *Parser::parseProduct()
{

    Token crr = current();
    if (crr.type == TokenType::LeftPar)
    {
        next();
        Node *sum = parseSum();
        assert(current().type == TokenType::RightPar);
        next();

        Token op = current();
        if (op.type == TokenType::MultiplyOp || op.type == TokenType::DivideOp)
        {
            next();
            Node *right = parseSum();
            return new Expression(sum, right, op.type);
        }

        return sum;
    }
    else
    {
        Node *num = parseNumber();
        if (num != nullptr)
        {
            Token crr = current();
            if (crr.type == TokenType::MultiplyOp || crr.type == TokenType::DivideOp)
            {
                next();
                Node *operand2 = parseSum();
                return new Expression{num, operand2, crr.type};

                assert(false);
            }

            return num;
        }
        return nullptr;
    }
}

Node *Parser::parseSum()
{
    Node *left = parseProduct();
    if (left != nullptr)
    {
        Token op = current();
        if (op.type == TokenType::Plus || op.type == TokenType::Minus)
        {
            next();
            Node *right = parseSum();
            return new Expression(left, right, op.type);
        }

        return left;
    }
}