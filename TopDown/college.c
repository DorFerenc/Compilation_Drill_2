#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "college.h"

TokenInfo yylval; // Global variable to store semantic values
int line = 1;     // Global variable to track the line number

// Function to print an error message
void yyerror(const char* s) {
    fprintf(stderr, "***Error on line %d: %s\n", yylineno, s);
}

// Function to skip white space
void skipWhiteSpace() {
    int c;
    while ((c = getchar()) == ' ' || c == '\t' || c == '\r' || c == '\n') {
        if (c == '\n') {
            line++;
        }
    }
    ungetc(c, stdin);
}

// Function to parse a course
void parseCourse() {
    printf("COURSES\t\t\t%s\n", yytext);

    // Parse course number
    skipWhiteSpace();
    if (yylex() == NUM) {
        printf("NUM\t\t\t%d\n", yylval.num);
    } else {
        yyerror("Expected course number.");
        exit(1);
    }

    // Parse course name
    skipWhiteSpace();
    if (yylex() == NAME) {
        printf("NAME\t\t\t%s\n", yylval.name);
    } else {
        yyerror("Expected course name.");
        exit(1);
    }

    // Parse course credits
    skipWhiteSpace();
    if (yylex() == CREDITS) {
        printf("CREDITS\t\t\t%.1f\n", yylval.credits);
    } else {
        yyerror("Expected course credits.");
        exit(1);
    }

    // Parse course degree
    skipWhiteSpace();
    if (yylex() == DEGREE) {
        printf("DEGREE\t\t\t%s\n", yylval.degree);
    } else {
        yyerror("Expected course degree.");
        exit(1);
    }

    // Parse course school
    skipWhiteSpace();
    if (yylex() == SCHOOL) {
        printf("SCHOOL\t\t\t%s\n", yylval.school);
    } else {
        yyerror("Expected course school.");
        exit(1);
    }

    // Parse course elective
    skipWhiteSpace();
    if (yylex() == ELECT) {
        printf("ELECT\t\t\t%s\n", yytext);
    }

    // Skip any remaining white space
    skipWhiteSpace();
}

// Function to parse a list of courses
void parseCourseList() {
    while (1) {
        skipWhiteSpace();
        int token = yylex();
        if (token == COURSES) {
            parseCourse();
        } else {
            break; // End of course list
        }
    }
}

// Function to parse the input
int parseInput(const char* filename) {
    extern FILE* yyin;
    yyin = fopen(filename, "r");
    if (!yyin) {
        fprintf(stderr, "Error opening input file\n");
        return 1;
    }

    printf("TOKEN\t\t\tLEXEME\t\t\tSEMANTIC VALUE\n");
    printf("---------------------------------------------------------------\n");

    parseCourseList();

    fclose(yyin);
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input file name>\n", argv[0]);
        return 1;
    }

    if (parseInput(argv[1]) == 0) {
        printf("Parsing completed successfully.\n");
        return 0;
    } else {
        fprintf(stderr, "Parsing failed.\n");
        return 1;
    }
}
