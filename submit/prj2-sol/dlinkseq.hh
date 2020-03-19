#ifndef DLINK_SEQ_HH_
#define DLINK_SEQ_HH_

#include "seq.hh"

#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

template <typename E> class DLinkSeqConstIter;


template <typename E>
class DLinkSeq : public Seq<E>{
    friend class DLinkSeqConstIter<E>;
    struct Node {
        E element;
        Node* prev;
        Node* next;
        Node(const E& element, Node* prev = nullptr, Node* next = nullptr): element(element), prev(prev), next(next) {
        	if (prev) prev->next = this;
        	if (next) next->prev = this;
        };
        ~Node() {
        	if (prev) prev->next = next;
        	if (next) next->prev = prev;
        }
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int count = 0;

public:
    DLinkSeq() = default;
    
    static SeqPtr<E> make() {
        return std::make_unique<DLinkSeq<E>>();
    }


    /** destructor */
    ~DLinkSeq() override {
        clear();
    } 
    
    /** clear contents from this seq, making it empty. */
    void clear() override {
        while (tail) {
            pop();
        }
    }
    
    /** add item to the start of this seq. */
    void unshift(const E& item) override {
        head = new Node(item, nullptr, head);
        if (!tail) {
            tail = head;
        }
        count++;
    }
    
    /** remove and return first item from this seq. 
     *  fails if this seq is empty.
     */
    E shift() override {
        assert(count && "shift() on empty dlist");
        auto to_delete = head;
        auto to_return = to_delete->element;
        head = head->next;
        delete to_delete;
        if (!head) {
            tail = head;
        }
        count--;
        return to_return;
    }
    
    /** add item at the end of this seq. */
    void push(const E& item) override {
        tail = new Node(item, tail);
        if (!head) {
            head = tail;
        }
        count++;
    }
    
    /** remove and return last item from this seq.
     *  fails if this seq is empty.
     */
    E pop() override {
        assert(count && "pop() on empty dlist");
        auto to_delete = tail;
        auto to_return = to_delete->element;
        tail = tail->prev;
        delete to_delete;
        if (!tail) {
            head = tail;
        }
        count--;
        return to_return;
    }
    
    /** return number of elements in this seq. */
    int size() const override { 
        return count;
    }

    /** return an iterator initialized to start of this seq */
    ConstIterPtr<E> cbegin() const override {
        return std::make_unique<DLinkSeqConstIter<E>>(head);
    }

    /** return an iterator initialized to end of this seq */
    ConstIterPtr<E> cend() const override {
        return std::make_unique<DLinkSeqConstIter<E>>(tail, true);
    }
};

template <typename E>
class DLinkSeqConstIter : public ConstIter<E> {
public:
    using NodeType = typename DLinkSeq<E>::Node;
    NodeType* curr;
    bool is_end;
    DLinkSeqConstIter(NodeType* curr, bool is_end = false): curr(curr), is_end(is_end) {}

    /** pre-increment */
    DLinkSeqConstIter& operator++() override {
        if (curr->next) {
            curr = curr->next;
            is_end = false;
        } else is_end = true;
        return *this;
    }

    /** pre-decrement */
    DLinkSeqConstIter& operator--() override {
        if (curr->prev) {
            curr = curr->prev;
            is_end = false;
        } else is_end = true;
        return *this;
    }

    // /** post-increment */
    // DLinkSeqConstIter& operator++(int) { }

    // /** post-decrement */
    // DLinkSeqConstIter& operator--(int) { }

    /** return true iff this pointer is not "NULL" */
    operator bool() override {
        if (is_end) return false;
        return curr;
    }

    /** Return element this is pointing to */
    const E& operator*() override {
        return curr->element;
    }

    /** Return pointer to element this is pointing to */
    const E* operator->() override {
        return &(curr->element);
    }
};

#endif
