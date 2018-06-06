#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <string>
#include <memory>



template < typename Type>
struct Node{
    std::shared_ptr<Node<Type>> next;
    Type value;

};


template <typename T>
class List
{
    std::shared_ptr<Node<T>> head;
    int size;
public:

    void add(T);
    T pop(int N);
    List(){head = nullptr;}

};


template<typename T>
void List<T>::add( T value)
{
    std::shared_ptr<Node<T>> tmp(new Node<T>);
    tmp->value = value;
    tmp->next = head;
    head = tmp;
}

template<typename T>
T List<T>::pop(int N)
{
    std::shared_ptr<Node<T>> tmp(head);
    if ((head != nullptr)  ) {
        for (int i = 0; i < N; i++)
            tmp = tmp->next;
        return tmp->value;
    }

}

#endif // LIST_H
