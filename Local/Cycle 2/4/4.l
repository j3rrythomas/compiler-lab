%{
    #include <stdio.h>
    int countc=0,countv=0;
    
%}

%%

[aeiouAEIOU]       {countv++;}
[bcdfghj-np-tv-zBCDFGHJ-NP-TV-Z]           {countc++;}

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