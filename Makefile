CXXFLAGS = -std=c++17 -Wall -Wextra -O2
CFLAGS = -std=c99 -Wall -Wextra -O2

LEXER_SRC = lexer/Lexer.cpp
PARSER_SRC = parser/bridge.cpp grammar.tab.o


all: run_lex run_pars


# Lexer 

run_lex: main_lex.o Lexer.o
	g++ $(CXXFLAGS) -o run_lex main_lex.o Lexer.o

main_lex.o: main_lex.cpp lexer/Lexer.h lexer/Token.h
	g++ $(CXXFLAGS) -c main_lex.cpp -o main_lex.o

Lexer.o: lexer/Lexer.cpp lexer/Lexer.h lexer/Token.h
	g++ $(CXXFLAGS) -c lexer/Lexer.cpp -o Lexer.o


# Parser 


run_pars: main_pars.o bridge.o Lexer.o grammar.tab.o
	g++ $(CXXFLAGS) -o run_pars main_pars.o bridge.o Lexer.o grammar.tab.o

main_pars.o: main_pars.cpp lexer/Lexer.h lexer/Token.h parser/grammar.tab.h
	g++ $(CXXFLAGS) -c main_pars.cpp -o main_pars.o

bridge.o: parser/bridge.cpp parser/grammar.tab.h lexer/Lexer.h lexer/Token.h
	g++ $(CXXFLAGS) -c parser/bridge.cpp -o bridge.o

grammar.tab.o: parser/grammar.tab.c parser/grammar.tab.h
	gcc $(CFLAGS) -c parser/grammar.tab.c -o grammar.tab.o

# Génération automatique du parser si grammar.y change
parser/grammar.tab.c parser/grammar.tab.h: parser/grammar.y
	bison -d -o parser/grammar.tab.c parser/grammar.y


# Nettoyage
clean:
	rm -f *.o lexer.o bridge.o grammar.tab.o run_lex run_pars parser/grammar.tab.*
