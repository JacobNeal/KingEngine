#ifndef KS_PARTICLE_H
#define KS_PARTICLE_H

#include "ksVector.h"

class ksParticle
{
public:
	ksParticle(ksVector position, ksVector velocity, int ttl)
		: m_position(position), m_velocity(velocity), m_ttl(ttl)
	{ }

	void update()
	{
		--m_ttl;
		m_position.x += m_velocity.x;
		m_position.y += m_velocity.y;
	}

	ksVector m_position;
	ksVector m_velocity;

	int m_ttl; // Time to Live
};

#endif