// #include "stdio.h"
// #include "../include/lexer.h"

// int main()
// {
//     char *source = "make num x = 5 + 10;\nmake string name = \"John Doe\";\nshow x;";

//     printf("Lexing the source code:\n%s\n", source);
//     printTokens(source);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"

#define MAX_FILE_SIZE 65536

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <source.bak>\n", argv[0]);
        return 1;
    }

    // Open the source file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        perror("Failed to open source file");
        return 1;
    }

    // Read file contents into buffer
    char *source = malloc(MAX_FILE_SIZE);
    if (!source)
    {
        perror("Failed to allocate memory");
        fclose(file);
        return 1;
    }

    size_t read_size = fread(source, 1, MAX_FILE_SIZE - 1, file);
    source[read_size] = '\0'; // Null-terminate the string

    fclose(file);

    printf("Lexing the source code:\n%s\n", source);
    printTokens(source);

    free(source);
    return 0;
}
