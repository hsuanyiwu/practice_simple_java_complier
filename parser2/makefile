a.out: parsetest2.o lex.yy.o errors.o y.tab.o AST.o ASTPrintTree.o
	gcc parsetest2.o lex.yy.o errors.o y.tab.o AST.o ASTPrintTree.o

AST.o: AST.h AST.c
	gcc -c AST.c

ASTPrintTree.o: ASTPrintTree.c ASTPrintTree.h
	gcc -c ASTPrintTree.c

errors.o: ..\errors.c ..\errors.h
	gcc -c ..\errors.c

y.tab.o: y.tab.h y.tab.c
	gcc -c y.tab.c

parsetest2.o: parsetest2.c y.tab.h AST.h ..\errors.h
	gcc -c parsetest2.c

lex.yy.o: lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.h: sjava.grm
	yacc -ydv sjava.grm

y.tab.c: sjava.grm
	yacc -ydv sjava.grm

lex.yy.c: sjava.lex y.tab.h
	lex sjava.lex

clean:
	rm -f a.out parsetest2.o lex.yy.o lex.yy.c errors.o y.tab.o AST.o ASTPrintTree.o core y.tab.o y.tab.h y.tab.c y.output
