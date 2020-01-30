//lang::CwC
#pragma once
#include "object.h"
#include "pair.h"

// Represents a Map object of Objects to Objects
// owns the values and does copy on puts (both key and value)
class Map : public Object {
    public:
    Pair* pairs_; // array of pairs (owned)
    size_t size_; // allocated space for map
    size_t elements_; // number of elements in the map


        // default constructor
        Map(){
            Map(1024);
        }

        // copy constructor
        Map(Map* m){
            pairs_ = m->pairs_;
            size_ = m->size_;
            elements_ = m->elements_;
            clear();
        }
        
        // private constructor just for making newly sized maps
        Map(size_t space) {
            size_ = space;
            pairs_ = new Pair[size_];
            elements_ = 0;
            clear();
        }

        // default destructor
        virtual ~Map(){
            delete[] pairs_;
        }

        // associates the value with the key in this map
        virtual void put(Object *key, Object *value) {
            Pair *addpair = new Pair(key, value); // make new pair
            if(!contains(key)) { // check unique address
                pairs_[getHash(key, size_)] = *addpair; // insert new pair
                elements_++; // increase number of elements in Map
            } else {
                rehash(*addpair); // rehash if key address not unique
            }
        }

        // returns the value associated this key in the map
        Object* get(Object* key) {
            if(contains(key)) { // check that the key exists in Map
                return pairs_[key->hash() % size_].getValue(); // gets value at location with the given key
            } else {
                printf("Object key does not exist in map");
                exit(1);
            }
        }

        // checks if the map contains a value with this key
        bool contains(Object* key) {
            return !pairs_[getHash(key, size_)].getNull(); // checks if there is an empty Pair at key
        }

        // returns the number of key value pairs in this map
        int size() {
            return elements_; // returns the number of elements in the Map
        }

        // removes the key value pair in this map
        Object* remove(Object* key) {
            Object *deaditem = pairs_ + getHash(key, size_); // retrieve the dead item
            if(contains(key)) { // check the key exists in the map
                Pair *nullpair = new Pair(); // make a null Pair to replace item
                pairs_[getHash(key, size_)] = *nullpair; //set space to null Pair
                elements_--; // decrease number of elements
                return deaditem; // return the item at this location
            } else {
                printf("Object key does not exist in map");
                exit(1);
            }
        }

        // clears the map
        void clear() {
            for(int i = 0; i < size_; i++) {
                Pair *nullpair = new Pair();
                pairs_[i] = *nullpair;
            }
        }

        // creates a clone of this map
        Map* clone() {
            return new Map(this); //TODO: does this work???
        }

        // returns an array of copied keys in map, not sorted
        // call size to determine the number String*
        Object** get_keys() {
            Object** allkeys = new Object*[elements_];
            size_t counter = 0;
            for(int i = 0; i < size_; i++) {
                if(!pairs_[i].getNull()) {
                    allkeys[counter] = pairs_[i].getKey();
                }
            }
            return allkeys;
        }

        // private method to rehash and expand when collision is found and add new item
        void rehash(Pair addpair) {
            size_t newsize = size_ * 2;
            Pair *newpairs = new Pair[newsize];
            Object **oldkeys = get_keys();
            for(int i = 0; i < elements_; i++) {
                size_t newhash = getHash(oldkeys[i], newsize);
                //TODO: finish this
            }
        }

        // returns the hash value for the given key
        size_t getHash(Object* key, size_t mod) {
            return key->hash() % mod;
        }
};