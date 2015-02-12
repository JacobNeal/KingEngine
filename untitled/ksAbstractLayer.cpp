#include "ksAbstractLayer.h"

ksAbstractLayer::ksAbstractLayer( std::string tilesheet )
	: m_num( 0 )
{
	if ( !m_text.loadFromFile( tilesheet ) )
		std::cout << "ERROR: Couldn't load tilesheet.\n";
}

void ksAbstractLayer::addObject( ksAbstract object )
{
	m_array.setPrimitiveType( sf::Quads );
	m_array.resize( ( m_num + 1 ) * 4 );

	m_abs_array.push_back( object );

	ksRect pos = object.getPosition();
	ksRect text = object.getTexture();
	int vec = m_num * 4;

	text.x /= 2;
	text.y /= 2;
	text.w /= 2;
	text.h /= 2;
	
	m_array[ vec ].position = sf::Vector2f( pos.x, pos.y );
	m_array[ vec + 1 ].position = sf::Vector2f( pos.x + pos.w, pos.y );
	m_array[ vec + 2 ].position = sf::Vector2f( pos.x + pos.w, pos.y + pos.h );
	m_array[ vec + 3 ].position = sf::Vector2f( pos.x, pos.y + pos.h );

	m_array[ vec ].texCoords = sf::Vector2f( text.x, text.y );
	m_array[ vec + 1 ].texCoords = sf::Vector2f( text.x + text.w, text.y );
	m_array[ vec + 2 ].texCoords = sf::Vector2f( text.x + text.w, text.y + text.h );
	m_array[ vec + 3 ].texCoords = sf::Vector2f( text.x, text.y + text.h );

	m_num++;
}

void ksAbstractLayer::animate( int object_number, int low, int high, int speed )
{
	m_abs_array[ object_number ].setAnimationLow( low );
	m_abs_array[ object_number ].setAnimationHigh( high );
	m_abs_array[ object_number ].setAnimationSpeed( speed );
}

void ksAbstractLayer::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	states.transform *= getTransform();
	states.texture = &m_text;
	target.draw( m_array, states );
}

void ksAbstractLayer::drawLayer( sf::RenderWindow & app )
{
	for ( int count = 0; count < m_num; count++ )
	{
		m_abs_array[ count ].animate();

		ksRect pos = m_abs_array[ count ].getPosition();
		ksRect text = m_abs_array[ count ].getTexture();
		int vec = count * 4;

		text.x /= 2;
		text.y /= 2;
		text.w /= 2;
		text.h /= 2;

		m_array[ vec ].position = sf::Vector2f( pos.x, pos.y );
		m_array[ vec + 1 ].position = sf::Vector2f( pos.x + pos.w, pos.y );
		m_array[ vec + 2 ].position = sf::Vector2f( pos.x + pos.w, pos.y + pos.h );
		m_array[ vec + 3 ].position = sf::Vector2f( pos.x, pos.y + pos.h );

		m_array[ vec ].texCoords = sf::Vector2f( text.x, text.y );
		m_array[ vec + 1 ].texCoords = sf::Vector2f( text.x + text.w, text.y );
		m_array[ vec + 2 ].texCoords = sf::Vector2f( text.x + text.w, text.y + text.h );
		m_array[ vec + 3 ].texCoords = sf::Vector2f( text.x, text.y + text.h );
	}

	app.draw( *this );
}

ksRect ksAbstractLayer::getRect( int object_number ) const 
{
	return m_abs_array[ object_number ].getPosition();
}

void ksAbstractLayer::setTileSheet( std::string tilesheet )
{
	if ( !m_text.loadFromFile( tilesheet ) )
		std::cout << "ERROR: Couldn't load tilesheet.\n";
}

int ksAbstractLayer::getCount()
{
	return m_num;
}

void ksAbstractLayer::purge()
{
	m_array.clear();
	m_abs_array.clear();
	m_num = 0;
}