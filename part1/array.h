// lang::CwC

#pragma once

#include "object.h"
#include "boolean.h"
#include "integer.h"
#include "float.h"
#include "string.h"
#include <stdlib.h>

class Array : public Object {
public:
	Object** array_; //owned -> means responsible for deleting
	size_t allocatedSize_;
	size_t currentSize_;

	// constructor
	Array() : Object() {
		currentSize_ = 0;
		allocatedSize_ = 10;
		array_ = new Object*[allocatedSize_];
	}

	// constructor
	Array(size_t size) : Object() {
		currentSize_ = 0;
		allocatedSize_ = size;
		array_ = new Object * [allocatedSize_];
	}

	// deconstructor
	virtual ~Array() {
		delete[] array_;
	}

	// increase the string array size by factor of 2
	void allocate_space() {
		allocatedSize_ = allocatedSize_ * 2;
		Object** temp = array_;
		array_ = new Object * [allocatedSize_];

		for (size_t i = 0; i < currentSize_; i++) {
			array_[i] = temp[i];
		}
		delete[] temp;
	}

	// get the length of this array
	virtual size_t length() {
		return currentSize_;
	}

	// check if this array equals to other array
	virtual bool equals(Object* other) {
		// if not string list
		if (dynamic_cast<Array*>(other) == nullptr)
		{
			return false;
		}

		Array* temp = dynamic_cast<Array*>(other);

		// validate the length
		if (currentSize_ != temp->currentSize_) {
			return false;
		}

		Object** temp_array = temp->array_;

		// compare each element in the list
		for (size_t i = 0; i < currentSize_; i++) {
			if (!array_[i]->equals(temp_array[i])) {
				return false;
			}
		}
		return true;
	}

	// hash override
	virtual size_t hash() {
		size_t hash = 0;

		for (size_t i = 0; i < currentSize_; i++) {
			hash = hash + i + array_[i]->hash();
		}
		return hash;
	}

	// append two Arrays
	virtual Array* append(Array* s) {
		size_t totalSize = currentSize_ + s->currentSize_;

		Array* ret = new Array(totalSize);
		for (size_t i = 0; i < currentSize_; i++) {
			ret->add(array_[i]);
		}

		for (size_t i = 0; i < s->currentSize_; i++) {
			ret->add(s->array_[i]);
		}

		return ret;
	}

	// get the object with the index in the array
	virtual Object* get(size_t index) {
		if (index >= currentSize_) {
			printf("Index out of range\n");
			exit(1);
		}

		return array_[index];
	}

	// add the obejct to the end of the array
	virtual void add(Object* o) {
		// if run out of space
		if (currentSize_ == allocatedSize_) {
			allocate_space();
		}

		array_[currentSize_] = o;
		currentSize_ = currentSize_ + 1;
	}

	// set the element in the given index to the given object
	virtual void set(size_t index, Object* o) {
		// validate the index first
		if (index >= currentSize_) {
			printf("Invalid index is provided");
			exit(1);
		}

		array_[index] = o;
	}

	// remove the element with the given index
	virtual Object* remove(size_t index) {
		// validate the index i
		if (index >= currentSize_) {
			printf("Invalid index is provided\n");
			exit(1);
		}

		Object* removed = array_[index];

		// shift elements after index i one unit to the left
		for (size_t j = index + 1; j < currentSize_; j++) {
			array_[j - 1] = array_[j];
		}

		// set last index to nullptr
		array_[currentSize_ - 1] = nullptr;

		currentSize_ = currentSize_ - 1;
		return removed;
	}

	// get the index of the given object
	virtual size_t index_of(Object* o) {
		for (size_t i = 0; i < currentSize_; i++) {
			if (array_[i]->equals(o)) {
				return i;
			}
		}
		return -1;
	}

	// remove all elements in the array
	virtual void clear() {
		for (size_t i = 0; i < currentSize_; i++) {
			array_[i] = nullptr;
		}
		currentSize_ = 0;
	}
};

class StrArray : public Array {
public:
	// constructor
	StrArray() : Array() {}

	// constructor
	StrArray(size_t size) : Array(size) {}

	// deconstructor
	virtual ~StrArray() {}

	virtual StrArray* append(StrArray* s) {
		size_t totalSize = currentSize_ + s->currentSize_;

		StrArray* ret = new StrArray(totalSize);
		for (size_t i = 0; i < currentSize_; i++) {
			ret->add(array_[i]);
		}

		for (size_t i = 0; i < s->currentSize_; i++) {
			ret->add(s->array_[i]);
		}

		return ret;
	}

	virtual String* get(size_t index) {
		return dynamic_cast<String*>(Array::get(index));
	}

	virtual void add(Object* o) {
		if (dynamic_cast<String*>(o) == nullptr) {
			printf("Expected string is given for strarray add\n");
			exit(1);
		}
		Array::add(o);
	}

	virtual void add(const char* s) {
		String* box = new String(s);
		Array::add(box);
	}

	virtual void set(size_t index, Object* o) {
		if (dynamic_cast<String*>(o) == nullptr) {
			printf("Expected string is given for strarray set\n");
			exit(1);
		}
		Array::set(index, o);
	}

	virtual String* remove(size_t index) {
		return dynamic_cast<String*>(Array::remove(index));
	}
};

class BoolArray : public Array {
public:
	// constructor
	BoolArray() : Array() {}

	// constructor
	BoolArray(size_t size) : Array(size) {}

	// deconstructor
	virtual ~BoolArray() {}

	virtual BoolArray* append(BoolArray* s) {
		size_t totalSize = currentSize_ + s->currentSize_;

		BoolArray* ret = new BoolArray(totalSize);
		for (size_t i = 0; i < currentSize_; i++) {
			ret->add(array_[i]);
		}

		for (size_t i = 0; i < s->currentSize_; i++) {
			ret->add(s->array_[i]);
		}

		return ret;
	}

	virtual Boolean* get(size_t index) {
		return dynamic_cast<Boolean*>(Array::get(index));
	}

	virtual void add(Object* o) {
		if (dynamic_cast<Boolean*>(o) == nullptr) {
			printf("Expected bool is given for boolarray add\n");
			exit(1);
		}
		Array::add(o);
	}

	virtual void add(bool b) {
		Boolean* box = new Boolean(b);
		Array::add(box);
	}

	virtual void set(size_t index, Object* o) {
		if (dynamic_cast<Boolean*>(o) == nullptr) {
			printf("Expected bool is given for boolarray set\n");
			exit(1);
		}
		Array::set(index, o);
	}

	virtual void set(size_t index, bool b) {
		Boolean* box = new Boolean(b);
		Array::set(index, box);
	}

	virtual Boolean* remove(size_t index) {
		return dynamic_cast<Boolean*>(Array::remove(index));
	}
};

class IntArray : public Array {
public:
	// constructor
	IntArray() : Array() {}

	// constructor
	IntArray(size_t size) : Array(size) {}

	// deconstructor
	virtual ~IntArray() {}

	virtual IntArray* append(IntArray* s) {
		size_t totalSize = currentSize_ + s->currentSize_;

		IntArray* ret = new IntArray(totalSize);
		for (size_t i = 0; i < currentSize_; i++) {
			ret->add(array_[i]);
		}

		for (size_t i = 0; i < s->currentSize_; i++) {
			ret->add(s->array_[i]);
		}

		return ret;
	}

	virtual Integer* get(size_t index) {
		return dynamic_cast<Integer*>(Array::get(index));
	}

	virtual void add(Object* o) {
		if (dynamic_cast<Integer*>(o) == nullptr) {
			printf("Expected int is given for intarray add\n");
			exit(1);
		}
		Array::add(o);
	}

	virtual void add(int i) {
		Integer* box = new Integer(i);
		Array::add(box);
	}

	virtual void set(size_t index, Object* o) {
		if (dynamic_cast<Integer*>(o) == nullptr) {
			printf("Expected int is given for intarray set\n");
			exit(1);
		}
		Array::set(index, o);
	}

	virtual void set(size_t index, int i) {
		Integer* box = new Integer(i);
		Array::set(index, box);
	}

	virtual Integer* remove(size_t index) {
		return dynamic_cast<Integer*>(Array::remove(index));
	}
};

class FloatArray : public Array {
public:
	// constructor
	FloatArray() : Array() {}

	// constructor
	FloatArray(size_t size) : Array(size) {}

	// deconstructor
	virtual ~FloatArray() {}

	virtual FloatArray* append(FloatArray* s) {
		size_t totalSize = currentSize_ + s->currentSize_;

		FloatArray* ret = new FloatArray(totalSize);
		for (size_t i = 0; i < currentSize_; i++) {
			ret->add(array_[i]);
		}

		for (size_t i = 0; i < s->currentSize_; i++) {
			ret->add(s->array_[i]);
		}

		return ret;
	}

	virtual Float* get(size_t index) {
		return dynamic_cast<Float*>(Array::get(index));
	}

	virtual void add(Object* o) {
		if (dynamic_cast<Float*>(o) == nullptr) {
			printf("Expected float is given for floatarray add\n");
			exit(1);
		}
		Array::add(o);
	}

	virtual void add(float f) {
		Float* box = new Float(f);
		Array::add(box);
	}

	virtual void set(size_t index, Object* o) {
		if (dynamic_cast<Float*>(o) == nullptr) {
			printf("Expected float is given for floatarray set\n");
			exit(1);
		}
		Array::set(index, o);
	}

	virtual void set(size_t index, float f) {
		Float* box = new Float(f);
		Array::set(index, box);
	}

	virtual Float* remove(size_t index) {
		return dynamic_cast<Float*>(Array::remove(index));
	}
};