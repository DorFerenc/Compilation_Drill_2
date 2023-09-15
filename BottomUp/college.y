%code {
	#include <stdio.h>
	extern int yylex (void);
	void yyerror (const char *s);
}

%code requires {
    struct electiveData {
        int sum_elective_courses;
        double totalCredits;
        int arr_length;
        char * course_names_of_3e[100];
        char * school_names_of_3e[100];
    };
}
%union {
   struct electiveData eD;
}

%type <electiveData> course_list
%type <electiveData> course
%type <int> elective

%token COURSES
%token NUM
%token NAME
%token CREDITS
%token DEGREE
%token SCHOOL
%token ELECT


%%
	input: COURSES course_list
		{ 
            
		};
	course_list: course_list course
		{

		};
	course_list: %empty
		{

		};
	course: NUM NAME CREDITS DEGREE SCHOOL elective
		{ 

		};
	elective: ELECT | %empty;
%%

int main (int argc, char **argv)
{
	extern FILE *yyin;
	if (argc != 2) {
		fprintf (stderr, "Usage: %s <input-file-name>\n", argv[0]);
	 	return 1;
	}
	yyin = fopen (argv [1], "r");
	if (yyin == NULL) {
		fprintf (stderr, "failed to open %s\n", argv[1]);
	   	return 2;
	}

	yyparse ();

	fclose (yyin);
	return 0;
}

void yyerror (const char *s)
{
	extern int line;
	fprintf (stderr, "line %d: %s\n", line, s);
}



