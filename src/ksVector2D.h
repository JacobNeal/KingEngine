/********************************************************
* Class:            ksVector2D
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksVector2D.h
*
*   Overview:
*       Utility class for a 2-Dimensional vector.
*
********************************************************/

#ifndef KS_VECTOR2D_H
#define KS_VECTOR2D_H

#include <math.h>

#define EPSILON 0.001

class ksVector2D
{
	public:
		//                 Constructors
		ksVector2D();
		ksVector2D(double a, double b);

		//                 Methods
		void               zero();
		bool               isZero();
		double             getLength() const;
		double             getLengthSq() const;
		void               normalize();
		double             getDotProduct(const ksVector2D & v2) const;
		int                getSign(const ksVector2D & v2) const;
		ksVector2D         getPerpendicularVector() const;
		void               truncate(double max);
		double             getDistance(const ksVector2D & v2) const;
		double             getDistanceSq(const ksVector2D & v2) const;
		void               reflect(const ksVector2D & norm);
		ksVector2D         getReverse() const;

		//                 Overloaded operators
		const ksVector2D & operator+=(const ksVector2D & rhs);
		const ksVector2D & operator-=(const ksVector2D & rhs);
		const ksVector2D & operator*=(const double & rhs);
		const ksVector2D & operator/=(const double & rhs);
		bool               operator==(const ksVector2D & rhs) const;
		bool               operator!=(const ksVector2D & rhs) const;

		//                 Data members
		double             X;
		double             Y;
};

//         Extra overloaded operators
ksVector2D operator*(const ksVector2D & lhs, double rhs);
ksVector2D operator*(double lhs, const ksVector2D & rhs);
ksVector2D operator-(const ksVector2D & lhs, const ksVector2D & rhs);
ksVector2D operator+(const ksVector2D & lhs, const ksVector2D & rhs);
ksVector2D operator/(const ksVector2D & lhs, const ksVector2D & rhs);
ksVector2D operator/(const ksVector2D & lhs, double val);

inline ksVector2D VecNormalize(const ksVector2D & vect)
{
    ksVector2D v = vect;

    double v_length = v.getLength();

    if (v_length > EPSILON)
    {
        v.X /= v_length;
        v.Y /= v_length;
    }

    return v;
}

inline double VecDistanceSq(const ksVector2D & vect, 
                            const ksVector2D & vect2)
{
    double y_separation = vect2.Y - vect.Y;
    double x_separation = vect2.X - vect.X;

    return (y_separation * y_separation) + 
           (x_separation * x_separation);
}

#endif
