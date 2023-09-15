%{
#include <stdio.h>
#include <string.h>
#include "college.tab.h"

int line = 1;

%}

%option noyywrap
%option yylineno

%%
\<courses\>  { return COURSES; }
[0-9]{5}     { yylval.num = atoi(yytext); return NUM; }
\"[^\"]+\"   { strcpy(yylval.name, yytext); return NAME; }
[0-5](\.[0-9]+)?|6 { yylval.credits_of_elective_courses = atof(yytext); return CREDITS; }
B\.Sc\.|M\.Sc\. { strcpy(yylval.degree, yytext); return DEGREE; }
Software|Electrical|Mechanical|Management|Biomedical { strcpy(yylval.school, yytext); return SCHOOL; }
Elective|elective { yylval.electivee = 1; return ELECT; }
[\t\r ]+    { /* skip white space */ }
[\n]+       { line += yyleng; }
.           { fprintf(stderr, "***Error on line: %d, unrecognized token: %s\n", line, yytext); }

%%
