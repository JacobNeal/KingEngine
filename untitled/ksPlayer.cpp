#include <fstream>
#include <iostream>
#include "ksPlayer.h"

float ksPlayer::getX( sf::View & map_view )
{
	return getPosition().x + ( map_view.getSize().x / 2 ) - ( m_rect.w / 2 );
}

float ksPlayer::getY( sf::View & map_view )
{
	return getPosition().y + ( map_view.getSize().y / 2 ) - ( m_rect.h / 2 );
}

void ksPlayer::setX( float x )
{
	m_rect.x = x;
}

ksPlayer::ksPlayer( std::string tilesheet, ksRect rect )
	: m_rect( rect ), m_vel_x( 0.f ), m_vel_y( 0.f ), m_type( 0 ), m_frame( 0 )
{
	m_text.loadFromFile( tilesheet );

	m_quad.setPrimitiveType( sf::Quads );
	m_quad.resize( 4 );

	m_quad[ 0 ].position = sf::Vector2f( rect.x, rect.y );
	m_quad[ 1 ].position = sf::Vector2f( rect.x + rect.w, rect.y );
	m_quad[ 2 ].position = sf::Vector2f( rect.x + rect.w, rect.y + rect.h );
	m_quad[ 3 ].position = sf::Vector2f( rect.x, rect.y + rect.h );

	m_quad[ 0 ].texCoords = sf::Vector2f( 0, 0 );
	m_quad[ 1 ].texCoords = sf::Vector2f( rect.w / 2, 0 );
	m_quad[ 2 ].texCoords = sf::Vector2f( rect.w / 2, rect.h / 2 );
	m_quad[ 3 ].texCoords = sf::Vector2f( 0, rect.h / 2 );
}

void ksPlayer::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	states.transform *= getTransform();
	states.texture = &m_text;
	target.draw( m_quad, states );
}

int ksPlayer::collide( sf::View & map_view, ksMap & map )
{
	ksRect temp( getPosition().x + ( map_view.getSize().x / 2 ) - ( m_rect.w / 2 ),
				 getPosition().y + ( map_view.getSize().y / 2 ) - ( m_rect.h / 2 ),
				 m_rect.w, m_rect.h );

	//if ( map_view.getCenter().x - ( map_view.getSize().x / 2 ) < 0 )
	//	temp.x = getPosition().x;
	//if ( map_view.getCenter().x + ( map_view.getSize().x / 2 ) > ( map.getWidth() * 32 ) )
	//	temp.x += getPosition().x;
	//if ( map_view.getCenter().y - ( map_view.getSize().y / 2 ) < 0 )
	//	temp.y = getPosition().y;
	//if ( map_view.getCenter().y + ( map_view.getSize().y / 2 ) > ( map.getHeight() * 32 ) )
	//	temp.y += getPosition().y;

	//std::cout << temp.x << '\t' << temp.y << '\n';

	for ( int row = 0; row < map.getHeight(); row++ )
		for ( int col = 0; col < map.getWidth(); col++ )
		{
			if ( map.getEvents()[ row ][ col ] == 1 )
			{
				if ( temp.checkCollision( ksRect( (col * TILE_WIDTH), (row * TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT ) ) )
					return 1;
			}
			else if ( map.getEvents()[ row ][ col ] != 0 )
			{
				if ( temp.checkCollision( ksRect( (col * TILE_WIDTH), (row * TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT ) ) )
				{
					return map.getEvents()[ row ][ col ];
				}
			}
		}

	return 0;
}

int ksPlayer::moveObject( sf::View & camera, ksMap & map )
{
	//m_vel_x *= 0.9;
	//m_vel_y *= 0.9;

	//move( m_vel_x, 0 );
	//m_rect.x += m_vel_x;
	int collide_x = 0;

	if ( m_vel_x != 0 )
	{
		move( m_vel_x, 0 );
		m_rect.x += m_vel_x;

		collide_x = collide( camera, map );

		if ( collide_x == 1 )
		{
			move( -m_vel_x, 0 );
			m_rect.x -= m_vel_x;
			m_vel_x = 0;
		}
	}

	//move( 0, m_vel_y );
	//m_rect.y += m_vel_y;
	int collide_y = 0;

	if ( m_vel_y != 0.0 )
	{
		move( 0, m_vel_y );
		m_rect.y += m_vel_y;

		collide_y = collide( camera, map );
		if ( collide_y == 1 )
		{
			move( 0, -m_vel_y );
			m_rect.y -= m_vel_y;
			m_vel_y = 0;
		}
	}

	// Animate the object
	if ( m_vel_y == 3.f )
		animate( 3, 8, 5 );
	else if ( m_vel_y == 6.f )
		animate( 3, 8, 3 );
	else if ( m_vel_y == -3.f )
		animate( 12, 17, 5 );
	else if ( m_vel_y == -6.f )
		animate( 12, 17, 3 );
	else if ( m_vel_x == 3.f )
		animate( 21, 26, 5 );
	else if ( m_vel_x == 6.f )
		animate( 21, 26, 3 );
	else if ( m_vel_x == -3.f )
		animate( 30, 35, 5 );
	else if ( m_vel_x == -6.f )
		animate( 30, 35, 3 );
	else
	{
		if ( m_type >= 0 && m_type <= 8 )
			animate( 0, 2, 60 );
		else if ( m_type >= 9 && m_type <= 17 )
			animate( 9, 11, 60 );
		else if ( m_type >= 18 && m_type <= 26 )
			animate( 18, 20, 60 );
		else if ( m_type >= 27 && m_type <= 35 )
			animate( 27, 29, 60 );
	}

	m_vel_x = 0.0f;
	m_vel_y = 0.0f;

	if ( collide_x <= 1 && collide_y <= 1 )
		return collide_x;
	else
		return collide_x > 1 ? collide_x : collide_y;
}

void ksPlayer::changeVelX( float x )
{
	m_vel_x = m_vel_x + x;
}

void ksPlayer::changeVelY( float y )
{
	m_vel_y = m_vel_y + y;
}

ksRect ksPlayer::getVelocity()
{
	return ksRect( m_vel_x, m_vel_y, 0, 0 );
}

ksRect ksPlayer::getRect()
{
	return m_rect;
}

void ksPlayer::animate( int type_low, int type_high, int speed )
{
	if ( m_type < type_low || m_type > type_high )
	{
		m_frame = 1;
		m_type = type_low;

		ksRect tsrect( ( m_type - ( 9 * ( m_type / 9 ) ) ) * m_rect.w,
			( m_type / 9 ) * m_rect.h, m_rect.w, m_rect.h );

		tsrect.x /= 2;
		tsrect.y /= 2;
		tsrect.w /= 2;
		tsrect.h /= 2;

		m_quad[ 0 ].texCoords = sf::Vector2f( tsrect.x, tsrect.y );
		m_quad[ 1 ].texCoords = sf::Vector2f( tsrect.x + tsrect.w, tsrect.y );
		m_quad[ 2 ].texCoords = sf::Vector2f( tsrect.x + tsrect.w, tsrect.y + tsrect.h );
		m_quad[ 3 ].texCoords = sf::Vector2f( tsrect.x, tsrect.y + tsrect.h );
	}
	else if ( m_frame % speed == 0 )
	{
		if ( m_type == type_high )
			m_type = type_low;
		else
			m_type++;

		ksRect tsrect( ( m_type - ( 9 * ( m_type / 9 ) ) ) * m_rect.w,
			( m_type / 9 ) * m_rect.h, m_rect.w, m_rect.h );

		tsrect.x /= 2;
		tsrect.y /= 2;
		tsrect.w /= 2;
		tsrect.h /= 2;

		m_quad[ 0 ].texCoords = sf::Vector2f( tsrect.x, tsrect.y );
		m_quad[ 1 ].texCoords = sf::Vector2f( tsrect.x + tsrect.w, tsrect.y );
		m_quad[ 2 ].texCoords = sf::Vector2f( tsrect.x + tsrect.w, tsrect.y + tsrect.h );
		m_quad[ 3 ].texCoords = sf::Vector2f( tsrect.x, tsrect.y + tsrect.h );
	}
	m_frame++;
}

void ksPlayer::setPlayerPosition( sf::View map_view, float x, float y )
{
	setPosition( x - ( map_view.getSize().x / 2 ) + ( m_rect.w / 2 ), y - ( map_view.getSize().y / 2 ) + ( m_rect.h / 2 ) );
	m_rect.x = x;
	m_rect.y = y;
}

void ksPlayer::setVelocity( float x, float y )
{
	m_vel_x = x;
	m_vel_y = y;
}