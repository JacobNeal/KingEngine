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

#ifndef KS_DRAWABLE_H
#define KS_DRAWABLE_H

#include <SFML/Graphics.hpp>
#include "ksColor.h"
#include "ksVector.h"

class ksDrawable : public sf::Drawable, public sf::Transformable
{
public:
	ksDrawable(int size = 0, sf::String texture = "");

	ksDrawable(const ksDrawable & copy);

	// Include the ability to set a color for a vertex.
	void addVector2f(int position, double x, double y, ksColor color = ksColor(0, 0, 0, 0));
	void addVector2f(int position, ksVector vector, ksColor color = ksColor(0, 0, 0, 0));

	// If the layer is using a texture you can set the coordinates
	// that'll be read off the image at each position in the vertex array.
	void addTextureCoordinates(int position, double x, double y);

	bool addTexture(sf::String texture);

	void setVertexColor(int position, ksColor color);

	void setPrimitiveType(sf::String primitive_type);

	// Resize the vertex array.
	void resize(int size);

	// Clear the vertex array.
	void clearLayer();

	void setLayerPosition(ksVector position);
	ksVector getLayerPosition();

	// Inherited from SFML types for sf::Drawable.
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

protected:
	sf::VertexArray m_array;
	sf::Texture		m_texture;
	bool			m_texture_available;
	std::string		m_primitive_type;
};

#endif