#ifndef __LEX
#define __LEX
#include <vector>

enum class TokenType
{
    LeftPar,
    RightPar,
    Number,
    MultiplyOp,
    DivideOp,
    ModuloOp,
    Plus,
    Minus,
    Invalid
};

struct Token
{
    TokenType type;
    char symbolToken;
    int value;
};

struct LexerResult
{
    std::vector<Token> tokens;
};

class Lexer
{
private:
    const char *source;
    unsigned currentIndex;
    bool state;

    bool match(char c);
    bool isDigit() const;
    void next();
    char getChar() const;
    void skipWhitespace();
    Token nextToken();

    Token number();
    Token symbolToken();

public:
    Lexer(const char *_s);
    LexerResult tokenize();
};

#endif