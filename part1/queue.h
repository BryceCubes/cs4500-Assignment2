#pragma once
// lang::CwC
#include "object.h"
#include "string.h"
#include <stdlib.h>

// A Queue of Objects. Supports pushing onto the back, and popping and peeking from the front.
// First in, first out.
class Queue : public Object {
public:
    Object** queue_;
    size_t allocatedSize_;
    size_t currentSize_;
    size_t headIndex_;
    size_t tailIndex_;

    // set allocated size to 10 by default
    Queue() : Object() {
        allocatedSize_ = 10;
        currentSize_ = 0;
        headIndex_ = 0;
        tailIndex_ = -1;
        queue_ = new Object * [allocatedSize_];
    }

    // set allocated size to given number
    Queue(size_t size) : Object() {
        allocatedSize_ = size;
        currentSize_ = 0;
        headIndex_ = 0;
        tailIndex_ = -1;
        queue_ = new Object * [allocatedSize_];
    }

    // destructor
    virtual ~Queue() {
        delete[] queue_;
    }

    // private helper to move given index, if last index, move to first index
    void move_next(size_t& index) {
        if (index == (allocatedSize_ - 1)) {
            index = 0;
        }
        else {
            index = index + 1;
        }
    }

    // Push an object onto the end of the queue.
    virtual void push(Object* o) {
        // if the queue is full, terminate program
        if (currentSize_ >= allocatedSize_) {
            printf("The queue is full and cannot push more elements\n");
            exit(1);
        }

        // move tail index one unit to the right
        move_next(tailIndex_);

        queue_[tailIndex_] = o;

        currentSize_ += 1;
    }

    // Pop the first item off of the queue and return it.
    virtual Object* pop() {
        // if no items in the queue, terminate the program
        if (currentSize_ <= 0) {
            printf("The queue is empty and cannot pop any element\n");
            exit(1);
        }

        Object* ret = queue_[headIndex_];
        
        queue_[headIndex_] = nullptr;
        // move head index one unit to the right
        move_next(headIndex_);
        currentSize_ -= 1;

        return ret;
    }

    // Return the last item in the queue without removing it.
    virtual Object* peek() {
        // if the queue has no elements, terminate the program
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
        // make sure to clear the last element
        queue_[headIndex_] = nullptr;
        headIndex_ = 0;
        tailIndex_ = -1;
        currentSize_ = 0;
    }

    // Return whether this Queue is equal to the given object.
    virtual bool equals(Object* o) {
        // if not queue list
        if (dynamic_cast<Queue*>(o) == nullptr)
        {
            return false;
        }

        Queue* temp = dynamic_cast<Queue*>(o);

        // validate the size
        if (currentSize_ != temp->currentSize_) {
            return false;
        }

        Object** temp_queue = temp->queue_;

        // compare each element in the queue
        for (size_t i = 0; i < currentSize_; i++) {
            if (!queue_[(headIndex_+i) % allocatedSize_]->equals(temp_queue[(temp->headIndex_+i) % (temp->allocatedSize_)])) {
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

    virtual ~StrQueue() {}

    // Push a String onto the end of the queue.
    virtual void push(String* s) {
        Queue::push(s);
    }

    // Push the object onto the end of the queue.
    virtual void push(Object* o) {
        // make sure the object is string
        if (dynamic_cast<String*>(o) == nullptr)
        {
            printf("Only push string into strqueue\n");
            exit(1);
        }
        Queue::push(o);
    }

    // Pop the first String off of the queue and return it.
    virtual String* pop() {
        return dynamic_cast<String*>(Queue::pop());
    }

    // Return the first String in the queue without removing it.
    virtual String* peek() {
        return dynamic_cast<String*>(Queue::peek());
    }
};