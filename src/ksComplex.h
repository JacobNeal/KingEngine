/********************************************************
* Class:            ksComplex
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksComplex.h
*
*   Overview:
*       Class that contains the complex game entity type
*       for KingEngine. This complex type allows for
*       characters to be state driven based on different
*       behavior states. These behavior states can be
*       accessed and set through using the Lua scripting
*       language to define which behaviors individual
*       complex entities will have.
*
*       This class inherits from the ksEntity type.
*
********************************************************/

#ifndef KS_COMPLEX_H
#define KS_COMPLEX_H

#include "ksEntity.h"
#include "ksPathFinder.h"
#include "ksPathNode.h"
#include "ksComplexBehavior.h"
#include "defines.h"
#include <list>

class ksComplex : public ksEntity
{
    public:
        //                              Constructors
        ksComplex(ksPathFinder * path_finder, ksWorld * world, int x, int y, int z, 
                  int w, int h, int current_tile);

        //                              Methods
        virtual void                    update();
        void                            move(int row, int col, bool loop = false);
        void                            seek(ksVector2D vect);
        void                            flee(ksVector2D vect);
        void                            arrive(ksVector2D vect);
        void                            pursue(ksComplex * entity);
        void                            evade(ksComplex * entity);
        void                            avoidObstacles();
        void                            addToGroup(ksComplex * entity);
        void                            clearGroup();
        void                            group();
        void                            tag();
        void                            untag();
        void                            toggleBehavior();
        // virtual void                    moveEntity(int x, int y, int z);

        //                              Accessor methods
        ksPathNode                      getNextPathNode();
        ksVector2D                      getHeading();
        ksVector2D                      getVelocity();
        ksVector2D                      getPosition();
        ksVector2D                      getSide();
        bool                            getTag();
        int                             getBoundingRadius();

    protected:
        //                              Data members
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
