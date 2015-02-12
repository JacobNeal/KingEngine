#ifndef KS_COMPLEX_H
#define KS_COMPLEX_H

#include "ksAbstract.h"

class ksComplex : public ksAbstract
{
	public:
		ksComplex( ksRect position, int type );
		void moveComplex( float x, float y, int ** objects );
};

#endif