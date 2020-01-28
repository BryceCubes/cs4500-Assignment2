#pragma once
#include "object.h"

class Float : public Object {
public:
	float value_;

	Float(float value) : Object() {
		value_ = value;
	}

	~Float() {}

	virtual bool equals(Object* that) {
		// if given object is a boolean
		if (dynamic_cast<Float*>(that) == nullptr)
		{
			return false;
		}

		return value_ == dynamic_cast<Float*>(that)->value_;
	}

	virtual float getValue() {
		return value_;
	}

	virtual size_t hash() {
		return value_;
	}
};