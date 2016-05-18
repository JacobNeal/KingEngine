/********************************************************
* Class:            ksContainer
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksContainer.h
*
*   Overview:
*       Class for a container of ksControls that allow
*       for the controls to be dynamically aligned when
*       the width and height of the container changes.
*
********************************************************/

#ifndef KS_CONTAINER_H
#define KS_CONTAINER_H

#include <SFML/Graphics.hpp>
#include "ksControl.h"
#include "defines.h"
#include <vector>

enum ksAlign
{
    CENTER = 1,
    ROW = 2,
    COLUMN = 3
};

class ksContainer : public ksControl, public sf::Drawable, public sf::Transformable
{
    public:
        //                       Constructors
        ksContainer(double width, double height, ksAlign alignment, ksColor color = ksColor(45, 45, 48), double radius = 16, int resolution = 4);
        
        //                         Methods
        void                       addControl(ksControl * control);
        virtual void               draw(sf::RenderTarget & target, sf::RenderStates states) const;
        virtual void               drawControl(sf::RenderWindow & app);
        virtual bool               getVisibility();
        virtual void               moveControl(double x, double y);
        virtual bool               pressed(int mouse_x, int mouse_y);
        virtual bool               isPressed();
        virtual void               resize(int screen_width, int screen_height);
        virtual void               setCenter(double x, double y);
        void                       setColor(ksColor color);
        virtual void               setControlPosition(double x, double y);
        virtual void               setOpacity(double opacity);
        virtual void               setPressed(bool pressed);
        void                       setWidth(double width);
        void                       setHeight(double height);
        virtual void               setVisibility(bool visibility);
        
    private:
        void                       update();
        void                       updateContainedControls();
        
        //                         Members
        ksAlign                    m_alignment;
        sf::VertexArray            m_array;
        std::vector<ksControl *>   m_controls;
        double                     m_width;
        double                     m_height;
        bool                       m_pressed;
        ksColor                    m_color;
        double                     m_radius;
        int                        m_resolution;
        bool                       m_visible;
        double                     m_opacity;
};

#endif