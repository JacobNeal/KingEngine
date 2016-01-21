/********************************************************
* Class:			ksEntityLayer
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksEntityLayer.cpp
********************************************************/

#include "ksEntityLayer.h"

/*********************************************************
*	ksEntityLayer(char * tilesheet)
*
*	Initialize the entity layer by loading the passed
*	tilesheet.
*********************************************************/
ksEntityLayer::ksEntityLayer(char * tilesheet)
	: m_num_of_entities(0), m_pressedEntity(nullptr)
{
	m_texture.loadFromFile(tilesheet);
	//if (!m_texture.loadFromFile(tilesheet))
		//ErrorReport.reportNewError("Couldn't load tilesheet.");
}

/*********************************************************
*	addEntity
*
*	Add a base game entity to the drawable layer.
*********************************************************/
void ksEntityLayer::addEntity(ksEntity * entity)
{
	m_array.setPrimitiveType(sf::Quads);
	m_array.resize((m_num_of_entities + 1) * 4);

	m_entities[m_num_of_entities] = entity;

	int   vec = m_num_of_entities * 4;
	float x   = (float) entity->getPosition().X;
	float y   = (float) entity->getPosition().Y;
	float w   = (float) entity->getTextureCoord().W;
	float h   = (float) entity->getTextureCoord().H;

	m_array[vec].position = sf::Vector2f(x, y);
	m_array[vec + 1].position = sf::Vector2f(x + w, y);
	m_array[vec + 2].position = sf::Vector2f(x + w, y + h);
	m_array[vec + 3].position = sf::Vector2f(x, y + h);

	x = (float) entity->getTextureCoord().X / 2;
	y = (float) entity->getTextureCoord().Y / 2;
	w = (float) entity->getTextureCoord().W / 2;
	h = (float) entity->getTextureCoord().H / 2;

	m_array[vec].texCoords     = sf::Vector2f(x, y);
	m_array[vec + 1].texCoords = sf::Vector2f(x + w, y);
	m_array[vec + 2].texCoords = sf::Vector2f(x + w, y + h);
	m_array[vec + 3].texCoords = sf::Vector2f(x, y + h);

	m_num_of_entities++;
}

/*********************************************************
*	animate
*
*	Set the lower and upper tile boundaries and frame
*	delay of an entity's animation.
*********************************************************/
void ksEntityLayer::animate(int entity_number, int lower_tile, int upper_tile, int frame_delay)
{
	m_entities[entity_number]->setAnimationLower(lower_tile);
	m_entities[entity_number]->setAnimationUpper(upper_tile);
	m_entities[entity_number]->setAnimationDelay(frame_delay);
}

/*********************************************************
*   pressEntity
*
*   Press the first entity that the mouse coordinates are
*   contained within.
*********************************************************/
bool ksEntityLayer::pressEntity(int mouse_x, int mouse_y)
{
	for (int count = 0; count < m_num_of_entities; ++count)
	{
		ksRect entity = m_entities[count]->getRect();

		if (mouse_x > entity.X &&
			mouse_x < (entity.X + entity.W) &&
			mouse_y >(entity.Y) &&
			mouse_y < (entity.Y + entity.H))
		{
			m_entities[count]->setPressed(true);
			m_pressedEntity = m_entities[count];
			return true;
		}
		else
			m_entities[count]->setPressed(false);
	}

	return false;
}

/*********************************************************
*   depressEntity
*
*   Set the pressed flag of the most recently pressed
*   entity to false.
*********************************************************/
void ksEntityLayer::depressEntity()
{
	if (m_pressedEntity != nullptr)
		m_pressedEntity->setPressed(false);
}

/*********************************************************
*	drawLayer
*
*	Draw the layer of base game entities.
*********************************************************/
void ksEntityLayer::drawLayer(sf::RenderWindow & app)
{
	for (unsigned int count = 0; count < m_entities.size(); ++count)
	{
		// Update each entities animation before drawing.
		m_entities[count]->animate();

		int   vec = count * 4;
		float x   = (float) m_entities[count]->getPosition().X;
		float y   = (float) m_entities[count]->getPosition().Y;
		float w   = (float) m_entities[count]->getTextureCoord().W;
		float h   = (float) m_entities[count]->getTextureCoord().H;

		m_array[vec].position     = sf::Vector2f(x, y);
		m_array[vec + 1].position = sf::Vector2f(x + w, y);
		m_array[vec + 2].position = sf::Vector2f(x + w, y + h);
		m_array[vec + 3].position = sf::Vector2f(x, y + h);

		x = (float) m_entities[count]->getTextureCoord().X / 2;
		y = (float) m_entities[count]->getTextureCoord().Y / 2;
		w = (float) m_entities[count]->getTextureCoord().W / 2;
		h = (float) m_entities[count]->getTextureCoord().H / 2;

		m_array[vec].texCoords     = sf::Vector2f(x, y);
		m_array[vec + 1].texCoords = sf::Vector2f(x + w, y);
		m_array[vec + 2].texCoords = sf::Vector2f(x + w, y + h);
		m_array[vec + 3].texCoords = sf::Vector2f(x, y + h);
	}

	app.draw(*this);
}

/*********************************************************
*	drawLayer
*
*	The overloaded SFML pure virtual method for drawing
*	an sf::Drawable type.
*********************************************************/
void ksEntityLayer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_array, states);
}

/*********************************************************
*	purge
*
*	Empty the entity layer of all base game entities.
*********************************************************/
void ksEntityLayer::purge()
{
	m_array.clear();
	m_entities.clear();
	m_num_of_entities = 0;
}

/*********************************************************
*	setTilesheet
*
*	Set the tilesheet for all base game entities.
*********************************************************/
bool ksEntityLayer::setTilesheet(char * tilesheet)
{
	return m_texture.loadFromFile(tilesheet);
}

/*********************************************************
*   getRect
*
*   Return the rectangle (x, y, width, height), of a
*   particular base game entity.
*********************************************************/
ksRect ksEntityLayer::getRect(int entity_number)
{
	ksRect rect;

	rect.X = m_entities[entity_number]->getPosition().X;
	rect.Y = m_entities[entity_number]->getPosition().Y;
	rect.W = m_entities[entity_number]->getTextureCoord().W;
	rect.H = m_entities[entity_number]->getTextureCoord().H;

	return rect;
}

/*********************************************************
*   getCount
*
*   Return the total number of base game entities.
*********************************************************/
int ksEntityLayer::getCount()
{
	return m_num_of_entities;
}
