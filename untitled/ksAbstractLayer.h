#ifndef KS_ABSTRACT_LAYER_H
#define KS_ABSTRACT_LAYER_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "ksAbstract.h"
#include "ksComplex.h"

class ksAbstractLayer : public sf::Drawable, public sf::Transformable
{
	public:
		ksAbstractLayer( std::string tilesheet );
		void addObject( ksAbstract obj );
		void animate( int object_number, int low, int high, int speed );

		virtual void draw( sf::RenderTarget & target, sf::RenderStates states ) const;
		void drawLayer( sf::RenderWindow & app );

		ksRect getRect( int object_number ) const;
		int getCount();

		void setTileSheet( std::string tilesheet );

		void purge();

	private:
		sf::VertexArray m_array;
		std::vector<ksAbstract> m_abs_array;

		sf::Texture m_text;
		ksRect * m_position;

		int m_num;
};

#endif