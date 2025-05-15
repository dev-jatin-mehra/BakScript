#ifndef TOKENS_H
#define TOKENS_H

typedef enum
{
    TOKEN_REPEAT,         // repeat keyword
    TOKEN_NUM,            // num keyword
    TOKEN_STRING,         // string keyword
    TOKEN_WHEN,           // when keyword
    TOKEN_OTHERWISE,      // otherwise keyword
    TOKEN_SHOW,           // show keyword
    TOKEN_IDENTIFIER,     // variable names
    TOKEN_NUMBER,         // numbers like 5, 10 etc
    TOKEN_STRING_LITERAL, // string literals "John"
    TOKEN_EQUAL,          // =
    TOKEN_GT,               // '>'
    TOKEN_LT,               // '<'
    TOKEN_SEMICOLON,      // ;
    TOKEN_COLON,          // :
    TOKEN_PLUS,           // +
    TOKEN_MINUS,          // -
    TOKEN_STAR,           // *
    TOKEN_SLASH,          // /
    TOKEN_LBRACE,         // {
    TOKEN_RBRACE,         // }
    TOKEN_EOF             // end of file/input
} TK_TYPE;

typedef struct
{
    TK_TYPE type;
    char *lexeme;
} Token;

#endif
