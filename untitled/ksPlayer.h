#ifndef KS_OBJECT_H
#define KS_OBJECT_H

#include <SFML/Graphics.hpp>
#include "cArray2D.h"
#include "ksTile.h"
#include "ksMap.h"

class ksPlayer : public sf::Drawable, public sf::Transformable
{
	public:
		ksPlayer( std::string tilesheet, ksRect rect );
		virtual void draw( sf::RenderTarget & target, sf::RenderStates states ) const;
		void animate( int type_low, int type_high, int speed );
		int collide( sf::View & camera, ksMap & map );
		int moveObject( sf::View & camera, ksMap & map );
		void changeVelX( float x );
		void changeVelY( float y );
		void setVelocity( float x, float y );
		ksRect getVelocity();
		ksRect getRect();
		float getX( sf::View & map_view );
		float getY( sf::View & map_view );
		void setX( float x );

		void setPlayerPosition( sf::View map_view, float x, float y );

	private:
		sf::VertexArray m_quad;
		sf::Texture m_text;
		ksRect m_rect;
		float m_vel_x;
		float m_vel_y;
		int m_type;
		int m_frame;
};

#endif