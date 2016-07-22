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

#ifndef KS_CONTROL_H
#define KS_CONTROL_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include "defines.h"

////////////////////////////////////////////////////////////
/// \brief Class that contains an abstract base control that is
/// drawable and customized using a VertexArray.
///
/// This class cannot be instantiated.
///
////////////////////////////////////////////////////////////
class ksControl
{
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Draws the control to the screen.
        ///
        /// \param app  The renderable window to draw to.
        ///
        ////////////////////////////////////////////////////////////
        virtual void drawControl(sf::RenderWindow & app) = 0;

        ////////////////////////////////////////////////////////////
        /// \brief Return the visibility of the control.
        ///
        /// \see setVisibility
        ////////////////////////////////////////////////////////////
        virtual bool getVisibility() = 0;

        ////////////////////////////////////////////////////////////
        /// \brief Move the control by the passed (x, y) values.
        ///
        /// \param x  How much on the x-axis to move the control.
        /// \param y  How much on the y-axis to move the control.
        ///
        ////////////////////////////////////////////////////////////
        virtual void moveControl(double x, double y) = 0;

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
        virtual bool pressed(int mouse_x, int mouse_y) = 0;

        ////////////////////////////////////////////////////////////
        /// \brief Return whether or not the control is already pressed.
        ///
        /// \see pressed
        ///
        ////////////////////////////////////////////////////////////
        virtual bool isPressed() = 0;

        ////////////////////////////////////////////////////////////
        /// \brief Resize the control based on the new application
        /// width and height.
        ///
        /// \param screen_width  The new screen width in pixels.
        /// \param screen_height The new screen height in pixels.
        ///
        ////////////////////////////////////////////////////////////
        virtual void resize(int screen_width, int screen_height) = 0;

        ////////////////////////////////////////////////////////////
        /// \brief Position the control relative to the passed (x, y) pair
        /// that represents the future center position.
        ///
        /// \param x  The new x-coordinate to center the control around.
        /// \param y  The new y-coordinate to center the control around.
        ///
        /// \see setControlPosition
        ///
        ////////////////////////////////////////////////////////////
        virtual void setCenter(double x, double y) = 0;

        ////////////////////////////////////////////////////////////
        /// \brief Position the control relative to the passed (x, y) pair.
        ///
        /// \param x  The x-coordinate to position the control at.
        /// \param y  The y-coordinate to position the control at.
        ///
        /// \see setCenter
        ///
        ////////////////////////////////////////////////////////////
        virtual void setControlPosition(double x, double y) = 0;

        ////////////////////////////////////////////////////////////
        /// \brief Update the opacity of the control.
        ///
        /// \param opacity  The opacity from (0.0-1.0) to set the control to.
        ///
        ////////////////////////////////////////////////////////////
        virtual void setOpacity(double opacity) = 0;

        ////////////////////////////////////////////////////////////
        /// \brief Set whether or not the control is pressed.
        ///
        /// \param pressed  Whether or not the control is pressed.
        ///
        /// \see pressed, isPressed
        ///
        ////////////////////////////////////////////////////////////
        virtual void setPressed(bool pressed) = 0;

        ////////////////////////////////////////////////////////////
        /// \brief Set the visibility of the control.
        ///
        /// \param visibility  Whether or not the control should be visible.
        ///
        ////////////////////////////////////////////////////////////
        virtual void setVisibility(bool visibility) = 0;
};

#endif
