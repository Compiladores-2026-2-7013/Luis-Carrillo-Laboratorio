%{
  #include <iostream>
%}

%option c++
%option noyywrap


digito [0-9]
letra [a-zA-Z]
palabra {letra}+
espacio [ \t\n]
hexadecimal [0-9a-fA-F]

%%

{espacio} { std::cout << "Encontré un espacio: " << yytext << std::endl; }
{digito}+ { std::cout << "Encontré un número: " << yytext << std::endl; }
int { std::cout << "Encontré una palabra reservada: " << yytext << std::endl; }
float { std::cout << "Encontré una palabra reservada: " << yytext << std::endl; }
if { std::cout << "Encontré una palabra reservada: " << yytext << std::endl; }
else { std::cout << "Encontré una palabra reservada: " << yytext << std::endl; }
return { std::cout << "Encontré una palabra reservada: " << yytext << std::endl; }
({letra}|"_")({letra}|{digito}|"_"){1,32} { std::cout << "Encontré un identificador: " << yytext << std::endl; }
0[xX]{hexadecimal}+ {std::cout << "Encontré un hexadecimal: " << yytext << std::endl; }
{palabra} { std::cout << "Encontré una palabra: " << yytext << std::endl; }

%%


int main() {
  FlexLexer* lexer = new yyFlexLexer;
  lexer->yylex();
}
