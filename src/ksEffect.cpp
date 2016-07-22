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
#include "ksEffect.h"

////////////////////////////////////////////////////////////
ksEffect::ksEffect()
    : m_number_of_lights(0), /*m_current_color(1),*/
      m_first_duration(0), m_second_duration(0)
      /*m_current_frame(0)*/
{
    m_array.setPrimitiveType(sf::Triangles);
}

////////////////////////////////////////////////////////////
void ksEffect::addLight(ksVector2D start, ksVector2D end,
                        int diameter, sf::Color first,
                        sf::Color second)
{
    m_first[m_number_of_lights]     = first;
    m_second[m_number_of_lights]    = second;

    int radius      = diameter / 2;
    int edge        = (3 * radius) / 4;
    int temp_vertex = m_number_of_lights * 27;

    // Octagon = (8 triangles * 3 points) = 24 + (3 points for beam) = 27
    m_array.resize((m_number_of_lights + 1) * 27);

    m_array[temp_vertex].position       = sf::Vector2f(end.X,          end.Y);
    m_array[temp_vertex + 1].position   = sf::Vector2f(end.X + edge,   end.Y - edge);
    m_array[temp_vertex + 2].position   = sf::Vector2f(end.X + radius, end.Y);

    m_array[temp_vertex + 3].position   = sf::Vector2f(end.X,          end.Y);
    m_array[temp_vertex + 4].position   = sf::Vector2f(end.X + radius, end.Y);
    m_array[temp_vertex + 5].position   = sf::Vector2f(end.X + edge,   end.Y + edge);

    m_array[temp_vertex + 6].position   = sf::Vector2f(end.X,          end.Y);
    m_array[temp_vertex + 7].position   = sf::Vector2f(end.X + edge,   end.Y + edge);
    m_array[temp_vertex + 8].position   = sf::Vector2f(end.X,          end.Y + radius);

    m_array[temp_vertex + 9].position   = sf::Vector2f(end.X,          end.Y);
    m_array[temp_vertex + 10].position  = sf::Vector2f(end.X,          end.Y + radius);
    m_array[temp_vertex + 11].position  = sf::Vector2f(end.X - edge,   end.Y + edge);

    m_array[temp_vertex + 12].position  = sf::Vector2f(end.X,          end.Y);
    m_array[temp_vertex + 13].position  = sf::Vector2f(end.X - edge,   end.Y + edge);
    m_array[temp_vertex + 14].position  = sf::Vector2f(end.X - radius, end.Y);

    m_array[temp_vertex + 15].position  = sf::Vector2f(end.X,          end.Y);
    m_array[temp_vertex + 16].position  = sf::Vector2f(end.X - radius, end.Y);
    m_array[temp_vertex + 17].position  = sf::Vector2f(end.X - edge,   end.Y - edge);

    m_array[temp_vertex + 18].position  = sf::Vector2f(end.X,          end.Y);
    m_array[temp_vertex + 19].position  = sf::Vector2f(end.X - edge,   end.Y - edge);
    m_array[temp_vertex + 20].position  = sf::Vector2f(end.X,          end.Y - radius);

    m_array[temp_vertex + 21].position  = sf::Vector2f(end.X,          end.Y);
    m_array[temp_vertex + 22].position  = sf::Vector2f(end.X,          end.Y - radius);
    m_array[temp_vertex + 23].position  = sf::Vector2f(end.X + edge,   end.Y - edge);

    // Draw a triangle beam connecting the start point with the edges of the octagon.
    m_array[temp_vertex + 24].position  = sf::Vector2f(start.X,        start.Y);
    m_array[temp_vertex + 25].position  = sf::Vector2f(end.X + edge,   end.Y + edge);
    m_array[temp_vertex + 26].position  = sf::Vector2f(end.X - edge,   end.Y - edge);

    for (int count = m_number_of_lights * 27; count < (m_number_of_lights + 1) * 27; ++count)
        m_array[count].color = first;

    m_number_of_lights += 1;
}

////////////////////////////////////////////////////////////
void ksEffect::clear()
{
    m_array.clear();
    m_first.clear();
    m_second.clear();
    m_number_of_lights = 0;
}

////////////////////////////////////////////////////////////
void ksEffect::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_array, states);
}

////////////////////////////////////////////////////////////
sf::Color ksEffect::getFirstColor(int index)
{
    return m_first[index];
}

////////////////////////////////////////////////////////////
sf::Color ksEffect::getSecondColor(int index)
{
    return m_second[index];
}

////////////////////////////////////////////////////////////
int ksEffect::getFirstDuration()
{
   return m_first_duration; 
}

////////////////////////////////////////////////////////////
int ksEffect::getSecondDuration()
{
    return m_second_duration;
}

////////////////////////////////////////////////////////////
void ksEffect::setFirstColor(int index, sf::Color first)
{
    m_first[index] = first;
}

////////////////////////////////////////////////////////////
void ksEffect::setSecondColor(int index, sf::Color second)
{
    m_second[index] = second;
}

////////////////////////////////////////////////////////////
void ksEffect::setFirstDuration(int duration)
{
    m_first_duration = duration;
}

////////////////////////////////////////////////////////////
void ksEffect::setSecondDuration(int duration)
{
    m_second_duration = duration;
}
