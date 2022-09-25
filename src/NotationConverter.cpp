#include "..\Headers\NotationConverter.hpp"


std::string NotationConverter::prefixToInfix(std::string inStr) {
    /* Initialize Variables */
    Deque<Operation> opStack; /* Purposed for moving and manipulating the Tokens in Precedence */
    Deque<Token> tknStack; /* For the Operands! */
    std::string outStr = ""; /* Return String */
    Deque<Token> tokens = this->parsePref2Inf(inStr); /* This is the tokenized rep. we need for pref->inf */
    /*Algorithm will go through converting the Operands */
    while ( !tokens.isEmpty() ) {
        Token* curr = tokens.popLeft();
        //std::cout<< curr->GetType() <<"\n";
        if (curr->GetType() == "Token.Operation") {
            /*add this into the queue*/
            if( tknStack.getLength() > 1) {
                Token* val2 = tknStack.popLeft();
                Token* val1 = tknStack.popLeft();
                Operation* opPtr = new Operation(curr);
                tknStack.pushLeft(new Operand(val1, val2, opPtr) );
                delete val1;
                delete val2;
                delete opPtr;
            }
            else std::cout << "CRITICAL ERROR" <<"\n";
        }
        
        else {
            tknStack.pushLeft(curr);
        }
    }
    std::string returnString = tknStack.popLeft()->toString();
    return john_utils::reverseParentesis(john_utils::reverseString(returnString));
}

Deque<Token> NotationConverter::parsePref2Inf(std::string inStr) {
       /* Operation to reverse the following str */
    inStr = john_utils::reverseString(inStr);
    Deque<Token> returnVal;
    /* Correct the tokens in the String */
    for (int i = 0; i< inStr.length(); i++) {
        char curr = inStr[i];
        std::string s = "";
        s += curr;
        switch(curr) {
            case '+':
            case '-':
                returnVal.pushRight(new Operation(curr));
                break;
            case '*':
            case '/':
                returnVal.pushRight(new Operation(curr));
                break;
            case ')':
                returnVal.pushRight(new Operation(curr));
                break;
            case '(':
               returnVal.pushRight(new Operation(curr));
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

std::string NotationConverter::infixToPrefix(std::string inStr) {
    /* Initialize Variables */
    Deque<Operation> opStack; /* Purposed for moving and manipulating the Tokens in Precedence */
    std::string outStr = ""; /* Return String */
    Deque<Token> tokens = this->parseInf2Pref(inStr); /* This is the tokenized rep. we need for inf->pref */
    while( !tokens.isEmpty() ) {
        /* Convert to Postfix Algorithm */
        Token* curr = tokens.popLeft();
        //std::cout<< curr->GetType() <<"\n";
        if (curr->GetType() == "Token.Operation") {
            /* Peek the Stack to see if it has higher Precedence */
            Operation * optnPtr = new Operation(curr);
            delete curr;
            if (optnPtr->toString() == ")") {
                /* While we have tokens in the stack and while we are in this enviornment, */
                while( !opStack.isEmpty() && opStack.peekLeft()->toString() != "(") {
                    Operation* tknPtr = opStack.popLeft();
                    outStr += tknPtr->toString();
                    delete tknPtr;
                }
                if( !opStack.isEmpty() ) {
                   delete opStack.popLeft();
                }
            }
            
            else {
                /* Keeps Track of reinsertion of tokens */
                bool inserted = false;
                while ( !inserted ) {
                    /* Condition for Instant Push */
                    if( !opStack.isEmpty() && ( /* Ensures errors have not occured... */
                    optnPtr->higherPrecedence( opStack.peekLeft() ) || /* Either this Operand has Higher precedence, */
                    opStack.peekLeft()->toString() == "(")) { /* Or We have entered a Parentesis Enviornment  */
                        /* Directly Push Operand */
                        opStack.pushLeft(optnPtr);
                        inserted = true;
                    }
                    else if( !opStack.isEmpty() ) {
                        /* Not Higher Priority, append current operand to the Out-string  */
                        Operation* tknPtr = opStack.popLeft();
                        outStr += tknPtr->toString();
                        delete tknPtr;
                    }
                    else {
                        /* Opstack is Empty, direct push */
                        opStack.pushLeft(optnPtr);
                        inserted = true;
                    }
                }

            }
        } /* End of == "Token.Operand "*/
        else {
            outStr+=curr->toString();
            delete curr;
        }
    }
    while( !opStack.isEmpty() ) {
        Operation* tknPtr = opStack.popLeft();
        outStr += tknPtr->toString();
        delete tknPtr;
    }
    return john_utils::reverseString(outStr);
}


/**q
 * @brief Token Parser for Infix to Prefix
 * 
 * @param inStr untokenized String
 * @return Deque<Token> Parsed tokenized String for specific Operation
 */
Deque<Token> NotationConverter::parseInf2Pref(std::string inStr) {
    /* Operation to reverse the following str */
    inStr = john_utils::reverseString(inStr);
    Deque<Token> returnVal;
    /* Correct the tokens in the String */
    for (int i = 0; i< inStr.length(); i++) {
        char curr = inStr[i];
        std::string s = "";
        s += curr;
        switch(curr) {
            case '+':
            case '-':
                returnVal.pushRight(new Operation(curr));
                break;
            case '*':
            case '/':
                returnVal.pushRight(new Operation(curr));
                break;
            case ')':
                returnVal.pushRight(new Operation('('));
                break;
            case '(':
               returnVal.pushRight(new Operation(')'));
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



std::string NotationConverter::postfixToInfix(std::string inStr) {
   /* Create the stream */
   Deque<Token> opStack;
   Deque<Token> tokens = this->parsePost2Inf(inStr);
   /* This algorithm utilizes the Null Character and Stack to append to the stream */
   while( !tokens.isEmpty() ) {
       Token* curr = tokens.popLeft();
       //std::cout<< curr->GetType() <<"\n";
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
    std::string returnString = opStack.popLeft()->toString();
    return returnString;
}
/**
 * @brief Token Parser for Infix to Postfix
 * 
 * @param inStr untokenized String
 * @return Deque<Token> Parsed tokenized String for specific Operation
 */
Deque<Token> NotationConverter::parsePost2Inf(std::string inStr) {
    /*  */
    Deque<Token> returnVal;
    for (int i = 0; i< inStr.length(); i++) {
        char curr = inStr[i];
        std::string s = "";
        s += curr;
        switch(curr) {
            case '+':
            case '-':
                returnVal.pushRight(new Operation(curr));
                break;
            case '*':
            case '/':
                returnVal.pushRight(new Operation(curr));
                break;
            case ')':
            case '(':
               returnVal.pushRight(new Operation(curr));
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


std::string NotationConverter::infixToPostfix(std::string inStr) {
    /* Initialize Variables */
    Deque<Operation> opStack; /* Purposed for moving and manipulating the Tokens in Precedence */
    std::string outStr = ""; /* Return String */
    Deque<Token> tokens = this->parsePost2Inf(inStr); /* This is the tokenized rep. we need for inf->pref */
    while( !tokens.isEmpty() ) {
        /* Convert to Postfix Algorithm */
        Token* curr = tokens.popLeft();
        //std::cout<< curr->GetType() <<"\n";
        if (curr->GetType() == "Token.Operation") {
            /* Peek the Stack to see if it has higher Precedence */
            Operation * optnPtr = new Operation(curr);
            delete curr;
            if (optnPtr->toString() == ")") {
                /* While we have tokens in the stack and while we are in this enviornment, */
                while( !opStack.isEmpty() && opStack.peekLeft()->toString() != "(") {
                    Operation* tknPtr = opStack.popLeft();
                    outStr += tknPtr->toString();
                    delete tknPtr;
                }
                if( !opStack.isEmpty() ) {
                   delete opStack.popLeft();
                }
            }
            
            else {
                /* Keeps Track of reinsertion of tokens */
                bool inserted = false;
                while ( !inserted ) {
                    /* Condition for Instant Push */
                    if( !opStack.isEmpty() && ( /* Ensures errors have not occured... */
                    optnPtr->higherPrecedence( opStack.peekLeft() ) || /* Either this Operand has Higher precedence, */
                    opStack.peekLeft()->toString() == "(")) { /* Or We have entered a Parentesis Enviornment  */
                        /* Directly Push Operand */
                        opStack.pushLeft(optnPtr);
                        inserted = true;
                    }
                    else if( !opStack.isEmpty() ) {
                        /* Not Higher Priority, append current operand to the Out-string  */
                        Operation* tknPtr = opStack.popLeft();
                        outStr += tknPtr->toString();
                        delete tknPtr;
                    }
                    else {
                        /* Opstack is Empty, direct push */
                        opStack.pushLeft(optnPtr);
                        inserted = true;
                    }
                }

            }
        } /* End of == "Token.Operand "*/
        else {
            outStr+=curr->toString();
            delete curr;
        }
    }
    while( !opStack.isEmpty() ) {
        Operation* tknPtr = opStack.popLeft();
        outStr += tknPtr->toString();
        delete tknPtr;
    }
    return outStr;
}