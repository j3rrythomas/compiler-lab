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
int isSeperator(char *str);
int isComment(char *str);
int isBracket(char *str);

char *retPattern(char *str);

void main()
{
    FILE *fin, *fout;
    fin = fopen("1.c", "r");
    char ch, str[100];
    int countn = 1;
    while ((ch = fgetc(fin)) != EOF)
    {
        if (ch == ' ' || ch == '\n' || ch == '\t' || isSeperator(&ch) || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '*')
        {
            if (strlen(str) >= 1)
            {
                printf("%d: <%s,%s>\n", countn, str, retPattern(str));
            }
            if (isSeperator(&ch) || ch == '(' || ch == ')' || ch == '[' || ch == ']')
            {
                printf("%d: <%c,%s>\n", countn, ch, "SYNC");
            }
            if(ch=='*'){
                printf("%d: <%c,%s>\n", countn, ch, "OPERATOR");
            }
            memset(str, 0, sizeof(str));
            if (ch == '\n')
                countn++;
        }
        else
        {
            strncat(str, (char *)&ch, 1);
        }
    }
    // char ip;
    // while (1)
    // {
    //     printf("Enter ip\n");
    //     scanf("%c", &ip);
    //     printf("%d\n", isBracket(&ip));
    //     printf("%d\n", isSeperator(&ip));
    // }
}

char *retPattern(char *str)
{
    if (isKeyword(str))
    {
        return "KEYWORD";
    }
    if (isConstant(str))
    {
        return "CONSTANT";
    }
    if (isOperator(str))
    {
        return "OPERATOR";
    }
    if (isSeperator(str))
    {
        return "SEPERATOR";
    }
    if (isIdentifier(str))
    {
        return "IDENTIFIER";
    }
    return "OTHER";
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

int isSeperator(char *str)
{
    const char *seperators[] = {",", ";"};

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(str, seperators[i]) == 0 || strncmp(str, seperators[i], 1) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// int isComment(char *str)
// {
//     if (matchPattern(str, "^\\/\\*.*\\*\\/$"))
//     {
//         return 1;
//     }
//     return 0;
// }
int isBracket(char *str)
{
    const char *brackets[] = {"[", "]", "{", "}", "(", ")"};

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(str, brackets[i]) == 0 || strncmp(str, brackets[i], 1) == 0)
        {
            return 1;
        }
    }
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