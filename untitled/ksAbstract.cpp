#include "ksAbstract.h"

ksAbstract::ksAbstract( ksRect position, int type )
	: m_position( position ), m_type( type ), m_frame( 0 ), m_speed( 1 ), m_low( type ), m_high( type )
{
	m_texture = ksRect( ( type - ( TILES_PER_LINE * ( type / TILES_PER_LINE ) ) ) * position.w,
		( type / TILES_PER_LINE ) * position.h, position.w, position.h );
}

void ksAbstract::animate()
{
	if ( m_type < m_low || m_type > m_high )
	{
		m_frame = 1;
		m_type = m_low;

		m_texture = ksRect( ( m_type - ( TILES_PER_LINE * ( m_type / TILES_PER_LINE ) ) ) * m_texture.w,
			( m_type / TILES_PER_LINE ) * m_texture.h, m_texture.w, m_texture.h );
	}
	else if ( m_frame % m_speed == 0 )
	{
		if ( m_type == m_high )
			m_type = m_low;
		else
			m_type++;

		m_texture = ksRect( ( m_type - ( TILES_PER_LINE * ( m_type / TILES_PER_LINE ) ) ) * m_texture.w,
			( m_type / TILES_PER_LINE ) * m_texture.h, m_texture.w, m_texture.h );
	}
	m_frame++;
}

ksRect ksAbstract::getPosition() const
{
	return m_position;
}

ksRect ksAbstract::getTexture() const
{
	return m_texture;
}

void ksAbstract::setAnimationLow( int low )
{
	m_low = low;
}

void ksAbstract::setAnimationHigh( int high )
{
	m_high = high;
}

void ksAbstract::setAnimationSpeed( int speed )
{
	m_speed = speed;
}