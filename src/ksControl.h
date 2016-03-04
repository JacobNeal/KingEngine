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
        virtual void               update() = 0;
//        virtual void               drawControl() = 0;
        virtual void               move(double x, double y) = 0;
        virtual sf::VertexArray *  getVertexArray() = 0;
        virtual bool               pressed(int mouse_x, int mouse_y) = 0;
        virtual bool               isPressed() = 0;
        virtual void               setPressed(bool pressed) = 0;
};

#endif
