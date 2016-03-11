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
//ksButton::ksButton(sf::Font * font, std::string text, double x, double y)
ksButton::ksButton(double x, double y, std::string text, double w, double h)
    : /*m_text(text, font, 12),*/ m_position(x, y), m_width(96.0), m_height(32.0), 
    m_pressed(false)
{
    m_array.setPrimitiveType(sf::Triangles);

    double top_left_x     = x - (w / 2);
    double top_left_y     = y - (h / 2);

    double top_right_x    = x + (w / 2);
    double top_right_y    = top_left_y;

    double bottom_right_x = top_right_x;
    double bottom_right_y = y + (h / 2);

    double bottom_left_x  = top_left_x;
    double bottom_left_y  = bottom_right_y;

    double border_width   = 5;
    double border_radius  = w * 0.05;

    sf::Vector2f points[16];
    sf::Color color(0, 0, 0, 75);

    points[0]  = sf::Vector2f(top_left_x, top_left_y + border_radius);
    points[1]  = sf::Vector2f(top_left_x + border_radius, top_left_y);
    points[2]  = sf::Vector2f(top_left_x + border_radius, top_left_y + border_width);
    points[3]  = sf::Vector2f(top_left_x + border_width, top_left_y + border_radius);
    points[4]  = sf::Vector2f(top_right_x - border_radius, top_right_y);
    points[5]  = sf::Vector2f(top_right_x, top_right_y + border_radius);
    points[6]  = sf::Vector2f(top_right_x - border_width, top_right_y + border_radius);
    points[7]  = sf::Vector2f(top_right_x - border_radius, top_right_y + border_width);
    points[8]  = sf::Vector2f(bottom_right_x - border_width, bottom_right_y - border_radius);
    points[9]  = sf::Vector2f(bottom_right_x, bottom_right_y - border_radius);
    points[10] = sf::Vector2f(bottom_right_x - border_radius, bottom_right_y);
    points[11] = sf::Vector2f(bottom_right_x - border_radius, bottom_right_y - border_width);
    points[12] = sf::Vector2f(bottom_left_x, bottom_left_y - border_radius);
    points[13] = sf::Vector2f(bottom_left_x + border_width, bottom_left_y - border_radius);
    points[14] = sf::Vector2f(bottom_left_x + border_radius, bottom_left_y - border_width);
    points[15] = sf::Vector2f(bottom_left_x + border_radius, bottom_left_y);

    m_array.append(sf::Vertex(points[0], color));
    m_array.append(sf::Vertex(points[1], color));
    m_array.append(sf::Vertex(points[3], color));

    m_array.append(sf::Vertex(points[3], color));
    m_array.append(sf::Vertex(points[1], color));
    m_array.append(sf::Vertex(points[2], color));

    m_array.append(sf::Vertex(points[1], color));
    m_array.append(sf::Vertex(points[4], color));
    m_array.append(sf::Vertex(points[7], color));
    
    m_array.append(sf::Vertex(points[2], color));
    m_array.append(sf::Vertex(points[1], color));
    m_array.append(sf::Vertex(points[7], color));

    m_array.append(sf::Vertex(points[4], color));
    m_array.append(sf::Vertex(points[5], color));
    m_array.append(sf::Vertex(points[7], color));

    m_array.append(sf::Vertex(points[6], color));
    m_array.append(sf::Vertex(points[5], color));
    m_array.append(sf::Vertex(points[7], color));

    m_array.append(sf::Vertex(points[6], color));
    m_array.append(sf::Vertex(points[5], color));
    m_array.append(sf::Vertex(points[9], color));

    m_array.append(sf::Vertex(points[6], color));
    m_array.append(sf::Vertex(points[8], color));
    m_array.append(sf::Vertex(points[9], color));

    m_array.append(sf::Vertex(points[8], color));
    m_array.append(sf::Vertex(points[9], color));
    m_array.append(sf::Vertex(points[11], color));

    m_array.append(sf::Vertex(points[9], color));
    m_array.append(sf::Vertex(points[10], color));
    m_array.append(sf::Vertex(points[11], color));

    m_array.append(sf::Vertex(points[10], color));
    m_array.append(sf::Vertex(points[11], color));
    m_array.append(sf::Vertex(points[15], color));

    m_array.append(sf::Vertex(points[14], color));
    m_array.append(sf::Vertex(points[11], color));
    m_array.append(sf::Vertex(points[15], color));

    m_array.append(sf::Vertex(points[13], color));
    m_array.append(sf::Vertex(points[14], color));
    m_array.append(sf::Vertex(points[15], color));

    m_array.append(sf::Vertex(points[12], color));
    m_array.append(sf::Vertex(points[13], color));
    m_array.append(sf::Vertex(points[15], color));

    m_array.append(sf::Vertex(points[0], color));
    m_array.append(sf::Vertex(points[3], color));
    m_array.append(sf::Vertex(points[15], color));

    m_array.append(sf::Vertex(points[0], color));
    m_array.append(sf::Vertex(points[12], color));
    m_array.append(sf::Vertex(points[13], color));

    /*m_array.append(sf::Vertex(sf::Vector2f(x - BUTTON_SHADOW_OFFSET,
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
    */

    //m_text.setPosition(x, y);
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
*   drawControl
*
*   Draws the control along with any other associated
*   object to the screen.
********************************************************/
void ksButton::drawControl(sf::RenderWindow * app)
{
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
    
        for (int count = 0; count < m_array.getVertexCount(); ++count)
            m_array[count].color = sf::Color(0, 0, 0, 255);
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
        for (int count = 0; count < m_array.getVertexCount(); ++count)
            m_array[count].color = sf::Color(0, 0, 0, 75);
    }
    else
    {
        for (int count = 0; count < m_array.getVertexCount(); ++count)
            m_array[count].color = sf::Color(0, 0, 0, 255);
    }
}
