/********************************************************
* Class:            ksLight
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksLight.h
*
*   Overview:
*       Class that contains data regarding a light source
*       that is used by the lighting system.
*
********************************************************/

#ifndef KS_LIGHT_H
#define KS_LIGHT_H

#include <SFML/Graphics.hpp>

class ksLight
{
    public:
        //                       Constructors
        ksLight(ksVector3f position, int diameter, ksColor color)
            : m_position(position), m_diameter(diameter), m_color(color)
        { }
        
        //                       Methods
        void move(ksVector3f position)
        {
            m_position += position;
        }
        
        ksVector3f getPosition()
        {
            return m_position;
        }
        
        int getDiameter()
        {
            return m_diameter;
        }
        
        ksColor getColor()
        {
            return m_color;
        }
        
        void setPosition(ksVector3f position)
        {
            m_position = position;
        }
        
        void setColor(ksColor color)
        {
            m_color = color;
        }
        
        void setDiameter(int diameter)
        {
            m_diameter = diameter;
        }
        
    private:
        //                       Members
        ksVector3f               m_position;
        int                      m_diameter;
        ksColor                  m_color;
};

#endif