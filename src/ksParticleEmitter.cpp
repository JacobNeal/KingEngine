/********************************************************
* Class:			ksParticleEmitter
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksParticleEmitter.cpp
********************************************************/

#include "ksParticleEmitter.h"
#include <iostream>
#include <time.h>

/*********************************************************
*	ksParticleEmitter
*
*	Initialize the particle emitter, and seed the random.
*********************************************************/
ksParticleEmitter::ksParticleEmitter(ksWorld * world, sf::Color color, sf::Vector3f location, int size, 
    int num, int speed, int reach)
        : m_world(world), m_color(color), m_emitter_location(location), m_size(size),
        m_num(num), m_velocity(speed), m_reach(reach)
{
    srand(time(NULL));
    
    // Using triangle primitives for OpenGL ES compliance
    m_array.setPrimitiveType(sf::Triangles);
}

/*********************************************************
*	draw
*
*	The overloaded SFML pure virtual method for drawing
*	an sf::Drawable type.
*********************************************************/
void ksParticleEmitter::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_array, states);
}

/*********************************************************
*	getColor
*
*	Return the overall color of all the generated particles.
*********************************************************/
sf::Color ksParticleEmitter::getColor()
{
    return m_color;
}

/*********************************************************
*	moveEmitter
*
*	Move emitter by the passed x, y, and z values.
*********************************************************/
void ksParticleEmitter::moveEmitter(int x, int y, int z)
{
    m_emitter_location.x += x;
    m_emitter_location.y += y;
    m_emitter_location.z += z;
}

/*********************************************************
*	setColor
*
*	Set the color of the emitted particles.
*********************************************************/
void ksParticleEmitter::setColor(sf::Color color)
{
    m_color = color;
}

/*********************************************************
*	setSize
*
*	Set the individual particle size.
*********************************************************/
void ksParticleEmitter::setSize(int size)
{
    m_size = size;
}

/*********************************************************
*	setNumber
*
*	Set the frequency of particles emitted each frame of
*   execution.
*********************************************************/
void ksParticleEmitter::setNumber(int num)
{
    m_num = num;
}

/*********************************************************
*	setVelocity
*
*	Set the velocity of the emitted particles.
*********************************************************/
void ksParticleEmitter::setVelocity(int vel)
{
    m_velocity = vel;
}

/*********************************************************
*	setReach
*
*	Set the reach of the particles that are emitted.
*********************************************************/
void ksParticleEmitter::setReach(int reach)
{
    m_reach = reach;
}

/*********************************************************
*	update
*
*	Update the particle emitter each frame of execution
*   to call the update of the individual 
*********************************************************/
void ksParticleEmitter::update()
{
    // Generate new particles each frame.
    for (int count = 0; count < m_num; ++count)
        m_particles.push_back(generateParticle());
    
    m_array.resize(m_particles.size() * 6);
        
    for (int particle = 0; particle < m_particles.size(); ++particle)
    {
        m_particles[particle].update();
        
        // Erase any particles that have expired.
        if (m_particles[particle].m_time_to_live <= 0)
        {
            m_particles.erase(m_particles.begin() + particle);
            --particle;
            m_array.resize(m_particles.size() * 6);
        }
        else
        {
            // Update the drawable vertex array with the updated
            // particle location and color.
            sf::Vector3f pos = m_particles[particle].m_position;
            
            m_array[particle * 6].position         = m_world->transform3DWithPixelValue(pos.x, pos.y, pos.z);
            m_array[particle * 6].color            = m_color;
            
            m_array[(particle * 6) + 1].position   = m_world->transform3DWithPixelValue(pos.x + m_size, pos.y, pos.z);
            m_array[(particle * 6) + 1].color      = m_color;
            
            m_array[(particle * 6) + 2].position   = m_world->transform3DWithPixelValue(pos.x + m_size, pos.y + m_size, pos.z);
            m_array[(particle * 6) + 2].color      = m_color;
            
            m_array[(particle * 6) + 3].position   = m_world->transform3DWithPixelValue(pos.x, pos.y + m_size, pos.z);
            m_array[(particle * 6) + 3].color      = m_color;
            
            m_array[(particle * 6) + 4].position   = m_array[particle * 6].position;
            m_array[(particle * 6) + 4].color      = m_color;
            
            m_array[(particle * 6) + 5].position   = m_array[(particle * 6) + 2].position;
            m_array[(particle * 6) + 5].color      = m_color;
        }
    }
}

/*********************************************************
*	generateParticle
*
*	Generate a particle that starts at the location of the
*   emitter, but has a random velocity on (x,y,z), and
*   a random time to live that is within the assigned
*   reach value.
*********************************************************/
ksParticle ksParticleEmitter::generateParticle()
{
    ksParticle particle(m_emitter_location,
        sf::Vector3f(rand() % m_velocity + 1, rand() % m_velocity + 1, rand() % m_velocity + 1),
        rand() % m_reach + 1);
        
    return particle;
}