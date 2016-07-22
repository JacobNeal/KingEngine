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

#ifndef KS_ENTITY_LAYER_H
#define KS_ENTITY_LAYER_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include "ksEntity.h"
#include "ksWorld.h"
#include "globals.h"
#include <map>

////////////////////////////////////////////////////////////
/// \brief Class that contains a drawable layer of game entities.
///
/// \see ksEntity, ksComplex
///
////////////////////////////////////////////////////////////
class ksEntityLayer : public sf::Drawable, public sf::Transformable
{
	public:
		////////////////////////////////////////////////////////////
		/// \brief Initialize the layer of entities.
		///
		/// \param world      Reference to the world containing these entities.
		/// \param tilesheet  The tilesheet used by all entities in this layer.
		///
		////////////////////////////////////////////////////////////
		ksEntityLayer(ksWorld * world, std::string tilesheet);
		
		//void                    worldLoaded();

		////////////////////////////////////////////////////////////
		/// \brief Add a base entity to the drawable layer.
		///
		/// \param entity  Reference to the entity to be added.
		///
		/// \see purge
		///
		////////////////////////////////////////////////////////////
        void addEntity(ksEntity * entity);

		////////////////////////////////////////////////////////////
		/// \brief Set the lower and upper tile boundaries and frame
        /// delay of an entity's animation.
		///
		/// \param entity_number  Index of the entity to animate.
		/// \param lower_tile     The tile number of the lower boundary of the animation.
		/// \param upper_tile     The tile number of the upper boundary of the animation.
		/// \param frame_delay    Number of frames between each tile transition.
		///
		////////////////////////////////////////////////////////////
        void animate(int entity_number, int lower_tile, int upper_tile, int frame_delay);

		////////////////////////////////////////////////////////////
		/// \brief Press the first entity that the mouse coordinates are
        /// contained within.
		///
		/// \param mouse_x  The x screen coordinate of the mouse.
		/// \param mouse_y  The y screen coordinate of the mouse.
		///
		/// \see depressEntity
		///
		////////////////////////////////////////////////////////////
        bool pressEntity(int mouse_x, int mouse_y);

		////////////////////////////////////////////////////////////
		/// \brief Set the pressed flag of the most recently pressed
        /// entity to false.
		///
		/// \see pressEntity
		///
		////////////////////////////////////////////////////////////
		void depressEntity();

		////////////////////////////////////////////////////////////
		/// \brief Draw the layer of base game entities.
		///
		/// \param app  Reference to the renderable SFML window.
		///
		/// \see draw
		///
		////////////////////////////////////////////////////////////
		void drawLayer(sf::RenderWindow & app);

		////////////////////////////////////////////////////////////
		/// \brief The overloaded SFML pure virtual method for drawing
        /// an sf::Drawable type.
		///
		/// \param target  Reference to the SFML renderable target.
		/// \param states  Renderable SFML states associated with the window.
		///
		/// \see drawLayer
		///
		////////////////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

		////////////////////////////////////////////////////////////
		/// \brief Sort the entities in the layer by row.
		/// Currently uses an inefficient bubble sort that should be updated in the future.
		///
		////////////////////////////////////////////////////////////
        void sortEntitiesByRow();

		////////////////////////////////////////////////////////////
		/// \brief Empty the entity layer of all base entities.
		///
		/// \see addEntity
        ///
		////////////////////////////////////////////////////////////
		void purge();

		////////////////////////////////////////////////////////////
		/// \brief Update the screen position of all entities in this
        /// layer. This can be beneficial for when the camera changes.
		///
        ////////////////////////////////////////////////////////////
        void updateScreenPosition();

		////////////////////////////////////////////////////////////
		/// \brief Set the tilesheet for all the base entities.
		///
		/// \param tilesheet  The tilesheet for all the entities in this layer.
		///
		////////////////////////////////////////////////////////////
		bool setTilesheet(std::string tilesheet);

		////////////////////////////////////////////////////////////
		/// \brief Return the rectangle (x, y, width, height) in screen
        /// coordinates, of a particular base game entity.
		///
		/// \param entity_number  The index of the entity.
		///
		////////////////////////////////////////////////////////////
		ksRect getRect(int entity_number);

		////////////////////////////////////////////////////////////
		/// \brief Return the total number of entities in this layer.
		///
		////////////////////////////////////////////////////////////
		int getCount();

	private:
		////////////////////////////////////////////////////////////
		// Member Data
		////////////////////////////////////////////////////////////
        sf::VertexArray         m_array;
        ksWorld *               m_world;
        std::map<int, ksEntity *> m_entities;
		sf::Texture             m_texture;
        ksRect *                m_position;
		int                     m_num_of_entities;
		ksEntity *              m_pressedEntity;
};

#endif
