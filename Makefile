CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SRC= lexer

all: lexer_test


lexer_test: main.o Lexer.o
	$(CXX) $(CXXFLAGS) -o lexer_test main.o Lexer.o

main.o: main.cpp $(SRC)/Lexer.h $(SRC)/Token.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Lexer.o: $(SRC)/Lexer.cpp $(SRC)/Lexer.h $(SRC)/Token.h
	$(CXX) $(CXXFLAGS) -c $(SRC)/Lexer.cpp -o Lexer.o

clean:
	rm -f *.o $(SRC)/*.o lexer_test

run: lexer_test
	./lexer_test test.jura
