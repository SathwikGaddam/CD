%{
#include <stdio.h>
%}

%%

[ \t\r\n]+                                      {}
"//".*                                          {}
"/*"([^*]|\*+[^*/])*\*+"/"                      {}

"int"|"float"|"char"|"if"|"else"|"while"|"return" { printf("KEYWORD: %s\n", yytext); }
[0-9]+"."[0-9]+                                 { printf("FLOAT: %s\n", yytext); }
[0-9]+                                          { printf("INT: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*                          { printf("ID: %s\n", yytext); }
"=="|"!="|"<="|">="|"<"|">"                     { printf("REL_OP: %s\n", yytext); }
"+"|"-"|"*"|"/"|"="                             { printf("OP: %s\n", yytext); }
"("|")"|"{"|"}"|";"|","                         { printf("DELIM: %s\n", yytext); }
.                                               { printf("ERROR: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}


// run
vi file.l
flex file.l
gcc lex.yy.c
./a.out
