#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include "..\NotationConverterInterface.hpp" /* Interface */
#include ".\modules\Deque.hpp" /* Conversion */
#include <iomanip> /*String Streams*/
#include <sstream> /* More String Streams */
#include ".\modules\JohnAlgorithms.hpp" /* String Reversing */

class Token;

class NotationConverter : NotationConverterInterface {

    public:
      std::string postfixToInfix(std::string inStr);
      std::string postfixToPrefix(std::string inStr){return infixToPrefix(postfixToInfix(inStr));}
      std::string infixToPostfix(std::string inStr);
      std::string infixToPrefix(std::string inStr);
      std::string prefixToInfix(std::string inStr);
      std::string prefixToPostfix(std::string inStr){return infixToPostfix(prefixToInfix(inStr));}
      

    private:
    Deque<Token> parsePref2Inf(std::string inStr);
    Deque<Token> parsePost2Inf(std::string inStr);
    Deque<Token> parseInf2Pref(std::string inStr);
    void checkValidity(char inp);
    std::string addSpaces(std::string inStr);
};

#endif

#ifndef TOKEN_H
#define TOKEN_H

class Token {
    protected:
        std::string value;
        std::string type;
    public:
        Token() {
            this->type = "Token";
        }

        Token(std::string const& val): Token() {this->value = val;}
        Token(const Token& t): Token() {this->value = t.value;}
        Token(Token * const t): Token() {this->value = t->value;}
        std::string GetType() const {return this->type;}
        const std::string toString() const {return this->value;}
        friend std::ostream& operator<<(std::ostream& out, const Token& t) {
            out<< t.value;
            return out;
        }
};

#endif

#ifndef OPERATION_H
#define OPERATION_H

typedef enum {ADD, MULT, PAR} PRECEDENCE;

class Operation: public Token {
    private:
        PRECEDENCE pr;
    public:
      
        Operation() {
            this->type = "Token.Operation";
        }
        Operation(char val) : Operation() {
          this->value = "";this->value+=val;
          switch(val) {
            case '+':
            case '-':
                this->pr = ADD;
                break;
            case '*':
            case '/':
                this->pr = MULT;
                break;
            case ')':
            case '(':
               this->pr = PAR;
                break;
            default:
            // throw 
                break;
        }  
        
        }
        Operation(Token* const t) : Operation(t->toString()[0]) {}
        Operation(const Operation& copy): Operation() {this->value = copy.value; this->pr = copy.pr;}
        Operation(Operation * const copy): Operation() {this->value = copy->value; this->pr = copy->pr;}


        ~Operation() {}
        bool higherPrecedence(Operation that) {
            return this->pr - that.pr >= 0;
        }


        bool higherPrecedence(Operation * const that) {
            return this->pr - that->pr > 0;
        } 
};



#endif

#ifndef OPERAND_H
#define OPERAND_H


/**
 * @brief Data Storage Class for single character values
 * 
 */
// class Expression;
class Operand: public Token {
    private:

    public:
      Operand() {
        this->type = "Token.Operand";
      }
    //   Operand(const Token& t): Token(t) {}
    //   Operand(Token* const t): Token(t) {}
      Operand(std::string const& val) : Token(val) {this->type = "Token.Operand";}
      Operand (Operand* const copy): Operand() {this->value = copy->value; this->type = "Token.Operand";}
      Operand (const Operand& copy): Operand() {this->value = copy.value; this->type = "Token.Operand";}
      Operand(Token* const one, Token* const two, Operation* const op) : Operand() {
            std::stringstream str;
            str << "( " << one->toString() << " " << op->toString() << " "<< two->toString() << " )";
            this->value = str.str();
            this->type = "Token.Operand";
      }
      Operand(const Token& one, const Token& two, const Operation& op) {
            std::stringstream str;
            str << "( " << one.toString() << " " << op.toString() << " " << two.toString() << " )";
            this->value = str.str();
            this->type = "Token.Operand";
      }
    //   Operand(const Expression& t) : Token(t.toString()) {}
    //   Operand (Expression* const t) : Token(t->toString()) {}

      ~Operand() {}
    //   explicit operator Expression() {
    //     return Expression(this->toString());
    //   }
};

#endif

// #ifndef EXPRESSION_H
// #define EXPRESSION_H

// class Expression: public Operand {
//     private:
//     public:
//         Expression(const Token& t) : Operand(t) {}
//         Expression(Token* const t) : Operand(t) {}
//         Expression(const Token& one, const Token& two, const Operation& op) {
//             std::stringstream str;
//             str << "( " << one.toString() << " " << op.toString() << " " << two.toString() << " )";
//             this->value = str.str();
//         }

//         Expression(Token* const one, Token* const two, Operation* const op) {
//             std::stringstream str;
//             str << "( " << one->toString() << " " << op->toString() << " "<< two->toString() << " )";
//             this->value = str.str();
//         }
//         Expression(std::string const& val) {this->value = val;}
//         Expression (Expression* const copy) {this->value = copy->value;}
//         Expression (const Expression& copy) {this->value = copy.value;}
//         ~Expression() {}
        
//         // operator Operand() {
//         //     return Operand(this->value);
//         // }
       
//         explicit operator Operand() {
//             return Operand(this->value);
//         }
//         std::string GetType() const {
//           return "Token.Expression";
//         }
// };

// #endif


/* Considering this stuff, I was thinking of a method for performing Operations that took 2 Operands and one Operation, but that doesnt seem necessary */