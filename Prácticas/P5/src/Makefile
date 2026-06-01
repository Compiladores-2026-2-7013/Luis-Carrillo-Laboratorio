# Compilador C_1 - Práctica 5: Tabla de Tipos y Tabla de Símbolos

CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Iheaders
FLEX = flex
BISON = bison

# Archivos fuente
SRCS = main.cpp TypeTab.cpp SymTab.cpp PilaTs.cpp
OBJS = main.o TypeTab.o SymTab.o PilaTs.o Parser.o Lexer.o

# Ejecutable
TARGET = comp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Generar Parser con Bison
Parser.cpp Parser.hpp: parser.yy
	$(BISON) parser.yy

# Generar Lexer con Flex (después de Parser para tener Parser.hpp)
Lexer.cpp: lexer.ll Parser.hpp
	$(FLEX) lexer.ll

# Compilar archivos objeto
main.o: main.cpp Parser.hpp headers/Lexer.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

TypeTab.o: TypeTab.cpp headers/TypeTab.hpp
	$(CXX) $(CXXFLAGS) -c TypeTab.cpp

SymTab.o: SymTab.cpp headers/SymTab.hpp
	$(CXX) $(CXXFLAGS) -c SymTab.cpp

PilaTs.o: PilaTs.cpp headers/PilaTs.hpp headers/SymTab.hpp
	$(CXX) $(CXXFLAGS) -c PilaTs.cpp

Parser.o: Parser.cpp
	$(CXX) $(CXXFLAGS) -c Parser.cpp

Lexer.o: Lexer.cpp headers/Lexer.hpp Parser.hpp
	$(CXX) $(CXXFLAGS) -c Lexer.cpp

clean:
	rm -f $(TARGET) $(OBJS) Parser.cpp Parser.hpp Lexer.cpp

.PHONY: all clean
