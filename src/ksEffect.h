/********************************************************
* Class:            ksEffect
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksEffect.h
*
*   Overview:
*       Contains all effect lighting in the engine
*       and compliments ksWorld rendering with providing
*       color lighting to all the tiles.
*
********************************************************/

#ifndef KS_EFFECTS_H
#define KS_EFFECTS_H

#include <SFML/Graphics.hpp>
#include "ksTile.h"
#include <map>

class ksEffect : public sf::Drawable, public sf::Transformable
{
    public:
        //                       Constructors
        ksEffect();

        //                       Methods
        void                     addLight(ksVector2D start, ksVector2D end, int diameter, 
                                          sf::Color first, sf::Color second);
        void                     clear();
        virtual void             draw(sf::RenderTarget & target, sf::RenderStates states) const;

        //                       Accessor methods
        sf::Color                getFirstColor(int index);
        sf::Color                getSecondColor(int index);
        int                      getFirstDuration();
        int                      getSecondDuration();

        //                       Mutators
        void                     setFirstColor(int index, sf::Color first);
        void                     setSecondColor(int index, sf::Color second);
        void                     setFirstDuration(int duration);
        void                     setSecondDuration(int duration);

    private:
        //                       Data members
        sf::VertexArray          m_array;
        std::map<int, sf::Color> m_first;
        std::map<int, sf::Color> m_second;
        int                      m_number_of_lights;
        int                      m_current_color;
        int                      m_first_duration;
        int                      m_second_duration;
        int                      m_current_frame;
};

#endif
