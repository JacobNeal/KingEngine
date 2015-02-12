#include "ksParticleEngine.h"
#include <iostream>
#include <time.h>

ksParticleEngine::ksParticleEngine( sf::Color color, sf::Vector2f location, int size, int num, int speed, int reach )
	: m_color( color ), m_size( size ), 
	  m_num( num ), m_speed( speed ), m_reach( reach )
{
	srand( time(NULL) );
	setPosition( location );
}

void ksParticleEngine::update()
{
	for ( int count = 0; count < m_num; count++ )
		m_particles.push_back( generateParticle() );

	for ( int particle = 0; particle < m_particles.size(); particle++ )
	{
		m_particles[ particle ].update();

		if ( m_particles[ particle ].m_ttl <= 0 )
		{
			m_particles.erase( m_particles.begin() + particle );
			particle--;
		}
	}

	m_array.setPrimitiveType( sf::Quads );
	m_array.resize( m_particles.size() * 4 );

	for ( int count = 0; count < m_particles.size(); count++ )
	{
		sf::Vector2f temp = m_particles[ count ].m_position;

		m_array[ ( count * 4 ) ].position = temp;
		m_array[ ( count * 4 ) + 1 ].position = sf::Vector2f( temp.x + m_size, temp.y );
		m_array[ ( count * 4 ) + 2 ].position = sf::Vector2f( temp.x + m_size, temp.y + m_size );
		m_array[ ( count * 4 ) + 3 ].position = sf::Vector2f( temp.x, temp.y + m_size );

		m_array[ ( count * 4 ) ].color = m_color;
		m_array[ ( count * 4 ) + 1 ].color = m_color;
		m_array[ ( count * 4 ) + 2 ].color = m_color;
		m_array[ ( count * 4 ) + 3 ].color = m_color;
	}
}

ksParticle ksParticleEngine::generateParticle()
{
	return ksParticle( 
		getPosition(), 
		sf::Vector2f( rand() % m_speed + 1,
					  rand() % m_speed + 1 ),
		rand() % m_reach + 1 );
}

void ksParticleEngine::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	states.transform *= getTransform();
	target.draw( m_array, states );
}

void ksParticleEngine::setColor( sf::Color color )
{
	m_color = color;
}

void ksParticleEngine::setSize( int size )
{
	m_size = size;
}

void ksParticleEngine::setNumber( int num )
{
	m_num = num;
}

void ksParticleEngine::setVelocity( int vel )
{
	m_speed = vel;
}

void ksParticleEngine::setReach( int reach )
{
	m_reach = reach;
}

sf::Color ksParticleEngine::getColor()
{
	return m_color;
}