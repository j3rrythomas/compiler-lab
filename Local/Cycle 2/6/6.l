%{
    #include "y.tab.h"
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*    return id;

.                      return yytext[0];

\n                     return 0;

%%

int yywrap(){
    return 1;
}