a.out: semantictest.o lex.yy.o errors.o y.tab.o AST.o ASTPrintTree.o type.o environment.o hash.o semantic.o
	gcc semantictest.o lex.yy.o errors.o y.tab.o AST.o ASTPrintTree.o type.o environment.o hash.o semantic.o

semantic.o: AST.h semantic.h semantic.c type.h environment1.h environment2.h
	gcc -c semantic.c

AST.o: AST.h AST.c
	gcc -c AST.c

hash.o: hash.h hash.c
	gcc -c hash.c

environment.o: environment.c environment1.h environment2.h
	gcc -c environment.c

type.o: type.h environment1.h type.c
	gcc -c type.c

ASTPrintTree.o: ASTPrintTree.c ASTPrintTree.h AST.h
	gcc -c ASTPrintTree.c

errors.o: errors.c errors.h
	gcc -c errors.c

y.tab.o: y.tab.h y.tab.c
	gcc -c y.tab.c

semantictest.o: semantictest.c y.tab.h AST.h errors.h semantic.h
	gcc -c semantictest.c

lex.yy.o: lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.h: sjava.grm
	yacc -dv sjava.grm

y.tab.c: sjava.grm
	yacc -dv sjava.grm

lex.yy.c: sjava.lex y.tab.h
	lex sjava.lex

clean:
	rm -f a.out semantic.o lex.yy.o lex.yy.c errors.o y.tab.o AST.o ASTPrintTree.o core y.tab.o y.tab.h y.tab.c y.output AST.o type.o environment.o semantictest.o hash.o
