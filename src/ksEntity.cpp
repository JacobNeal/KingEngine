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
ksEntity::ksEntity(ksWorld * world, ksWorldWall wall, int row, int col, int w, int h, int current_tile)
    : m_world(world), m_wall(wall), m_width(w), m_height(h), m_current_tile(current_tile), m_frame(0), 
      m_anim_delay(1), m_lower_tile(current_tile), m_upper_tile(current_tile),
	  m_pressed(false), m_visible(true)
{
	m_texture_coord.X = (current_tile - (TILE_PER_LINE * (current_tile / TILE_PER_LINE))) * (w * TILE_WIDTH);
	m_texture_coord.Y = (current_tile / TILE_PER_LINE) * (h * TILE_HEIGHT);
	m_texture_coord.W = (w * TILE_WIDTH);
	m_texture_coord.H = (h * TILE_HEIGHT);
    
    ksTile temp = world->getTilePosition(wall, row, col, w, h);

    m_current_node.row = row;
    m_current_node.col = col;
    m_current_node.TL  = temp.TL;
    m_current_node.TR  = temp.TR;
    m_current_node.BL  = temp.BL;
    m_current_node.BR  = temp.BR;
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

void ksEntity::setTilePosition(ksPathNode node)
{
    m_current_node = node;
}

void ksEntity::setWall(ksWorldWall wall)
{
    m_wall = wall;
    
    ksTile temp = m_world->getTilePosition(m_wall, m_current_node.row,
                                         m_current_node.col, m_width, m_height);

    m_current_node.TL  = temp.TL;
    m_current_node.TR  = temp.TR;
    m_current_node.BL  = temp.BL;
    m_current_node.BR  = temp.BR;
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
    return m_width;
}

/********************************************************
*   getHeight
*
*   Returns the height in tiles of the entity.
********************************************************/
int ksEntity::getHeight()
{
    return m_height;
}

/********************************************************
*   getRow
*
*   Returns the row that the entity is on. 
********************************************************/
int ksEntity::getRow()
{
    return m_current_node.row;
}

/********************************************************
*   getColumn
*
*   Returns the column that the entity is on.
********************************************************/
int ksEntity::getColumn()
{
    return m_current_node.col;
}

/********************************************************
*   getWall
*
*   Returns the enum for the wall type to determine
*   which wall the entity is on and how to use the row 
*   and column members.
********************************************************/
ksWorldWall ksEntity::getWall()
{
    return m_wall;
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
