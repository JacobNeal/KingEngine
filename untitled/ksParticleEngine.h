#ifndef KS_PARTICLE_ENGINE_H
#define KS_PARTICLE_ENGINE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "ksParticle.h"

class ksParticleEngine : public sf::Drawable, public sf::Transformable
{
	public:
		ksParticleEngine( sf::Color color, sf::Vector2f location, int size = 8, int num = 10, int speed = 20, int reach = 20 );
		void update();

		void setColor( sf::Color color );
		void setSize( int size );
		void setNumber( int num );
		void setVelocity( int vel );
		void setReach( int reach );

		sf::Color getColor();

		void draw( sf::RenderTarget & target, sf::RenderStates states ) const;

	private:
		ksParticle generateParticle();

		sf::VertexArray m_array;
		sf::Color m_color;

		int m_size;
		int m_num;
		int m_speed;
		int m_reach;

		std::vector<ksParticle> m_particles;
};

#endif