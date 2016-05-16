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

#ifndef KS_LABEL_H
#define KS_LABEL_H

#include <SFML/Graphics.hpp>
#include <string>
#include "ksVector2D.h"
#include "ksControl.h"

class ksLabel : public ksControl
{
    public:
        //                         Constructors
        ksLabel(sf::Font * font, std::string str, double x, double y, int character_size = 12);

        //                         Methods
        virtual void               drawControl(sf::RenderWindow & app);
        virtual bool               getVisibility();
        virtual void               moveControl(double x, double y);
        virtual bool               pressed(int mouse_x, int mouse_y);
        virtual bool               isPressed();
        virtual void               resize(int screen_width, int screen_height);
        virtual void               setCenter(double x, double y);
        virtual void               setControlPosition(double x, double y);
        virtual void               setOpacity(double opacity);
        virtual void               setPressed(bool pressed);
        void                       setText(std::string str);
        virtual void               setVisibility(bool visibility);

    private:
        //                         Data members
        ksVector2D                 m_position;
        sf::Text                   m_text;
        bool                       m_pressed;
        bool                       m_visible;
        int                        m_character_size;
};

#endif
