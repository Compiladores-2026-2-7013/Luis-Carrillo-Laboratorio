#include <iostream>
#include <string>
#include <fstream>
#include "headers/Lexer.hpp"
#include "headers/ParserLL.hpp"

using namespace std;


int main(int argc, char *argv[]){
    if(argc < 2){
        cout<<"Faltan argumentos "<<endl;
        return EXIT_FAILURE;
    }
    filebuf fb;
    fb.open(string(argv[1]), ios::in);
    istream in(&fb);
    Lexer lexer(&in);
    ParserLL parser(&lexer);
    parser.parse();
    fb.close();
    return 0;
}
