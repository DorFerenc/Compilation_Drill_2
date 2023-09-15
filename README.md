# Compilation_Drills_2

Name: Dor Ferenc
ID:

yacc  college.y 
college.y:1.1-5: warning: POSIX Yacc does not support %code [-Wyacc]
    1 | %code {
      | ^~~~~
college.y:9.1-5: warning: POSIX Yacc does not support %code [-Wyacc]
    9 | %code requires {
      | ^~~~~
college.y:64.22-27: warning: POSIX Yacc does not support %empty [-Wyacc]
   64 |         course_list: %empty
      |                      ^~~~~~
college.y:103.8-13: warning: POSIX Yacc does not support %empty [-Wyacc]
  103 |     |  %empty 
      |        ^~~~~~
mv -f y.tab.c college.c
cc    -c -o college.o college.c
cc   college.o   -o college
/usr/bin/ld: college.o: warning: relocation against `yyin' in read-only section `.text'
/usr/bin/ld: college.o: in function `yyparse':
college.c:(.text+0x363): undefined reference to `yylex'
/usr/bin/ld: college.o: in function `main':
college.c:(.text+0xd2d): undefined reference to `yyin'
/usr/bin/ld: college.c:(.text+0xd34): undefined reference to `yyin'
/usr/bin/ld: college.c:(.text+0xd75): undefined reference to `yyin'
/usr/bin/ld: college.o: in function `yyerror':
college.c:(.text+0xd9a): undefined reference to `line'
/usr/bin/ld: warning: creating DT_TEXTREL in a PIE
collect2: error: ld returned 1 exit status
make: *** [<builtin>: college] Error 1
rm college.o college.c