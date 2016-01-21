/********************************************************
* Class:			ksVector2D
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksVector2D.cpp
********************************************************/

#include "ksVector2D.h"

/*********************************************************
*	ksVector2D()
*
*	Initialize vector x, y to 0.0.
*********************************************************/
ksVector2D::ksVector2D() : X(0.0), Y(0.0)
{ }

/*********************************************************
*	ksVector2D(double a, double b)
*
*	Initialize vector to passed components.
*********************************************************/
ksVector2D::ksVector2D(double a, double b) : X(a), Y(b)
{ }

/*********************************************************
*	zero
*
*	Zero the vector components.
*********************************************************/
void ksVector2D::zero()
{
	X = 0.0;
	Y = 0.0;
}

/***********************************************************
*	isZero
*
*	Returns true if both of the vector components are equal
*	to zero.
***********************************************************/
bool ksVector2D::isZero()
{
	// Returns true if the product is really small (0.01)
	return (X * Y) < 0.01;
}

/*********************************************************
*	getLength
*
*	Returns the length of the 2-Dimensional vector.
*********************************************************/
double ksVector2D::getLength() const
{
	return sqrt((X * X) + (Y * Y));
}

/*********************************************************
*	getLengthSq
*
*	Returns the length of the vector squared.
*********************************************************/
double ksVector2D::getLengthSq() const
{
	return ((X * X) + (Y * Y));
}

/*********************************************************
*	normalize
*
*	Normalize the 2-Dimensional vector.
*********************************************************/
void ksVector2D::normalize()
{
	double vect_length = getLength();

	if (vect_length > EPSILON)
	{
		X /= vect_length;
		Y /= vect_length;
	}
}

/*********************************************************
*	getDotProduct
*
*	Calculate and return the dot product of the vector.
*********************************************************/
double ksVector2D::getDotProduct(const ksVector2D & v2) const
{
	return (X * v2.X) + (Y * v2.Y);
}

/*********************************************************
*	getSign
*
*	Return whether v2 is clockwise(+1) to the vector, or
*	counter-clockwise(-1).
*********************************************************/
int ksVector2D::getSign(const ksVector2D & v2) const
{
	return (Y * v2.X) > (X * v2.Y) ? -1 : 1;
}

/*********************************************************
*	getPerpendicularVector
*
*	Returns a vector that is perpendicular to the vector.
*********************************************************/
ksVector2D ksVector2D::getPerpendicularVector() const
{
	return ksVector2D(-Y, X);
}

/*********************************************************
*	truncate
*
*	Truncate the components of the vector to not exceed
*	the passed value.
*********************************************************/
void ksVector2D::truncate(double max)
{
	if (getLength() > max)
	{
		normalize();
		*this *= max;
	}
}

/*********************************************************
*	getDistance
*
*	Calculates the Euclidean distance between the two
*	vectors.
*********************************************************/
double ksVector2D::getDistance(const ksVector2D & v2) const
{
	double x_separation = v2.Y - Y;
	double y_separation = v2.X - X;

	return sqrt((y_separation * y_separation) + (x_separation * x_separation));
}

/*********************************************************
*	getDistanceSq
*
*	Calculates the Euclidean distance between the two
*	vectors squared.
*********************************************************/
double ksVector2D::getDistanceSq(const ksVector2D & v2) const
{
	double x_separation = v2.Y - Y;
	double y_separation = v2.X - X;

	return (y_separation * y_separation) + (x_separation * x_separation);
}

/*********************************************************
*	reflect
*
*	Reflects the vector based on the passed normalized
*	vector. (Ex: a ball bounces off a wall)
*********************************************************/
void ksVector2D::reflect(const ksVector2D & norm)
{
	*this += 2.0 * getDotProduct(norm) * norm.getReverse();
}

/*********************************************************
*	getReverse
*
*	Returns the reverse vector of this vector.
*********************************************************/
ksVector2D ksVector2D::getReverse() const
{
	return ksVector2D(-X, -Y);
}

/*********************************************************
*	operator+=
*
*	Returns the result of adding 2 vectors.
*********************************************************/
const ksVector2D & ksVector2D::operator+=(const ksVector2D & rhs)
{
	X += rhs.X;
	Y += rhs.Y;

	return *this;
}

/*********************************************************
*	operator-=
*
*	Returns the result of subtracting 2 vectors.
*********************************************************/
const ksVector2D & ksVector2D::operator-=(const ksVector2D & rhs)
{
	X -= rhs.X;
	Y -= rhs.Y;

	return *this;
}

/***********************************************************
*	operator*=
*
*	Returns the result of multiplying a vector's components
*	by a double.
***********************************************************/
const ksVector2D & ksVector2D::operator*=(const double & rhs)
{
	X *= rhs;
	Y *= rhs;

	return *this;
}

/***********************************************************
*	operator/=
*
*	Returns the result of dividing a vector's components
*	by a double.
***********************************************************/
const ksVector2D & ksVector2D::operator/=(const double & rhs)
{
	X /= rhs;
	Y /= rhs;

	return *this;
}

/***********************************************************
*	operator==
*
*	Returns whether or not the 2 components of the 2 vectors
*	are equal by determining if their difference is less
*	than a very small number (EPSILON = 0.001).
***********************************************************/
bool ksVector2D::operator==(const ksVector2D & rhs) const
{
	return (fabs(X - rhs.X) < EPSILON) &&
		(fabs(Y - rhs.Y) < EPSILON);
}

/***********************************************************
*	operator!=
*
*	Returns true if the 2 components of the 2 vectors are
*	not equal.
***********************************************************/
bool ksVector2D::operator!=(const ksVector2D & rhs) const
{
	return (X != rhs.X) || (Y != rhs.Y);
}

/***********************************************************
*	operator*=
*
*	Returns a vector multiplied by a double.
***********************************************************/
ksVector2D operator*(const ksVector2D & lhs, double rhs)
{
	ksVector2D result(lhs);
	result *= rhs;
	return result;
}

/***********************************************************
*	operator*=
*
*	Returns a vector multiplied by a double.
***********************************************************/
ksVector2D operator*(double lhs, const ksVector2D & rhs)
{
	ksVector2D result(rhs);
	result *= lhs;
	return result;
}

/***********************************************************
*	operator-
*
*	Returns the difference between 2 vectors.
***********************************************************/
ksVector2D operator-(const ksVector2D & lhs, const ksVector2D & rhs)
{
	ksVector2D result(lhs);
	result.X -= rhs.X;
	result.Y -= rhs.Y;
	return result;
}

/***********************************************************
*	operator+
*
*	Returns the sum of 2 vectors.
***********************************************************/
ksVector2D operator+(const ksVector2D & lhs, const ksVector2D & rhs)
{
	ksVector2D result(lhs);
	result.X += rhs.X;
	result.Y += rhs.Y;
	return result;
}

/***********************************************************
*	operator/
*
*	Returns the result of dividing the components of a vector
*	by a double.
***********************************************************/
ksVector2D operator/(const ksVector2D & lhs, double val)
{
	ksVector2D result(lhs);
	result.X /= val;
	result.Y /= val;
	return result;
}
