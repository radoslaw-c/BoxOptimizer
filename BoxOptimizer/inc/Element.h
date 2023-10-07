class Element
{
public:
	Element();
	Element(float length, float width);

	//getters
	float length() { return _length; }
	float width() { return _width; }

	//setters
	void length(float len) { _length = len; }
	void width(float width) { _width = width; }

private:
	float _length, _width;
};

