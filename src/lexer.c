#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
#include "lexer.h"

Lexer init_lexer(char *source)
{
    Lexer lexer;
    lexer.source = source;
    lexer.pos = 0;
    return lexer;
}

char peek(Lexer *lexer)
{
    return lexer->source[lexer->pos];
}

char advance(Lexer *lexer)
{
    return lexer->source[lexer->pos++];
}

void skipWhiteSpace(Lexer *lexer)
{
    while (isspace(peek(lexer)))
    {
        advance(lexer);
    }
}

Token scanIdentifier(Lexer *lexer)
{
    char buffer[MAX_TOKEN_LENGTH];
    int length = 0;

    while ((isalnum(peek(lexer)) || peek(lexer) == '_') && length < MAX_TOKEN_LENGTH - 1)
    {
        buffer[length++] = advance(lexer);
    }
    buffer[length] = '\0';

    if (strcmp(buffer, "repeat") == 0)
        return (Token){TOKEN_REPEAT, strdup(buffer)};
    if (strcmp(buffer, "num") == 0)
        return (Token){TOKEN_NUM, strdup(buffer)};
    if (strcmp(buffer, "string") == 0)
        return (Token){TOKEN_STRING, strdup(buffer)};
    if (strcmp(buffer, "when") == 0)
        return (Token){TOKEN_WHEN, strdup(buffer)};
    if (strcmp(buffer, "otherwise") == 0)
        return (Token){TOKEN_OTHERWISE, strdup(buffer)};
    if (strcmp(buffer, "show") == 0)
        return (Token){TOKEN_SHOW, strdup(buffer)};

    return (Token){TOKEN_IDENTIFIER, strdup(buffer)};
}

Token scanNumber(Lexer *lexer)
{
    char buffer[MAX_TOKEN_LENGTH];
    int length = 0;

    while (isdigit(peek(lexer)) && length < MAX_TOKEN_LENGTH - 1)
    {
        buffer[length++] = advance(lexer);
    }

    // Optional: handle decimals later if needed

    buffer[length] = '\0';
    return (Token){TOKEN_NUMBER, strdup(buffer)};
}

Token scanString(Lexer *lexer)
{
    advance(lexer); // skip opening quote
    char buffer[MAX_TOKEN_LENGTH];
    int length = 0;

    while (peek(lexer) != '"' && peek(lexer) != '\0' && length < MAX_TOKEN_LENGTH - 1)
    {
        buffer[length++] = advance(lexer);
    }

    if (peek(lexer) == '"')
    {
        advance(lexer); // skip closing quote
        buffer[length] = '\0';
        return (Token){TOKEN_STRING_LITERAL, strdup(buffer)};
    }
    else
    {
        printf("Error: Unterminated string literal\n");
        exit(1);
    }
}

Token getNextToken(Lexer *lexer)
{
    skipWhiteSpace(lexer);

    char c = peek(lexer);

    if (isalpha(c) || c == '_')
        return scanIdentifier(lexer);
    if (isdigit(c))
        return scanNumber(lexer);
    if (c == '"')
        return scanString(lexer);

    switch (c)
    {
    case '=':
        advance(lexer);
        return (Token){TOKEN_EQUAL, "="};
    case '>':
        advance(lexer);
        return (Token){TOKEN_GT, ">"};
    case '<':
        advance(lexer);
        return (Token){TOKEN_LT, "<"};
    case ';':
        advance(lexer);
        return (Token){TOKEN_SEMICOLON, ";"};
    case ':':
        advance(lexer);
        return (Token){TOKEN_COLON, ":"};
    case '+':
        advance(lexer);
        return (Token){TOKEN_PLUS, "+"};
    case '-':
        advance(lexer);
        return (Token){TOKEN_MINUS, "-"};
    case '*':
        advance(lexer);
        return (Token){TOKEN_STAR, "*"};
    case '/':
        advance(lexer);
        return (Token){TOKEN_SLASH, "/"};
    case '{':
        advance(lexer);
        return (Token){TOKEN_LBRACE, "{"};
    case '}':
        advance(lexer);
        return (Token){TOKEN_RBRACE, "}"};
    case '\0':
        return (Token){TOKEN_EOF, "EOF"};
    default:
        printf("Unexpected Character: %c\n", c);
        exit(1);
    }
}

void printTokens(char *source)
{
    Lexer lexer = init_lexer(source);
    Token token;
    do
    {
        token = getNextToken(&lexer);
        printf("Token: %d, Lexeme: %s\n", token.type, token.lexeme);
    } while (token.type != TOKEN_EOF);
}
