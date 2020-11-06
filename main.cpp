#include "Lexer.cpp"

int main()
{
    Lexer l("(1+2) + 1* 4 + 534 * 123512");
    auto res = l.tokenize();
}