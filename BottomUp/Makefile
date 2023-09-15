CC = gcc

#first target is the default target
college: lex.yy.o college.tab.o
	$(CC) lex.yy.o college.tab.o -o college
	
college.tab.c college.tab.h: college.y
	bison -d college.y
	
lex.yy.c: college.lex
	flex college.lex

lex.yy.o: lex.yy.c college.tab.h
	$(CC) -c lex.yy.c
	
college.tab.o: college.tab.c college.tab.h
#	$(CC) -c exp.tab.c

# clean is a 'phony target'  (not a file)	
clean:
	rm -f college college.tab.o lex.yy.o college.tab.c college.tab.h lex.yy.c
	
	
# CC = gcc
# BISON = bison

# # Target for your college project
# college: college.tab.c lex.yy.c
# 	$(CC) -o college.exe college.tab.c lex.yy.c -ll

# # Generate college.tab.c and college.tab.h from college.y
# college.tab.c: college.y
# 	$(BISON) -d college.y

# # Compile lex.yy.c from college.lex
# lex.yy.c: college.lex
# 	flex college.lex

# clean:
# 	rm college.tab.c college.tab.h lex.yy.c college.exe

# run:
# 	./college.exe input.txt

