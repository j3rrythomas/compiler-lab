#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int matchPattern(char *str, char *pattern);
int isIdentifier(char *str);
int isKeyword(char *str);
int isOperator(char *str);
int isConstant(char *str);
int isNumber(char *str);
int isLiteral(char *str);

void main()
{
    char ip[100];
    while (1)
    {
        printf("Enter ip\n");
        scanf("%s", ip);
        if (isConstant(ip) == 1)
        {
            printf("Matched\n");
        }
        else
        {
            printf("Not Matched\n");
        }
    }
}

int isIdentifier(char *str)
{
    // \\[[0-9]*\\]
    if (matchPattern(str, "^[a-zA-Z_][a-zA-Z0-9_]*$") == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isKeyword(char *str)
{
    const char *keywords[] = {
        "auto",
        "break",
        "case",
        "char",
        "continue",
        "do",
        "default",
        "const",
        "double",
        "else",
        "enum",
        "extern",
        "for",
        "if",
        "goto",
        "float",
        "int",
        "long",
        "register",
        "return",
        "signed",
        "static",
        "sizeof",
        "short",
        "struct",
        "switch",
        "typedef",
        "union",
        "void",
        "while",
        "volatile",
        "unsigned"};

    for (int i = 0; i < 32; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int isOperator(char *str)
{
    const char *arop[] = {"+", "-", "*", "/", "%"};
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(str, arop[i]) == 0)
        {
            return 1;
        }
    }
    const char *asnop[] = {"=",
                           "+=",
                           "-=",
                           "*=",
                           "/=",
                           "%=",
                           ">>=",
                           "<<=",
                           "&=",
                           "^=",
                           "|="};
    for (int i = 0; i < 11; i++)
    {
        if (strcmp(str, asnop[i]) == 0)
        {
            return 1;
        }
    }
    const char *logop[] = {"&",
                           "|",
                           "^",
                           "&&",
                           "||"};
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(str, logop[i]) == 0)
        {
            return 1;
        }
    }
    const char *relop[] = {">", "<", ">=", "<=", "==", "!="};
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(str, relop[i]) == 0)
        {
            return 1;
        }
    }
    const char *unaryop[] = {"++", "--", "&"};
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(str, unaryop[i]) == 0)
        {
            return 1;
        }
    }
    const char *shiftop[] = {">>", "<<"};
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(str, shiftop[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int isConstant(char *str)
{
    if (isLiteral(str) || isNumber(str))
        return 1;
    return 0;
}

int isNumber(char *str)
{
    // \\.[0-9][0-9]*[E[+|-|][0-9][0-9]*|]
    if (matchPattern(str, "^[+|-][0-9][0-9]*$"))
        return 1;
    if (matchPattern(str, "^[0-9][0-9]*$"))
        return 1;
    if (matchPattern(str, "^[+|-][0-9][0-9]*.[0-9][0-9]*$"))
        return 1;
    if (matchPattern(str, "^[0-9]*.[0-9][0-9]*$"))
        return 1;
    if (matchPattern(str, "^[+|-][0-9][0-9]*.[0-9][0-9]*E[0-9][0-9]*$"))
        return 1;
    if (matchPattern(str, "^[0-9][0-9]*.[0-9][0-9]*E[0-9][0-9]*$"))
        return 1;
    return 0;
}

int isLiteral(char *str)
{
    if (matchPattern(str, "^\"[^\"]*\"$"))
        return 1;
    if (matchPattern(str, "^\'[^\']*\'$"))
        return 1;
    return 0;
}

int matchPattern(char *str, char *pattern)
{
    regex_t regex;
    if (regcomp(&regex, pattern, 0) != 0)
    {
        printf("Regex compilation failed\n");
        exit(1);
    };

    if (regexec(&regex, str, 0, NULL, 0) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}