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
#include "defines.h"

class ksControl
{
    public:
        //                         Methods
        virtual void               drawControl(sf::RenderWindow & app) = 0;
        virtual bool               getVisibility() = 0;
        virtual void               moveControl(double x, double y) = 0;
        virtual bool               pressed(int mouse_x, int mouse_y) = 0;
        virtual bool               isPressed() = 0;
        virtual void               resize(int screen_width, int screen_height) = 0;
        virtual void               setCenter(double x, double y) = 0;
        virtual void               setControlPosition(double x, double y) = 0;
        virtual void               setOpacity(double opacity) = 0;
        virtual void               setPressed(bool pressed) = 0;
        virtual void               setVisibility(bool visibility) = 0;
};

#endif
