#ifndef KS_PARTICLE_H
#define KS_PARTICLE_H

#include <SFML/Graphics.hpp>

class ksParticle
{
	public:
		ksParticle( sf::Vector2f position, sf::Vector2f velocity, int ttl )
			:	m_position( position ), m_velocity( velocity ), m_ttl( ttl )
		{ }

		void update()
		{
			--m_ttl;
			m_position += m_velocity;
		}

		sf::Vector2f m_position;
		sf::Vector2f m_velocity;

		int m_ttl; // Time to Live
};

#endif