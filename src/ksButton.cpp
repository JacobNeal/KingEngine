/********************************************************
* Class:            ksButton
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksButton.cpp
********************************************************/

#include "ksButton.h"

/********************************************************
*   ksButton
*
*   Initializes the button class by setting the position
*   of the control to the passed x and y.
********************************************************/
ksButton::ksButton(double x, double y)
    : m_position(x, y), m_width(96.0), m_height(32.0), m_pressed(false), m_visible(true)
{
    m_array.setPrimitiveType(sf::Quads);

    m_array.append(sf::Vertex(sf::Vector2f(x - BUTTON_SHADOW_OFFSET,
                                           y + BUTTON_SHADOW_OFFSET), 
                                           sf::Color(50, 50, 50)));
    m_array.append(sf::Vertex(sf::Vector2f(x - BUTTON_SHADOW_OFFSET + m_width, 
                                           y + BUTTON_SHADOW_OFFSET),
                                           sf::Color(50, 50, 50)));
    m_array.append(sf::Vertex(sf::Vector2f(x - BUTTON_SHADOW_OFFSET + m_width,
                                           y + BUTTON_SHADOW_OFFSET + m_height),
                                           sf::Color(50, 50, 50)));
    m_array.append(sf::Vertex(sf::Vector2f(x - BUTTON_SHADOW_OFFSET,
                                           y + BUTTON_SHADOW_OFFSET + m_height),
                                           sf::Color(50, 50, 50)));

    m_array.append(sf::Vertex(sf::Vector2f(x, y), sf::Color(100, 100, 100)));
    m_array.append(sf::Vertex(sf::Vector2f(x + m_width, y), sf::Color(100, 100, 100)));
    m_array.append(sf::Vertex(sf::Vector2f(x + m_width, y + m_height), sf::Color(100, 100, 100)));
    m_array.append(sf::Vertex(sf::Vector2f(x, y + m_height), sf::Color(100, 100, 100)));
}

/********************************************************
*   update
*
*   Updates the current state / animation of the button.
********************************************************/
void ksButton::update()
{
    // Update here.
}

/********************************************************
*   move
*
*   Move all the vertices inside of this control by
*   the x and y modifiers passed.
********************************************************/
void ksButton::move(double x, double y)
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
*   Returns the Vertex Array that defines the color,
*   position and texture coordinates of this control.
********************************************************/
sf::VertexArray * ksButton::getVertexArray()
{
    return &m_array;
}

/********************************************************
*   pressed
*
*   Returns whether or not the button is pressed within
*   the given mouse coordinates.
********************************************************/
bool ksButton::pressed(int mouse_x, int mouse_y)
{
    if (mouse_x >= m_position.X &&
        mouse_y >= m_position.Y &&
        mouse_x <= (m_position.X + m_width) &&
        mouse_y <= (m_position.Y + m_height))
    {
        m_pressed = true;

        // Invert colors of button (pop effect)
        for (int count = 0; count < 4; ++count)
            m_array[count].color = sf::Color(100, 100, 100);

        for (int count = 4; count < 8; ++count)
            m_array[count].color = sf::Color(50, 50, 50);
    }
    
    return m_pressed;
}

/********************************************************
*   isPressed
*
*   Returns whether or not the button is pressed.
********************************************************/
bool ksButton::isPressed()
{
    return m_pressed;
}

/********************************************************
*   setPressed
*
*   Sets whether or not the button is pressed.
*   (this can allow for a button to be depressed)
********************************************************/
void ksButton::setPressed(bool pressed)
{
    m_pressed = pressed;
    
    // Invert colors of button (pop effect)
    popEffect();
}

/********************************************************
*   popEffect
*
*   Inverts the colors of the rectangle of the button
*   with it's shadow to give a 'pop effect'.
********************************************************/
void ksButton::popEffect()
{
    if (!m_pressed)
    {
        for (int count = 0; count < 4; ++count)
            m_array[count].color = sf::Color(50, 50, 50);

        for (int count = 4; count < 8; ++count)
            m_array[count].color = sf::Color(100, 100, 100);
    }
    else
    {
        for (int count = 0; count < 4; ++count)
            m_array[count].color = sf::Color(100, 100, 100);
        
        for (int count = 4; count < 8; ++count)
            m_array[count].color = sf::Color(50, 50, 50);
    }
}
