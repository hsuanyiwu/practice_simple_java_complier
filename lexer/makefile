a.out: main.o lex.yy.o errors.o
	gcc -g main.o lex.yy.o errors.o

errors.o: errors.c errors.h
	gcc -g -c errors.c

main.o: main.c tokens.h errors.h
	gcc -g -c main.c

lex.yy.o: lex.yy.c tokens.h
	gcc -g -c lex.yy.c

lex.yy.c: sjava.lex tokens.h
	lex sjava.lex

clean:
	rm -f a.out main.o lex.yy.o lex.yy.c errors.o
