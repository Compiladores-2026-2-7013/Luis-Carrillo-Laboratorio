#include <iostream>
#include <string>
#include <fstream>
#include "headers/Lexer.hpp"
#include "headers/Parser.hpp"

using namespace std;
using namespace C_1;


int main(int argc, char *argv[]){
  
  if(argc < 2){
    cout<<"Faltan argumentos "<<endl;
    return EXIT_FAILURE;
  }
  
  filebuf fb;
  fb.open(string(argv[1]), ios::in);
  istream in(&fb);
  Lexer lexer(&in);
  Parser parser(&lexer);
  parser.parse();
  fb.close();
  return 0;

}
