#include "headers/Production.h"

Production::Production()
{    
}

Production::Production(int head, vector<int> body)
{
    this->head = head;
    this->body = body;
}

Production::~Production(){

}

int Production::getHead()
{
    return head;
}

vector<int> Production::getBody(){
    return body;
}
