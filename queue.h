#pragma once
// lang::CwC
#include "object.h"
#include "string.h"
#include <stdlib.h>

// A Queue of Objects. Supports pushing onto the front, and popping and peeking from the end.
// First in, first out.
class Queue : public Object {
public:
    Object** queue_;
    size_t allocatedSize_;
    size_t currentSize_;
    size_t headIndex_;
    size_t tailIndex_;

    Queue() : Object() {
        allocatedSize_ = 10;
        currentSize_ = 0;
        headIndex_ = 0;
        tailIndex_ = -1;
        queue_ = new Object * [allocatedSize_];
    }

    Queue(size_t size) : Object() {
        allocatedSize_ = size;
        currentSize_ = 0;
        headIndex_ = 0;
        tailIndex_ = -1;
        queue_ = new Object * [allocatedSize_];
    }

    virtual ~Queue() {
        delete[] queue_;
    }

    void move_next(size_t& index) {
        if (index == (allocatedSize_ - 1)) {
            index = 0;
        }
        else {
            index = index + 1;
        }
    }

    // Push an object onto the front of the queue.
    virtual void push_front(Object* o) {
        if (currentSize_ >= allocatedSize_) {
            printf("The queue is full and cannot push more elements\n");
            exit(1);
        }

        move_next(tailIndex_);

        queue_[tailIndex_] = o;

        currentSize_ += 1;
    }

    // Pop the last item off of the queue and return it.
    virtual Object* pop_end() {
        if (currentSize_ <= 0) {
            printf("The queue is empty and cannot pop any element\n");
            exit(1);
        }

        Object* ret = queue_[headIndex_];

        queue_[headIndex_] = nullptr;
        move_next(headIndex_);
        currentSize_ -= 1;

        return ret;
    }

    // Return the last item in the queue without removing it.
    virtual Object* peek_end() {
        if (currentSize_ <= 0) {
            printf("The queue is empty and cannot peek any element\n");
            exit(1);
        }

        return queue_[headIndex_];
    }

    // Clear out the queue.
    virtual void clear() {
        while (headIndex_ != tailIndex_) {
            queue_[headIndex_] = nullptr;
            move_next(headIndex_);
        }
        queue_[headIndex_] = nullptr;
        headIndex_ = 0;
        tailIndex_ = -1;
        currentSize_ = 0;
    }

    // Return whether this Queue is equal to the given object.
    virtual bool equals(Object* o) {
        // if not string list
        if (dynamic_cast<Queue*>(o) == nullptr)
        {
            return false;
        }

        Queue* temp = dynamic_cast<Queue*>(o);

        // validate the length
        if (currentSize_ != temp->currentSize_) {
            return false;
        }

        Object** temp_queue = temp->queue_;

        // compare each element in the list
        for (size_t i = 0; i < currentSize_; i++) {
            if (!queue_[(headIndex_+i)%allocatedSize_]->equals(temp_queue[(temp->headIndex_+1) % (temp->allocatedSize_)])) {
                return false;
            }
        }
        return true;
    }

    // A hash value for this queue.
    virtual size_t hash() {
        size_t hash = 0;

        for (size_t i = 0; i < currentSize_; i++) {
            hash += queue_[(headIndex_ + i) % allocatedSize_]->hash();
        }
        return hash;
    }

    // Return how many items are in the Queue.
    virtual size_t size() {
        return currentSize_;
    }

    // Return whether the queue is empty.
    virtual bool isEmpty() {
        return currentSize_ == 0;
    }
};

class StrQueue : public Queue {
public:

    StrQueue() : Queue() {
    }

    StrQueue(size_t size) : Queue(size) {
    }

    virtual ~StrQueue() {
        delete[] queue_;
    }

    // Push a String onto the front of the queue.
    virtual void push_front(String* s) {
        Queue::push_front(s);
    }

    virtual void push_front(Object* o) {
        if (dynamic_cast<String*>(o) == nullptr)
        {
            printf("Only push string into strqueue\n");
            exit(1);
        }
        Queue::push_front(o);
    }

    // Pop the last String off of the queue and return it.
    virtual String* pop_end() {
        return dynamic_cast<String*>(Queue::pop_end());
    }

    // Return the last String in the queue without removing it.
    virtual String* peek_end() {
        return dynamic_cast<String*>(Queue::peek_end());
    }
};