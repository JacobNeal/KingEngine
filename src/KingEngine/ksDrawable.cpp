/*********************************************
* Class: ksDrawableLayer	-	for SFML
*
* Purpose:
*	This class is part of the base elements
*	of the engine, so this class needs to be
*	changed in the event of future ports of
*	KingEngine.
*
*********************************************/

#include "ksDrawable.h"
#include <iostream>

ksDrawable::ksDrawable(int size, sf::String texture)
{
	m_texture_available = (texture.getSize() > 0);

	if (m_texture_available)
	{
		if (!m_texture.loadFromFile(texture))
			std::cout << "ERROR: Couldn't load the tilesheet.\n";
	}

	m_array.setPrimitiveType(sf::Triangles);
	m_primitive_type = "quad";
	m_array.resize(size);
}

ksDrawable::ksDrawable(const ksDrawable & copy)
	: m_array(copy.m_array), m_texture(copy.m_texture), m_texture_available(copy.m_texture_available)
{
}

void ksDrawable::addVector2f(int position, double x, double y, ksColor color)
{
	m_array[position].position = sf::Vector2f(x, y);

	if (color != ksColor(0, 0, 0, 0))
		m_array[position].color = color;
}

void ksDrawable::addVector2f(int position, ksVector vector, ksColor color)
{
	m_array[position].position = sf::Vector2f(vector.x, vector.y);

	if (color != ksColor(0, 0, 0, 0))
		m_array[position].color = color;
}

void ksDrawable::addTextureCoordinates(int position, double x, double y)
{
	m_array[position].texCoords = sf::Vector2f(x, y);
}

bool ksDrawable::addTexture(sf::String texture)
{
	m_texture_available = m_texture.loadFromFile(texture);
	return m_texture_available;
}

void ksDrawable::setVertexColor(int position, ksColor color)
{
	m_array[position].color = color;
}

void ksDrawable::setPrimitiveType(sf::String primitive_type)
{
	if (primitive_type == "quad")
	{
		m_primitive_type = "quad";
	}
	//m_array.setPrimitiveType(sf::TrianglesStrip);
	else if (primitive_type == "triangle")
	{
		m_primitive_type = "triangle";
	}
	//m_array.setPrimitiveType(sf::Triangles);
}

void ksDrawable::resize(int size)
{
	m_array.resize(size);
}

void ksDrawable::clearLayer()
{
	m_array.clear();
}

void ksDrawable::setLayerPosition(ksVector position)
{
	setPosition(sf::Vector2f(position.x, position.y));
}

ksVector ksDrawable::getLayerPosition()
{
	return ksVector(getPosition().x, getPosition().y);
}

void ksDrawable::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (m_texture_available)
		states.texture = &m_texture;

	target.draw(m_array, states);
}