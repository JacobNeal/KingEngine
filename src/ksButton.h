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

#ifndef KS_BUTTON_H
#define KS_BUTTON_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include "ksContainer.h"
#include "ksLabel.h"

////////////////////////////////////////////////////////////
/// \brief Button class that inherits from the base game control.
///
/// \see ksControl
///
////////////////////////////////////////////////////////////
class ksButton : public ksControl
{
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Initializes a button control which is a container
        /// with a label aligned in the center.
        ///
        /// \param font          Reference to the desired font for the button.
        /// \param text          The text for the button.
        /// \param w             The width of the button in pixels.
        /// \param h             The height of the button in pixels.
        /// \param color         The color of the button's container.
        /// \param pressed_color The color of the button while pressed.
        /// \param radius        The border radius of the button's container.
        /// \param resolution    The number of subtriangles in each corner.
        /// The higher the number the greater the performance impact.
        ///
        /// \see setColor, setControlPosition, setOpacity, setText
        ///
        ////////////////////////////////////////////////////////////
        ksButton(sf::Font * font, std::string text, double w, double h, ksColor color = ksColor(45, 45, 48), 
                 ksColor pressed_color = ksColor(30, 30, 30), double radius = 16, int resolution = 4);

        ////////////////////////////////////////////////////////////
        /// \brief Draws the control along with any other associated
        /// object to the screen.
        ///
        /// \param app  The renderable window to display the control in.
        ///
        ////////////////////////////////////////////////////////////
        virtual void drawControl(sf::RenderWindow & app);

        ////////////////////////////////////////////////////////////
        /// \brief Return the visibility of the button control.
        ///
        ////////////////////////////////////////////////////////////
        virtual bool getVisibility();

        ////////////////////////////////////////////////////////////
        /// \brief Move all the vertices inside of this control by
        /// the x and y modifiers passed.
        ///
        /// \param x The amount of pixels on the x-axis to move the control.
        /// \param y The amount of pixels on the y-axis to move the control.
        ///
        ////////////////////////////////////////////////////////////
        virtual void moveControl(double x, double y);

        ////////////////////////////////////////////////////////////
        /// \brief Returns whether or not the button is pressed within
        /// the given mouse coordinates.
        ///
        /// \param mouse_x  The mouse x coordinate.
        /// \param mouse_y  The mouse y coordinate.
        ///
        ////////////////////////////////////////////////////////////
        virtual bool pressed(int mouse_x, int mouse_y);

        ////////////////////////////////////////////////////////////
        /// \brief Returns whether or not the button is pressed.
        ///
        ////////////////////////////////////////////////////////////
        virtual bool isPressed();

        ////////////////////////////////////////////////////////////
        /// \brief Sets the control to be in the released state.
        ///
        ////////////////////////////////////////////////////////////
        virtual void released();

        ////////////////////////////////////////////////////////////
        /// \brief Resize the button container and contained label
        /// based on the new application width and height.
        ///
        ////////////////////////////////////////////////////////////
        virtual void resize(int screen_width, int screen_height);

        ////////////////////////////////////////////////////////////
        /// \brief Position the control relative to the passed (x, y)
        /// pair that represents the future center position.
        ///
        /// \param x  The x-coordinate to center the button in.
        /// \param y  The y-coordinate to center the button in.
        ///
        ////////////////////////////////////////////////////////////
        virtual void setCenter(double x, double y);

        ////////////////////////////////////////////////////////////
        /// \brief Set the color of the container underlying the button.
        ///
        /// \param color  The color to set the button's container to.
        ///
        ////////////////////////////////////////////////////////////
        void setColor(ksColor color);

        ////////////////////////////////////////////////////////////
        /// \brief Position the control relative to the passed (x, y)
        /// pair.
        ///
        /// \param x  Set the button position to the x-coordinate.
        /// \param y  Set the button position to the y-coordinate.
        ///
        ////////////////////////////////////////////////////////////
        virtual void setControlPosition(double x, double y);

        ////////////////////////////////////////////////////////////
        /// \brief Set the opacity of the button's container and label.
        ///
        /// \param opacity  The opacity of the button from 0.0 to 1.0.
        ///
        ////////////////////////////////////////////////////////////
        virtual void setOpacity(double opacity);

        ////////////////////////////////////////////////////////////
        /// \brief Sets whether or not the button is pressed.
        /// (this can allow for a button to be depressed)
        ///
        /// \param pressed  Whether or not the button is pressed.
        ///
        ////////////////////////////////////////////////////////////
        virtual void setPressed(bool pressed);

        ////////////////////////////////////////////////////////////
        /// \brief Sets the text of the button control to the passed value.
        ///
        /// \param str  The string to set the button's text to.
        ///
        ////////////////////////////////////////////////////////////
        void setText(std::string str);

        ////////////////////////////////////////////////////////////
        /// \brief Sets the visibility of the button container and label.
        ///
        /// \param visibility  Whether or not the button is visible.
        ///
        ////////////////////////////////////////////////////////////
        virtual void setVisibility(bool visibility);

    private:
        ////////////////////////////////////////////////////////////
        // Member Data
        ////////////////////////////////////////////////////////////
        ksContainer                m_container;
        ksLabel                    m_label;
        ksColor                    m_color;
        ksColor                    m_pressed_color;
};

#endif
