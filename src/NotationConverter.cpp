#include "..\Headers\NotationConverter.hpp"

std::string NotationConverter::postfixToInfix(std::string inStr) {
   /* Create the stream */
   Deque<Token> opStack;
   Deque<Token> tokens = this->parse(inStr);
   /* This algorithm utilizes the Null Character and Stack to append to the stream */
   while( !tokens.isEmpty() ) {
       Token* curr = tokens.popLeft();
       std::cout<< curr->GetType() <<"\n";
       /* Current Token is an Operand, push it */
       if (curr->GetType() == "Token.Operand" ) {
           opStack.pushLeft (
               curr /* Push the new Operand */
           );
       }
       else {
           /*  */
           Token* val2 = opStack.popLeft();
           Token* val1 = opStack.popLeft();   
           opStack.pushLeft(new Operand(val1, val2, (Operation*)curr) );
           delete val1;
           delete val2;
           delete curr;
       }
   }
    return opStack.popLeft()->toString();
}
/**
 * @brief 
 * 
 * @param inStr untokenized String
 * @return std::vector<Token> Parsed tokenized String
 */
Deque<Token> NotationConverter::parse(std::string inStr) {
    /*  */
    Deque<Token> returnVal;
    for (int i = 0; i< inStr.length(); i++) {
        char curr = inStr[i];
        std::string s = "";
        s += curr;
        switch(curr) {
            case '+':
            case '-':
                returnVal.pushRight(new Operation(curr, ADD));
                break;
            case '*':
            case '/':
                returnVal.pushRight(new Operation(curr, MULT));
                break;
            case ')':
            case '(':
               returnVal.pushRight(new Operation(curr, PAR));
                break;
            case ' ':
                break;
            default:
                returnVal.pushRight(new Operand(s));
                break;
        }
    }

    return returnVal;
}

