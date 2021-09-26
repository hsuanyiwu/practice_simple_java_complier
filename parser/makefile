a.out: parsetest.o lex.yy.o errors.o y.tab.o
	gcc parsetest.o lex.yy.o errors.o y.tab.o

errors.o: errors.c errors.h
	gcc -c errors.c

y.tab.o: y.tab.h y.tab.c
	gcc -c y.tab.c

parsetest.o: parsetest.c y.tab.h errors.h
	gcc -c parsetest.c

lex.yy.o: lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.h: sjava.grm
	yacc -dv sjava.grm

y.tab.c: sjava.grm
	yacc -dv sjava.grm

lex.yy.c: sjava.lex y.tab.h
	lex sjava.lex
clean:
	rm -f a.out main.o lex.yy.o lex.yy.c errors.o core parsetest.o y.tab.o y.tab.c y.tab.h y.output
