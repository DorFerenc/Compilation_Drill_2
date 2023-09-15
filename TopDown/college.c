#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "college.h"

extern enum token yylex(void);
int lookahead;

struct electiveData {
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
int elective();

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
    struct electiveData eD = course_list(); // TODO malloc
    printf("There are %d elective courses\n", eD.sum_elective_courses);
    printf("The total number of credits of the elective courses is %.1f\n", eD.totalCredits);
    printf("The elective courses with 3 credits or more are:\n");
    printf("COURSE \t \t \t SCHOOL\n");
    printf("----------------------------------\n");
    for (int i = 0; i <= eD.arr_length; i++)
    {
        printf("%s \t \t %s \n", eD.course_names_of_3e[i], eD.school_names_of_3e[i]);
    }
    printf("\n");
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
    struct electiveData finalED = { 0, 0.0, -1, {0}, {0} };  // Initialize arrays to 0
    while (lookahead == NUM) // while there is another couse number
    {
        struct electiveData tempED = course();
        finalED.sum_elective_courses += tempED.sum_elective_courses;
        finalED.totalCredits += tempED.totalCredits;
        finalED.arr_length += tempED.arr_length;
        if(tempED.arr_length > 0) {
            finalED.course_names_of_3e[finalED.arr_length] = tempED.course_names_of_3e[0]; //TODO malloc
            finalED.school_names_of_3e[finalED.arr_length] = tempED.school_names_of_3e[0]; //TODO malloc
        }
    }
    return finalED;
}

struct electiveData course()
{
    struct electiveData insideED = { 0, 0.0, 0, {0}, {0} };

    double tempCredits = 0.0;
    char* tempName;
    char* tempSchool;

    if (lookahead == NUM)
        match(NUM);

    if (lookahead == NAME)
    {   
        tempName = strdup(lexicalValue.name); // Use strdup to allocate memory
        match(NAME);
    }

    if (lookahead == CREDITS)
    {
        tempCredits = lexicalValue.credits_of_elective_courses;
        match(CREDITS);
    }

    if (lookahead == DEGREE)
        match(DEGREE);

    if (lookahead == SCHOOL)
    {
        tempSchool = strdup(lexicalValue.school); // Use strdup to allocate memory
        match(SCHOOL);
    }

    int e = elective();

    if (e == 1) 
    {
        insideED.sum_elective_courses = 1;
        insideED.totalCredits = tempCredits;
        if (tempCredits >= 3.0) {
            insideED.course_names_of_3e[0] = strdup(tempName);
            insideED.school_names_of_3e[0] = strdup(tempSchool);
            insideED.arr_length = 1;
        }
    }
    
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