#include <iostream>
#include <string>
#include <fstream>
#include "Lexer.cpp"

int main(int argc, char *argv[]){
    if(argc < 2){
        cout<<"Faltan argumentos "<<endl;
        return EXIT_FAILURE;
    }
    filebuf fb;
    fb.open(string(argv[1]), ios::in);
    istream in(&fb);
    
    return 0;
    /*
    calc::Lexer scanner{ std::cin, std::cerr };
    calc::Parser parser{ &scanner };
    //std::cout.precision(10);
    parser.parse();*/
}
