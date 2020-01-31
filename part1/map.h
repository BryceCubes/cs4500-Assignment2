//lang::CwC
#pragma once
#include "object.h"
#include "pair.h"

// Represents a Map Object of Objects to Objects
// owns the values and does copy on puts (both key and value)
class Map : public Object
{
public:
    Pair *pairs_;     // array of pairs (owned)
    size_t size_;     // allocated space for map
    size_t elements_; // number of elements in the map

    // default constructor
    Map()
    {
        size_ = 1024;
        pairs_ = new Pair[size_];
        elements_ = 0;
        clear();
    }

    // copy constructor
    Map(Map *m)
    {
        pairs_ = m->pairs_;
        size_ = m->size_;
        elements_ = m->elements_;
    }

    // default destructor
    virtual ~Map()
    {
        delete[] pairs_;
    }

    // associates the value with the key in this map
    virtual void put(Object *key, Object *value)
    {
        Pair *addpair = new Pair(key, value); // make new pair
        if (!contains(key))
        { // check unique key
            if (!pairs_[getHash(key, size_)].getNull())
            {                     // check unique address
                rehash(*addpair); // rehash to allow both values
            }
            else
            {
                pairs_[getHash(key, size_)] = *addpair; // add new pair
                elements_++;                            // increase number of elements in Map
            }
        }
        else
        {
            pairs_[getHash(key, size_)] = *addpair; // overwrite pair
        }
    }

    // returns the value associated this key in the map
    Object *get(Object *key)
    {
        if (contains(key))
        {                                                  // check that the key exists in Map
            return pairs_[getHash(key, size_)].getValue(); // gets value at location with the given key
        }
        else
        {
            printf("No pair exists for the given key \n");
            return nullptr;
        }
    }

    // checks if the map contains a value with this key
    bool contains(Object *key)
    {
        return !pairs_[getHash(key, size_)].getNull(); // checks if there is an empty Pair at key
    }

    // returns the number of key value pairs in this map
    int size()
    {
        return elements_; // returns the number of elements in the Map
    }

    // removes the key value pair in this map
    Object *remove(Object *key)
    {
        Object *deaditem = get(key); // retrieve dead item
        Pair *nullpair = new Pair(); // create null pair
        if (deaditem != nullptr)
        {                                            // check that get returned an item
            pairs_[getHash(key, size_)] = *nullpair; // set location of item to null object
            elements_--;                             // reduce the number of elements in list
            return deaditem;                         // return the item removed
        }
        else
        {
            printf("No pair exists for the given key \n");
            return nullptr;
        }
    }

    // clears the map
    void clear()
    {
        for (int i = 0; i < size_; i++)
        {
            Pair *nullpair = new Pair(); // empty pair consuctor acting as 'null'
            pairs_[i] = *nullpair;       // set all locations equal to this and overwrite old data
        }
        elements_ = 0; // set element # back to 0
    }

    // creates a clone of this map
    Map *clone()
    {
        return new Map(this);
    }

    // returns an array of copied keys in map, not sorted
    // call size to determine the number String*
    Object **get_keys()
    {
        Object **allkeys = new Object *[elements_]; // make an array of keys
        size_t keyidx = 0;                          // counter to keep track of index in key array
        for (int i = 0; i < size_; i++)
        {
            if (!pairs_[i].getNull())
            {                                         // if the pair is not null
                allkeys[keyidx] = pairs_[i].getKey(); // get the key
                keyidx++;                             // move to next index in array of keys
            }
        }
        return allkeys; // return list of keys
    }

    // private method to rehash and expand when collision is found and add new item
    void rehash(Pair addpair)
    {
        size_t newsize = size_ * 2;         // declare what the new size of the Map will be
        Pair *newpairs = new Pair[newsize]; // create a new list of pairs of the new size
        Pair *oldpairs = pairs_;            // assign the current list of pairs
        Object **oldkeys = get_keys();      // get the list of keys for easy retrieval of Map items
        for (int i = 0; i < elements_; i++)
        {                                                  // iterate through list of keys
            size_t oldhash = getHash(oldkeys[i], size_);   // find key address in old array
            size_t newhash = getHash(oldkeys[i], newsize); // find pair address in new array
            newpairs[newhash] = pairs_[oldhash];           // sets the new location for the Pair
        }
        newpairs[getHash(addpair.getKey(), newsize)] = addpair; // add new item
        size_ = newsize;                                        // resets the size to the new size
        pairs_ = newpairs;                                      // sets to new pair list
        elements_++;                                            // incremement number of elements
        delete[] oldpairs;                                      // delete the old array of Pairs
    }

    // private method returns the hash value for the given key
    size_t getHash(Object *key, size_t mod)
    {
        return key->hash() % mod; // use the Object's hash method and mod it by given size
    }

    virtual bool equals(Object *that)
    {
        if (dynamic_cast<Map *>(that) == nullptr)
        { //check that it is map
            return false;
        }
        Map *temp = dynamic_cast<Map *>(that);

        if (size() != temp->size())
        { // check sizes first
            return false;
        }

        Object **thiskeys = get_keys(); // get keys
        Object **thatkeys = temp->get_keys();
        size_t tempsize = size(); //size for going through keys
        bool allsame = true;      // tracks if all values are equal

        for (int i = 0; i < tempsize; i++)
        {
            if (!get(thiskeys[i])->equals(get(thatkeys[i])))
            {
                allsame = false; // not equal
                break;
            }
        }
        return allsame;
    }

    virtual size_t hash()
    {
        size_t hash = 0;            // start hash counter
        Object **keys = get_keys(); // get list of keys
        for (int i = 0; i < elements_; i++)
        {
            Pair hashpair = pairs_[getHash(keys[i], size_)]; // get pair for key
            hash * 10 + hashpair.hash();                     // add hashed pair
        }
    }
};