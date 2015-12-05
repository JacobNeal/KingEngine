#ifndef KS_MAP_H
#define KS_MAP_H

#include <iostream>
#include "ksDrawable.h"
#include "ksRect.h"
#include "ksFile.h"
#include "ksTile.h"

class ksMap : public ksDrawable
{
public:
	ksMap(sf::Text * debugText, sf::String tilesheet, sf::String filename, int width, int height);
	void load(sf::String tilesheet, sf::String filename, int width, int height);

	~ksMap();
	//std::vector<std::vector<int>> & getEvents();
	int ** getEvents();
	ksRect & getTileRect();
	sf::String & getMapName();

	int getWidth();
	int getHeight();

private:
	sf::String m_map_name;
	ksRect m_rect;
	int ** m_evt;

	sf::Text * m_debugText;
};

#endif