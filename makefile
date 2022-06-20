all: rf-lang-lexer

run: rf-lang-lexer
	./rf-lang-lexer

rf-lang-lexer: main.cpp
	g++ -std=c++11 main.cpp -o rf-lang-lexer

clean:
	rm rf-lang-lexer
