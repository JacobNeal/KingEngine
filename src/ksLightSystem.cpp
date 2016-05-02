/********************************************************
* Class:			ksLightSystem
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksLightSystem.cpp
********************************************************/

#include "ksLightSystem.h"

/*********************************************************
*	ksLightSystem
*
*	Initialize the light system to a non-lit default state
*   based on the passed base colors for the shadows.
*********************************************************/
ksLightSystem::ksLightSystem(ksWorld * world, sf::Color light_base_color, sf::Color dark_base_color)
    : m_world(world), m_light_base_color(light_base_color), m_dark_base_color(dark_base_color),
    m_number_of_lights(0), m_deepest_light_z(0)
{
    m_array.setPrimitiveType(sf::Triangles);
    
    // 5 walls * 2 triangles * 3 vertices = 30 vertices
    // Deepest light source: 4 extra walls * 2 triangles * 3 vertices = 24 vertices
    // 30 vertices + 24 vertices = 54 vertices.
    m_array.resize(54);
    
    // Left
    m_array[0].position     = m_world->transform3D(0, 0, m_deepest_light_z);
    m_array[0].color        = m_light_base_color;
    
    m_array[1].position     = m_world->transform3D(0, 0, 1);
    m_array[1].color        = m_dark_base_color;
    
    m_array[2].position     = m_world->transform3D(0, 1, 1);
    m_array[2].color        = m_dark_base_color;
    
    m_array[3].position     = m_world->transform3D(0, 1, m_deepest_light_z);
    m_array[3].color        = m_light_base_color;
    
    m_array[4]              = m_array[0];
    m_array[5]              = m_array[2];
    
    // Right
    m_array[6].position     = m_world->transform3D(1, 0, m_deepest_light_z);
    m_array[6].color        = m_light_base_color;
    
    m_array[7].position     = m_world->transform3D(1, 0, 1);
    m_array[7].color        = m_dark_base_color;
    
    m_array[8].position     = m_world->transform3D(1, 1, 1);
    m_array[8].color        = m_dark_base_color;
    
    m_array[9].position     = m_world->transform3D(1, 1, m_deepest_light_z);
    m_array[9].color        = m_light_base_color;
    
    m_array[10]              = m_array[6];
    m_array[11]              = m_array[8];
    
    // Top
    m_array[12].position     = m_world->transform3D(0, 0, m_deepest_light_z);
    m_array[12].color        = m_light_base_color;
    
    m_array[13].position     = m_world->transform3D(1, 0, m_deepest_light_z);
    m_array[13].color        = m_light_base_color;
    
    m_array[14].position     = m_world->transform3D(1, 0, 1);
    m_array[14].color        = m_dark_base_color;
    
    m_array[15].position     = m_world->transform3D(0, 0, 1);
    m_array[15].color        = m_dark_base_color;
    
    m_array[16]              = m_array[12];
    m_array[17]              = m_array[14];
    
    // Bottom
    m_array[18].position     = m_world->transform3D(0, 1, m_deepest_light_z);
    m_array[18].color        = m_light_base_color;
    
    m_array[19].position     = m_world->transform3D(1, 1, m_deepest_light_z);
    m_array[19].color        = m_light_base_color;
    
    m_array[20].position     = m_world->transform3D(1, 1, 1);
    m_array[20].color        = m_dark_base_color;
    
    m_array[21].position     = m_world->transform3D(0, 1, 1);
    m_array[21].color        = m_dark_base_color;
    
    m_array[22]              = m_array[18];
    m_array[23]              = m_array[20];
    
    // Front
    m_array[24].position     = m_world->transform3D(0, 0, 1);
    m_array[24].color        = m_dark_base_color;
    
    m_array[25].position     = m_world->transform3D(1, 0, 1);
    m_array[25].color        = m_dark_base_color;
    
    m_array[26].position     = m_world->transform3D(1, 1, 1);
    m_array[26].color        = m_dark_base_color;
    
    m_array[27].position     = m_world->transform3D(0, 1, 1);
    m_array[27].color        = m_dark_base_color;
    
    m_array[28]              = m_array[24];
    m_array[29]              = m_array[26];
    
    for (int count = 30; count < 54; ++count)
        m_array[count].color = m_light_base_color;
}

/*********************************************************
*	addLight
*
*	Add a light to the lighting system and update the
*   darkest base color based on the total number of 
*   light sources.
*********************************************************/
void ksLightSystem::addLight(sf::Vector3f position, int diameter, sf::Color color)
{
    int radius = diameter / 2;
    int edge = (3 * radius) / 4;
    int temp = (m_number_of_lights * 24) + 54;
    
    sf::Vector2f center = m_world->transform3DWithPixelValue(position.x, position.y, position.z);
    
    m_array.resize(((m_number_of_lights + 1) * 24) + 54);
    
    m_array[temp].position        = center;
    m_array[temp + 1].position    = m_world->transform3DWithPixelValue(position.x + edge, position.y - edge, position.z);
    m_array[temp + 2].position    = m_world->transform3DWithPixelValue(position.x + radius, position.y, position.z);
    
    m_array[temp + 3].position    = center;
    m_array[temp + 4].position    = m_world->transform3DWithPixelValue(position.x + radius, position.y, position.z);
    m_array[temp + 5].position    = m_world->transform3DWithPixelValue(position.x + edge, position.y + edge, position.z);
    
    m_array[temp + 6].position    = center;
    m_array[temp + 7].position    = m_world->transform3DWithPixelValue(position.x + edge, position.y + edge, position.z);
    m_array[temp + 8].position    = m_world->transform3DWithPixelValue(position.x, position.y + radius, position.z);
    
    m_array[temp + 9].position    = center;
    m_array[temp + 10].position   = m_world->transform3DWithPixelValue(position.x, position.y + radius, position.z);
    m_array[temp + 11].position   = m_world->transform3DWithPixelValue(position.x - edge, position.y + edge, position.z);
    
    m_array[temp + 12].position   = center;
    m_array[temp + 13].position   = m_world->transform3DWithPixelValue(position.x - edge, position.y + edge, position.z);
    m_array[temp + 14].position   = m_world->transform3DWithPixelValue(position.x - radius, position.y, position.z);
    
    m_array[temp + 15].position   = center;
    m_array[temp + 16].position   = m_world->transform3DWithPixelValue(position.x - radius, position.y, position.z);
    m_array[temp + 17].position   = m_world->transform3DWithPixelValue(position.x - edge, position.y - edge, position.z);
    
    m_array[temp + 18].position   = center;
    m_array[temp + 19].position   = m_world->transform3DWithPixelValue(position.x - edge, position.y - edge, position.z);
    m_array[temp + 20].position   = m_world->transform3DWithPixelValue(position.x, position.y - radius, position.z);
    
    m_array[temp + 21].position   = center;
    m_array[temp + 22].position   = m_world->transform3DWithPixelValue(position.x, position.y - radius, position.z);
    m_array[temp + 23].position   = m_world->transform3DWithPixelValue(position.x + edge, position.y - edge, position.z);
    
    m_array[temp].color           = color;
    
    for (int count = 1; count < 24; ++count)
    {
        if (count % 3 == 0)
            m_array[temp + count].color = color;
        else
            m_array[temp + count].color = sf::Color(color.r, color.g, color.b, 0);
    }
        
    // Push the wall shadows back further from the light
    if (position.z > m_deepest_light_z)
    {
        m_deepest_light_z = position.z;
        updateWallShadows();
    }
    
    for (int count = 0; count < 54; ++count)
    {
        if (m_array[count].color == m_dark_base_color)
        {
            m_array[count].color.a -= 75;
            
            if (m_array[count].color.a < 0)
                m_array[count].color.a = 0;
        }
        // else if (m_array[count].color == m_light_base_color)
        // {
        //     m_array[count].color.a -= 75;
            
        //     if (m_array[count].color.a < 0)
        //         m_array[count].color.a = 0;
        // }
    }
    
    m_dark_base_color.a -= 75;
    
    if (m_dark_base_color.a < 0)
        m_dark_base_color.a = 0;
        
    // m_light_base_color.a -= 75;
    
    // if (m_light_base_color.a < 0)
    //     m_light_base_color.a = 0;
        
    for (int count = 30; count < 54; ++count)
        m_array[count].color = m_light_base_color;
    
    ++m_number_of_lights;
}

/*********************************************************
*	draw
*
*	The overloaded SFML pure virtual method for drawing
*	an sf::Drawable type.
*********************************************************/
void ksLightSystem::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_array, states);
}

/*********************************************************
*	updateWallShadows
*
*	Push the wall shadows further back based on the
*   deepest light source that's been added.
*********************************************************/
void ksLightSystem::updateWallShadows()
{
    // Left
    m_array[0].position     = m_world->transform3DWithPixelValue(0, 0, m_deepest_light_z);
    m_array[1].position     = m_world->transform3DWithPixelValue(0, 0, m_world->getDepth());
    m_array[2].position     = m_world->transform3DWithPixelValue(0, m_world->getHeight(), m_world->getDepth());
    m_array[3].position     = m_world->transform3DWithPixelValue(0, m_world->getHeight(), m_deepest_light_z);
    m_array[4]              = m_array[0];
    m_array[5]              = m_array[2];
    
    // Right
    m_array[6].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), 0, m_deepest_light_z);
    m_array[7].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), 0, m_world->getDepth());
    m_array[8].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), m_world->getHeight(), m_world->getDepth());
    m_array[9].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), m_world->getHeight(), m_deepest_light_z);
    m_array[10]              = m_array[6];
    m_array[11]              = m_array[8];
    
    // Top
    m_array[12].position     = m_world->transform3DWithPixelValue(0, 0, m_deepest_light_z);
    m_array[13].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), 0, m_deepest_light_z);
    m_array[14].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), 0, m_world->getDepth());
    m_array[15].position     = m_world->transform3DWithPixelValue(0, 0, m_world->getDepth());
    m_array[16]              = m_array[12];
    m_array[17]              = m_array[14];
    
    // Bottom
    m_array[18].position     = m_world->transform3DWithPixelValue(0, m_world->getHeight(), m_deepest_light_z);
    m_array[19].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), m_world->getHeight(), m_deepest_light_z);
    m_array[20].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), m_world->getHeight(), m_world->getDepth());
    m_array[21].position     = m_world->transform3DWithPixelValue(0, m_world->getHeight(), m_world->getDepth());
    m_array[22]              = m_array[18];
    m_array[23]              = m_array[20];
    
    // Front
    m_array[24].position     = m_world->transform3DWithPixelValue(0, 0, m_world->getDepth());
    m_array[25].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), 0, m_world->getDepth());
    m_array[26].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), m_world->getHeight(), m_world->getDepth());
    m_array[27].position     = m_world->transform3DWithPixelValue(0, m_world->getHeight(), m_world->getDepth());
    m_array[28]              = m_array[24];
    m_array[29]              = m_array[26];
    
    // Left deepest light source
    m_array[30].position     = m_world->transform3DWithPixelValue(0, 0, 0);
    m_array[31].position     = m_world->transform3DWithPixelValue(0, 0, m_deepest_light_z);
    m_array[32].position     = m_world->transform3DWithPixelValue(0, m_world->getHeight(), m_deepest_light_z);
    m_array[33].position     = m_world->transform3DWithPixelValue(0, m_world->getHeight(), 0);
    m_array[34]              = m_array[30];
    m_array[35]              = m_array[32];
    
    // Right deepest light source
    m_array[36].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), 0, 0);
    m_array[37].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), 0, m_deepest_light_z);
    m_array[38].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), m_world->getHeight(), m_deepest_light_z);
    m_array[39].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), m_world->getHeight(), 0);
    m_array[40]              = m_array[36];
    m_array[41]              = m_array[38];
    
    // Top deepest light source
    m_array[42].position     = m_world->transform3DWithPixelValue(0, 0, 0);
    m_array[43].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), 0, 0);
    m_array[44].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), 0, m_deepest_light_z);
    m_array[45].position     = m_world->transform3DWithPixelValue(0, 0, m_deepest_light_z);
    m_array[46]              = m_array[42];
    m_array[47]              = m_array[44];
    
    // Bottom deepest light source
    m_array[48].position     = m_world->transform3DWithPixelValue(0, m_world->getHeight(), 0);
    m_array[49].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), m_world->getHeight(), 0);
    m_array[50].position     = m_world->transform3DWithPixelValue(m_world->getWidth(), m_world->getHeight(), m_deepest_light_z);
    m_array[51].position     = m_world->transform3DWithPixelValue(0, m_world->getHeight(), m_deepest_light_z);
    m_array[52]              = m_array[48];
    m_array[53]              = m_array[50];
}