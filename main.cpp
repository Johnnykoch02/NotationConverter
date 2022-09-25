#include ".\Headers\NotationConverter.hpp"

#include <string>
#include <iostream>

int main(void) {

    NotationConverter nc = NotationConverter();
    std::cout << nc.postfixToInfix("X Y + A B + *") <<std::endl;
    std::cout << nc.infixToPrefix("( ( X + Y ) * ( A + B ) )") <<std::endl;
    std::cout << nc.prefixToInfix("*+XY+AB") << "\n";
    std::cout << nc.infixToPostfix("( ( X + Y ) * ( A + B ) )") <<std::endl;
    std::cout << nc.prefixToPostfix("*+XY+AB") << "\n";
    std::cout << nc.postfixToPrefix("X Y + A B + *") <<std::endl;
}