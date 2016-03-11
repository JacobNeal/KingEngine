/*********************************************************
* Class:            ksComplexBehavior
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksComplexBehavior.h
*
*   Overview:
*       Contains the steering behaviors for calculating
*       group and individual behaviors for the ksComplex
*       type.
*
*********************************************************/

#ifndef KS_COMPLEXBEHAVIOR_H
#define KS_COMPLEXBEHAVIOR_H

#include "ksPathFinder.h"
#include <list>

class ksComplex;

class ksComplexBehavior
{
    public:
        //                  Constructors
        ksComplexBehavior(ksPathFinder * path_finder, ksWorld * world, ksComplex * vehicle);

        //                  Methods
        ksPathNode          calculate();
        ksVector2D          calculateForce();
        ksVector2D          calculatePrioritizedForce();
        ksVector2D          seek(ksVector2D position);
        ksVector2D          flee(ksVector2D position);
        ksVector2D          arrive(ksVector2D position);
        ksVector2D          pursue(ksComplex * pursuit_target);
        ksVector2D          offsetPursue(ksComplex * pursuit_target, ksVector2D offset);
        ksVector2D          evade(ksComplex * evasion_target);
        ksVector2D          obstacleAvoidance();
        void                move(int row, int col);
        void                addToGroup(ksComplex * entity);
        void                clearGroup();

        // Toggle on or off behaviors
        void                seekOn(ksVector2D vect);
        void                seekOff();
        void                fleeOn(ksVector2D vect);
        void                fleeOff();
        void                arriveOn(ksVector2D vect);
        void                arriveOff();
        void                pursuitOn(ksComplex * vehicle);
        void                pursuitOff();
        void                offsetPursuitOn(ksComplex * vehicle, ksVector2D offset);
        void                offsetPursuitOff();
        void                evasionOn(ksComplex * vehicle);
        void                evasionOff();
        void                groupOn();
        void                groupOff();
        void                obstacleOn();
        void                obstacleOff();

        //                  Accessor methods
        ksPathNode          getNextPathNode();
        ksVector2D          getPathHeading();

    protected:
        int                 applyRowBoundaries(int row);
        int                 applyColumnBoundaries(int col);
        ksPathNode          getNodePosition(int row, int col);
        void                moveInc(int transition_num);
        bool                accumulateForce(ksVector2D force);
        ksVector2D          getPointToLocalSpace(ksVector2D point, ksVector2D heading,
                                              ksVector2D side, ksVector2D position);
        ksVector2D          getPointToWorldSpace(ksVector2D point, ksVector2D heading,
                                                 ksVector2D side, ksVector2D position);
        ksVector2D          getVectorToWorldSpace(ksVector2D vect, ksVector2D heading,
                                               ksVector2D side);

        //                  Group behavior
        ksVector2D          separation();
        ksVector2D          alignment();
        ksVector2D          cohesion();

        //                  Data members
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
