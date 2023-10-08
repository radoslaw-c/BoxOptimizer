class Element_T
{
public:
	Element_T();
	Element_T(float length, float width, int id);

	//getters
	float length() { return _length; }
	float width() { return _width; }
	int id() { return _id; }

	//setters
	void length(float len) { _length = len; }
	void width(float width) { _width = width; }

private:
	float _length, _width;
	int _id;
};

