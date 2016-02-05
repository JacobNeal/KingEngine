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
#define kS_COMPLEX_H

#include "ksEntity.h"
#include "ksPathFinder.h"
#include "ksPathNode.h"
#include "defines.h"
#include <list>

class ksComplex : public ksEntity
{
    public:
        //                              Constructors
        ksComplex(ksPathFinder * path_finder, ksWorldWall wall, int row, int col, 
                  int w, int h, int current_tile);

        //                              Methods
        virtual void                    update();
        void                            move(int row, int col);

    protected:
        //                              Data members
        ksPathFinder *                  m_path_finder;
        ksPathNode                      m_current_node;
        std::list<ksPathNode>           m_path;
        std::list<ksPathNode>::iterator m_path_iter;
};

#endif
