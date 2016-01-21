/********************************************************
* Class:            ksControl
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksControl.h
*
*   Overview:
*       Class that contains a base control that can be
*       drawable and customized using a VertexArray.
*
********************************************************/

#ifndef KS_CONTROL_H
#define KS_CONTROL_H

#include <SFML/Graphics.hpp>

class ksControl
{
    public:
        //                         Constructors
        //ksControl(double x, double y);

        //                         Methods
        virtual void               update() = 0;
        virtual void               move(double x, double y) = 0;
        virtual sf::VertexArray *  getVertexArray() = 0;
        virtual bool               pressed(int mouse_x, int mouse_y) = 0;
        virtual bool               isPressed() = 0;
        virtual void               setPressed(bool pressed) = 0;

    private:
        //                         Data members
        /*sf::VertexArray            m_array;
        ksVector2D                 m_position;
        double                     m_width;
        double                     m_height;
        bool                       m_pressed;
        bool                       m_visible;*/

};

#endif
