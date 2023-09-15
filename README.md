# Compilation_Drills_2

Name: Dor Ferenc
ID:

gcc    -c -o college.tab.o college.tab.c
college.y: In function ‘yyparse’:
college.y:84:47: error: request for member ‘name’ in something not a structure or union
   84 |             tempName = strdup($2.name); // Use strdup to allocate memory
      |                                               ^
college.y:85:66: error: request for member ‘credits_of_elective_courses’ in something not a structure or union
   85 |             tempCredits = $3.credits_of_elective_courses;
      |                                                                  ^
college.y:86:51: error: request for member ‘school’ in something not a structure or union
   86 |             tempSchool = strdup($5.school); // Use strdup to allocate memory
      |                                                   ^
make: *** [<builtin>: college.tab.o] Error 1