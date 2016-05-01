/********************************************************
* Class:            ksParticle
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksParticle.h
*
*   Overview:
*       Class for containing a 3D particle, with velocity
*       and a time to live before it's destroyed.
*       
*       This class is directly used by: ksParticleEmitter.
*
********************************************************/

#ifndef KS_PARTICLE_H

#include <SFML/Graphics.hpp>

class ksParticle
{
    public:
        //                       Constructors
        ksParticle(sf::Vector3f position, sf::Vector3f velocity, int time_to_live)
            : m_position(position), m_velocity(velocity), m_time_to_live(time_to_live)
            { }
        
        //                       Methods
        void                     update()
        {
            --m_time_to_live;
            m_position += m_velocity;
        }
        
        //                       Members
        // This is a small class used only for ksParticleEmitter, so these members
        // will be public instead of creating accessors and mutators for each.
        sf::Vector3f             m_position;
        sf::Vector3f             m_velocity;
        int                      m_time_to_live;
};

#endif