#ifndef UNTITLED11_LISTNODE_H
#define UNTITLED11_LISTNODE_H

// linked list form + stack operations
class ListNode {

    // node form + basic node operations
    class Node {
        int key;
        Node *next = nullptr;
    public:
        explicit Node(int key) { this->key = key; }

        [[nodiscard]] int get_key() const;

        Node *get_next();

        void set_next(Node *k);
    };

    Node *first;
    Node *last;

public:
    ListNode() {
        first = nullptr;
        last = nullptr;
    }

    void push(int key);

    void pop();

    Node *head();

    bool empty();

    void print_list();

    // fun to test the good behaviour of the algorithm (used in demo());
    // if the result is sorted it will return "true"
    // else, the algorithm doesn't work properly, and it will return "false"
    bool test_sorted();
};

#endif //UNTITLED11_LISTNODE_H
