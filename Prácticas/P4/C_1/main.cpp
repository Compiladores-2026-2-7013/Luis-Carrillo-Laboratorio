#include <iostream>
#include <string>
#include <fstream>
#include "Lexer.cpp"

using namespace std;

int main(int argc, char *argv[]){
    if(argc < 2){
        cout<<"Faltan argumentos "<<endl;
        return EXIT_FAILURE;
    }
    filebuf fb;
    fb.open(string(argv[1]), ios::in);
    istream in(&fb);
    
    return 0;
}
