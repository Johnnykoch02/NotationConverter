#include ".\Headers\NotationConverter.hpp"

#include <string>
#include <iostream>

int main(void) {

    NotationConverter nc = NotationConverter();
    std::cout << nc.postfixToInfix("X Y + A B + *") <<std::endl;
    std::cout << nc.infixToPrefix("( ( X + Y ) * ( A + B ) )") <<std::endl;
    
}