#pragma once


// yylex returns 0 when EOF is encountered
enum token {
    COURSES = 300,
    NUM = 301,
    NAME = 302,
    CREDITS = 303,
    DEGREE = 304,
    SCHOOL = 305,
    ELECT = 306
};

char* token_name(enum token token);

union _lexVal { // what we want to extract using lex
    int is_elective;
    double credits_of_elective_courses;
    char name[100];
    char school[100];
};

void errorMsg(const char* s);
