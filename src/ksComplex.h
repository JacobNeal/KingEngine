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
        ksComplex(ksPathFinder * path_finder, ksWorld * world, ksWorldWall wall, int row, int col, 
                  int w, int h, int current_tile);

        //                              Methods
        virtual void                    update();
        void                            move(int row, int col, bool loop = false);
        void                            seek(int row, int col);
        void                            flee(int row, int col, int range);
        void                            pursue(ksComplex * entity);
        void                            evade(ksComplex * entity);
        void                            addToGroup(ksEntity * entity);
        void                            clearGroup();
        void                            group();
    
        //                              Accessor methods
        ksPathNode                      getNextPathNode();

    protected:
        //                              Data members
        ksPathFinder *                  m_path_finder;
        ksComplexBehavior               m_behavior;
        std::list<ksPathNode>           m_path;
        std::list<ksPathNode>::iterator m_path_iter;
        bool                            m_loop_path;
        int                             m_start_row;
        int                             m_start_col;
        int                             m_finish_row;
        int                             m_finish_col;
};

#endif
