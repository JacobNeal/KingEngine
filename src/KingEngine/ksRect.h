/************************************************************
* Class: ksRect
*
* Constructors:
*		ksRect( int rx, int ry, int rw, int rh )
*				Intialize the rect to the passed values.
*
* Methods:
*		ksRect & operator= ( const ksRect & rhs )
*				Set the rect equal to the value of the
*				passed rect.
************************************************************/

#ifndef KS_RECT_H
#define KS_RECT_H

class ksRect
{
public:
	ksRect() : x(0.f), y(0.f), w(0.f), h(0.f) { }
	ksRect(float rx, float ry, float rw, float rh) : x(rx), y(ry), w(rw), h(rh) { }

	ksRect & operator= (const ksRect & rhs)
	{
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
			w = rhs.w;
			h = rhs.h;
		}
		return *this;
	}

	inline bool checkCollision(ksRect obj);

	float x, y, w, h;
};

inline bool ksRect::checkCollision(ksRect obj)
{
	if (y + h <= obj.y)
		return false;
	if (y >= obj.y + obj.h)
		return false;
	if (x + w <= obj.x)
		return false;
	if (x >= obj.x + obj.w)
		return false;

	return true;
}

#endif