/********************************************************
* Class:            ksLabel
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksLabel.cpp
********************************************************/

#include "ksLabel.h"
#include <iostream>

/********************************************************
*   ksLabel
*
*   Intitializes the label class by setting the text of
*   the label and it's position to the passed values.
********************************************************/
ksLabel::ksLabel(sf::Font * font, std::string str, double x, double y, int character_size)
    : m_text(str, *font, character_size), m_pressed(false), m_visible(true),
    m_character_size(character_size)
{
    // Change origin point of the text object
    sf::FloatRect textRect = m_text.getLocalBounds();
    
    m_text.setOrigin(textRect.left + (textRect.width / 2.0f),
        textRect.top + (textRect.height / 2.0f));
        
    // Set the position of the text object
    m_text.setPosition(x, y);
}

/********************************************************
*   drawControl
*
*   Draws the label control containing the text object 
*   to the screen.
********************************************************/
void ksLabel::drawControl(sf::RenderWindow & app)
{
    if (m_visible)
    {
        app.draw(m_text);
    }
}

/********************************************************
*   getVisibility
*
*   Return the visibility of the label.
********************************************************/
bool ksLabel::getVisibility()
{
    return m_visible;
}

/********************************************************
*   moveControl
*
*   Move all the text object of this control by
*   the x and y modifiers passed.
********************************************************/
void ksLabel::moveControl(double x, double y)
{
    m_text.move(x, y);
}

/********************************************************
*   pressed
*
*   Overload the pressed method of the ksControl base
*   class. For now labels are not considered "pressable".
*   They've been added as a control for the purpose
*   of having text alignment in the UI.
********************************************************/
bool ksLabel::pressed(int mouse_x, int mouse_y)
{
    return false;
}

/********************************************************
*   isPressed
*
*   Return whether or not the control is currently being
*   pressed.
********************************************************/
bool ksLabel::isPressed()
{
    return m_pressed;
}

/********************************************************
*   resize
*
*   Resize the label character size based on the new
*   application width and height.
********************************************************/
void ksLabel::resize(int screen_width, int screen_height)
{
    m_character_size = ((double) m_character_size / (DEFAULT_WINDOW_WIDTH * DEFAULT_WINDOW_HEIGHT)) * (screen_width * screen_height);
    
    m_text.setCharacterSize(m_character_size);
    
    std::cout << "Character size: " << m_character_size << '\n';
    
    // Change origin point of the text object
    sf::FloatRect textRect = m_text.getLocalBounds();
    
    m_text.setOrigin(textRect.left + (textRect.width / 2.0f),
        textRect.top + (textRect.height / 2.0f));
    
    // Update the position of the label
    m_text.setPosition((m_text.getPosition().x / DEFAULT_WINDOW_WIDTH) * screen_width,
        (m_text.getPosition().y / DEFAULT_WINDOW_HEIGHT) * screen_height);
}

/********************************************************
*   setCenter
*
*   Position the control relative to the passed (x, y)
*   pair that represents the future center position.
********************************************************/
void ksLabel::setCenter(double x, double y)
{
    m_text.setPosition(x, y);
}

/********************************************************
*   setControlPosition
*
*   Position the control relative to the passed (x, y)
*   pair.
********************************************************/
void ksLabel::setControlPosition(double x, double y)
{
    m_text.setPosition(x, y);
}

/********************************************************
*   setOpacity
*
*   Set the opacity of the label, where 0.0 is completely
*   translucent and 1.0 is completely visible.
********************************************************/
void ksLabel::setOpacity(double opacity)
{
    // Get the current color of the text object.
    sf::Color temp = m_text.getColor();
    
    // Update the color to the passed opacity converted
    // to an alpha value.
    m_text.setColor(sf::Color(temp.r, temp.g, temp.b, opacity * 255));
}

/********************************************************
*   setPressed
*
*   Set whether or not the label is being pressed.
********************************************************/
void ksLabel::setPressed(bool pressed)
{
    m_pressed = pressed;
}

/********************************************************
*   setText
*
*   Set the string of the text object to the passed value.
********************************************************/
void ksLabel::setText(std::string str)
{
    m_text.setString(str);
}

/********************************************************
*   setVisibility
*
*   Set the visibility of the label.
********************************************************/
void ksLabel::setVisibility(bool visibility)
{
    m_visible = visibility;
}
