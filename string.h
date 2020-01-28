//lang::CwC
#pragma once
#include "object.h"
#include <string.h>
#include <ctype.h>

class String : public Object {
public:
	const char* value_;
	size_t length_;

	// Default constructor
	String() : Object() {
		length_ = 0;
		value_ = "";
	}

	String(const char* value) : Object() {
		length_ = strlen(value);
		value_ = value;
	}

	// Destructor
	virtual ~String() {}

	virtual bool equals(Object* that) {
		// if given object is a string
		if (dynamic_cast<String*>(that) == nullptr)
		{
			return false;
		}

		return strcmp(value_, dynamic_cast<String*>(that)->value_) == 0;
	}

	virtual size_t hash() {
		size_t hash = 0;

		for (size_t i = 0; i < length_; i++) {
			hash = hash * 10 + value_[i];
		}

		return hash;
	}

	virtual const char* getValue() {
		return value_;
	}

	size_t getLength() {
		return length_;
	}
};
