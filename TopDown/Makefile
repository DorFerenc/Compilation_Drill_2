CC = gcc

# Target for your college project
college: college.o lex.yy.o
	$(CC) -o college.exe college.o lex.yy.o -ll

# Compile lex.yy.c from college.lex
lex.yy.o: lex.yy.c college.h
	$(CC) -c lex.yy.c

# Compile college.c
college.o: college.c college.h 
	$(CC) -c college.c
	
# Generate lex.yy.c from college.lex
lex.yy.c: college.lex
	flex college.lex
	
clean:
	rm college.o lex.yy.o college.exe
