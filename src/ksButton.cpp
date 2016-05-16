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
ksButton::ksButton(sf::Font * font, std::string text, double w, double h, ksColor color, 
    ksColor pressed_color, double radius, int resolution)
    : m_container(w, h, ksAlign::CENTER, color, radius, resolution), m_label(font, text, (w/2), (h/2)),
    m_color(color), m_pressed_color(pressed_color)
{
    // Add the label to the containing control for the button
    m_container.addControl(&m_label);
}

/********************************************************
*   drawControl
*
*   Draws the control along with any other associated
*   object to the screen.
********************************************************/
void ksButton::drawControl(sf::RenderWindow & app)
{
    m_container.drawControl(app);
}

/********************************************************
*   getVisibility
*
*   Return the visibility of the button control.
********************************************************/
bool ksButton::getVisibility()
{
    return m_container.getVisibility();
}

/********************************************************
*   moveControl
*
*   Move all the vertices inside of this control by
*   the x and y modifiers passed.
********************************************************/
void ksButton::moveControl(double x, double y)
{
    m_container.moveControl(x, y);
}

/********************************************************
*   pressed
*
*   Returns whether or not the button is pressed within
*   the given mouse coordinates.
********************************************************/
bool ksButton::pressed(int mouse_x, int mouse_y)
{   
    return m_container.pressed(mouse_x, mouse_y);
}

/********************************************************
*   isPressed
*
*   Returns whether or not the button is pressed.
********************************************************/
bool ksButton::isPressed()
{
    return m_container.isPressed();
}

/********************************************************
*   resize
*
*   Resize the button container and contained label
*   based on the new application width and height.
********************************************************/
void ksButton::resize(int screen_width, int screen_height)
{
    m_container.resize(screen_width, screen_height);
}

/********************************************************
*   released
*
*   Sets the control to be in the released state.
********************************************************/
void ksButton::released()
{
    
}

/********************************************************
*   setCenter
*
*   Position the control relative to the passed (x, y)
*   pair that represents the future center position.
********************************************************/
void ksButton::setCenter(double x, double y)
{
    m_container.setCenter(x, y);
}

/********************************************************
*   setColor
*
*   Set the color of the container underlying the button.
********************************************************/
void ksButton::setColor(ksColor color)
{
    m_container.setColor(color);
}

/********************************************************
*   setControlPosition
*
*   Position the control relative to the passed (x, y)
*   pair.
********************************************************/
void ksButton::setControlPosition(double x, double y)
{
    m_container.setPosition(x, y);
}

/********************************************************
*   setOpacity
*
*   Set the opacity of the button's container and label.
********************************************************/
void ksButton::setOpacity(double opacity)
{
    m_container.setOpacity(opacity);
    m_label.setOpacity(opacity);
}

/********************************************************
*   setPressed
*
*   Sets whether or not the button is pressed.
*   (this can allow for a button to be depressed)
********************************************************/
void ksButton::setPressed(bool pressed)
{
    m_container.setPressed(pressed);
}

/********************************************************
*   setText
*
*   Sets the text of the button control to the passed
*   value.
********************************************************/
void ksButton::setText(std::string str)
{
    m_label.setText(str);
}

/********************************************************
*   setVisibility
*
*   Sets the visibility of the button container and label.
********************************************************/
void ksButton::setVisibility(bool visibility)
{
    m_container.setVisibility(visibility);
    m_label.setVisibility(visibility);
}
