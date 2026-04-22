CXX = g++
CXXDEBUG = -g -Wall
CXXSTD=-std=c++17
CXXFLAGS= -Wno-deprecated-register -O0 $(CXXSTD) $(CXXDEBUG)

EXE=compiler

CPPOBJ = Grammar ParserLL main Production Symbol
FILES=$(addsuffix .cpp, $(CPPOBJ))
OBJS=$(addsuffix .o, $(CPPOBJ))
LOBJS= lexer
SOBJS= objs
###########################################################
DIST_NAME = P2_Prog2_G2101_p11
TESTER_OBJECT = ../tester/tester.o
TEST_EXES = test_element test_stack_element
########################################################
HEADERS_TO_SUBMIT=*.h
SOURCES_TO_SUBMIT=
SUPPORT_TO_SUBMIT=*.txt Makefile

CLEANLIST= $(addsuffix .o, $(CPPOBJ)) Lexer.cpp

.PHONY: all
all: $(LOBJS) $(SOBJS) wc

objs: $(FILES)
	@echo "Checking.."
	$(CXX) $(CXXFLAGS) -c $(FILES)

wc: $(FILES)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) lexer.o



lexer: lexer.ll
	flex $<
	$(CXX) $(CXXFLAGS) -c Lexer.cpp -o lexer.o

.PHONY: clean
clean: 
		rm -rf $(CLEANLIST) lexer.o $(EXE)

.PHONY: dist
dist:
	@echo "Preparing for submission"
	rm -f $(DIST_NAME).zip
	mkdir -p $(DIST_NAME)
	pandoc --latex-engine=xelatex --template=../../pandoc.tex -o $(DIST_NAME)/memoria.pdf memoria.md
	cp $(HEADERS_TO_SUBMIT) $(SOURCES_TO_SUBMIT) $(SUPPORT_TO_SUBMIT) $(DIST_NAME)/
	zip $(DIST_NAME).zip $(DIST_NAME)/*
	rm -rf $(DIST_NAME)
	@echo "Submission is ready"
