/********************************************************
* Class:            ksPathNode
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksPathNode.h
*
*   Overview:
*       Contains the path node type for use in
*       calculating and traversing the shortest path
*       between two given points.
*
********************************************************/

#ifndef KS_PATHNODE_H
#define KS_PATHNODE_H

#include "ksVector2D.h"

class ksPathNode
{
    public:
        int row;
        int col;
        int cost;

        ksVector2D TL;
        ksVector2D TR;
        ksVector2D BL;
        ksVector2D BR;
        ksVector2D center;

        ksPathNode() : row(-1), col(-1), cost(0)
        { }

        ksPathNode(const ksPathNode & rhs)
        {
            row    = rhs.row;
            col    = rhs.col;
            cost   = rhs.cost;
            TL     = rhs.TL;
            TR     = rhs.TR;
            BL     = rhs.BL;
            BR     = rhs.BR;
            center = rhs.center;
        }

        ksPathNode & operator= (const ksPathNode & rhs)
        {
            row    = rhs.row;
            col    = rhs.col;
            cost   = rhs.cost;
            TL     = rhs.TL;
            TR     = rhs.TR;
            BL     = rhs.BL;
            BR     = rhs.BR;
            center = rhs.center;

            return *this;
        }

        bool operator== (const ksPathNode & rhs)
        {
            return (row  == rhs.row &&
                    col  == rhs.col);
        }
};

/*bool operator== (const ksPathNode & node1, const ksPathNode & node2)
{
    return (node1.row  == node2.row &&
            node1.col  == node2.col &&
            node1.cost == node2.cost);
}*/

#endif
