/********************************************************
* Class:            ksControlLayer
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksControlLayer.h
*
*   Overview:
*       Class that contains a drawable layer of in game
*       controls. 
*       These include: 
*           ksButton, ksText, and ksContainer.
*
********************************************************/

#ifndef KS_CONTROL_LAYER_H
#define KS_CONTROL_LAYER_H

#include <SFML/Graphics.hpp>
#include "ksControl.h"
#include <map>

class ksControlLayer : public sf::Drawable, public sf::Transformable
{
    public:
        //                  Constructors
        ksControlLayer(std::string tilesheet);

        //                  Methods
        void                addControl(ksControl * control);
        void                drawLayer(sf::RenderWindow & app);
        virtual void        draw(sf::RenderTarget & target, sf::RenderStates states) const;
        bool                pressControl(int mouse_x, int mouse_y);
        void                depressControl();
        void                purge();

        //                  Mutators
        bool                setTilesheet(std::string tilesheet);

        //                  Accessor Methods
        int                 getCount();

    private:
        //                  Data members
        sf::VertexArray     m_array;
        std::map<int, ksControl *> m_controls;
        sf::Texture         m_texture;
        int                 m_num_of_controls;
        ksControl *         m_pressedControl;
};

#endif
