# CC = gcc

# #first target is the default target
# college: lex.yy.o college.tab.o
# 	$(CC) lex.yy.o college.tab.o -o college

# college.tab.c college.tab.h: college.y
# 	bison -d college.y

# lex.yy.c: college.lex
# 	flex college.lex

# lex.yy.o: lex.yy.c college.tab.h
# 	$(CC) -c lex.yy.c

# # college.tab.o: college.tab.c college.tab.h
# # 	$(CC) -c exp.tab.c

# clean:
# 	rm -f college college.tab.o lex.yy.o college.tab.c college.tab.h lex.yy.c

# run: college.exe
# 	./college.exe input.txt

objects = bisongen lex.yy.o
initiatedC = lex.yy.c college.tab.c
initiatedH = college.tab.h
exec = college.exe

college.exe: $(objects)
	gcc $(initiatedC) -o $(exec)

lex.yy.o : lex.yy.c
	gcc -c lex.yy.c
	
lex.yy.c : college.lex
	flex college.lex

bisongen:
	bison -d college.y
	
clean :
	rm $(objects) $(initiatedC) $(initiatedH) $(exec)

run: college.exe
	./college.exe input.txt