/********************************************************
* Class:			ksEntity
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksEntity.cpp
********************************************************/

#include "ksEntity.h"
#include <iostream>

/*********************************************************
*	ksEntity
*
*	Initialize entity to the position, width, height and 
*	current tile passed.
*********************************************************/
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

/*********************************************************
*	animate
*
*	Animate the entity between the lower and upper tile
*	bounds with the given animation delay (in frames).
*********************************************************/
void ksEntity::animate()
{
	if (m_current_tile < m_lower_tile || m_current_tile > m_upper_tile)
	{
		m_frame = 1;
		m_current_tile = m_lower_tile;

		m_texture_coord.X = (m_current_tile - (TILE_PER_LINE * (m_current_tile / TILE_PER_LINE))) * (m_texture_coord.W * TILE_WIDTH);
		m_texture_coord.Y = (m_current_tile / TILE_PER_LINE) * (m_texture_coord.H * TILE_WIDTH);
	}
	else if (m_frame % m_anim_delay == 0)
	{
		if (m_current_tile == m_upper_tile)
			m_current_tile = m_lower_tile;
		else
			++m_current_tile;

		m_texture_coord.X = (m_current_tile - (TILE_PER_LINE * (m_current_tile / TILE_PER_LINE))) * (m_texture_coord.W * TILE_WIDTH);
		m_texture_coord.Y = (m_current_tile / TILE_PER_LINE) * (m_texture_coord.H * TILE_WIDTH);
	}
	++m_frame;

    update();
}

/********************************************************
*   update
*
*   Call the frame by frame update method. This method
*   should be overridden in any derived classes.
********************************************************/
void ksEntity::update()
{ }

/*********************************************************
*	setAnimationLow
*
*	Set the lower tile boundary for the animation of the
*	entity.
*********************************************************/
void ksEntity::setAnimationLower(int lower_tile)
{
	m_lower_tile = lower_tile;
}

/*********************************************************
*	setAnimationUpper
*
*	Set the upper tile boundary for the animation of the
*	entity.
*********************************************************/
void ksEntity::setAnimationUpper(int upper_tile)
{
	m_upper_tile = upper_tile;
}

/*********************************************************
*	setAnimationDelay
*
*	Set the animation delay (in frames).
*********************************************************/
void ksEntity::setAnimationDelay(int frame_delay)
{
	m_anim_delay = frame_delay;
}

/*********************************************************
*	setPressed
*
*	Set whether or not the entity is being pressed.
*********************************************************/
void ksEntity::setPressed(bool pressed)
{
	m_pressed = pressed;
}

/*********************************************************
*	setVisible
*
*	Set the visibility of the entity.
*********************************************************/
void ksEntity::setVisible(bool visible)
{
	m_visible = visible;
}

/*********************************************************
*   setTilePosition
*
*   Set the position of the entity to the passed path node.
*********************************************************/
void ksEntity::setTilePosition(ksPathNode node)
{
    m_current_node = node;
}

/*********************************************************
*	getPosition
*
*	Returns the position of the entity in vector form.
*********************************************************/
const ksPathNode & ksEntity::getTilePosition()
{
	return m_current_node;
}

/*********************************************************
*	getTextureCoord
*
*	Returns the texture coordinates of the entity.
*********************************************************/
const ksRect & ksEntity::getTextureCoord()
{
	return m_texture_coord;
}

/********************************************************
*   getWidth
*
*   Returns the width in tiles of the entity.
********************************************************/
int ksEntity::getWidth()
{
    return m_w;
}

/********************************************************
*   getHeight
*
*   Returns the height in tiles of the entity.
********************************************************/
int ksEntity::getHeight()
{
    return m_h;
}

/*********************************************************
*	isPressed
*
*	Returns whether or not the entity is being pressed.
*********************************************************/
bool ksEntity::isPressed()
{
	return m_pressed;
}

/*********************************************************
*	isVisible
*
*	Returns whether or not the entity is visible.
*********************************************************/
bool ksEntity::isVisible()
{
	return m_visible;
}

int ksEntity::X()
{
    return m_x;
}

int ksEntity::Y()
{
    return m_y;
}

int ksEntity::Z()
{
    return m_z;
}

void ksEntity::moveEntity(int x, int y, int z)
{
    m_x += x;
    m_y += y;
    m_z += z;
    
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