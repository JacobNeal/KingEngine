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

#ifndef KS_COMPLEXBEHAVIOR_H
#define KS_COMPLEXBEHAVIOR_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ksPathFinder.h"
#include <list>

class ksComplex;

////////////////////////////////////////////////////////////
/// \brief Contains the steering behaviors for calculating group 
/// and individual behaviors for the ksComplex type.
///
////////////////////////////////////////////////////////////
class ksComplexBehavior
{
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Initializes the state of the complex behavior type.
        ///
        /// \param path_finder Reference to a path finder used for complex entities.
        /// \param world       Reference to the world for calculating the steering force of complex entities.
        /// \param vehicle     Reference to the complex entity that this behavior is for.
        ///
        ////////////////////////////////////////////////////////////
        ksComplexBehavior(ksPathFinder * path_finder, ksWorld * world, ksComplex * vehicle);

        //ksPathNode calculate();

        ////////////////////////////////////////////////////////////
        /// \brief Calculates the force using the sum of the weighted
        /// steering behaviors.
        ///
        /// \see calculatePrioritizedForce
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D calculateForce();

        ////////////////////////////////////////////////////////////
        /// \brief Calculates the steering force using the prioritized
        /// sum of the weighted behaviors.
        ///
        /// \see calculateForce
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D calculatePrioritizedForce();

        ////////////////////////////////////////////////////////////
        /// \brief Perform the seek steering behavior using the passed
        /// vector position, by normalizing the vector between the sought
        /// position and the current position, and multiplying it by the 
        /// speed.
        ///
        /// \param position  The position being seeked.
        ///
        /// \see flee, arrive, pursue, evade
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D seek(ksVector2D position);

        ////////////////////////////////////////////////////////////
        /// \brief Perform the flee steering behavior using the passed
        /// vector. This method calculates the panic distance and uses
        /// the squared value to determine whether or not it should flee.
        /// The range gets checked in the calculate method.
        ///
        /// \param position  The position being fleed from.
        ///
        /// \see seek, arrive, pursue, evade
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D flee(ksVector2D position);

        ////////////////////////////////////////////////////////////
        /// \brief Performs the arrive steering behavior, where the
        /// complex entity will slow down upon arrival at it's destination.
        ///
        /// \param position  The position to arrive at.
        ///
        /// \see seek, flee, pursue, evade
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D arrive(ksVector2D position);

        ////////////////////////////////////////////////////////////
        /// \brief Get the estimated future position of the target
        /// entity and seek that position.
        ///
        /// \param pursuit_target  The complex entity being pursued.
        ///
        /// \see seek, flee, arrive, evade
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D pursue(ksComplex * pursuit_target);

        ////////////////////////////////////////////////////////////
        /// \brief NOT CURRENTLY IMPLEMENTED.
        ///
        /// Gets the vector force that will pursue the desired
        /// target at a particular offset away from it.
        ///
        /// \param pursuit_target  The complex entity being pursued.
        /// \param offset          How far away to follow the leading entity.
        ///
        /// \see seek, flee, arrive, pursue, evade
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D offsetPursue(ksComplex * pursuit_target, ksVector2D offset);

        ////////////////////////////////////////////////////////////
        /// \brief Get the estimated future position of the target entity
        /// and flee from that position.
        ///
        /// \param evasion_target  The complex entity being evaded.
        ///
        /// \see seek, flee, arrive, pursue
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D evade(ksComplex * evasion_target);

        ////////////////////////////////////////////////////////////
        /// \brief Calculates a steering force that will avoid nearby
        /// obstacles and entities, based on who is in the group and
        /// who it closest by.
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D obstacleAvoidance();

        ////////////////////////////////////////////////////////////
        /// \brief DEPRECATED - shouldn't be used anymore.
        ///
        /// Use pathfinding to move the complex type on the shortest path
        /// to the desired row and column.
        ///
        /// \param row  The row in the world to move to.
        /// \param col  The col in the world to move to.
        ///
        ////////////////////////////////////////////////////////////
        void move(int row, int col);

        ////////////////////////////////////////////////////////////
        /// \brief Add an entity to the complex type's group so that they 
        /// can be considered when performing group separation, alignment,
        /// and cohesion.
        ///
        /// \param entity  The entity to be added for group steering behavior calculation
        ///
        /// \see clearGroup, groupOn, groupOff
        ///
        ////////////////////////////////////////////////////////////
        void addToGroup(ksComplex * entity);

        ////////////////////////////////////////////////////////////
        /// \brief Clear all complex entities from the group so that they 
        /// may not be considered when performing group behaviors.
        ///
        /// \see addToGroup, groupOn, groupOff
        ///
        ////////////////////////////////////////////////////////////
        void clearGroup();

        ////////////////////////////////////////////////////////////
        /// \brief Toggle on the seek behavior so that this complex entity
        /// will seek the desired row and column.
        ///
        /// \param vect  The vector position to seek.
        ///
        /// \see seekOff, seek
        ///
        ////////////////////////////////////////////////////////////
        void seekOn(ksVector2D vect);

        ////////////////////////////////////////////////////////////
        /// \brief Toggle off the seek behavior for this complex entity.
        ///
        /// \see seekOn, seek
        ///
        ////////////////////////////////////////////////////////////
        void seekOff();

        ////////////////////////////////////////////////////////////
        /// \brief Toggle on the flee behavior so that this complex entity
        /// will flee from the desired row and column assuming it's within 
        /// range.
        ///
        /// \param vect  The vector position to flee from.
        ///
        /// \see fleeOff, flee
        ///
        ////////////////////////////////////////////////////////////
        void fleeOn(ksVector2D vect);

        ////////////////////////////////////////////////////////////
        /// \brief Toggle off the flee behavior for this complex entity.
        ///
        /// \see fleeOn, flee
        ///
        ////////////////////////////////////////////////////////////
        void fleeOff();

        ////////////////////////////////////////////////////////////
        /// \brief Toggle on the arrive behavior for this complex entity.
        ///
        /// \param vect  The vector position to arrive at.
        ///
        /// \see arriveOff, arrive
        ///
        ////////////////////////////////////////////////////////////
        void arriveOn(ksVector2D vect);

        ////////////////////////////////////////////////////////////
        /// \brief Toggle off the arrive behavior for this complex entity.
        ///
        /// \see arriveOn, arrive
        ///
        ////////////////////////////////////////////////////////////
        void arriveOff();

        ////////////////////////////////////////////////////////////
        /// \brief Toggle on the pursuit behavior for this complex entity.
        ///
        /// \param vehicle  The complex entity being pursued.
        ///
        /// \see pursuitOff, pursue
        ///
        ////////////////////////////////////////////////////////////
        void pursuitOn(ksComplex * vehicle);

        ////////////////////////////////////////////////////////////
        /// \brief Toggle off the pursuit behavior for this complex entity.
        ///
        /// \see pursuitOn, pursue
        ///
        ////////////////////////////////////////////////////////////
        void pursuitOff();

        ////////////////////////////////////////////////////////////
        /// \brief Toggle on the offset pursuit behavior for this complex entity.
        ///
        /// \param pursuit_target  The complex entity being pursued.
        /// \param offset          How far away to follow the leading entity.
        ///
        /// \see offsetPursuitOff, offsetPursue
        ///
        ////////////////////////////////////////////////////////////
        void offsetPursuitOn(ksComplex * vehicle, ksVector2D offset);

        ////////////////////////////////////////////////////////////
        /// \brief Toggle off the offset pursuit behavior for this complex entity.
        ///
        /// \see offsetPursuitOn, offsetPursue
        ///
        ////////////////////////////////////////////////////////////
        void offsetPursuitOff();

        ////////////////////////////////////////////////////////////
        /// \brief Toggle on the evasion behavior for this complex entity.
        ///
        /// \param vehicle  The complex entity being evaded.
        ///
        /// \see evasionOff, evade
        ///
        ////////////////////////////////////////////////////////////
        void evasionOn(ksComplex * vehicle);

        ////////////////////////////////////////////////////////////
        /// \brief Toggle off the evasion behavior for this complex entity.
        ///
        /// \see evasionOn, evade
        ///
        ////////////////////////////////////////////////////////////
        void evasionOff();

        ////////////////////////////////////////////////////////////
        /// \brief Toggle on the group behaviors so that this complex
        /// entity will have group separation, alignment and cohesion
        /// within it's group.
        ///
        /// \see groupOff
        ///
        ////////////////////////////////////////////////////////////
        void groupOn();

        ////////////////////////////////////////////////////////////
        /// \brief Toggle off the group behaviors for this complex entity.
        ///
        /// \see groupOn
        ///
        ////////////////////////////////////////////////////////////
        void groupOff();

        ////////////////////////////////////////////////////////////
        /// \brief Toggle on the obstacle avoidance behavior for this
        /// complex entity.
        ///
        /// \see obstacleOff, obstacleAvoidance
        ///
        ////////////////////////////////////////////////////////////
        void obstacleOn();

        ////////////////////////////////////////////////////////////
        /// \brief Toggle off the obstacle avoidance behavior for this
        /// complex entity.
        ///
        /// \see obstacleOn, obstacleAvoidance
        ///
        ////////////////////////////////////////////////////////////
        void obstacleOff();

        ////////////////////////////////////////////////////////////
        /// \brief Return the estimated next path node of this complex entity.
        ///
        ////////////////////////////////////////////////////////////
        ksPathNode getNextPathNode();

        ////////////////////////////////////////////////////////////
        /// \brief Returns the path heading of the vehicle.
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D getPathHeading();

    protected:
        ////////////////////////////////////////////////////////////
        /// \brief Ensure that the passed row is a valid row, and if it's
        /// not, adjust it and return the correct max value.
        ///
        /// \param row  The row to check the boundaries of.
        ///
        /// \see applyColumnBoundaries
        ///
        ////////////////////////////////////////////////////////////
        int applyRowBoundaries(int row);

        ////////////////////////////////////////////////////////////
        /// \brief Ensure that the passed column is a valid column, and if
        /// it's not, adjust it and return the correct max value.
        ///
        /// \param col  The column to check the boundaries of.
        ///
        /// \see applyRowBoundaries
        ///
        ////////////////////////////////////////////////////////////
        int applyColumnBoundaries(int col);

        ////////////////////////////////////////////////////////////
        /// \brief Get the node position from ksWorld for the passed row
        /// and column and set up all the memnbers of the path node.
        ///
        /// \param row  The row of the node position.
        /// \param col  The column of the node position.
        ///
        ////////////////////////////////////////////////////////////
        ksPathNode getNodePosition(int row, int col);

        ////////////////////////////////////////////////////////////
        /// \brief Move the complex entity incrementally using the 
        /// difference between the current and next nodes (delta) in
        /// the number of transition steps between nodes.
        ///
        /// \param transition_num The number of steps to take between nodes.
        ///
        ////////////////////////////////////////////////////////////
        void moveInc(int transition_num);

        ////////////////////////////////////////////////////////////
        /// \brief Allow for the next added force to be added if there's
        /// enough remaining force relative to the maximum steering force.
        /// If there isn't enough remaining force, then fill the remainder
        /// of the steering force with the incoming force. Returns false
        /// if there wasn't enough remaining force.
        ///
        /// \param force  The new steering force to be added.
        ///
        ////////////////////////////////////////////////////////////
        bool accumulateForce(ksVector2D force);

        ////////////////////////////////////////////////////////////
        /// \brief Converts a point, heading, side and position to local
        /// space for behavior based calculations.
        ///
        /// \param point    The point to be converted.
        /// \param heading  The heading vector of the complex entity.
        /// \param side     The vector running parallel to the heading vector.
        /// \param position The position of the complex entity.
        ///
        /// \see getPointToWorldSpace, getVectorToWorldSpace
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D getPointToLocalSpace(ksVector2D point, ksVector2D heading,
                                        ksVector2D side, ksVector2D position);

        ////////////////////////////////////////////////////////////
        /// \brief Converts a point, heading, side, and position to
        /// world space for behavior based calculations.
        ///
        /// \param point    The point to be converted.
        /// \param heading  The heading vector of the complex entity.
        /// \param side     The vector running parallel to the heading vector.
        /// \param position The position of the complex entity.
        ///
        /// \see getPointToLocalSpace, getVectorToWorldSpace
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D getPointToWorldSpace(ksVector2D point, ksVector2D heading,
                                        ksVector2D side, ksVector2D position);

        ////////////////////////////////////////////////////////////
        /// \brief Returns a vector to world space relative to the passed
        /// vector, heading, and side.
        ///
        /// \param vect     The vector to be converted.
        /// \param heading  The heading vector of the complex entity.
        /// \param side     The vector running parallel to the heading vector.
        /// \param position The position of the complex entity.
        ///
        /// \see getPointToLocalSpace, getPointToWorldSpace
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D getVectorToWorldSpace(ksVector2D vect, ksVector2D heading,
                                         ksVector2D side);

        ////////////////////////////////////////////////////////////
        // Group Behavior
        ////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////
        /// \brief Perform separation on the group of complex entities.
        ///
        /// \see alignment, cohesion
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D separation();

        ////////////////////////////////////////////////////////////
        /// \brief Perform alignment on the group of complex entities.
        ///
        /// \see separation, cohesion
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D alignment();

        ////////////////////////////////////////////////////////////
        /// \brief Perform cohesion on the group of complex entities.
        ///
        /// \see separation, alignment
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D cohesion();

        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        ksPathFinder *      m_path_finder;
        ksWorld *           m_world;
        ksComplex *         m_vehicle;

        bool                m_seek;
        bool                m_flee;
        bool                m_pursuit;
        bool                m_offset_pursuit;
        bool                m_evasion;
        bool                m_group_on;
        bool                m_path_on;
        bool                m_obstacle;
        bool                m_arrive;

        ksComplex *         m_pursuit_target;
        ksComplex *         m_evasion_target;
        ksVector2D          m_pursuit_offset;
        ksVector2D          m_steering_force;

        ksVector2D          m_target;

        std::list<ksPathNode> m_wander_path;
        std::list<ksPathNode>::iterator m_path_iter;
        std::list<ksComplex *> m_group;

        ksVector2D          m_tl_delta;
        ksVector2D          m_tr_delta;
        ksVector2D          m_bl_delta;
        ksVector2D          m_br_delta;
        ksVector2D          m_center_delta;

        int                 m_target_row;
        int                 m_target_col;
        int                 m_target_range;

        ksPathNode          m_current_node;
        ksPathNode          m_next_node;

        ksVector2D          m_vehicle_velocity;
        ksVector2D          m_vehicle_heading;
};

#endif
