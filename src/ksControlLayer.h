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

#ifndef KS_CONTROL_LAYER_H
#define KS_CONTROL_LAYER_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include "ksControl.h"
#include <map>

////////////////////////////////////////////////////////////
/// \brief Class that contains a drawable layer of in game controls.
/// These include: ksButton, ksText, and ksContainer.
///
////////////////////////////////////////////////////////////
class ksControlLayer : public sf::Drawable, public sf::Transformable
{
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Initialize the control layer class.
        ///
        /// \param tilesheet  The tilesheet that the controls use.
        ///
        ////////////////////////////////////////////////////////////
        ksControlLayer(std::string tilesheet);

        ////////////////////////////////////////////////////////////
        /// \brief Adding a drawable control to the layer  of controls 
        /// to be drawn.
        ///
        /// \param control  Reference to the control to be added.
        ///
        ////////////////////////////////////////////////////////////
        void addControl(ksControl * control);

        ////////////////////////////////////////////////////////////
        /// \brief Draw the layer of controls to screen using the render
        /// window that was passed.
        ///
        /// \param app  Reference to the renderable window to draw in.
        ///
        /// \see draw
        ///
        ////////////////////////////////////////////////////////////
        void drawLayer(sf::RenderWindow & app);

        ////////////////////////////////////////////////////////////
        /// \brief Override the default behavior for drawing objects in SFML.
        ///
        /// \param target  Reference to the SFML renderable target.
        /// \param states  Reference to any SFML renderable states.
        ///
        ////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

        ////////////////////////////////////////////////////////////
        /// \brief Returns whether or not one of the controls is pressed
        /// based on the passed mouse coordinates.
        ///
        /// \param mouse_x  The mouse x-coordinate.
        /// \param mouse_y  The mouse y-coordinate.
        ///
        /// \see depressControl
        ///
        ////////////////////////////////////////////////////////////
        bool pressControl(int mouse_x, int mouse_y);

        ////////////////////////////////////////////////////////////
        /// \brief Set the pressed flag of the most recently pressed
        /// control to false.
        ///
        /// \see pressControl
        ///
        ////////////////////////////////////////////////////////////
        void depressControl();

        ////////////////////////////////////////////////////////////
        /// \brief Remove all the drawable controls in the Control Layer.
        ///
        /// \see addControl
        ///
        ////////////////////////////////////////////////////////////
        void purge();

        ////////////////////////////////////////////////////////////
        /// \brief Resize all of the controls within this layer based
        /// on the new application width and height.
        ///
        /// \param screen_width  The new width of the screen.
        /// \param screen_height The new height of the screen.
        ///
        ////////////////////////////////////////////////////////////
        void resize(int screen_width, int screen_height);

        ////////////////////////////////////////////////////////////
        /// \brief Change the tilesheet that all the controls in the
        /// layer will use.
        ///
        /// \param tilesheet  The tilesheet that all the controls use in the layer.
        ///
        ////////////////////////////////////////////////////////////
        bool setTilesheet(std::string tilesheet);

        ////////////////////////////////////////////////////////////
        /// \brief Return the number of controls in this layer.
        ///
        /// \see addControl, purge
        ///
        ////////////////////////////////////////////////////////////
        int getCount();

    private:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        sf::VertexArray     m_array;
        std::map<int, ksControl *> m_controls;
        sf::Texture         m_texture;
        int                 m_num_of_controls;
        ksControl *         m_pressedControl;
};

#endif
