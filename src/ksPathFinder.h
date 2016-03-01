/********************************************************
* Class:            ksPathFinder
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksPathFinder.h
*
*   Overview:
*       Contains the path finder type that will calculate
*       the shortest path between two given points using
*       the A* pathfinding algorithm and the Manhattan 
*       heuristic.
*
********************************************************/

#ifndef KS_PATHFINDER_H
#define KS_PATHFINDER_H

#include <vector>
#include <list>
#include <algorithm>
#include "ksPathNode.h"
#include "ksEntity.h"
#include "ksWorld.h"

class ksPathFinder
{
    public:
        //                    Constructors
        ksPathFinder(ksWorld * world);
        
        //                    Methods
        std::list<ksPathNode> calculatePath(ksEntity * entity, int finish_row, int finish_col);
        ksPathNode            getNodeWithLowestCost();
        void                  findAdjacentNodes(ksPathNode current, std::vector<ksPathNode> & adjacent);
        int                   getHeuristicValue(ksPathNode current, ksPathNode finish);
        bool                  foundInClosed(ksPathNode current);
        bool                  foundInOpen(ksPathNode current);
        ksPathNode            createPathNode(int row, int col);

    private:
        //                    Data members
        ksWorld * m_world;
        ksEntity * m_entity;
        std::list<ksPathNode> m_open;
        std::list<ksPathNode> m_closed;
        ksWorldWall           m_wall;
        ksPathNode            m_start;
        ksPathNode            m_finish;
};

#endif
