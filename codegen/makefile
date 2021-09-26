sjc: sjc.o lex.yy.o errors.o y.tab.o AST.o ASTPrintTree.o type.o environment.o hash.o semantic.o AAT.o AATBuildTree.o AATPrintTree.o register.o label.o codegen.o
	gcc -o sjc sjc.o lex.yy.o errors.o y.tab.o AST.o ASTPrintTree.o type.o environment.o hash.o semantic.o AAT.o AATBuildTree.o AATPrintTree.o register.o label.o codegen.o


codegen.o: AAT.h register.h label.h codegen.h codegen.c
	gcc -c codegen.c


semantic.o: AST.h AAT.h AATBuildTree.h semantic.h semantic.c type.h environment1.h environment2.h register.h label.h
	gcc -c semantic.c


label.o: label.h label.c
	gcc -c label.c

register.o: register.h register.c
	gcc -c register.c

AST.o: AST.h AST.c
	gcc -c AST.c


AAT.o: AAT.h AAT.c
	gcc -c AAT.c

AATBuildTree.o: AATBuildTree.h AATBuildTree.c
	gcc -c AATBuildTree.c

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

sjc.o: sjc.c AST.h AAT.h errors.h semantic.h
	gcc -c sjc.c

lex.yy.o: lex.yy.c y.tab.h
	gcc -c lex.yy.c

y.tab.h: sjava.grm
	yacc -dv sjava.grm

y.tab.c: sjava.grm
	yacc -dv sjava.grm

lex.yy.c: sjava.lex y.tab.h
	lex sjava.lex

clean:
	rm -f a.out semantic.o lex.yy.o lex.yy.c errors.o y.tab.o AST.o ASTPrintTree.o core y.tab.o y.tab.h y.tab.c y.output AST.o type.o environment.o semantictest.o hash.o label.o sjc.o AATPrintTree.o AATBuildTree.o codegen.o AAT.o register.o
