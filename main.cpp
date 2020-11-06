#include "Lexer.h"
#include "Parser.h"
#include "ASTChecker.h"

int main()
{
    //Lexer l("(1+2) + 1* 4 + 534 * 123512");
    //Lexer l("(1+2)*3");
    Lexer l("1* 4 + 534 * 123512");
    auto res = l.tokenize();

    Parser p(res);
    Node *ast = p.buildAST();

    Printer visitor;
    ast->acceptVisitor(visitor);
}