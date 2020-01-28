//lang::CwC
#pragma once
#include "object.h"

class Pair : public Object {
    public:

    Object* key_;
    Object* value_;

    // Empty constructor for an empty pair
    Pair() {
        key_ = new Object();
        value_ = new Object();
    }

    // Constructor with key and value
    Pair(Object *key, Object* value) {
        key_ = key;
        value_ = value;
    }
};