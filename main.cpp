#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "Lexer.h"
//#include "ShuntingYard.cpp"
#include "Parser.h"
#include "ASTVisitors.h"

std::string toRPN(LexerResult &&lr);

TEST_CASE("Shunting yard")
{
    Lexer l("42");
    CHECK(toRPN(l.tokenize()) == "42 ");

    Lexer l2("1 + 2 * 3 + 3");
    CHECK(toRPN(l2.tokenize()) == "1 2 3 * + 3 + ");

    Lexer l3("(1 + 2 * 3) - (4 + 6)");
    CHECK(toRPN(l3.tokenize()) == "1 2 3 * + 4 6 + - ");
}

TEST_CASE("Visitor and Parser 1")
{
    Lexer l("1+2*3 + 12/2 + 7");
    auto res = l.tokenize();

    Parser p(res);
    Node *ast = p.buildAST();

    Printer visitor;
    ast->acceptVisitor(visitor);
}

TEST_CASE("Visitor and Parser 2")
{
    std::cout << "\n\n";
    Lexer l("1 * 4 + (534 - 8 / 2) / 4");
    auto res = l.tokenize();

    Parser p(res);
    Node *ast = p.buildAST();

    Printer visitor;
    ast->acceptVisitor(visitor);
}

int main()
{
    doctest::Context().run();
}