#include "Lexer.h"
#include <cmath>

inline bool Lexer::match(char c)
{
    if (getChar() == c)
    {
        next();
        return true;
    }
    return false;
}

inline void Lexer::next()
{
    currentIndex++;
}

inline char Lexer::getChar() const
{
    return source[currentIndex];
}

inline void Lexer::skipWhitespace()
{
    char crr = getChar();
    while (crr == ' ' || crr == '\f' || crr == '\n' || crr == '\r' || crr == '\t' || crr == '\v')
    {
        next();
        crr = getChar();
    }
}

inline bool Lexer::isDigit() const
{
    return getChar() >= '0' && getChar() <= '9';
}

Token Lexer::number()
{
    int num = 0;
    if (isDigit())
    {
        while (isDigit())
        {
            num = num * 10 + (getChar() % 48);
            next();
        }

        state = true;
        return Token{TokenType::Number, '_', num};
    }
    state = false;
    return Token{TokenType::Invalid, '?', 0};
}

Token Lexer::symbolToken()
{
    state = true;
    if (match('+'))
        return Token{TokenType::Plus, '+', 0};
    else if (match('-'))
        return Token{TokenType::Minus, '-', 0};
    else if (match('*'))
        return Token{TokenType::MultiplyOp, '*', 0};
    else if (match('/'))
        return Token{TokenType::DivideOp, '/', 0};
    else if (match('('))
        return Token{TokenType::LeftPar, '(', 0};
    else if (match(')'))
        return Token{TokenType::RightPar, ')', 0};

    state = false;
    next();
    return Token{TokenType::Invalid, '?', 0};
}

Token Lexer::nextToken()
{
    Token res = number();
    if (state)
        return res;

    return symbolToken();
}

Lexer::Lexer(const char *_s) : source(_s), currentIndex(0), state(true)
{
}
LexerResult Lexer::tokenize()
{

    LexerResult lex;
    while (getChar() != '\0')
    {
        skipWhitespace();
        lex.tokens.push_back(nextToken());
    }
    return lex;
}