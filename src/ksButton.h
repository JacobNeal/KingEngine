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
#include "ksContainer.h"
#include "ksLabel.h"

class ksButton : public ksControl
{
    public:
        //                         Constructors
        ksButton(sf::Font * font, std::string text, double w, double h, ksColor color = ksColor(45, 45, 48), 
                 ksColor pressed_color = ksColor(30, 30, 30), double radius = 16, int resolution = 4);

        //                         Methods
        virtual void               drawControl(sf::RenderWindow & app);
        virtual void               moveControl(double x, double y);
        virtual bool               pressed(int mouse_x, int mouse_y);
        virtual bool               isPressed();
        virtual void               released();
        virtual void               setCenter(double x, double y);
        void                       setColor(ksColor color);
        virtual void               setControlPosition(double x, double y);
        virtual void               setPressed(bool pressed);
        void                       setText(std::string str);

    private:
        //                         Data members
        ksContainer                m_container;
        ksLabel                    m_label;
        ksColor                    m_color;
        ksColor                    m_pressed_color;
};

#endif
