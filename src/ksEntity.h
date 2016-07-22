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

#ifndef KS_ENTITY_H
#define KS_ENTITY_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ksVector2D.h"
#include "ksTile.h"
#include "ksRect.h"
#include "ksWorld.h"
#include "ksPathNode.h"
#include "defines.h"
#include <list>
#include <algorithm>

////////////////////////////////////////////////////////////
/// \brief Class for the base game entity in KingEngine.
///
/// \see ksComplex
///
////////////////////////////////////////////////////////////
class ksEntity
{
	public:
        ////////////////////////////////////////////////////////////
		/// \brief Initializes the base game entity.
		///
		/// \param world        Reference to the world which contains this entity.
		/// \param x            The x world coordinate to position this entity.
		/// \param y            The y world coordinate to position this entity.
		/// \param z            The z world coordinate to position this entity.
		/// \param w            The width in tiles of this entity.
		/// \param h            The height in tiles of this entity.
		/// \param current_tile The subrectangle on the entity tilesheet.
		///
		////////////////////////////////////////////////////////////
        ksEntity(ksWorld * world, int x, int y, int z, int w, int h, int current_tile);

        ////////////////////////////////////////////////////////////
		/// \brief Animate the entity between the lower and upper tile
        /// bounds with the given animation delay (in frames).
		///
		/// \see setAnimationDelay, setAnimationLower, setAnimationUpper
		///
		////////////////////////////////////////////////////////////
        void animate();

		////////////////////////////////////////////////////////////
		/// \brief Call the frame by frame update method. This method
        /// should be overridden in any derived classes.
		///
		////////////////////////////////////////////////////////////
        virtual void update();

		////////////////////////////////////////////////////////////
		/// \brief Move the entity by the passed x, y, and z coordinates.
		///
		/// \param x  The amount to move along the x-axis in world coordinates.
		/// \param y  The amount to move along the y-axis in world coordinates.
		/// \param z  The amount to move along the z-axis in world coordinates.
		///
		/// \see updateScreenPosition
		///
		////////////////////////////////////////////////////////////
        void moveEntity(int x, int y, int z);

		////////////////////////////////////////////////////////////
		/// \brief Set the lower tile boundary for the animation of the
        /// entity.
		/// \param lower_tile  The lower boundary tile number for the entity's animation.
		///
		/// \see setAnimationUpper, setAnimationDelay
		///
		////////////////////////////////////////////////////////////
		void setAnimationLower(int lower_tile);

		////////////////////////////////////////////////////////////
		/// \brief Set the upper tile boundary for the animation of the
        /// entity.
		/// \param upper_tile  The upper boundary tile number for the entity's animation.
		///
		/// \see setAnimationLower, setAnimationDelay
		///
		////////////////////////////////////////////////////////////
		void setAnimationUpper(int upper_tile);

        ////////////////////////////////////////////////////////////
		/// \brief Set the animation delay (in frames).
		///
		/// \param frame_delay  The number of frames between each tile transition.
		///
		/// \see setAnimationLower, setAnimationUpper
		///
		////////////////////////////////////////////////////////////
		void setAnimationDelay(int frame_delay);

		////////////////////////////////////////////////////////////
		/// \brief Set whether or not the entity is being pressed.
		///
		/// \param press  Set whether or not the entity is clicked or pressed.
		///
		/// \see isPressed
		///
		////////////////////////////////////////////////////////////
        void setPressed(bool press);

		////////////////////////////////////////////////////////////
		/// \brief Set the visibility of the entity.
		///
		/// \param visible  Whether or not the entity is visible.
		///
		/// \see isVisible
		///
		////////////////////////////////////////////////////////////
		void setVisible(bool visible);

		////////////////////////////////////////////////////////////
		/// \brief Set the position of the entity to the passed path node.
		///
		/// \param node  The path node to update the entity's position to.
		///
		////////////////////////////////////////////////////////////
        void setTilePosition(ksPathNode node);

		////////////////////////////////////////////////////////////
		/// \brief Update the position of the entity on the screen by
        /// converting the (x, y, z) world coordinates into screen coordinates.
		///
		/// \see moveEntity
		///
		////////////////////////////////////////////////////////////
        void updateScreenPosition();

		////////////////////////////////////////////////////////////
		/// \brief Returns the position of the entity in vector form.
		///
		////////////////////////////////////////////////////////////
		const ksPathNode & getTilePosition();

		////////////////////////////////////////////////////////////
		/// \brief Returns the texture coordinates of the entity.
		///
		////////////////////////////////////////////////////////////
		const ksRect & getTextureCoord();

		////////////////////////////////////////////////////////////
		/// \brief Returns the width in tiles of the entity.
		///
		/// \see getHeight
		///
		////////////////////////////////////////////////////////////
		int getWidth();

		////////////////////////////////////////////////////////////
		/// \brief Returns the height in tiles of the entity.
		///
		/// \see getWidth
		///
		////////////////////////////////////////////////////////////
        int getHeight();

		////////////////////////////////////////////////////////////
		/// \brief Returns whether or not the entity is being clicked or pressed.
		///
		/// \see pressed
		///
		////////////////////////////////////////////////////////////
        bool isPressed();

		////////////////////////////////////////////////////////////
		/// \brief Returns whether or not the entity is visible.
		///
		/// \see setVisible
		///
		////////////////////////////////////////////////////////////
		bool isVisible();

		////////////////////////////////////////////////////////////
		/// \brief Returns the x world coordinate of the entity.
		///
		////////////////////////////////////////////////////////////
        int X();

		////////////////////////////////////////////////////////////
		/// \brief Returns the y world coordinate of the entity.
		///
		////////////////////////////////////////////////////////////
        int Y();

		////////////////////////////////////////////////////////////
		/// \brief Returns the z world coordinate of the entity.
		///
		////////////////////////////////////////////////////////////
        int Z();

	protected:
		////////////////////////////////////////////////////////////
		// Member Data
		////////////////////////////////////////////////////////////
        ksWorld *          m_world;
        ksPathNode         m_current_node;
        int                m_width;
        int                m_height;
		int                m_current_tile;
		ksRect             m_texture_coord;
		int                m_upper_tile;
		int                m_lower_tile;
		int                m_anim_delay;
		int                m_frame;
		bool               m_pressed;
		bool               m_visible;
        int                m_x;
        int                m_y;
        int                m_z;
        int                m_w;
        int                m_h;
};

#endif
