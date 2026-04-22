#include "headers/Symbol.h"

Symbol::Symbol(/* args */)
{
}

Symbol::Symbol(Token token)
{
  this->type = terminal;    
  this->value.token = token;
}

Symbol::Symbol(NoTerm noTerm)
{
  this->type = nonterminal;    
  this->value.noTerm = noTerm;
}

Symbol::~Symbol()
{
}

SymType Symbol::getType()
{
  return type;
}

Token Symbol::getToken()
{
  return value.token;
}

NoTerm Symbol::getNoTerm()
{
  return value.noTerm;
}
