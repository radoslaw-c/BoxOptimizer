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
	int getId() { return _id; }
	Position_T getPosition() { return _Position; }

	//setters
	void setLength(float len) { _length = len; }
	void setWidth(float width) { _width = width; }
	void setPosition(Position_T position) { _Position = position; }

private:
	float _width, _length;
	int _id;
	Position_T _Position;
};

