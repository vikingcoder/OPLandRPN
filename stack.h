#ifndef STACK_H
#define STACK_H
#include "list.h"



enum optype {power = 3, devide = 2, multiply = 2, minus = 1, plus = 1, null=0};

template <typename T>
struct stack
{
    std::shared_ptr<stack> next;
    std::shared_ptr<List<T>> ls;
    stack(){
        std::shared_ptr<List<T>> lst(new List<T>);
        ls = lst;
    }
    optype type;
};


template <typename T>
class Stack
{
    std::shared_ptr<stack<T>> head;
public:
    Stack(){}
    bool getStateHead();
    optype getOptype();
    void setOptype(optype);
    T pop();
    void puch(T);
    void puch(std::string,optype);
};

template<typename T>
optype Stack<T>::getOptype()
{
    return head->type;
}

template<typename T>
void Stack<T>::setOptype(optype type)
{
    head->type = type;
}

template <typename T>
void Stack<T>::puch(T value){
    std::shared_ptr<stack<T>> tmp(new stack<T>);
    tmp->ls->add(value);
    tmp->next = head;
    head = tmp;
}

template<typename T>
void Stack<T>::puch(std::string value, optype type)
{
    std::shared_ptr<stack<T>> tmp(new stack<T>);
    tmp->ls->add(value);
    tmp->type = type;
    tmp->next = head;
    head = tmp;
}


template <typename T>
T Stack<T>::pop()
{
    std::shared_ptr<stack<T>> tmp;
    if(head!= nullptr){
        tmp = head;
        head = tmp->next;
        return tmp->ls->pop(0);
    }
    else return "empty";
}

template<typename T>
bool Stack<T>::getStateHead(){
    if(head== NULL) return false;
    else return true;
}
#endif // STACK_H
