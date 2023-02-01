// Author:      Alex Ely
// Date:        12/9/2022
// Project:     Lab 14
// Description: Node template with smart pointers

#ifndef LIST_HPP_
#define LIST_HPP_

#include <memory>

using std::shared_ptr; using std::weak_ptr; using std::make_shared;

// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class node{
public:
    node(): next_(nullptr), prev_(nullptr) {}

    // functions can be inlined
    T getData() const { return data_; }
    void setData(const T& data){ data_ = data; }

    // or can be defined outside
    shared_ptr<node<T>> getNext() const { return next_; }
    shared_ptr<node<T>> getPrev() const { return prev_; }
    void setNext(shared_ptr<node<T>> const next) { next_ = next; }
    void setPrev(shared_ptr<node<T>> const prev) { prev_ = prev; }
private:
    T data_;
    shared_ptr<node<T>> next_;
    shared_ptr<node<T>> prev_;
};

#endif // LIST_HPP_