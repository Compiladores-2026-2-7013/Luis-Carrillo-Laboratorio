TARGET = compilador

LEXER_IN = lexer.ll
LEXER_OUT = Lexer.cpp
PARSER_IN = gramatica.yy
PARSER_OUT = Parser.cpp

all: $(TARGET)

$(TARGET): $(LEXER_IN) $(PARSER_IN)
	bison -d $(PARSER_IN)
	flex++ $(LEXER_IN)
	g++ $(PARSER_OUT) $(LEXER_OUT) -o $(TARGET)

clean:
	rm -f $(LEXER_OUT) $(PARSER_OUT) Parser.hpp $(TARGET)

run: $(TARGET)
	./$(TARGET) prueba