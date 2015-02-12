#include "ksText.h"
#include <fstream>
#include <iostream>

ksText::ksText()
{ }

ksText::ksText( std::string tilesheet, std::string text, int x, int y, sf::Color color, int size )
	: m_string( text ), red( (int) color.r ), green( (int) color.g ), blue( (int) color.b ),
						alpha( (int) color.a )
{
	setText( tilesheet, text, x, y, color );
}

ksText::ksText( const ksText & copy )
	: m_array( copy.m_array ), m_string( copy.m_string ), m_text( copy.m_text ),
	  red( (int) copy.red ), green( (int) copy.green ), blue( (int) copy.blue ),
	  alpha( (int) copy.alpha )
{ }

ksText::~ksText()
{ }

ksText & ksText::operator= ( const ksText & rhs )
{
	if ( this != &rhs )
	{
		m_array = rhs.m_array;
		m_text = rhs.m_text;
		m_string = rhs.m_string;

		red = rhs.red;
		green = rhs.green;
		blue = rhs.blue;
		alpha = rhs.alpha;
	}

	return *this;
}


void ksText::setText( std::string tilesheet, std::string text, int x, int y, sf::Color color, int size )
{
	m_string = text;
	red = (int) color.r;
	green = (int) color.g;
	blue = (int) color.b;
	alpha = (int) color.a;

	m_text.loadFromFile( tilesheet );
	m_array.setPrimitiveType( sf::Quads );
	m_array.resize( text.length() * 4 );

	int margin = size - ( size / 3 );

	for ( int count = 0; text[ count ] != '\0'; count++ )
	{
		int tile_type = 0;

		if ( text[ count ] >= ' ' && text[ count ] <= '~' )
			tile_type = ( text[ count ] - 32 );

		ksRect tsrect( ( tile_type - ( 10 * ( tile_type / 10 ) ) ) * 16,
			( tile_type / 10 ) * 16, 16, 16 );

		m_array[ ( count * 4 ) ].position = sf::Vector2f( x + ( count * margin ), y );
		m_array[ ( count * 4 ) + 1 ].position = sf::Vector2f( x + ( count * margin ) + size, y );
		m_array[ ( count * 4 ) + 2 ].position = sf::Vector2f( x + ( count * margin ) + size, y + size );
		m_array[ ( count * 4 ) + 3 ].position = sf::Vector2f( x + ( count * margin ), y + size );

		m_array[ ( count * 4 ) ].texCoords = sf::Vector2f( tsrect.x, tsrect.y );
		m_array[ ( count * 4 ) + 1 ].texCoords = sf::Vector2f( tsrect.x + 16, tsrect.y );
		m_array[ ( count * 4 ) + 2 ].texCoords = sf::Vector2f( tsrect.x + 16, tsrect.y + 16 );
		m_array[ ( count * 4 ) + 3 ].texCoords = sf::Vector2f( tsrect.x, tsrect.y + 16 );

		m_array[ ( count * 4 ) ].color = color;
		m_array[ ( count * 4 ) + 1 ].color = color;
		m_array[ ( count * 4 ) + 2 ].color = color;
		m_array[ ( count * 4 ) + 3 ].color = color;
	}
}

void ksText::setText( ksText & text )
{
	setText( "Tiles/consolas_font_map.png", text.m_string, getPosition().x, getPosition().y, sf::Color( red, green, blue, alpha ) );
}

std::string ksText::getText()
{
	return m_string;
}

sf::Color ksText::getColor()
{
	return sf::Color( red, green, blue, alpha );
}

void ksText::setColor( int red_number, int green_number, int blue_number, int alpha_number )
{
	for ( int count = 0; count < m_string.length(); count++ )
	{
		m_array[ ( count * 4 ) ].color = sf::Color( red_number, green_number, blue_number, alpha_number );
		m_array[ ( count * 4 ) + 1 ].color = sf::Color( red_number, green_number, blue_number, alpha_number );
		m_array[ ( count * 4 ) + 2 ].color = sf::Color( red_number, green_number, blue_number, alpha_number );
		m_array[ ( count * 4 ) + 3 ].color = sf::Color( red_number, green_number, blue_number, alpha_number );
	}
	red = red_number;
	green = green_number;
	blue = blue_number;
	alpha = alpha_number;
}

void ksText::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	states.transform *= getTransform();
	states.texture = &m_text;
	target.draw( m_array, states );
}