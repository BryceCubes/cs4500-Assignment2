//lang::CwC
#pragma once

#include <stdio.h>

class Object {
public:

	// Default constructor
	Object() {}

	// Destructor
	~Object() {}

	virtual bool equals(Object* that) {
		return this->hash() == that->hash();
	}

	virtual size_t hash() {
		// this type of cast is used because we want to use
		// its address as hash
		return reinterpret_cast<size_t>(this);
	}
};
