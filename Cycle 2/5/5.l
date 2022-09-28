%{
    #include <stdio.h>
%}

%%


[a-zA-Z_][a-zA-Z_0-9]* return id;

[0-9]+(\.[0-9]*)?      return num;

[+/*]                  return op;

.                      return yytext[0];

\n                     return 0;

%%

int main(){
    FILE *fp = fopen("sample.txt", "r");
	if(fp) yyin = fp;
    yyout=fopen("4op.txt","w+");
    yylex();
     printf("\nVowels: %d\n",countv);
    printf("Consonants: %d\n",countc);
    return 1;
}