/********************************************************
* Class:            ksLightSystem
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksLightSystem.h
*
*   Overview:
*       Class that contains the system for lighting and
*       shadows in the KingEngine. The lighting is 
*       calculated based on a reference to the game world 
*       that contains the required 3D transformation
*       methods.
*
********************************************************/

#ifndef KS_LIGHT_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "ksWorld.h"
#include "ksLight.h"

class ksLightSystem : public sf::Drawable, public sf::Transformable
{
    public:
        //                       Constructors
        ksLightSystem(ksWorld * world, sf::Color light_base_color, sf::Color dark_base_color);
            
        //                       Methods
        void                     addLight(sf::Vector3f position, int diameter, sf::Color color);
        ksVector3f               getLightPosition(int index);
        void                     setLightPosition(int index, int x, int y, int z);
        void                     setLightColor(ksColor color);
        void                     setDarkColor(ksColor color);
        void                     draw(sf::RenderTarget & target, sf::RenderStates states) const;
        void                     updateWallShadows();
        
    private:
        //                       Members
        ksWorld *                m_world;
        sf::Color                m_light_base_color;
        sf::Color                m_dark_base_color;
        sf::VertexArray          m_array;
        int                      m_number_of_lights;
        int                      m_deepest_light_z;
        std::vector<ksLight>     m_lights;
};

#endif