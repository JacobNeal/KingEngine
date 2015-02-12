#include "ksEffect.h"

ksEffect::ksEffect( sf::Color color1, sf::Color color2,
				   int duration1, int duration2 )
				  : m_current_color( 1 ),
				   m_duration_1( duration1 ),
				   m_duration_2( duration2 ),
				   m_number_of_lights( 1 ),
				   m_current( 0 )
{
	m_array.setPrimitiveType( sf::Triangles );
	m_array.resize( 24 );

	m_color_1.push_back( color1 );
	m_color_2.push_back( color2 );

	// Edge = 400
	// Radius = 540

	// Center
	m_array[ 0 ].position = sf::Vector2f( 400, 320 );
	m_array[ 1 ].position = sf::Vector2f( 800, -80 );
	m_array[ 2 ].position = sf::Vector2f( 940, 320 );

	m_array[ 3 ].position = sf::Vector2f( 400, 320 );
	m_array[ 4 ].position = sf::Vector2f( 940, 320 );
	m_array[ 5 ].position = sf::Vector2f( 800, 720 );

	m_array[ 6 ].position = sf::Vector2f( 400, 320 );
	m_array[ 7 ].position = sf::Vector2f( 800, 720 );
	m_array[ 8 ].position = sf::Vector2f( 400, 860 );

	m_array[ 9 ].position = sf::Vector2f( 400, 320 );
	m_array[ 10 ].position = sf::Vector2f( 400, 860 );
	m_array[ 11 ].position = sf::Vector2f( 0, 720 );

	m_array[ 12 ].position = sf::Vector2f( 400, 320 );
	m_array[ 13 ].position = sf::Vector2f( 0, 720 );
	m_array[ 14 ].position = sf::Vector2f( -140, 320 );

	m_array[ 15 ].position = sf::Vector2f( 400, 320 );
	m_array[ 16 ].position = sf::Vector2f( -140, 320 );
	m_array[ 17 ].position = sf::Vector2f( 0, -80 );

	m_array[ 18 ].position = sf::Vector2f( 400, 320 );
	m_array[ 19 ].position = sf::Vector2f( 0, -80 );
	m_array[ 20 ].position = sf::Vector2f( 400, -220 );

	m_array[ 21 ].position = sf::Vector2f( 400, 320 );
	m_array[ 22 ].position = sf::Vector2f( 400, -220 );
	m_array[ 23 ].position = sf::Vector2f( 800, -80 );

	for ( int count = 0; count < 24; count++ )
		m_array[ count ].color = color1;
}

void ksEffect::set( int light_num, sf::Color color1, sf::Color color2,
				   int duration1, int duration2 )
{
	//clear();

	m_color_1[ light_num ] = color1;
	m_color_2[ light_num ] = color2;
	m_current_color = 1;
	m_duration_1 = duration1;
	m_duration_2 = duration2;
	m_current = 0;
}

void ksEffect::add( sf::Vector2f center, int diameter, sf::Color color1, sf::Color color2 )
{
	int radius = diameter / 2;
	int edge = ( 3 * radius ) / 4;
	int temp_vertex = m_number_of_lights * 24;

	m_array.resize( ( m_number_of_lights + 1 ) * 24 );

	m_array[ temp_vertex ].position = center;
	m_array[ temp_vertex + 1 ].position = sf::Vector2f( center.x + edge, center.y - edge );
	m_array[ temp_vertex + 2 ].position = sf::Vector2f( center.x + radius, center.y );

	m_array[ temp_vertex + 3 ].position = center;
	m_array[ temp_vertex + 4 ].position = sf::Vector2f( center.x + radius, center.y );
	m_array[ temp_vertex + 5 ].position = sf::Vector2f( center.x + edge, center.y + edge );

	m_array[ temp_vertex + 6 ].position = center;
	m_array[ temp_vertex + 7 ].position = sf::Vector2f( center.x + edge, center.y + edge );
	m_array[ temp_vertex + 8 ].position = sf::Vector2f( center.x, center.y + radius );

	m_array[ temp_vertex + 9 ].position = center;
	m_array[ temp_vertex + 10 ].position = sf::Vector2f( center.x, center.y + radius );
	m_array[ temp_vertex + 11 ].position = sf::Vector2f( center.x - edge, center.y + edge );

	m_array[ temp_vertex + 12 ].position = center;
	m_array[ temp_vertex + 13 ].position = sf::Vector2f( center.x - edge, center.y + edge );
	m_array[ temp_vertex + 14 ].position = sf::Vector2f( center.x - radius, center.y );

	m_array[ temp_vertex + 15 ].position = center;
	m_array[ temp_vertex + 16 ].position = sf::Vector2f( center.x - radius, center.y );
	m_array[ temp_vertex + 17 ].position = sf::Vector2f( center.x - edge, center.y - edge );

	m_array[ temp_vertex + 18 ].position = center;
	m_array[ temp_vertex + 19 ].position = sf::Vector2f( center.x - edge, center.y - edge );
	m_array[ temp_vertex + 20 ].position = sf::Vector2f( center.x, center.y - radius );

	m_array[ temp_vertex + 21 ].position = center;
	m_array[ temp_vertex + 22 ].position = sf::Vector2f( center.x, center.y - radius );
	m_array[ temp_vertex + 23 ].position = sf::Vector2f( center.x + edge, center.y - edge );

	m_color_1.push_back( color1 );
	m_color_2.push_back( color2 );

	m_number_of_lights++;
}

void ksEffect::resizeMap( int width_tiles, int height_tiles )
{
	int x = width_tiles * TILE_WIDTH;
	int y = height_tiles * TILE_WIDTH;

	int diameter = 1.35 * x;
	int radius = diameter / 2;
	int edge = ( 3 * radius ) / 4;
	
	sf::Vector2f center( (x / 2), (y / 2) );

	m_array[ 0 ].position = center;
	m_array[ 1 ].position = sf::Vector2f( center.x + edge, center.y - edge );
	m_array[ 2 ].position = sf::Vector2f( center.x + radius, center.y );

	m_array[ 3 ].position = center;
	m_array[ 4 ].position = sf::Vector2f( center.x + radius, center.y );
	m_array[ 5 ].position = sf::Vector2f( center.x + edge, center.y + edge );

	m_array[ 6 ].position = center;
	m_array[ 7 ].position = sf::Vector2f( center.x + edge, center.y + edge );
	m_array[ 8 ].position = sf::Vector2f( center.x, center.y + radius );

	m_array[ 9 ].position = center;
	m_array[ 10 ].position = sf::Vector2f( center.x, center.y + radius );
	m_array[ 11 ].position = sf::Vector2f( center.x - edge, center.y + edge );

	m_array[ 12 ].position = center;
	m_array[ 13 ].position = sf::Vector2f( center.x - edge, center.y + edge );
	m_array[ 14 ].position = sf::Vector2f( center.x - radius, center.y );

	m_array[ 15 ].position = center;
	m_array[ 16 ].position = sf::Vector2f( center.x - radius, center.y );
	m_array[ 17 ].position = sf::Vector2f( center.x - edge, center.y - edge );

	m_array[ 18 ].position = center;
	m_array[ 19 ].position = sf::Vector2f( center.x - edge, center.y - edge );
	m_array[ 20 ].position = sf::Vector2f( center.x, center.y - radius );

	m_array[ 21 ].position = center;
	m_array[ 22 ].position = sf::Vector2f( center.x, center.y - radius );
	m_array[ 23 ].position = sf::Vector2f( center.x + edge, center.y - edge );
}

void ksEffect::update()
{
	if ( m_current < m_duration_1 )
		m_current++;
	else if ( m_current >= m_duration_1 && m_current - m_duration_1 < m_duration_2 )
	{
		m_current_color = 2;
		m_current++;
	}
	else
	{
		m_current = 0;
		m_current_color = 1;
	}

	for ( int count = 0; count < 24; count++ )
	{
		sf::Color inner_color;
		sf::Color outer_color;

		if ( m_current_color == 1 )
			inner_color = m_color_1[ 0 ];
		else
			inner_color = m_color_2[ 0 ];

		outer_color = inner_color;
		outer_color.a -= inner_color.a / 2;

		if ( count % 3 == 0 )
			m_array[ count ].color = outer_color;
		else
			m_array[ count ].color = inner_color;
	}

	for ( int count = 1; count < m_number_of_lights; count++ )
	{
		int vertex_temp = count * 24;
		sf::Color inner_color;
		sf::Color outer_color;

		if ( m_current_color == 1 )
			inner_color = m_color_1[ count ];
		else
			inner_color = m_color_2[ count ];

		outer_color = inner_color;
		outer_color.a -= ( 3 * outer_color.a ) / 4;

		m_array[ vertex_temp ].color = inner_color;

		for ( int current_vertex = 1; current_vertex < 24; current_vertex++ )
		{
			if ( current_vertex % 3 == 0 )
				m_array[ vertex_temp + current_vertex ].color = inner_color;
			else
				m_array[ vertex_temp + current_vertex ].color = outer_color;
		}
	}
}

void ksEffect::clear()
{
	m_array.clear();
	m_color_1.clear();
	m_color_2.clear();

	m_number_of_lights = 1;
	m_array.resize( 24 );

	m_color_1.push_back( sf::Color( 0, 0, 0, 0 ) );
	m_color_2.push_back( sf::Color( 0, 0, 0, 0 ) );

	m_array[ 0 ].position = sf::Vector2f( 400, 320 );
	m_array[ 1 ].position = sf::Vector2f( 800, -80 );
	m_array[ 2 ].position = sf::Vector2f( 940, 320 );

	m_array[ 3 ].position = sf::Vector2f( 400, 320 );
	m_array[ 4 ].position = sf::Vector2f( 940, 320 );
	m_array[ 5 ].position = sf::Vector2f( 800, 720 );

	m_array[ 6 ].position = sf::Vector2f( 400, 320 );
	m_array[ 7 ].position = sf::Vector2f( 800, 720 );
	m_array[ 8 ].position = sf::Vector2f( 400, 860 );

	m_array[ 9 ].position = sf::Vector2f( 400, 320 );
	m_array[ 10 ].position = sf::Vector2f( 400, 860 );
	m_array[ 11 ].position = sf::Vector2f( 0, 720 );

	m_array[ 12 ].position = sf::Vector2f( 400, 320 );
	m_array[ 13 ].position = sf::Vector2f( 0, 720 );
	m_array[ 14 ].position = sf::Vector2f( -140, 320 );

	m_array[ 15 ].position = sf::Vector2f( 400, 320 );
	m_array[ 16 ].position = sf::Vector2f( -140, 320 );
	m_array[ 17 ].position = sf::Vector2f( 0, -80 );

	m_array[ 18 ].position = sf::Vector2f( 400, 320 );
	m_array[ 19 ].position = sf::Vector2f( 0, -80 );
	m_array[ 20 ].position = sf::Vector2f( 400, -220 );

	m_array[ 21 ].position = sf::Vector2f( 400, 320 );
	m_array[ 22 ].position = sf::Vector2f( 400, -220 );
	m_array[ 23 ].position = sf::Vector2f( 800, -80 );
}

void ksEffect::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	states.transform *= getTransform();
	target.draw( m_array, states );
}