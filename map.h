//lang::CwC
#pragma once
#include "object.h"
#include "pair.h"

// Represents a Map object of Objects to Objects
// owns the values and does copy on puts (both key and value)
class Map : public Object {
    public:
    Pair* pairs_; // array of pairs 
    size_t size_; // allocated space for map
    size_t elements_; // number of elements in the map

        // private constructor just for making newly sized maps
        Map(size_t space) {
            size_ = space;
            pairs_ = new Pair[size_];
            elements_ = 0;
        }

        // default constructor
        Map(){
            Map(1024);
        }

        // copy constructor
        Map(Map* m){
            size_t newsize = 1024;
            //Make sure we can fit all the elements from the given Map
            while(newsize < m->size_) {
                size_ *= 2;
            }

            // Make a new map of required size
            Map(newsize);

            // Copy elements from given map
            // TODO: this may become a helper method later
            for(size_t i = 0; i <= m->elements_; i++) {
                pairs_[i] = m->pairs_[i];
                elements_ ++;
            }

        }

        // default destructor
        virtual ~Map(){
            delete[] pairs_;
        }

        // associates the value with the key in this map
        virtual void put(Object *key, Object *value) {
            Pair *addpair = new Pair(key, value);
            pairs_[elements_] = *addpair;
        }

        // returns the value associated this key in the map
        Object* get(Object* key);

        // checks if the map contains a value with this key
        bool contains(Object* key);

        // returns the number of key value pairs in this map
        int size();

        // removes the key value pair in this map
        Object* remove(Object* key);

        // clears the map
        void clear();

        // creates a clone of this map
        Map* clone();

        // returns an array of copied keys in map, not sorted
        // call size to determine the number String*
        Object** get_keys();

};