/********************************************************
* Class:            ksEffect
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksEffect.cpp
********************************************************/

#include "ksEffect.h"

/********************************************************
*   ksEffect
*
*   Initialize the effect layer of lights to default
*   values.
********************************************************/
ksEffect::ksEffect()
    : m_number_of_lights(0), /*m_current_color(1),*/
      m_first_duration(0), m_second_duration(0)
      /*m_current_frame(0)*/
{
    m_array.setPrimitiveType(sf::Triangles);
}

/********************************************************
*   addLight
*
*   Add a light (colored octagon) into the effect layer 
*   and draw a triangle beam connecting the light source 
*   with it's destination if the starting location != 
*   ending location.
********************************************************/
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

/********************************************************
*   clear
*
*   Clear the effect layer of all active lights.
********************************************************/
void ksEffect::clear()
{
    m_array.clear();
    m_first.clear();
    m_second.clear();
    m_number_of_lights = 0;
}

/********************************************************
*   draw
*
*   Overloads the draw method of drawable entities in
*   the SFML library, so that this layer can be drawn.
********************************************************/
void ksEffect::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_array, states);
}

/********************************************************
*   getFirstColor
*
*   Returns the first color of one of the lights.
********************************************************/
sf::Color ksEffect::getFirstColor(int index)
{
    return m_first[index];
}

/********************************************************
*   getSecondColor
*
*   Returns the second color of one of the lights.
********************************************************/
sf::Color ksEffect::getSecondColor(int index)
{
    return m_second[index];
}

/********************************************************
*   getFirstDuration
*
*   Returns the first duration of the effect layer.
********************************************************/
int ksEffect::getFirstDuration()
{
   return m_first_duration; 
}

/********************************************************
*   getSecondDuration
*
*   Returns the second duration of the effect layer.
********************************************************/
int ksEffect::getSecondDuration()
{
    return m_second_duration;
}

/********************************************************
*   setFirstColor
*
*   Sets the first color of one of the lights.
********************************************************/
void ksEffect::setFirstColor(int index, sf::Color first)
{
    m_first[index] = first;
}

/********************************************************
*   setSecondColor
*
*   Sets the second color of one of the lights.
********************************************************/
void ksEffect::setSecondColor(int index, sf::Color second)
{
    m_second[index] = second;
}

/********************************************************
*   setFirstDuration
*
*   Sets the first duration of the effect layer.
********************************************************/
void ksEffect::setFirstDuration(int duration)
{
    m_first_duration = duration;
}

/********************************************************
*   setSecondDuration
*
*   Sets the second duration of the effect layer.
********************************************************/
void ksEffect::setSecondDuration(int duration)
{
    m_second_duration = duration;
}
