#pragma once
#include "object.h"

class Boolean : public Object {
public:
	bool value_;

	Boolean(bool value) : Object() {
		value_ = value;
	}

	~Boolean() {}

	virtual bool equals(Object* that) {
		// if given object is a boolean
		if (dynamic_cast<Boolean*>(that) == nullptr)
		{
			return false;
		}

		return value_ == dynamic_cast<Boolean*>(that)->value_;
	}

	virtual bool getValue() {
		return value_;
	}

	virtual size_t hash() {
		return value_ ? 1 : 0;
	}
};