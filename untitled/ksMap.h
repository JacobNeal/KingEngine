#ifndef KS_MAP_H
#define KS_MAP_H

#include "cArray2D.h"
#include "ksTile.h"

class ksMap : public sf::Drawable, public sf::Transformable
{
	public:
		ksMap( std::string tilesheet, std::string filename, int width, int height );
		void load( std::string tilesheet, std::string filename, int width, int height );
		
		~ksMap();
		virtual void draw( sf::RenderTarget & target, sf::RenderStates states ) const;
		//std::vector<std::vector<int>> & getEvents();
		int ** getEvents();
		ksRect & getTileRect();
		std::string & getMapName();

		int getWidth();
		int getHeight();

	private:
		sf::VertexArray m_map;
		sf::Texture m_text;
		std::string m_map_name;
		ksRect m_rect;
		//cArray2D<int> m_evt;
		//std::vector<std::vector<int>> m_evt;
		int ** m_evt;
};

#endif