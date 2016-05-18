/********************************************************
* Class:            ksImageControl
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksImageControl.h
*
*   Overview:
*       Allows a full image from it's own texture to be
*       drawn and used as a control in the engine.
*
********************************************************/

#ifndef KS_IMAGE_CONTROL_H
#define KS_IMAGE_CONTROL_H

#include "ksControl.h"
#include <SFML/Graphics.hpp>

class ksImageControl : public ksControl
{
    public:
        //                         Constructors
        ksImageControl(std::string filename, double x, double y, int width, int height);

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
        virtual void               setVisibility(bool visibility);
      
    private:
        //                         Members
        sf::Texture                m_texture;
        sf::Sprite                 m_sprite;
        bool                       m_visible;
        bool                       m_pressed;
};

#endif