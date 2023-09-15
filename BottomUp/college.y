%code {
	#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
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
   char name[100];
   double credits_of_elective_courses;
   char school[100];
   int electivee;
}

%token <name> NAME
%token <credits_of_elective_courses> CREDITS
%token <school> SCHOOL
%type <eD> course_list
%type <eD> course
%type <electivee> elective

%token COURSES
%token NUM
%token DEGREE
%token ELECT


%%
	input: COURSES course_list
		{ 
            printf("There are %d elective courses\n", $2.sum_elective_courses);
            printf("The total number of credits of the elective courses is %.1f\n", $2.totalCredits);
            printf("The elective courses with 3 credits or more are:\n");
            printf("COURSE \t \t \t SCHOOL\n");
            printf("----------------------------------\n");
            for (int i = 0; i <= $2.arr_length; i++)
            {
                printf("%s \t \t %s \n", $2.course_names_of_3e[i], $2.school_names_of_3e[i]);
            }
            printf("\n");
		};
	course_list: course_list course
		{
            $$.sum_elective_courses += $2.sum_elective_courses;
            $$.totalCredits += $2.totalCredits;
            $$.arr_length += $2.arr_length;
            if($2.arr_length > 0) 
            {
                $$.course_names_of_3e[$$.arr_length] = $2.course_names_of_3e[0];
                $$.school_names_of_3e[$$.arr_length] = $2.school_names_of_3e[0]; 
            }
		};
	course_list: %empty
		{
            $$.sum_elective_courses = 0;
            $$.totalCredits = 0.0;
            $$.arr_length = -1;
            $$.course_names_of_3e[0] = NULL;
            $$.school_names_of_3e[0] = NULL;
		};
	course: NUM NAME CREDITS DEGREE SCHOOL elective
		{ 
            $$.sum_elective_courses = 0;
            $$.totalCredits = 0.0;
            $$.arr_length = 0;
            $$.course_names_of_3e[0] = NULL;
            $$.school_names_of_3e[0] = NULL;

            if ($6 == 1) 
            {
                $$.sum_elective_courses = 1;
                $$.totalCredits = $3;
                if ($3 >= 3) {
                    $$.course_names_of_3e[0] = strdup($2);
                    $$.school_names_of_3e[0] = strdup($5);
                    $$.arr_length = 1;
                }
            }
		};
	elective: ELECT
    {
        $$ = 1;
    }
    |  %empty 
    {
        $$ = 0;
    };
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



