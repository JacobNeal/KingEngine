////////////////////////////////////////////////////////////
//
// KingEngine
// The MIT License (MIT)
// Copyright (c) 2016 Beyond Parallel
//
// Permission is hereby granted, free of charge, to any person 
// obtaining a copy of this software and associated documentation 
// files (the "Software"), to deal in the Software without restriction, 
// including without limitation the rights to use, copy, modify, merge, 
// publish, distribute, sublicense, and/or sell copies of the Software, 
// and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be 
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ksEntity.h"
#include <iostream>

////////////////////////////////////////////////////////////
ksEntity::ksEntity(ksWorld * world, int x, int y, int z, int w, int h, 
        int current_tile)
    : m_world(world), m_current_tile(current_tile), 
      m_upper_tile(current_tile), m_lower_tile(current_tile), 
      m_anim_delay(1), m_frame(0), m_pressed(false), m_visible(true),
      m_x(x), m_y(y), m_z(z), m_w(w), m_h(h)
{
	m_texture_coord.X = (current_tile - (TILE_PER_LINE * (current_tile / TILE_PER_LINE))) * (w * TILE_WIDTH);
	m_texture_coord.Y = (current_tile / TILE_PER_LINE) * (h * TILE_WIDTH);
	m_texture_coord.W = (w * TILE_WIDTH);
	m_texture_coord.H = (h * TILE_HEIGHT);
    
    m_current_node.row = 0;
    m_current_node.col = 0;
    
    // Transform the 3D world position into screen coordinates.
    sf::Vector2f TL = m_world->transform3DWithPixelValue(m_x, m_y, m_z);
    sf::Vector2f TR = m_world->transform3DWithPixelValue(m_x + (((double) m_w / m_world->getMapCol()) * m_world->getWidth()), m_y, m_z);
    sf::Vector2f BR = m_world->transform3DWithPixelValue(m_x + (((double) m_w / m_world->getMapCol()) * m_world->getWidth()), 
        m_y + (((double) m_h / m_world->getMapRow()) * m_world->getHeight()), m_z);
    sf::Vector2f BL = m_world->transform3DWithPixelValue(m_x, m_y + (((double) m_h / m_world->getMapRow()) * m_world->getHeight()), m_z);
    
    // Set the current path node to the screen coordinates.
    m_current_node.TL = ksVector2D(TL.x, TL.y);
    m_current_node.TR = ksVector2D(TR.x, TR.y);
    m_current_node.BR = ksVector2D(BR.x, BR.y);
    m_current_node.BL = ksVector2D(BL.x, BL.y);
}

////////////////////////////////////////////////////////////
void ksEntity::animate()
{
	if (m_current_tile < m_lower_tile || m_current_tile > m_upper_tile)
	{
		m_frame = 1;
		m_current_tile = m_lower_tile;

		m_texture_coord.X = (m_current_tile - (TILE_PER_LINE * (m_current_tile / TILE_PER_LINE))) * m_texture_coord.W;
		m_texture_coord.Y = (m_current_tile / TILE_PER_LINE) * m_texture_coord.H;
	}
	else if (m_frame % m_anim_delay == 0)
	{
		if (m_current_tile == m_upper_tile)
			m_current_tile = m_lower_tile;
		else
			++m_current_tile;

		m_texture_coord.X = (m_current_tile - (TILE_PER_LINE * (m_current_tile / TILE_PER_LINE))) * m_texture_coord.W;
		m_texture_coord.Y = (m_current_tile / TILE_PER_LINE) * m_texture_coord.H;
	}
	++m_frame;
}

////////////////////////////////////////////////////////////
void ksEntity::update()
{ }

////////////////////////////////////////////////////////////
void ksEntity::setAnimationLower(int lower_tile)
{
	m_lower_tile = lower_tile;
}

////////////////////////////////////////////////////////////
void ksEntity::setAnimationUpper(int upper_tile)
{
	m_upper_tile = upper_tile;
}

////////////////////////////////////////////////////////////
void ksEntity::setAnimationDelay(int frame_delay)
{
	m_anim_delay = frame_delay;
}

////////////////////////////////////////////////////////////
void ksEntity::setPressed(bool pressed)
{
	m_pressed = pressed;
}

////////////////////////////////////////////////////////////
void ksEntity::setVisible(bool visible)
{
	m_visible = visible;
}

////////////////////////////////////////////////////////////
void ksEntity::setTilePosition(ksPathNode node)
{
    m_current_node = node;
}

////////////////////////////////////////////////////////////
const ksPathNode & ksEntity::getTilePosition()
{
	return m_current_node;
}

////////////////////////////////////////////////////////////
const ksRect & ksEntity::getTextureCoord()
{
	return m_texture_coord;
}

////////////////////////////////////////////////////////////
int ksEntity::getWidth()
{
    return m_w;
}

////////////////////////////////////////////////////////////
int ksEntity::getHeight()
{
    return m_h;
}

////////////////////////////////////////////////////////////
bool ksEntity::isPressed()
{
	return m_pressed;
}

////////////////////////////////////////////////////////////
bool ksEntity::isVisible()
{
	return m_visible;
}

////////////////////////////////////////////////////////////
int ksEntity::X()
{
    return m_x;
}

////////////////////////////////////////////////////////////
int ksEntity::Y()
{
    return m_y;
}

////////////////////////////////////////////////////////////
int ksEntity::Z()
{
    return m_z;
}

////////////////////////////////////////////////////////////
void ksEntity::moveEntity(int x, int y, int z)
{
    m_x += x;
    m_y += y;
    m_z += z;
    
    updateScreenPosition();
}

////////////////////////////////////////////////////////////
void ksEntity::updateScreenPosition()
{
    // Transform the 3D world position into screen coordinates.
    sf::Vector2f TL = m_world->transform3DWithPixelValue(m_x, m_y, m_z);
    sf::Vector2f TR = m_world->transform3DWithPixelValue(m_x + (((double) m_w / m_world->getMapCol()) * m_world->getWidth()), m_y, m_z);
    sf::Vector2f BR = m_world->transform3DWithPixelValue(m_x + (((double) m_w / m_world->getMapCol()) * m_world->getWidth()), 
        m_y + (((double) m_h / m_world->getMapRow()) * m_world->getHeight()), m_z);
    sf::Vector2f BL = m_world->transform3DWithPixelValue(m_x, m_y + (((double) m_h / m_world->getMapRow()) * m_world->getHeight()), m_z);
    
    // Set the current path node to the screen coordinates.
    m_current_node.TL = ksVector2D(TL.x, TL.y);
    m_current_node.TR = ksVector2D(TR.x, TR.y);
    m_current_node.BR = ksVector2D(BR.x, BR.y);
    m_current_node.BL = ksVector2D(BL.x, BL.y);
}