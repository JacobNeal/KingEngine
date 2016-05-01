/********************************************************
* Class:            ksParticleEmitter
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksParticleEmitter.h
*
*   Overview:
*       Emits particles from a particular location with
*       an assignable particle size, frequency, speed,
*       and overall reach.
*
*       The color, location, size, frequency, speed, and
*       reach are all customizable.
*
********************************************************/

#ifndef KS_PARTICLE_EMITTER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "ksWorld.h"
#include "ksParticle.h"

class ksParticleEmitter : public sf::Drawable, public sf::Transformable
{
    public:
        //                       Constructors
        ksParticleEmitter(ksWorld * world, sf::Color color, sf::Vector3f location, int size = 8, 
            int num = 10, int speed = 20, int reach = 20);
         
         //                      Methods
         void                    draw(sf::RenderTarget & target, sf::RenderStates states) const;
         sf::Color               getColor();
         void                    moveEmitter(int x, int y, int z);
         void                    setColor(sf::Color color);
         void                    setSize(int size);
         void                    setNumber(int num);
         void                    setVelocity(int vel);
         void                    setReach(int reach);
         void                    update();
         
    private:
         ksParticle              generateParticle();
         
         //                      Members
         ksWorld *               m_world;
         sf::Vector3f            m_emitter_location;
         sf::VertexArray         m_array;
         sf::Color               m_color;
         std::vector<ksParticle> m_particles;
         int                     m_size;
         int                     m_num;
         int                     m_velocity;
         int                     m_reach;
};

#endif