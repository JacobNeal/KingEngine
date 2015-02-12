#include <iostream>
#include <fstream>
#include "ksMap.h"

ksMap::ksMap( std::string tilesheet, std::string filename, int width, int height )
	: m_rect( 0, 0, width, height )
{
	m_evt = new int * [ height ];
	
	for ( int row = 0; row < height; row++ )
		m_evt[ row ] = new int [ width ];

	load( tilesheet, filename, width, height );
}

void ksMap::load( std::string tilesheet, std::string filename, int width, int height )
{
	std::ifstream map( filename + ".ks" );
	m_map_name = filename;

	int tile_type = -1;
	int cur_x = 0;
	int cur_y = 0;

	if ( map.is_open() )
	{
		m_text.loadFromFile( tilesheet );

		m_map.setPrimitiveType( sf::Quads );
		m_map.resize( width * height * 4 );

		for ( int num = 0; num < ( width * height ) && !map.eof(); ++num )
		{
			map >> tile_type;

			ksRect tsrect( ( tile_type - ( TILE_PER_LINE * ( tile_type / TILE_PER_LINE ) ) ) * TILE_WIDTH,
						   ( tile_type / TILE_PER_LINE ) * TILE_HEIGHT,
							 TILE_WIDTH, TILE_HEIGHT );

			tsrect.x /= 2;
			tsrect.y /= 2;
			tsrect.w /= 2;
			tsrect.h /= 2;

			if ( tile_type >= 0 && tile_type < TILE_SPRITES )
			{
				sf::Vertex * quad = &m_map[ num * 4 ];

				quad[ 0 ].position = sf::Vector2f( cur_x, cur_y );
				quad[ 1 ].position = sf::Vector2f( ( cur_x + TILE_WIDTH ), cur_y );
				quad[ 2 ].position = sf::Vector2f( ( cur_x + TILE_WIDTH ), ( cur_y + TILE_HEIGHT ) );
				quad[ 3 ].position = sf::Vector2f( cur_x, ( cur_y + TILE_HEIGHT ) );

				quad[ 0 ].texCoords = sf::Vector2f( tsrect.x, tsrect.y );
				quad[ 1 ].texCoords = sf::Vector2f( tsrect.x + tsrect.w, tsrect.y );
				quad[ 2 ].texCoords = sf::Vector2f( tsrect.x + tsrect.w, tsrect.y + tsrect.h );
				quad[ 3 ].texCoords = sf::Vector2f( tsrect.x, tsrect.y + tsrect.h );
			}

			cur_x += TILE_WIDTH;
			
			if ( cur_x >= ( width * TILE_WIDTH ) )
			{
				cur_x = 0;
				cur_y += TILE_HEIGHT;
			}
		}
		
		map.close();
	}
	else
		std::cout << "Cannot find: " << filename << ".ks" << '\n';

	map.open( filename + "_evt.ks" );

	for ( int row = 0; row < m_rect.h; row++ )
		delete [] m_evt[ row ];

	delete [] m_evt;

	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = width;
	m_rect.h = height;
	
	if ( map.is_open() )
	{
		//m_evt.resize( height );
		m_evt = new int * [ height ];

		for ( int row = 0; row < height; row++ )
		{
			//m_evt[ row ].resize( width );
			m_evt[ row ] = new int [ width ];

			for ( int col = 0; col < width && !map.eof(); col++ )
				map >> m_evt[ row ][ col ];
		}

		map.close();
	}
	else
		std::cout << "Cannot find: " << filename << "_evt.ks" << '\n';
}

ksMap::~ksMap()
{
	for ( int row = 0; row < m_rect.h; row++ )
		delete [] m_evt[ row ];

	delete [] m_evt;
}

void ksMap::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	states.transform *= getTransform();
	states.texture = &m_text;
	target.draw( m_map, states );
}

ksRect & ksMap::getTileRect()
{
	return m_rect;
}

std::string & ksMap::getMapName()
{
	return m_map_name;
}

//std::vector<std::vector<int>> & ksMap::getEvents()
//{
//	return m_evt;
//}

int ** ksMap::getEvents()
{
	return m_evt;
}

int ksMap::getWidth()
{
	return m_rect.w;
}

int ksMap::getHeight()
{
	return m_rect.h;
}