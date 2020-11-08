#include "Lexer.h"
#include <stack>
#include <sstream>
#include <cassert>

int getPrecedence(TokenType op)
{
    switch (op)
    {
    case TokenType::Plus:
        return 1;
    case TokenType::Minus:
        return 1;
    case TokenType::MultiplyOp:
        return 2;
    case TokenType::DivideOp:
        return 2;

    default:
        assert(false);
    }

    return -1;
}

char getSymbol(TokenType op)
{
    switch (op)
    {
    case TokenType::Plus:
        return '+';
    case TokenType::Minus:
        return '-';
    case TokenType::MultiplyOp:
        return '*';
    case TokenType::DivideOp:
        return '/';

    default:
        assert(false);
    }

    return -1;
}

std::string toRPN(LexerResult &&lr)
{
    std::stringstream output;
    std::stack<TokenType> ops;
    for (int i = 0; i < lr.tokens.size(); i++)
    {
        Token token = lr.tokens[i];
        if (token.type == TokenType::Number)
        {
            output << token.value << " ";
            continue;
        }
        else if (token.type == TokenType::LeftPar)
        {
            ops.push(token.type);
            continue;
        }
        else if (token.type == TokenType::RightPar)
        {
            while (!ops.empty() && ops.top() != TokenType::LeftPar)
            {
                output << getSymbol(ops.top()) << " ";
                ops.pop();
            }
            assert(ops.top() == TokenType::LeftPar);
            ops.pop();
        }
        else
        {
            int tokenOpPrecedence = getPrecedence(token.type);
            if (!ops.empty() && ops.top() != TokenType::LeftPar && tokenOpPrecedence <= getPrecedence(ops.top()))
            {
                while (!ops.empty() && ops.top() != TokenType::LeftPar && tokenOpPrecedence <= getPrecedence(ops.top()))
                {
                    output << getSymbol(ops.top()) << " ";
                    ops.pop();
                }
            }
            ops.push(token.type);
        }
    }

    while (!ops.empty())
    {
        output << getSymbol(ops.top()) << " ";
        ops.pop();
    }
    return output.str();
}
