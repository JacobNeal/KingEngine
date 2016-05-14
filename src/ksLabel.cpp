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
ksLabel::ksLabel(sf::Font * font, std::string str, double x, double y)
    : m_text(str, *font, 12), m_pressed(false), m_visible(true)
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
    app.draw(m_text);
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
