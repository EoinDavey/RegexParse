test: test.cpp token.o lexer.o parser.o ast.o dfa.o
	g++ test.cpp token.o lexer.o parser.o ast.o dfa.o -o test

parser.o: parser.cpp parser.h token.o lexer.o ast.o
	g++ -c parser.cpp

token.o: token.h token.cpp
	g++ -c token.cpp

lexer.o: lexer.h lexer.cpp token.o
	g++ -c lexer.cpp

ast.o: ast.h ast.cpp
	g++ -c ast.cpp

dfa.o: dfa.h dfa.cpp ast.o
	g++ -c dfa.cpp

clean:
	rm *.o
	rm *~
	rm *.out
