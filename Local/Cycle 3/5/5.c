#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int retPriority(char op);
void construct3AC(char *code);

typedef struct
{
    char lhs[10];
    char rhs[10];
} codetab;

typedef struct
{
    char lhs[10];
    char rhs[10];
} threeac;

codetab codes[10] = {'\0'};
threeac ops[10] = {'\0'};
int code_ct = 0;
int ac_ct = 0;

int retPriority(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '/':
    case '*':
        return 2;
    default:
        return 0;
    }
}

void construct3AC(char *code)
{
    char op[10][10] = {'\0'}, opn[10] = {'\0'}, str[10] = {'\0'};
    int ix = 0, nix = 0;
    for (int i = 0; i <= strlen(code); i++)
    {

        if (i != strlen(code))
        {
            if (code[i] != '+' && code[i] != '-' && code[i] != '*' && code[i] != '/')
            {
                strncat(str, &code[i], 1);
            }
            else
            {
                int pr = retPriority(code[i]);
                if (pr == 0)
                {
                    printf("Invalid input\n");
                    exit(1);
                }
                strcpy(op[ix], str);
                bzero(str, sizeof(str));
                ix++;
                if (pr > retPriority(opn[strlen(opn) - 1]) || strlen(opn) == 0)
                {
                    strncat(opn, &code[i], 1);
                    nix++;
                }
                else
                {
                    // printf("%c %s %d %d %s %s %c\n", code[i], str, ix, nix, op[ix], op[ix - 1], opn[nix]);
                    char a = (char)(ac_ct + 48);
                    char rh[10] = {'\0'}, lh[10] = "t";
                    strncat(lh, &a, 1);
                    strcpy(ops[ac_ct].lhs, lh);
                    strcpy(rh, op[ix - 2]);
                    strncat(rh, &opn[nix - 1], 1);
                    strcat(rh, op[ix - 1]);
                    strcpy(op[ix - 2], lh);
                    ix = ix - 1;
                    strcpy(ops[ac_ct++].rhs, rh);
                    opn[nix - 1] = code[i];
                }
            }
        }
        else
        {
            strcpy(op[ix], str);
            bzero(str, sizeof(str));
            ix++;
            while (ix >= 2)
            {
                // printf("%c %s %d %d %s %s %c\n", code[i], str, ix, nix, op[ix], op[ix - 1], opn[nix]);
                char a = (char)(ac_ct + 48);
                char rh[10] = {'\0'}, lh[10] = "t";
                strncat(lh, &a, 1);
                strcpy(ops[ac_ct].lhs, lh);
                strcpy(rh, op[ix - 2]);
                strncat(rh, &opn[nix - 1], 1);
                strcat(rh, op[ix - 1]);
                strcpy(op[ix - 2], lh);
                ix = ix - 1;
                nix = nix - 1;
                strcpy(ops[ac_ct++].rhs, rh);
            }
        }
    }
}

void main()
{
    // printf("Enter the number of equations\n");
    // scanf("%d", &code_ct);
    printf("Enter equation\n");
    // for (int i = 0; i < code_ct; i++)
    // {
    scanf("%s = %s", codes[0].lhs, codes[0].rhs);
    // }
    construct3AC(codes[0].rhs);
    char a = (char)(ac_ct - 1 + 48);
    char rh[10] = "t";
    strcpy(ops[ac_ct].lhs, codes[0].lhs);
    strncat(rh, &a, 1);
    strcpy(ops[ac_ct++].rhs, rh);
    printf("3AC CODE\n");
    for (int i = 0; i < ac_ct; i++)
    {
        printf("%s : %s\n", ops[i].lhs, ops[i].rhs);
    }
}
