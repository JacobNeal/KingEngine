/********************************************************
* Class:            ksLabel
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksLabel.h
*
*   Overview:
*       Label class that inherits from the base game
*       control.
*
********************************************************/

#ifndef KS_CONTROL_H
#define KS_CONTROL_H

#include <SFML/Graphics.hpp>
#include <string>
#include "ksVector2D.h"
#include "ksControl.h"

class ksLabel : public ksControl
{
    public:
        //                         Constructors
        ksLabel(std::string str, double x, double y);

        //                         Methods
        virtual void               update();
        virtual void               move(double x, double y);
        virtual sf::VertexArray *  getVertexArray();

    private:
        //                         Data members
        sf::VertexArray            m_array;
        ksVector2D                 m_position;
        std::string                m_string;
        bool                       m_pressed;
        bool                       m_visible;
};

#endif
