%{
    #include <stdio.h>
    int countl=1,countw=0,countc=0;
%}

%option yylineno

%%

[\n]                        { countl++;countw++; }
[ ][ ]*                     {countw++;}
.                           {countc++;}

%%

int main(){
    FILE* fin;
    fin=fopen("sample.txt","r");
    yyin=fin;
    yylex();
    printf("\nLines: %d\n",countl);
    printf("Words: %d\n",countw);
    printf("Characters: %d\n",countc);

}