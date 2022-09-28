%{
    #include <stdio.h>
    
%}

%%

"abc"       {fprintf(yyout,"%s","ABC");}
[.]           {fprintf(yyout,"%s",yytext);}

%%

int main(){
    FILE *fp = fopen("sample.txt", "r");
	if(fp) yyin = fp;
    yyout=fopen("3op.txt","w+");
    yylex();
    return 1;
}