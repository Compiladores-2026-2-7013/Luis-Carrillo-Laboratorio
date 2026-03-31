CXX?=clang++
FLEX?=flex
EXE=analyzer
CXXDEBUG= -g -Wall
CXXSTD=-std=c++14
CXXFLAGS= -Wno-deprecated-register -O0 $(CXXDEBUG) $(CXXSTD) -I.

CPPOBJ= main Parser ./AL/Lexer

FILES= $(addsuffix .cpp, $(CPPOBJ))
OBJS = $(addsuffix .o, $(CPPOBJ))

CLEANLIST = $(OBJS) $(EXE) ./AL/Lexer.cpp

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS)

./AL/Lexer.cpp: lexer.ll
	mkdir -p AL
	$(FLEX) lexer.ll
	mv Lexer.cpp AL/

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(CLEANLIST)