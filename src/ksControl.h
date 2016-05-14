/********************************************************
* Class:            ksControl
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksControl.h
*
*   Overview:
*       Class that contains an abstract base control 
*       that is drawable and customized using a 
*       VertexArray.
*
********************************************************/

#ifndef KS_CONTROL_H
#define KS_CONTROL_H

#include <SFML/Graphics.hpp>

class ksControl
{
    public:
        //                         Methods
        virtual void               drawControl(sf::RenderWindow & app) = 0;
        virtual void               moveControl(double x, double y) = 0;
        virtual bool               pressed(int mouse_x, int mouse_y) = 0;
        virtual bool               isPressed() = 0;
        virtual void               setCenter(double x, double y) = 0;
        virtual void               setControlPosition(double x, double y) = 0;
        virtual void               setPressed(bool pressed) = 0;
};

#endif
