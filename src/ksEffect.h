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

#ifndef KS_EFFECTS_H
#define KS_EFFECTS_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include "ksTile.h"
#include <map>

////////////////////////////////////////////////////////////
/// \brief Contains all effect lighting in the engine
/// and compliments ksWorld rendering with providing
/// color lighting to all the tiles.
///
////////////////////////////////////////////////////////////
class ksEffect : public sf::Drawable, public sf::Transformable
{
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Initialize the effect layer of lights to default values.
        ///
        ////////////////////////////////////////////////////////////
        ksEffect();

        ////////////////////////////////////////////////////////////
        /// \brief Add a light (colored octagon) into the effect layer 
        /// and draw a triangle beam connecting the light source with it's
        /// destination if the starting location != ending location.
        ///
        /// \param start    The starting point of the light source. (Where it's emitting from)
        /// \param end      The ending point of the light source.
        /// \param diameter The diameter of the light source.
        /// \param first    The starting color of the light source.
        /// \param second   The secondary color of the light source. (For animated or flickering lights)
        ///
        /// \see clear
        ///
        ////////////////////////////////////////////////////////////
        void addLight(ksVector2D start, ksVector2D end, int diameter, 
                      sf::Color first, sf::Color second);

        ////////////////////////////////////////////////////////////
        /// \brief Clear the effect layer of all active lights.
        ///
        /// \see addLight
        ///
        ////////////////////////////////////////////////////////////
        void clear();

        ////////////////////////////////////////////////////////////
        /// \brief Overloads the draw method of drawable entities in
        /// the SFML library, so that this layer can be drawn.
        ///
        /// \param target  Reference to the SFML renderable target.
        /// \param states  Reference to any SFML renderable states.
        ///
        ////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

        ////////////////////////////////////////////////////////////
        /// \brief Returns the first color of one of the lights.
        ///
        /// \param index  The index of the light to return the color of.
        ///
        /// \see getSecondColor
        ///
        ////////////////////////////////////////////////////////////
        sf::Color getFirstColor(int index);

        ////////////////////////////////////////////////////////////
        /// \brief Returns the second color of one of the lights.
        ///
        /// \param index  The index of the light to return the color of.
        ///
        /// \see getFirstColor
        ///
        ////////////////////////////////////////////////////////////
        sf::Color getSecondColor(int index);

        ////////////////////////////////////////////////////////////
        /// \brief Returns the first duration of the effect layer.
        ///
        /// \see getSecondDuration
        ///
        ////////////////////////////////////////////////////////////
        int getFirstDuration();

        ////////////////////////////////////////////////////////////
        /// \brief Returns the second duration of the effect layer.
        ///
        /// \see getFirstDuration
        ///
        ////////////////////////////////////////////////////////////
        int getSecondDuration();

        ////////////////////////////////////////////////////////////
        /// \brief Sets the first color of one of the lights.
        ///
        /// \param index  The index of the light to set the color of.
        ///
        /// \param first  The color to set the light to.
        ///
        /// \see setSecondColor
        ///
        ////////////////////////////////////////////////////////////
        void setFirstColor(int index, sf::Color first);

        ////////////////////////////////////////////////////////////
        /// \brief Sets the second color of one of the lights.
        ///
        /// \param index   The index of the light to set the color of.
        ///
        /// \param second  The color to set the light to.
        ///
        /// \see setFirstColor
        ///
        ////////////////////////////////////////////////////////////
        void setSecondColor(int index, sf::Color second);

        ////////////////////////////////////////////////////////////
        /// \brief Sets the first duration of the effect layer.
        ///
        /// \param duration  Number of frames to stay the first color.
        ///
        /// \see setSecondDuration
        ///
        ////////////////////////////////////////////////////////////
        void setFirstDuration(int duration);

        ////////////////////////////////////////////////////////////
        /// \brief Sets the second duration of the effect layer.
        ///
        /// \param duration  Number of frames to stay the second color.
        ///
        /// \see setSecondDuration
        ///
        ////////////////////////////////////////////////////////////
        void setSecondDuration(int duration);

    private:
        ////////////////////////////////////////////////////////////
        // Member Data
        ////////////////////////////////////////////////////////////
        sf::VertexArray          m_array;
        std::map<int, sf::Color> m_first;
        std::map<int, sf::Color> m_second;
        int                      m_number_of_lights;
        //int                      m_current_color;
        int                      m_first_duration;
        int                      m_second_duration;
        //int                      m_current_frame;
};

#endif
