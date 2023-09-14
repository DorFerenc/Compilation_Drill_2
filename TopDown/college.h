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

union _lexVal {
    int num;
    char name[100];
    double credits;
    char degree[6];
    char school[100];
};


extern union _lexVal lexicalValue;

void errorMsg(const char* s);