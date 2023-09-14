#pragma once


// // yylex returns 0 when EOF is encountered
// enum token {
//     COURSES = 300,
//     NUM = 301,
//     NAME = 302,
//     CREDITS = 303,
//     DEGREE = 304,
//     SCHOOL = 305,
//     ELECT = 306
// };

// char* token_name(enum token token);

// union _lexVal {
//     int num;
//     char name[100];
//     double credits;
//     char degree[6];
//     char school[100];
// };


// extern union _lexVal lexicalValue;

// void errorMsg(const char* s);


// Define token types
#define COURSES 300
#define NUM 301
#define NAME 302
#define CREDITS 303
#define DEGREE 304
#define SCHOOL 305
#define ELECT 306

// Structure to hold semantic values
typedef struct {
    int num;
    char name[100];
    double credits;
    char degree[6];
    char school[100];
} TokenInfo;

// Function prototypes
extern int yylex();
extern int yylineno;
extern char* yytext;

void yyerror(const char* s);
int parseInput(const char* filename);