#include <iostream>
#include <fstream>
#include "headers/Lexer.hpp"
#include "Parser.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./comp <archivo_fuente>" << std::endl;
        return EXIT_FAILURE;
    }

    std::filebuf fb;
    if (!fb.open(argv[1], std::ios::in)) {
        std::cerr << "Error: no se pudo abrir el archivo '" << argv[1] << "'" << std::endl;
        return EXIT_FAILURE;
    }

    std::istream in(&fb);
    C1::Lexer lexer(&in);
    C1::Parser parser(&lexer);

    std::cout << "Analizando archivo: " << argv[1] << std::endl;
    std::cout << "-------------------------------------------" << std::endl;

    int result = parser.parse();

    fb.close();

    if (result == 0) {
        std::cout << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
        std::cout << "Analisis completado exitosamente." << std::endl;
    } else {
        std::cout << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
        std::cout << "El analisis termino con errores." << std::endl;
    }

    return result;
}
