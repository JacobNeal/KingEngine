/********************************************************
* Class:            ksButton
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksButton.h
*
*   Overview:
*       Button class that inherits from the base game
*       control.
*
********************************************************/

#ifndef KS_BUTTON_H
#define KS_BUTTON_H

#include <SFML/Graphics.hpp>
#include "ksVector2D.h"
#include "ksControl.h"
#include "defines.h"

class ksButton : public ksControl
{
    public:
        //                         Constructors
        ksButton(double x, double y);

        //                         Methods
        virtual void               update();
        virtual void               move(double x, double y);
        virtual sf::VertexArray *  getVertexArray();
        virtual bool               pressed(int mouse_x, int mouse_y);
        virtual bool               isPressed();
        virtual void               setPressed(bool pressed);

    private:
        //                         Private methods
        void                       popEffect();

        //                         Data members
        sf::VertexArray            m_array;
        ksVector2D                 m_position;
        double                     m_width;
        double                     m_height;
        bool                       m_pressed;
        bool                       m_visible;
};

#endif
