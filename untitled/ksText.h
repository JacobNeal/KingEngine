#ifndef KS_TEXT_H
#define KS_TEXT_H

#include <SFML/Graphics.hpp>
#include "ksRect.h"

class ksText : public sf::Drawable, public sf::Transformable
{
	public:
		ksText();
		ksText( std::string tilesheet, std::string text, int x, int y, sf::Color color = sf::Color( 255, 255, 255, 255 ), int size = 16 );
		ksText( const ksText & copy );
		~ksText();
		ksText & operator= ( const ksText & rhs );

		void setText( std::string tilesheet, std::string text, int x, int y, sf::Color color = sf::Color( 255, 255, 255, 255 ), int size = 16 );
		void setText( ksText & text );
		std::string getText();
		sf::Color getColor();

		void setColor( int red_number, int green_number, int blue_number, int alpha_number = 255 );

		virtual void draw( sf::RenderTarget & target, sf::RenderStates states ) const;

		int red;
		int green;
		int blue;
		int alpha;
	
	private:
		sf::VertexArray m_array;
		sf::Texture m_text;

		std::string m_string;
};

#endif