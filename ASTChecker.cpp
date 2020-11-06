#include "ASTChecker.h"
#include <iostream>

char Printer::printOp(TokenType t)
{
    if (t == TokenType::DivideOp)
        return '/';
    if (t == TokenType::MultiplyOp)
        return '*';
    if (t == TokenType::Plus)
        return '+';
    if (t == TokenType::Minus)
        return '-';
}

void Printer::visit(Leaf *node)
{
    std::cout << "Leaf " << node << " node with value: " << node->getVal() << '\n';
}
void Printer::visit(Expression *node)
{
    std::cout << "Expression node: " << node << "op: " << printOp(node->getOp()) << ", with left child - " << node->getLeft() << " and "
              << "right child - " << node->getRight() << '\n';
    node->getLeft()->acceptVisitor(*this);
    node->getRight()->acceptVisitor(*this);
}