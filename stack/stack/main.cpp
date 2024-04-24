//
//  main.cpp
//  stack
//
//  Created by Jurabek Aminov on 07.03.2022.
//

#include <iostream>


// для начала, реализуем обычный стэк на односвязном списке (только нужные методы)
template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(): data(0), next(nullptr) {}
};

template <typename T>
class my_stack {
    Node<T>* top_ptr;
public:
    my_stack(): top_ptr(nullptr) {}
    
    void pop() {
        if (top_ptr == nullptr) {
            std::cout << "Can't pop, stack is empty";
            return;
        }
        Node<T>* tmp_ptr = top_ptr;
        top_ptr = top_ptr->next;
        delete tmp_ptr;
    }
    
    ~my_stack() {
        while (top_ptr != nullptr) {
            pop();
        }
    }
    
    T& top() {
        if (top_ptr != nullptr) {
            return top_ptr->data;
        }
        else {
            std::cout << "Stack is empty" ;
            exit(-101);
        }
    }
    
    void push(T elem) {
        Node<T>* tmp_ptr = new Node<T>;
        tmp_ptr->data = elem;
        tmp_ptr->next = top_ptr;
        top_ptr = tmp_ptr;
    }
    
    bool empty() {
        return top_ptr == nullptr;
    }
    
};




int main(int argc, const char * argv[]) {
    my_stack<int> s;
    s.push(1);
    s.pop();
    s.push(2);
    s.push(4);
    std::cout << s.top() << std::endl;
    s.top() -= 1;
    std::cout << s.top() << std::endl;
    return 0;
}
