TARGET = compiler

LEXER_IN = lexer.ll
LEXER_OUT = Lexer.cpp
MAIN_SRC = main.cpp

all: $(TARGET)

$(TARGET): $(LEXER_IN) $(MAIN_SRC)
	flex++ $(LEXER_IN)
	g++ $(LEXER_OUT) $(MAIN_SRC) -o $(TARGET)

clean:
	rm -f $(LEXER_OUT) $(TARGET)

run: $(TARGET)
	./$(TARGET) prueba