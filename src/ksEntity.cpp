/********************************************************
* Class:			ksEntity
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksEntity.cpp
********************************************************/

#include "ksEntity.h"

/*********************************************************
*	ksEntity
*
*	Initialize entity to the position, width, height and 
*	current tile passed.
*********************************************************/
ksEntity::ksEntity(double x, double y, double w, double h, int current_tile)
    : m_position(x, y), m_current_tile(current_tile), m_frame(0),
      m_anim_delay(1), m_lower_tile(current_tile), m_upper_tile(current_tile),
	  m_pressed(false), m_visible(true)
{
	m_texture_coord.X = (current_tile - (TILE_PER_LINE * (current_tile / TILE_PER_LINE))) * w;
	m_texture_coord.Y = (current_tile / TILE_PER_LINE) * h;
	m_texture_coord.W = w;
	m_texture_coord.H = h;
}

/*********************************************************
*	ksEntity
*
*	Initialize entity to the position rectangle and
*	current tile passed.
*********************************************************/
ksEntity::ksEntity(ksRect position, int current_tile)
    : m_position(position.X, position.Y), m_current_tile(current_tile),
      m_frame(0), m_anim_delay(1), m_lower_tile(current_tile), m_upper_tile(current_tile),
	  m_pressed(false), m_visible(true)
{
	m_texture_coord.X = (current_tile - (TILE_PER_LINE * (current_tile / TILE_PER_LINE)) * position.W);
	m_texture_coord.Y = (current_tile / TILE_PER_LINE) * position.H;
	m_texture_coord.W = position.W;
	m_texture_coord.H = position.H;
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
}

/*********************************************************
*	move
*
*	Update the position of the entity by adding the passed
*	x and y values to it's current position.
*********************************************************/
void ksEntity::move(double x, double y)
{
	m_position.X += x;
	m_position.Y += y;
}

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
*	setPosition
*
*	Set the position of the entity to the x and y passed.
*********************************************************/
void ksEntity::setPosition(double x, double y)
{
	m_position.X = x;
	m_position.Y = y;
}

/*********************************************************
*	setPosition
*
*	Set the position of the entity to the 2D vector passed.
*********************************************************/
void ksEntity::setPosition(const ksVector2D & position)
{
	m_position.X = position.X;
	m_position.Y = position.Y;
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
*	getPosition
*
*	Returns the position of the entity in vector form.
*********************************************************/
const ksVector2D & ksEntity::getPosition()
{
	return m_position;
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

/*********************************************************
*   getRect
*
*   Returns a rectangle (x, y, width, height) for the base
*   game entity
*********************************************************/
ksRect ksEntity::getRect()
{
	ksRect rect;

	rect.X = m_position.X;
	rect.Y = m_position.Y;
	rect.W = m_texture_coord.W;
	rect.H = m_texture_coord.H;

	return rect;
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