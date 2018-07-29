test: test.cpp token.o lexer.o parser.o ast.o
	g++ test.cpp token.o lexer.o parser.o ast.o -o test

parser.o: parser.cpp parser.h token.o lexer.o ast.o
	g++ -c parser.cpp

token.o: token.h token.cpp
	g++ -c token.cpp

lexer.o: lexer.h lexer.cpp token.o
	g++ -c lexer.cpp

ast.o: ast.h ast.cpp
	g++ -c ast.cpp

clean:
	rm *.o
	rm *~
	rm *.out