#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "college.h"

extern enum token yylex(void);
int lookahead;

struct elctiveData {
    int sum_elective_courses;
    double totalCredits;
    int arr_length;
    char * course_names_of_3e[100];
    char * school_names_of_3e[100];
};


void match(int expectedToken)
{
    if (lookahead == expectedToken)
        lookahead = yylex();
    else {
        char e[100]; /* todo: error message should mention name of token
                   (not its number) */
        sprintf(e, "error: expected token %s, found token %s",
            token_name(expectedToken), token_name(lookahead));
        errorMsg(e);
        exit(1);
    }
}

void start()
{
    match(COURSES);
    struct elctiveData eD = course_list();
    printf("There are %d elective courses", eD.sum_elective_courses);
    printf("The total number of credits of the elective courses is %.2f", eD.totalCredits);
    printf("The elective courses with 3 credits or more are:");
    printf("COURSE \t \t \t SCHOOL");
    printf("----------------------------");
    for (int i = 0; i < eD.arr_length; i++)
    {
        printf("%s \t \t \t %s", eD.course_names_of_3e[i], eD.school_names_of_3e[i]);
    }
}


void parse()
{
    lookahead = yylex();
    start();
    if (lookahead != 0) {  // 0 means EOF
        errorMsg("EOF expected");
        exit(1);
    }
}

struct electiveData course_list()
{
    struct electiveData finalED = { 0, 0.0, 0, NULL, NULL };
    while (lookahead == NUM) // while there is another couse number
    {
        struct electiveData tempED = course();
        finalED.sum_elective_courses += tempED.sum_elective_courses;
        finalED.totalCredits += tempED.totalCredits;
        finalED.arr_length += tempED.arr_length;
        finalED.course_names_of_3e[finalED.arr_length] += course_names_of_3e[tempED.arr_length]; //TODO malloc
        finalED.school_names_of_3e[finalED.arr_length] += tempED.school_names_of_3e[tempED.arr_length]; //TODO malloc
    }
    return finalED;
}

struct electiveData course()
{
    //    int sum_elective_courses;
    // double totalCredits;
    // int arr_length;
    // char * course_names_of_3e[100];
    // char * school_names_of_3e[100];
    struct electiveData insideED = { 0, 0.0, 0, NULL, NULL };

    if (lookahead == NUM)
        match(NUM);

    if (lookahead == NAME)
    {
        if (lexicalValue.is_elective == 1 && lexicalValue.credits_of_elective_courses >= 3)
            insideED.course_names_of_3e[0] = ;

    }
    

}


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
