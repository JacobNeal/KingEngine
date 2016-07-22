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
#include "ksControlLayer.h"

////////////////////////////////////////////////////////////
ksControlLayer::ksControlLayer(std::string tilesheet)
    : m_num_of_controls(0), m_pressedControl(nullptr)
{
   m_texture.loadFromFile(tilesheet);
   m_array.setPrimitiveType(sf::Triangles);
}

////////////////////////////////////////////////////////////
void ksControlLayer::addControl(ksControl * control)
{
    m_controls[m_num_of_controls] = control;
    ++m_num_of_controls;
}

////////////////////////////////////////////////////////////
void ksControlLayer::drawLayer(sf::RenderWindow & app)
{
    for (int count = 0; count < m_num_of_controls; ++count)
        m_controls[count]->drawControl(app);
}

////////////////////////////////////////////////////////////
void ksControlLayer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
//    states.texture = &m_texture;
    target.draw(m_array, states);
}

////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////
void ksControlLayer::depressControl()
{
    if (m_pressedControl != nullptr)
        m_pressedControl->setPressed(false);
}

////////////////////////////////////////////////////////////
void ksControlLayer::purge()
{
    m_array.clear();
}

////////////////////////////////////////////////////////////
void ksControlLayer::resize(int screen_width, int screen_height)
{
    for (int count = 0; count < m_num_of_controls; ++count)
        m_controls[count]->resize(screen_width, screen_height);
}

////////////////////////////////////////////////////////////
bool ksControlLayer::setTilesheet(std::string tilesheet)
{
    return m_texture.loadFromFile(tilesheet);
}

////////////////////////////////////////////////////////////
int ksControlLayer::getCount()
{
    return m_num_of_controls;
}










