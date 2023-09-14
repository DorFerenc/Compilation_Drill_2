#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "college.h"

extern enum token yylex(void);
int lookahead;

// Structure for course information
struct CourseInfo {
    int num;
    char name[100];
    double credits;
    char degree[6];
    char school[100];
    char elective[10];
};

// Function to print an error message
void yyerror(const char* s) {
    fprintf(stderr, "***Error on line %d: %s\n", yylineno, s);
}

// Function to skip white space
void skipWhiteSpace() {
    int c;
    while ((c = getchar()) == ' ' || c == '\t' || c == '\r' || c == '\n') {
        if (c == '\n') {
            yylineno++;
        }
    }
    ungetc(c, stdin);
}

// Function to parse a course
struct CourseInfo parseCourse() {
    struct CourseInfo course;
    memset(&course, 0, sizeof(struct CourseInfo));

    // Parse course number
    skipWhiteSpace();
    if (yylex() == NUM) {
        course.num = lexicalValue.num;
    } else {
        yyerror("Expected course number.");
        exit(1);
    }

    // Parse course name
    skipWhiteSpace();
    if (yylex() == NAME) {
        strcpy(course.name, lexicalValue.name);
    } else {
        yyerror("Expected course name.");
        exit(1);
    }

    // Parse course credits
    skipWhiteSpace();
    if (yylex() == CREDITS) {
        course.credits = lexicalValue.credits;
    } else {
        yyerror("Expected course credits.");
        exit(1);
    }

    // Parse course degree
    skipWhiteSpace();
    if (yylex() == DEGREE) {
        strcpy(course.degree, lexicalValue.degree);
    } else {
        yyerror("Expected course degree.");
        exit(1);
    }

    // Parse course school
    skipWhiteSpace();
    if (yylex() == SCHOOL) {
        strcpy(course.school, lexicalValue.school);
    } else {
        yyerror("Expected course school.");
        exit(1);
    }

    // Parse course elective
    skipWhiteSpace();
    if (yylex() == ELECT) {
        strcpy(course.elective, yytext);
    }

    // Skip any remaining white space
    skipWhiteSpace();

    return course;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input file name>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error opening input file\n");
        return 2;
    }

    printf("TOKEN\t\t\tLEXEME\t\t\tSEMANTIC VALUE\n");
    printf("---------------------------------------------------------------\n");

    struct CourseInfo course;
    while ((lookahead = yylex()) != 0) {
        if (lookahead == COURSES) {
            course = parseCourse();
            printf("COURSES\t\t\t%s\n", course.name);
            printf("NUM\t\t\t%d\n", course.num);
            printf("NAME\t\t\t%s\n", course.name);
            printf("CREDITS\t\t\t%.1f\n", course.credits);
            printf("DEGREE\t\t\t%s\n", course.degree);
            printf("SCHOOL\t\t\t%s\n", course.school);
            if (strlen(course.elective) > 0) {
                printf("ELECT\t\t\t%s\n", course.elective);
            }
        }
    }

    fclose(yyin);
    return 0;
}
