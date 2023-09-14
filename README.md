# Compilation_Drills_2

Name: Dor Ferenc
ID:

college.c: In function ‘yyerror’:
college.c:21:50: error: ‘yylineno’ undeclared (first use in this function)
   21 |     fprintf(stderr, "***Error on line %d: %s\n", yylineno, s);
      |                                                  ^~~~~~~~
college.c:21:50: note: each undeclared identifier is reported only once for each function it appears in
college.c: In function ‘skipWhiteSpace’:
college.c:29:13: error: ‘yylineno’ undeclared (first use in this function)
   29 |             yylineno++;
      |             ^~~~~~~~
college.c: In function ‘parseCourse’:
college.c:88:33: error: ‘yytext’ undeclared (first use in this function); did you mean ‘yylex’?
   88 |         strcpy(course.elective, yytext);
      |                                 ^~~~~~
      |                                 yylex
college.c: In function ‘main’:
college.c:103:5: error: ‘yyin’ undeclared (first use in this function)
  103 |     yyin = fopen(argv[1], "r");