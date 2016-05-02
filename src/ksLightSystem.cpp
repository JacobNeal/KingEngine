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
    : m_world(world), m_light_base_color(light_base_color), m_dark_base_color(dark_base_color)
{
    m_array.setPrimitiveType(sf::Triangles);
    
    // 5 walls * 2 triangles * 3 vertices = 30 vertices
    m_array.resize(30);
    
    // Left
    m_array[0].position     = m_world->transform3D(0, 0, 0);
    m_array[0].color        = m_light_base_color;
    
    m_array[1].position     = m_world->transform3D(0, 0, 1);
    m_array[1].color        = m_dark_base_color;
    
    m_array[2].position     = m_world->transform3D(0, 1, 1);
    m_array[2].color        = m_dark_base_color;
    
    m_array[3].position     = m_world->transform3D(0, 1, 0);
    m_array[3].color        = m_light_base_color;
    
    m_array[4]              = m_array[0];
    m_array[5]              = m_array[2];
    
    // Right
    m_array[6].position     = m_world->transform3D(1, 0, 0);
    m_array[6].color        = m_light_base_color;
    
    m_array[7].position     = m_world->transform3D(1, 0, 1);
    m_array[7].color        = m_dark_base_color;
    
    m_array[8].position     = m_world->transform3D(1, 1, 1);
    m_array[8].color        = m_dark_base_color;
    
    m_array[9].position     = m_world->transform3D(1, 1, 0);
    m_array[9].color        = m_light_base_color;
    
    m_array[10]              = m_array[6];
    m_array[11]              = m_array[8];
    
    // Top
    m_array[12].position     = m_world->transform3D(0, 0, 0);
    m_array[12].color        = m_light_base_color;
    
    m_array[13].position     = m_world->transform3D(1, 0, 0);
    m_array[13].color        = m_light_base_color;
    
    m_array[14].position     = m_world->transform3D(1, 0, 1);
    m_array[14].color        = m_dark_base_color;
    
    m_array[15].position     = m_world->transform3D(0, 0, 1);
    m_array[15].color        = m_dark_base_color;
    
    m_array[16]              = m_array[12];
    m_array[17]              = m_array[14];
    
    // Bottom
    m_array[18].position     = m_world->transform3D(0, 1, 0);
    m_array[18].color        = m_light_base_color;
    
    m_array[19].position     = m_world->transform3D(1, 1, 0);
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