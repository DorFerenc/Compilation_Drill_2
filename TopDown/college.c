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

extern union _lexVal lexicalValue;

void match(int expectedToken);
void start();
void parse();
struct electiveData course_list();
struct electiveData course();

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
    struct elctiveData eD = course_list(); // TODO malloc
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
    struct electiveData insideED = { 0, 0.0, 0, NULL, NULL };

    if (lookahead == NUM)
        match(NUM);

    if (lookahead == NAME)
    {
        if (lexicalValue.is_elective == 1 && lexicalValue.credits_of_elective_courses >= 3)
            insideED.course_names_of_3e[0] = lexicalValue.name; //TODO malloc
        match(NAME);
    }

    if (lookahead == CREDITS)
    {
        if (lexicalValue.is_elective == 1)
            insideED.totalCredits += lexicalValue.credits_of_elective_courses;
        match(CREDITS);
    }

    if (lookahead == DEGREE)
        match(DEGREE);

    if (lookahead == SCHOOL)
    {
        if (lexicalValue.is_elective == 1 && lexicalValue.credits_of_elective_courses >= 3)
            insideED.school_names_of_3e[0] = lexicalValue.school; //TODO malloc
        match(SCHOOL);
    }

    int e = elective();
    
    return insideED;
}

int elective() {
    if (lookahead == ELECT)
    {
        match(ELECT);
        return 1;
    }
    return 0;
}


int main(int argc, char** argv)
{
    extern FILE* yyin;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file-name>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        fprintf(stderr, "failed to open %s\n", argv[1]);
        return 2;
    }

    parse();

    fclose(yyin);
    return 0;
}

void errorMsg(const char* s)
{
    extern int yylineno;
    fprintf(stderr, "line %d: %s\n", yylineno, s);
}