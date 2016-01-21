/********************************************************
* Class:            ksLabel
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksLabel.cpp
********************************************************/

#include "ksLabel.h"

/********************************************************
*   ksLabel
*
*   Intitializes the label class by setting the text of
*   the label and it's position to the passed values.
********************************************************/
ksLabel::ksLabel(std::string str, double x, double y)
    : m_position(x, y), m_string(str), m_pressed(false), m_visible(true)
{ }

/********************************************************
*   update
*
*   Updates the state of the label control.
********************************************************/
void ksLabel::update()
{
    // Update here.
}

/********************************************************
*   move
*
*   Move the label control relative to it's current
*   position.
********************************************************/
void ksLabel::move(double x, double y)
{
    for (int count = 0; count < m_array.getVertexCount(); ++count)
    {
        m_array[count].position.x += x;
        m_array[count].position.y += y;
    }
}

/********************************************************
*   getVertexArray
*
*   Returns the Vertex Array of the drawable control.
********************************************************/
sf::VertexArray * ksLabel::getVertexArray()
{
    return &m_array;
}
