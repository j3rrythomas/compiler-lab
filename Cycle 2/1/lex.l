%{    
    int countn=1;       
%}

%option yylineno

alpha          [a-zA-Z]
digit          [0-9]
alnum          [a-zA-Z0-9]

%%

"auto"|"break"|"case"|"char"|"continue"|"do"|"default"|"const"|"double"|"else"|"enum"|"extern"|"for"|"if"|"goto"|"float"|"int"|"long"|"register"|"return"|"signed"|"static"|"sizeof"|"short"|"struct"|"switch"|"typedef"|"union"|"void"|"while"|"volatile"|"unsigned"                      { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"KEYWORD"); }
^"#include"[ ]*<.+\.h>      { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"INCLUDE"); }
[-]?{digit}+                { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"INT_NUM"); }
[-]?{digit}+\.{digit}{1,6}  { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"FLOAT_NUM"); }
[a-zA-Z_][a-zA-Z0-9_]*      { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"IDENTIFIER"); }
"<="                        { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"RELOP_LE"); }
">="                        { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"RELOP_GE"); }
"=="                        { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"RELOP_EQ"); }
"!="                        { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"RELOP_NE"); }
">"	                    { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"RELOP_GT"); }
"<"	                    { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"RELOP_LT"); }
"&&"	                    { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"LOGOP_AND"); }
"||"	                    { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"LOGOP_OR"); }
"+"                         { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"ARMOP_+"); }
"-"                         { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"ARMOP_-"); }
"/"                         { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"ARMOP_/"); }
"*"                         { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"ARMOP_*"); }
"="                         { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"ASSIGN_OP"); }
(";"|",")                   {fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"SEPERATOR");}
"{"|"}"|"("|")"|"["|"]"     {fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"PARANTHESES");}
\/\/.*                      { ; }
\/\*(.*\n)*.*\*\/           { ; } 
[ \t]*                      { ; }
[\n]                        { countn++; }
.	                    { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"UNKNOWN"); }
["].*["]                    { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"STRING"); }
['].[']                     { fprintf(yyout,"%d <%s,%s>\n",countn,yytext,"CHARACTER"); }

%%

int yywrap() {
    fprintf(yyout,"Done");
    return 1;
}

int main(){
    FILE *fp = fopen("1.c", "r");
	if(fp) yyin = fp;
    yyout=fopen("lexop.txt","w+");
    yylex();
    return 1;
}


