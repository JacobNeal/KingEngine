#include "ksMap.h"

ksMap::ksMap(sf::Text * debugText, sf::String tilesheet, sf::String filename, int width, int height)
	: m_rect(0, 0, width, height)
{
	m_evt = new int *[height];

	for (int row = 0; row < height; row++)
		m_evt[row] = new int[width];

	m_debugText = debugText;

	//load(tilesheet, filename, width, height);
}

void ksMap::load(sf::String tilesheet, sf::String filename, int width, int height)
{
	ksFile map(m_debugText, filename + ".ks");
	m_map_name = filename;

	int tile_type = -1;
	int cur_x = 0;
	int cur_y = 0;

	m_debugText->setString(m_debugText->getString() + "ksMap loading...\n");

	if (addTexture(tilesheet))
		m_debugText->setString(m_debugText->getString() + "ksMap loaded tilesheet.\n");
	else
		m_debugText->setString(m_debugText->getString() + "ksMap failed to load tilesheet.\n");

	setPrimitiveType("quad");
	resize(width * height * 6);

	for (int num = 0; num < (width * height) && !map.endOfFile(); ++num)
	{
		tile_type = map.readInt();

		ksRect tsrect((tile_type - (TILE_PER_LINE * (tile_type / TILE_PER_LINE))) * TILE_WIDTH,
			(tile_type / TILE_PER_LINE) * TILE_HEIGHT,
			TILE_WIDTH, TILE_HEIGHT);

		tsrect.x /= 2;
		tsrect.y /= 2;
		tsrect.w /= 2;
		tsrect.h /= 2;

		if (tile_type >= 0 && tile_type < TILE_SPRITES)
		{
			addVector2f((num * 6), cur_x, cur_y);
			addVector2f((num * 6) + 1, (cur_x + TILE_WIDTH), cur_y);
			addVector2f((num * 6) + 2, (cur_x + TILE_WIDTH), (cur_y + TILE_HEIGHT));
			addVector2f((num * 6) + 3, cur_x, (cur_y + TILE_HEIGHT));
			addVector2f((num * 6) + 4, cur_x, cur_y);
			addVector2f((num * 6) + 5, (cur_x + TILE_WIDTH), (cur_y + TILE_HEIGHT));

			addTextureCoordinates((num * 6), tsrect.x, tsrect.y);
			addTextureCoordinates((num * 6) + 1, tsrect.x + tsrect.w, tsrect.y);
			addTextureCoordinates((num * 6) + 2, tsrect.x + tsrect.w, tsrect.y + tsrect.h);
			addTextureCoordinates((num * 6) + 3, tsrect.x, tsrect.y + tsrect.h);
			addTextureCoordinates((num * 6) + 4, tsrect.x, tsrect.y);
			addTextureCoordinates((num * 6) + 5, tsrect.x + tsrect.w, tsrect.y + tsrect.h);
		}

		cur_x += TILE_WIDTH;

		if (cur_x >= (width * TILE_WIDTH))
		{
			cur_x = 0;
			cur_y += TILE_HEIGHT;
		}
	}

	map.readFile(filename + "_evt.ks");

	for (int row = 0; row < m_rect.h; row++)
		delete[] m_evt[row];

	delete[] m_evt;

	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = width;
	m_rect.h = height;

	m_evt = new int *[height];

	for (int row = 0; row < height; row++)
	{
		m_evt[row] = new int[width];

		for (int col = 0; col < width && !map.endOfFile(); col++)
			m_evt[row][col] = map.readInt();
	}
}

ksMap::~ksMap()
{
	for (int row = 0; row < m_rect.h; row++)
		delete[] m_evt[row];

	delete[] m_evt;
}

ksRect & ksMap::getTileRect()
{
	return m_rect;
}

sf::String & ksMap::getMapName()
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