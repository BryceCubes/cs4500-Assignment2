#pragma once
#include "object.h"

class Integer : public Object {
public:
	int value_;

	Integer(int value) : Object() {
		value_ = value;
	}

	~Integer() {}

	virtual bool equals(Object* that) {
		// if given object is a boolean
		if (dynamic_cast<Integer*>(that) == nullptr)
		{
			return false;
		}

		return value_ == dynamic_cast<Integer*>(that)->value_;
	}

	virtual int getValue() {
		return value_;
	}

	virtual size_t hash() {
		return value_;
	}
};