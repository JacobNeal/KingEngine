////////////////////////////////////////////////////////////
//
// KingEngine
// The MIT License (MIT)
// Copyright (c) 2016 Beyond Parallel
//
// Permission is hereby granted, free of charge, to any person 
// obtaining a copy of this software and associated documentation 
// files (the "Software"), to deal in the Software without restriction, 
// including without limitation the rights to use, copy, modify, merge, 
// publish, distribute, sublicense, and/or sell copies of the Software, 
// and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be 
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////

#ifndef KS_CONTAINER_H
#define KS_CONTAINER_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////
/// \brief Class for a container of ksControls that allow for the
/// controls to be dynamically aligned when the width and height
/// of the container changes.
///
/// \see ksControl
///
////////////////////////////////////////////////////////////
class ksContainer : public ksControl, public sf::Drawable, public sf::Transformable
{
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Initialize the ksContainer class.
        ///
        /// \param width  The width in pixels of the container.
        /// \param height The height in pixels of the container.
        /// \param alignment The alignment of all the controls in the container. (CENTER, ROW, COLUMN)
        /// \param color     The background color of the container.
        /// \param radius    The border radius of the corners of the container.
        /// \param resolution How many subtriangles to split each corner into. (Higher number, less efficiency).
        ///
        ////////////////////////////////////////////////////////////
        ksContainer(double width, double height, ksAlign alignment, ksColor color = ksColor(45, 45, 48), double radius = 16, int resolution = 4);
        
        ////////////////////////////////////////////////////////////
        /// \brief Add a control to the list of controls contained within
        /// the container.
        ///
        /// \param control  Reference to the control to add to the container.
        ///
        ////////////////////////////////////////////////////////////
        void addControl(ksControl * control);

        ////////////////////////////////////////////////////////////
        /// \brief Override the default behavior for drawing objects in SFML.
        ///
        /// \param target  Reference to the SFML renderable target.
        /// \param states  Reference to any SFML renderable states.
        ///
        ////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

        ////////////////////////////////////////////////////////////
        /// \brief Draws the container along with any other associated object
        /// to the screen.
        ///
        /// \param app  Reference to the renderable window.
        ///
        ////////////////////////////////////////////////////////////
        virtual void drawControl(sf::RenderWindow & app);

        ////////////////////////////////////////////////////////////
        /// \brief Return the visibility of the control.
        ///
        /// \see setVisibility
        ////////////////////////////////////////////////////////////
        virtual bool getVisibility();

        ////////////////////////////////////////////////////////////
        /// \brief Move the container and any associated controls within
        /// the container by the passed (x, y) values.
        ///
        /// \param x  How much on the x-axis to move the control.
        /// \param y  How much on the y-axis to move the control.
        ///
        ////////////////////////////////////////////////////////////
        virtual void moveControl(double x, double y);

        ////////////////////////////////////////////////////////////
        /// \brief Return whether or not the control is pressed within
        /// the passed coordinates.
        ///
        /// \param mouse_x  The mouse x-coordinate.
        /// \param mouse_y  The mouse y-coordinate.
        ///
        /// \see isPressed
        ///
        ////////////////////////////////////////////////////////////
        virtual bool pressed(int mouse_x, int mouse_y);

        ////////////////////////////////////////////////////////////
        /// \brief Return whether or not the control is already pressed.
        ///
        /// \see pressed
        ///
        ////////////////////////////////////////////////////////////
        virtual bool isPressed();

        ////////////////////////////////////////////////////////////
        /// \brief Resize the container based on the new application
        /// width and height.
        ///
        /// \param screen_width  The new screen width in pixels.
        /// \param screen_height The new screen height in pixels.
        ///
        ////////////////////////////////////////////////////////////
        virtual void resize(int screen_width, int screen_height);

        ////////////////////////////////////////////////////////////
        /// \brief Position the control relative to the passed (x, y) pair
        /// that represents the future center position.
        ///
        /// \param x  The new x-coordinate to center the container around.
        /// \param y  The new y-coordinate to center the container around.
        ///
        /// \see setControlPosition
        ///
        ////////////////////////////////////////////////////////////
        virtual void setCenter(double x, double y);

        ////////////////////////////////////////////////////////////
        /// \brief Set the color of the rounded rectangle of the container.
        ///
        /// \param color  The color of the background of the container.
        ///
        /// \see setOpacity
        ///
        ////////////////////////////////////////////////////////////
        void setColor(ksColor color);

        ////////////////////////////////////////////////////////////
        /// \brief Position the control relative to the passed (x, y) pair.
        ///
        /// \param x  The x-coordinate to position the container at.
        /// \param y  The y-coordinate to position the container at.
        ///
        /// \see setCenter
        ///
        ////////////////////////////////////////////////////////////
        virtual void setControlPosition(double x, double y);

        ////////////////////////////////////////////////////////////
        /// \brief Update the opacity of the container and all contained
        /// controls.
        ///
        /// \param opacity  The opacity from (0.0-1.0) to set the container to.
        ///
        /// \see setColor
        ///
        ////////////////////////////////////////////////////////////
        virtual void setOpacity(double opacity);

        ////////////////////////////////////////////////////////////
        /// \brief Set whether or not the control is pressed.
        ///
        /// \param pressed  Whether or not the control is pressed.
        ///
        /// \see pressed, isPressed
        ///
        ////////////////////////////////////////////////////////////
        virtual void setPressed(bool pressed);

        ////////////////////////////////////////////////////////////
        /// \brief Set the width of the container and dynamically update
        /// the position of all the contained controls.
        ///
        /// \param width  The new width to set the container to.
        ///
        /// \see setHeight
        ///
        ////////////////////////////////////////////////////////////
        void setWidth(double width);

        ////////////////////////////////////////////////////////////
        /// \brief Set the height of the container and dynamically update
        /// the position of all the contained controls.
        ///
        /// \param height  The new height to set the container to.
        ///
        /// \see setWidth
        ///
        ////////////////////////////////////////////////////////////
        void setHeight(double height);

        ////////////////////////////////////////////////////////////
        /// \brief Set the visibility of the control.
        ///
        /// \param visibility  Whether or not the control should be visible.
        ///
        ////////////////////////////////////////////////////////////
        virtual void setVisibility(bool visibility);
        
    private:
        ////////////////////////////////////////////////////////////
        /// \brief Updates the current state of the container.
        ///
        /// \see updateContainedControls
        ///
        ////////////////////////////////////////////////////////////
        void update();

        ////////////////////////////////////////////////////////////
        /// \brief Updates the position of the controls contained within
        /// the container.
        ///
        /// \see update
        ///
        ////////////////////////////////////////////////////////////
        void updateContainedControls();
        
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
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