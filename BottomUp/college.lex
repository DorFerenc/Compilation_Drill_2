%{
#include <stdio.h>
#include <string.h>

#define COURSES 300
#define NUM 301
#define NAME 302
#define CREDITS 303
#define DEGREE 304
#define SCHOOL 305
#define ELECT 306

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
\"[^\"]+\"   { strcpy(yylval.name, yytext); return NAME; }
[0-5](\.[0-9]+)?|6 { yylval.credits = atof(yytext); return CREDITS; }
B\.Sc\.|M\.Sc\. { strcpy(yylval.degree, yytext); return DEGREE; }
Software|Electrical|Mechanical|Management|Biomedical { strcpy(yylval.school, yytext); return SCHOOL; }
Elective|elective { return ELECT; }
[\t\r ]+    { /* skip white space */ }
[\n]+       { line += yyleng; }
.           { fprintf(stderr, "***Error on line: %d, unrecognized token: %s\n", line, yytext); }

%%

int main(int argc, char **argv) {
    extern FILE *yyin;
    int token;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input file name>\n", argv[0]);
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error opening input.txt file\n");
        return 1;
    }

    printf("TOKEN\t\t\tLEXEME\t\t\tSEMANTIC VALUE\n");
    printf("---------------------------------------------------------------\n");

    while ((token = yylex()) != 0) {
        switch (token) {
            case COURSES:
                printf("COURSES\t\t\t%s\n", yytext);
                break;
            case NUM:
                printf("NUM\t\t\t%d\n", yylval.num);
                break;
            case NAME:
                printf("NAME\t\t\t%s\n", yytext);
                break;
            case CREDITS:
                printf("CREDITS\t\t\t%s\t\t\t%.1f\n", yytext, yylval.credits);
                break;
            case DEGREE:
                printf("DEGREE\t\t\t%s\n", yytext);
                break;
            case SCHOOL:
                printf("SCHOOL\t\t\t%s\n", yytext);
                break;
            case ELECT:
                printf("ELECT\t\t\t%s\n", yytext);
                break;
            default:
                fprintf(stderr, "error ...\n");
                exit(1);
        }
    }

    fclose(yyin);
    exit(0);
}
