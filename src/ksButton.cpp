////////////////////////////////////////////////////////////
//
// KingEngine
// The MIT License (MIT)
// Copyright (c) 2016 Beyond Parallel
//
// Permission is hereby granted, free of charge, to any person 
// obtaining a copy of this software and associated documentation 
// files (the "Software"), to deal in the Software without restriction, 
// including without limitation the rights to use, copy, modify, merge, 
// publish, distribute, sublicense, and/or sell copies of the Software, 
// and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be 
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ksButton.h"

////////////////////////////////////////////////////////////
ksButton::ksButton(sf::Font * font, std::string text, double w, double h, ksColor color, 
    ksColor pressed_color, double radius, int resolution)
    : m_container(w, h, ksAlign::CENTER, color, radius, resolution), m_label(font, text, (w/2), (h/2)),
    m_color(color), m_pressed_color(pressed_color)
{
    // Add the label to the containing control for the button
    m_container.addControl(&m_label);
}

////////////////////////////////////////////////////////////
void ksButton::drawControl(sf::RenderWindow & app)
{
    // Only draw the control if it's visible.
    if (m_container.getVisibility())
        m_container.drawControl(app);
}

////////////////////////////////////////////////////////////
bool ksButton::getVisibility()
{
    return m_container.getVisibility();
}

////////////////////////////////////////////////////////////
void ksButton::moveControl(double x, double y)
{
    m_container.moveControl(x, y);
}

////////////////////////////////////////////////////////////
bool ksButton::pressed(int mouse_x, int mouse_y)
{   
    return m_container.pressed(mouse_x, mouse_y);
}

////////////////////////////////////////////////////////////
bool ksButton::isPressed()
{
    return m_container.isPressed();
}

////////////////////////////////////////////////////////////
void ksButton::resize(int screen_width, int screen_height)
{
    m_container.resize(screen_width, screen_height);
}

////////////////////////////////////////////////////////////
void ksButton::released()
{
    
}

////////////////////////////////////////////////////////////
void ksButton::setCenter(double x, double y)
{
    m_container.setCenter(x, y);
}

////////////////////////////////////////////////////////////
void ksButton::setColor(ksColor color)
{
    m_container.setColor(color);
}

////////////////////////////////////////////////////////////
void ksButton::setControlPosition(double x, double y)
{
    m_container.setPosition(x, y);
}

////////////////////////////////////////////////////////////
void ksButton::setOpacity(double opacity)
{
    m_container.setOpacity(opacity);
    m_label.setOpacity(opacity);
}

////////////////////////////////////////////////////////////
void ksButton::setPressed(bool pressed)
{
    m_container.setPressed(pressed);
}

////////////////////////////////////////////////////////////
void ksButton::setText(std::string str)
{
    m_label.setText(str);
}

////////////////////////////////////////////////////////////
void ksButton::setVisibility(bool visibility)
{
    m_container.setVisibility(visibility);
    m_label.setVisibility(visibility);
}
