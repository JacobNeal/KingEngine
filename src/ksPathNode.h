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
        int f_score;
        int g_score;
        ksPathNode * parent;

        ksVector2D TL;
        ksVector2D TR;
        ksVector2D BL;
        ksVector2D BR;
        ksVector2D center;

        ksPathNode() : row(-1), col(-1), f_score(0), g_score(0),
                       parent(nullptr)
        { }

        ksPathNode(int c_row, int c_col) : row(c_row), col(c_col),
            f_score(0), g_score(0), parent(nullptr)
        { }

        ksPathNode(const ksPathNode & rhs)
        {
            row    = rhs.row;
            col    = rhs.col;
            TL     = rhs.TL;
            TR     = rhs.TR;
            BL     = rhs.BL;
            BR     = rhs.BR;
            center = rhs.center;
            parent = rhs.parent;
            f_score = rhs.f_score;
            g_score = rhs.g_score;
        }

        ksPathNode & operator= (const ksPathNode & rhs)
        {
            row    = rhs.row;
            col    = rhs.col;
            TL     = rhs.TL;
            TR     = rhs.TR;
            BL     = rhs.BL;
            BR     = rhs.BR;
            center = rhs.center;
            parent = rhs.parent;
            f_score = rhs.f_score;
            g_score = rhs.g_score;

            return *this;
        }

        bool operator== (const ksPathNode & rhs)
        {
            return (row  == rhs.row &&
                    col  == rhs.col);
        }

        bool operator!= (const ksPathNode & rhs)
        {
            return (row != rhs.row ||
                    col != rhs.col);
        }
};

/*bool operator== (const ksPathNode & node1, const ksPathNode & node2)
{
    return (node1.row  == node2.row &&
            node1.col  == node2.col &&
            node1.cost == node2.cost);
}*/

#endif
