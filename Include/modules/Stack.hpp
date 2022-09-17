#ifndef STACK_H
#define STACK_H

#include "Node.hpp"

/**
 * @brief node stack template class intialization and definition
 * 
 * @tparam T 
 */


template <class T>
class Stack {
 protected:
    
    Node<T>* top;
    unsigned int length;

    void CalcList::link(Node<T>* a, Node<T>* b) {
    /*This process puts node a's next to b, and b's prev to a*/
    if(nullptr != a)/*Cannot dereference null...*/
        a->next = b;
    if(nullptr != b)
        b->prev = a;
}

 public:
    /* Initialize Stack */
    Stack() {
      this->top = nullptr;
      this->length = 0;
    }
    /* Removes Node Stack */
    ~Stack() { 
      Node<T>* stackPtr = this->top;
      Node<T>* above;
      while (nullptr != stackPtr) {
        above = stackPtr;
        stackPtr = stackPtr->prev;
        if (nullptr!= above) delete above;
      }
    }

    /**
     * @brief method to add an element to the top of the stack
     * 
     * @param data 
     */

    void push(T data) {
        T* dataPtr = new T(data);
        Node<T>* node = new Node<T>(dataPtr);
        if (!this->isEmpty()) {
          this->link(this->top, node);
        }
        if (node) {
            this->top = node;
            this->length++;
        }
    }
    /**
     * @brief Method to add an existing program element to the stack
     * 
     * @param dataPtr 
     */
    void push(T* dataPtr) {
        Node<T>* node = new Node<T>(dataPtr);
        if (!this->isEmpty()) {
          this->link(this->top, node);
        }
        if (node) {
            this->top = node;
            this->length++;
        }
    }
    
    /**
     * @brief to view the element at the top of the stack
     * Warning! This variable is meant to be used for inqiury, not for usage in a program.
     * @return Node<T>* 
     */

    T* peek() {
        return this->top->getData(); /* Could create a new here, ask Corsova*/
    }

    /**
     * @brief to remove an element from the top of the stack
     * 
     * @return Node<T>* 
     */

    T* pop() {
        T * returnData = new T(this->top->getData());
        Node<T> * old_top = this->top;
        this->top = this->top->prev;
        this->top->next = nullptr;
        length--;
        delete old_top;
        return returnData;
    }
    
    /**
     * @brief to verify whether the top fo the stack is empty
     * 
     * @return true 
     * @return false 
     */

    bool isEmpty() {
        return nullptr == this->top;
    }
    

};

#endif