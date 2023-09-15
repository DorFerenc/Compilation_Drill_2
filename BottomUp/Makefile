objects = college.tab.o lex.yy.o
initiatedC = lex.yy.c college.tab.c
initiatedH = college.tab.h
exec = college.exe
input = input.txt

college.exe: $(objects)
	gcc $(initiatedC) -o $(exec)

lex.yy.o : lex.yy.c
	gcc -c lex.yy.c
	
lex.yy.c : college.lex
	flex college.lex

college.tab.c college.tab.h: college.y
	bison -d college.y
	
clean :
	rm $(objects) $(initiatedC) $(initiatedH) $(exec)

run: college.exe
	./$(exec) $(input)
