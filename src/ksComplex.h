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

#ifndef KS_COMPLEX_H
#define KS_COMPLEX_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ksEntity.h"
#include "ksPathFinder.h"
#include "ksPathNode.h"
#include "ksComplexBehavior.h"
#include "defines.h"
#include <list>

////////////////////////////////////////////////////////////
/// \brief Class that contains the complex game entity type
/// for KingEngine. This complex type allows for
/// characters to be state driven based on different
/// behavior states.
///
////////////////////////////////////////////////////////////
class ksComplex : public ksEntity
{
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Initializes the complex type
        ///
        /// \param path_finder  Reference to the complex type's path finder.
        /// \param world        Reference to the world containing the entity.
        /// \param x            The x-coordinate to position the entity.
        /// \param y            The y-coordinate to position the entity.
        /// \param z            The z-coordinate to position the entity.
        /// \param w            The width in tiles of the entity.
        /// \param h            The height in tiles of the entity.
        /// \param current_tile The sub-tile of the complex type's tilesheet.
        ///
        ////////////////////////////////////////////////////////////
        ksComplex(ksPathFinder * path_finder, ksWorld * world, int x, int y, int z, 
                  int w, int h, int current_tile);

        ////////////////////////////////////////////////////////////
        /// \brief Updates the current position of the complex type
        /// relative to its path.
        ///
        ////////////////////////////////////////////////////////////
        virtual void update();

        ////////////////////////////////////////////////////////////
        /// \brief Sets the path of the complex type using the A* path 
        /// finder as the default form of movement.
        ///
        /// \param row   The row to move the complex type to.
        /// \param col   The col to move the complex type to.
        /// \param loop  Loop the path once it's complete.
        ///
        ////////////////////////////////////////////////////////////
        void move(int row, int col, bool loop = false);

        ////////////////////////////////////////////////////////////
        /// \brief Call the seekOn method of the complex behavior class
        /// passing the desired position.
        ///
        /// \param vect  The position to seek.
        ///
        ////////////////////////////////////////////////////////////
        void seek(ksVector2D vect);

        ////////////////////////////////////////////////////////////
        /// \brief Call the fleeOn method of the complex behavior class
        /// passing the desired position.
        ///
        /// \param vect  The position to flee from.
        ///
        ////////////////////////////////////////////////////////////
        void flee(ksVector2D vect);

        ////////////////////////////////////////////////////////////
        /// \brief Call the arrive method of the complex behavior class
        /// passing the desired position.
        ///
        /// \param vect  The position to arrive at.
        ///
        ////////////////////////////////////////////////////////////
        void arrive(ksVector2D vect);

        ////////////////////////////////////////////////////////////
        /// \brief Call the pursue method of the complex behavior class
        /// passing the desired entity.
        ///
        /// \param entity  Reference to the desired entity.
        ///
        ////////////////////////////////////////////////////////////
        void pursue(ksComplex * entity);

        ////////////////////////////////////////////////////////////
        /// \brief Call the evade method of the complex behavior class
        /// passing the desired entity.
        ///
        /// \param entity  Reference to the desired entity.
        ///
        ////////////////////////////////////////////////////////////
        void evade(ksComplex * entity);

        ////////////////////////////////////////////////////////////
        /// \brief Turn on the obstacle avoidance for the complex type.
        ///
        ////////////////////////////////////////////////////////////
        void avoidObstacles();

        ////////////////////////////////////////////////////////////
        /// \brief Call the addToGroup method of the complex behavior
        /// class passing the desired entity.
        ///
        /// \param entity  Reference to the desired entity.
        ///
        /// \see clearGroup
        ///
        ////////////////////////////////////////////////////////////
        void addToGroup(ksComplex * entity);

        ////////////////////////////////////////////////////////////
        /// \brief Call the clear group method of the complex behavior
        /// class, clearing the group of entities from consideration 
        /// when performing group behaviors.
        ///
        /// \see addToGroup
        ///
        ////////////////////////////////////////////////////////////
        void clearGroup();

        ////////////////////////////////////////////////////////////
        /// \brief Call the group method of the complex behavior class
        /// so that group behaviors can be performed on this complex entity.
        ///
        ////////////////////////////////////////////////////////////
        void group();

        ////////////////////////////////////////////////////////////
        /// \brief Tags this entity if it's within range of another complex
        /// entity.
        ///
        /// \see untag
        ///
        ////////////////////////////////////////////////////////////
        void tag();

        ////////////////////////////////////////////////////////////
        /// \brief Untag this entity if it's no longer within range of
        /// another complex entity.
        ///
        /// \see tag
        ////////////////////////////////////////////////////////////
        void untag();

        ////////////////////////////////////////////////////////////
        /// \brief Toggle on or off the behavior and steering force
        /// of the complex behavior class.
        ///
        ////////////////////////////////////////////////////////////
        void toggleBehavior();
        // virtual void                    moveEntity(int x, int y, int z);

        ////////////////////////////////////////////////////////////
        /// \brief Returns the estimated next path node associated with
        /// this complex entity.
        ///
        /// \see getHeading, getVelocity, getPosition, getSide, getTag
        ////////////////////////////////////////////////////////////
        ksPathNode getNextPathNode();

        ////////////////////////////////////////////////////////////
        /// \brief Returns the heading vector based on the steering
        /// force of the complex entity.
        ///
        /// \see getNextPathNode, getVelocity, getPosition, getSide, getTag
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D getHeading();

        ////////////////////////////////////////////////////////////
        /// \brief Returns the velocity of the complex entity based on
        /// it's steering force.
        ///
        /// \see getNextPathNode, getHeading, getPosition, getSide, getTag
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D getVelocity();

        ////////////////////////////////////////////////////////////
        /// \brief Returns the current position of the complex entity.
        ///
        /// \see getNextPathNode, getHeading, getVelocity, getSide, getTag
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D getPosition();

        ////////////////////////////////////////////////////////////
        /// \brief Returns the vector that runs parallel to the complex
        /// entity's heading vector.
        ///
        /// \see getNextPathNode, getHeading, getVelocity, getPosition, getTag
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D getSide();

        ////////////////////////////////////////////////////////////
        /// \brief Returns whether or not the complex entity has been tagged
        /// by another complex entity for being within range.
        ///
        /// \see getNextPathNode, getHeading, getVelocity, getPosition, getSide
        ///
        ////////////////////////////////////////////////////////////
        bool getTag();

        ////////////////////////////////////////////////////////////
        /// \brief Returns the bounding radius of the complex entity.
        ///
        /// \see getNextPathNode, getHeading, getVelocity, getPosition, getSide, getTag
        ///
        ////////////////////////////////////////////////////////////
        int getBoundingRadius();

    protected:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        ksPathFinder *                  m_path_finder;
        ksComplexBehavior               m_behavior;
        std::list<ksPathNode>           m_path;
        std::list<ksPathNode>::iterator m_path_iter;
        ksPathNode                      m_current_path_node;
        bool                            m_loop_path;
        bool                            m_path_on;
        ksVector2D                      m_tl_delta;
        ksVector2D                      m_tr_delta;
        ksVector2D                      m_bl_delta;
        ksVector2D                      m_br_delta;
        ksVector2D                      m_center_delta;
        int                             m_start_row;
        int                             m_start_col;
        int                             m_finish_row;
        int                             m_finish_col;
        int                             m_bounding_radius;

        sf::Clock                       m_elapsed_time;
        ksVector2D                      m_heading;
        ksVector2D                      m_velocity;
        ksVector2D                      m_position;
        ksVector2D                      m_side;
        bool                            m_tag;
        bool                            m_behavior_on;
};

#endif
