/********************************************************
* Class:			ksEntityLayer
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksEntityLayer.cpp
********************************************************/

#include "ksEntityLayer.h"
#include <iostream>

/*********************************************************
*	ksEntityLayer(char * tilesheet)
*
*	Initialize the entity layer by loading the passed
*	tilesheet.
*********************************************************/
ksEntityLayer::ksEntityLayer(ksWorld * world, std::string tilesheet)
	: m_world(world), m_num_of_entities(0), m_pressedEntity(nullptr)
{
	m_texture.loadFromFile(tilesheet);
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
        ksPathNode entity = m_entities[count]->getTilePosition();

		if (mouse_x > entity.TL.X &&
			mouse_x < entity.TR.X &&
			mouse_y > entity.TL.Y &&
			mouse_y < entity.BL.Y)
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
    // Sort the entities before drawing.
    sortEntitiesByRow();

	for (unsigned int count = 0; count < m_entities.size(); ++count)
	{
        if (m_entities[count]->isVisible())
        {
            // Update each entities animation before drawing.
		    m_entities[count]->animate();

            ksPathNode tile = m_entities[count]->getTilePosition();

		    int vec  = count * 4;

    		m_array[vec].position     = sf::Vector2f(tile.TL.X, tile.TL.Y);
	    	m_array[vec + 1].position = sf::Vector2f(tile.TR.X, tile.TR.Y);
		    m_array[vec + 2].position = sf::Vector2f(tile.BR.X, tile.BR.Y);
		    m_array[vec + 3].position = sf::Vector2f(tile.BL.X, tile.BL.Y);

		    float x = (float) m_entities[count]->getTextureCoord().X / 2;
		    float y = (float) m_entities[count]->getTextureCoord().Y / 2;
		    float w = (float) m_entities[count]->getTextureCoord().W / 2;
		    float h = (float) m_entities[count]->getTextureCoord().H / 2;

		    m_array[vec].texCoords     = sf::Vector2f(x, y);
		    m_array[vec + 1].texCoords = sf::Vector2f(x + w, y);
		    m_array[vec + 2].texCoords = sf::Vector2f(x + w, y + h);
		    m_array[vec + 3].texCoords = sf::Vector2f(x, y + h);

            sf::Color color = sf::Color(255, 255, 255);

            m_array[vec].color     = color;
            m_array[vec + 1].color = color;
            m_array[vec + 2].color = color;
            m_array[vec + 3].color = color;
        }
    }

	app.draw(*this);
}

/*********************************************************
*	draw
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

void ksEntityLayer::sortEntitiesByRow()
{
    for (int count = 0; count < m_num_of_entities; ++count)
    {
        for (int count2 = 0; count2 < m_num_of_entities - count - 1; ++count2)
        {
            if (//m_entities[count2]->getWall() == m_entities[count2 + 1]->getWall() &&
                m_entities[count2]->getTilePosition().BL.Y > m_entities[count2 + 1]->getTilePosition().BL.Y)
            {
                ksEntity * temp        = m_entities[count2];
                m_entities[count2]     = m_entities[count2 + 1];
                m_entities[count2 + 1] = temp;
            }
        }
    }
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
bool ksEntityLayer::setTilesheet(std::string tilesheet)
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

	rect.X = m_entities[entity_number]->getTilePosition().TR.X;
	rect.Y = m_entities[entity_number]->getTilePosition().TR.Y;
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
