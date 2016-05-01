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
	m_texture_coord.X = (current_tile - (TILE_PER_LINE * (current_tile / TILE_PER_LINE))) * w;
	m_texture_coord.Y = (current_tile / TILE_PER_LINE) * h;
	m_texture_coord.W = w;
	m_texture_coord.H = h;
    
    m_current_node.row = 0;
    m_current_node.col = 0;
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
