#pragma once

#include "Position.h"

class Element_T
{
public:
	Element_T();
	Element_T(float length, float width, int id);

	//getters
	float getLength() { return _length; }
	float getWidth() { return _width; }
	int getId() const { return _id; }

	//setters
	void setLength(float len) { _length = len; }
	void setWidth(float width) { _width = width; }

private:
	float _width, _length;
	int _id;
};

