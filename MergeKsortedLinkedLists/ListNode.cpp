#include "ListNode.h"
#include <iostream>

int ListNode::Node::get_key() const {
    return key;
}

ListNode::Node *ListNode::Node::get_next() {
    return next;
}

void ListNode::Node::set_next(Node *k) {
    next = k;
}

void ListNode::push(int key) {
    auto *p = new Node(key);
    if (first != nullptr) {
        last->set_next(p);
        last = p;
    } else {
        first = last = p;
    }
}

void ListNode::pop() {
    auto *temp = first;
    first = first->get_next();
    delete temp;
}

ListNode::Node *ListNode::head() {
    return first;
}

bool ListNode::empty() {
    if (first != nullptr)
        return false;
    return true;
}

void ListNode::print_list() {
    auto *p = first;
    while (p != nullptr) {
        std::cout << p->get_key() << " -> ";
        p = p->get_next();
    }
    std::cout << "NIL\n";
}

bool ListNode::test_sorted() {
    ListNode::Node *temp = head();
    while (temp->get_next() != nullptr) {
        if (temp->get_key() > temp->get_next()->get_key()) {
            return false;
        }
        temp = temp->get_next();
    }
    return true;
}