#pragma once

#include "Position.h"

class Element_T
{
public:
	Element_T() {}
	Element_T(float width, float length, float height, int id);

	//getters
	float getLength() const { return length; }
	float getWidth() const{ return width; }
	float getHeight() const { return height; }
	int getId() const { return id; }

	//setters
	void setLength(float len) { length = len; }
	void setWidth(float width) { width = width; }

private:
	float width=0, length=0, height=0;
	int id=0;
};

