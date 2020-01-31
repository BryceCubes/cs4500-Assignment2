//lang::CwC
#pragma once
#include "object.h"

class Pair : public Object {
    public:

    bool isNull;
    Object* key_;
    Object* value_;

    // Empty constructor for an empty pair
    Pair() {
        isNull = true;
        key_ = new Object();
        value_ = new Object();
    }

    // Constructor with key and value
    Pair(Object *key, Object* value) {
        isNull = false;
        key_ = key;
        value_ = value;
    }

    Object *getKey() {
        return key_;
    }

    Object *getValue() {
        return value_;
    }

    bool getNull() {
        return isNull;
    }
    
};