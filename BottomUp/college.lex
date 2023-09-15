%{
#include <stdio.h>
#include <string.h>
#include "college.h"

#define COURSES 300
#define NUM 301
#define NAME 302
#define CREDITS 303
#define DEGREE 304
#define SCHOOL 305
#define ELECT 306

union _lexVal lexicalValue; // semantic value of current token

union {
    int num;
    char name[100];
    double credits;
    char degree[6];
    char school[100];
} yylval;

int line = 1;

%}

%option noyywrap
%option yylineno

%%
\<courses\>  { return COURSES; }
[0-9]{5}     { yylval.num = atoi(yytext); return NUM; }
\"[^\"]+\"   { strcpy(yylval.name, yytext); strcpy(lexicalValue.name, yytext); return NAME; }
[0-5](\.[0-9]+)?|6 { yylval.credits = atof(yytext); lexicalValue.credits_of_elective_courses = atof(yytext); return CREDITS; }
B\.Sc\.|M\.Sc\. { strcpy(yylval.degree, yytext); return DEGREE; }
Software|Electrical|Mechanical|Management|Biomedical { strcpy(yylval.school, yytext); strcpy(lexicalValue.school, yytext); return SCHOOL; }
Elective|elective { lexicalValue.is_elective = 1; return ELECT; }
[\t\r ]+    { /* skip white space */ }
[\n]+       { line += yyleng; }
.           { fprintf(stderr, "***Error on line: %d, unrecognized token: %s\n", line, yytext); }

%%
