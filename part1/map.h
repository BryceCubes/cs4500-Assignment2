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
            size_ = 1024;
            pairs_ = new Pair[size_];
            elements_ = 0;
            clear();
            printf("finished constructor \n");
        }

        // copy constructor
        Map(Map* m){
            pairs_ = m->pairs_;
            size_ = m->size_;
            elements_ = m->elements_;
        }
        
        // private constructor just for making newly sized maps
        Map(size_t space) {
            size_ = space;
            pairs_ = new Pair[size_];
            elements_ = 0;
            clear();
            printf("finished constructor \n");
        }

        // default destructor
        virtual ~Map(){
            delete[] pairs_;
        }

        // associates the value with the key in this map
        virtual void put(Object *key, Object *value) {
            Pair *addpair = new Pair(key, value); // make new pair
            printf("made pair \n");
            if(!contains(key)) { // check unique address
            printf("checked contains \n");
                pairs_[getHash(key, size_)] = *addpair; // insert new pair
                elements_++; // increase number of elements in Map
            } else {
                rehash(*addpair); // rehash if key address not unique
            }
            printf("finished put \n");
        }

        // returns the value associated this key in the map
        Object* get(Object* key) {
            if(contains(key)) { // check that the key exists in Map
                return pairs_[key->hash() % size_].getValue(); // gets value at location with the given key
            } else {
                printf("Object key does not exist in map");
                exit(1);
            }
            printf("finished get \n");
        }

        // checks if the map contains a value with this key
        bool contains(Object* key) {
            return !pairs_[getHash(key, size_)].getNull(); // checks if there is an empty Pair at key
            printf("finished contains \n");
        }

        // returns the number of key value pairs in this map
        int size() {
            return elements_; // returns the number of elements in the Map
            printf("finished size \n");
        }

        // removes the key value pair in this map
        Object* remove(Object* key) {
            Object *deaditem = &pairs_[getHash(key, size_)]; // retrieve the dead item
            if(contains(key)) { // check the key exists in the map
                Pair *nullpair = new Pair(); // make a null Pair to replace item
                pairs_[getHash(key, size_)] = *nullpair; //set space to null Pair
                elements_--; // decrease number of elements
                printf("before remove \n");
                return deaditem; // return the item at this location
            } else {
                printf("Object does not exist in Map");
                return nullptr;
            }
        }

        // clears the map
        void clear() {
            for(int i = 0; i < size_; i++) {
                Pair *nullpair = new Pair(); // empty pair consuctor acting as 'null'
                pairs_[i] = *nullpair; // set all locations equal to this and overwrite old data
            }
            elements_ = 0; // set element # back to 0
            printf("finished clear \n");
        }

        // creates a clone of this map
        Map* clone() {
            return new Map(this); //TODO: does this work???
            printf("finished clone \n");
        }

        // returns an array of copied keys in map, not sorted
        // call size to determine the number String*
        Object** get_keys() {
            Object** allkeys = new Object*[elements_]; // make an array of keys
            size_t keyidx = 0; // counter to keep track of index in array of keys
            for(int i = 0; i < size_; i++) {
                if(!pairs_[i].getNull()) { // if the pair is not null
                    allkeys[keyidx] = pairs_[i].getKey(); // get the key
                    keyidx ++; // move to next index in array of keys
                }
            }
            return allkeys; // return list of keys
            printf("finished getkeys \n");
        }

        // private method to rehash and expand when collision is found and add new item
        void rehash(Pair addpair) {
            size_t newsize = size_ * 2; // declare what the new size of the Map will be
            Pair *newpairs = new Pair[newsize]; // create a new list of pairs of the new size
            Pair *oldpairs = pairs_; // assign the current list of pairs
            Object **oldkeys = get_keys(); // get the list of keys for easy retrieval of Map items
            for(int i = 0; i < elements_; i++) { // iterate through list of keys
                size_t oldhash = getHash(oldkeys[i], size_); // find address of this key in the old array
                size_t newhash = getHash(oldkeys[i], newsize); // find new address for pair in new array
                newpairs[newhash] = pairs_[oldhash]; // sets the new location for the Pair
            }
            newpairs[getHash(addpair.getKey(), newsize)] = addpair; // add the item that could not fit TODO: check getKey()
            size_ = newsize; // resets the size to the new size
            pairs_ = newpairs; // sets the list of pairs to the new list
            elements_++; // incremement number of elements with new item added
            delete[] oldpairs; // delete the old array of Pairs
            printf("finished rehash \n");
        }

        // private method returns the hash value for the given key
        size_t getHash(Object* key, size_t mod) {
            printf("before hash \n");
            return key->hash() % mod; // use the Object's hash method and mod it by given size
        }
};