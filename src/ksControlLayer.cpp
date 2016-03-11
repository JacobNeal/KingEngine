/********************************************************
* Class:            ksControlLayer
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksControlLayer.cpp
********************************************************/

#include "ksControlLayer.h"

/********************************************************
*   ksControl
*
*   Initialize the control and set the texture to the
*   path of the tilesheet that was passed.
********************************************************/
ksControlLayer::ksControlLayer(std::string tilesheet)
    : m_num_of_controls(0), m_pressedControl(nullptr)
{
   m_texture.loadFromFile(tilesheet);
   m_array.setPrimitiveType(sf::Quads);
}

/********************************************************
*   addControl
*
*   Adding a drawable control to the layer  of controls 
*   to be drawn.
********************************************************/
void ksControlLayer::addControl(ksControl * control)
{
    m_controls[m_num_of_controls] = control;
    ++m_num_of_controls;
}

/********************************************************
*   drawLayer
*
*   Draw the layer of controls to screen using the render
*   window that was passed.
********************************************************/
void ksControlLayer::drawLayer(sf::RenderWindow & app)
{
    for (int count = 0; count < m_num_of_controls; ++count)
    {
        sf::VertexArray * temp = m_controls[count]->getVertexArray();

        for (int vertex_count = 0; 
                 vertex_count < temp->getVertexCount(); 
                 ++vertex_count)
            m_array.append((*temp)[vertex_count]);
    }

    app.draw(*this);
}

/********************************************************
*   draw
*
*   Override the default behavior for drawing objects
*   in SFML.
********************************************************/
void ksControlLayer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
//    states.texture = &m_texture;
    target.draw(m_array, states);
}

/********************************************************
*   pressControl
*
*   Returns whether or not one of the controls is
*   pressed based on the passed mouse coordinates.
********************************************************/
bool ksControlLayer::pressControl(int mouse_x, int mouse_y)
{
    for (int count = 0; count < m_num_of_controls; ++count)
    {
        if (m_controls[count]->pressed(mouse_x, mouse_y))
        {
            m_pressedControl = m_controls[count];
            return true;
        }
    }

    return false;
}

/********************************************************
*   depressControl
*
*   Set the pressed flag of the most recently pressed
*   control to false.
********************************************************/
void ksControlLayer::depressControl()
{
    if (m_pressedControl != nullptr)
        m_pressedControl->setPressed(false);
}

/********************************************************
*   purge
*
*   Remove all the drawable controls in the Control Layer.
********************************************************/

void ksControlLayer::purge()
{
    m_array.clear();
}

/********************************************************
*   setTilesheet
*
*   Change the tilesheet that all the controls in the
*   layer will use.
********************************************************/
bool ksControlLayer::setTilesheet(std::string tilesheet)
{
    return m_texture.loadFromFile(tilesheet);
}

/********************************************************
*   getCount
*
*   Return the number of controls in this layer.
********************************************************/
int ksControlLayer::getCount()
{
    return m_num_of_controls;
}










