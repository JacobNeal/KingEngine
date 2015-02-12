#ifndef KS_OBJECT
#define KS_OBJECT

#include <vector>
#include "cArray2D.h"
#include "ksAbstract.h"
#include "ksTile.h"

class ksObject : public ksAbstract
{
	public:
		ksObject( ksRect position, int type );
		void animate();
		void moveObject( cArray2D<int> objects );
		void setVelocityX( float velocity );
		void setVelocityY( float velocity );
		ksRect getVelocity() const;

	protected:
		float m_vel_x;
		float m_vel_y;
};

#endif