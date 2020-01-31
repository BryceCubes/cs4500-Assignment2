//lang::CwC
#pragma once
#include "object.h"

class Pair : public Object
{
public:
    bool isNull;    // does this object not contain a key-value pair
    Object *key_;   // the key object
    Object *value_; // stored value

    // Empty constructor for an empty pair
    Pair()
    {
        isNull = true;
        key_ = new Object();
        value_ = new Object();
    }

    // Constructor with key and value
    Pair(Object *key, Object *value)
    {
        isNull = false;
        key_ = key;
        value_ = value;
    }

    // Returns the key of the pair
    Object *getKey()
    {
        return key_;
    }

    // Returns the value of the pair
    Object *getValue()
    {
        return value_;
    }

    // Returns whether the pair is "null" or not
    bool getNull()
    {
        return isNull;
    }

    // Determines whether this is equal to the given Object
    virtual bool equals(Object *that)
    {
        if (dynamic_cast<Pair *>(that) == nullptr)
        {
            return false;
        }
        Pair *temp = dynamic_cast<Pair *>(that);
        return key_->equals(temp->getKey()) && value_->equals(temp->getValue());
    }

    // Hashes the key and value to a number
    virtual size_t hash()
    {
        size_t hash = 0;
        hash += ((key_->hash() * 10) + value_->hash());
    }
};