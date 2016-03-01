/********************************************************
* Class:            ksComplex
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksComplex.cpp
********************************************************/

#include "ksComplex.h"

/********************************************************
*   ksComplex
*
*   Initializes the complex type to the path finder
*   referenced that has been passed and calls the 
*   constructor of the base game entity class.
********************************************************/
ksComplex::ksComplex(ksPathFinder * path_finder, ksWorld * world, ksWorldWall wall, int row, int col,
                     int w, int h, int current_tile) :
                     ksEntity(world, wall, row, col, w, h, current_tile),
                     m_behavior(path_finder, world, this),
                     m_loop_path(false), m_start_row(row), m_start_col(col), 
                     m_finish_row(0), m_finish_col(0)
{
    m_path_finder = path_finder;
}

/********************************************************
*   update
*
*   Updates the current position of the complex type
*   relative to its path.
********************************************************/
void ksComplex::update()
{
    ksPathNode temp = m_behavior.calculate();

    if (m_current_node.TL != temp.TL ||
        m_current_node.TR != temp.TR ||
        m_current_node.BL != temp.BL ||
        m_current_node.BR != temp.BR)
    {
        m_current_node = temp;
    }
}

/********************************************************
*   move
*
*   Sets the path of the complex type using the A*
*   path finder as the default form of movement.
********************************************************/
void ksComplex::move(int row, int col, bool loop)
{
    m_behavior.move(row, col);
}

/********************************************************
*   seek
*
*   Call the seekOn method of the complex behavior class
*   passing the desired row and column.
********************************************************/
void ksComplex::seek(int row, int col)
{
    m_behavior.seekOn(row, col);
}

/********************************************************
*   flee
*
*   Call the fleeOn method of the complex behavior class
*   passing the desired row, column, and range.
********************************************************/
void ksComplex::flee(int row, int col, int range)
{
    m_behavior.fleeOn(row, col, range);
}

/********************************************************
*   pursue
*
*   Call the pursue method of the complex behavior class
*   passing the desired entity.
********************************************************/
void ksComplex::pursue(ksComplex * entity)
{
    m_behavior.pursue(entity);
}

/********************************************************
*   evade
*
*   Call the evade method of the complex behavior class
*   passing the desired entity.
********************************************************/
void ksComplex::evade(ksComplex * entity)
{
    m_behavior.evade(entity);
}

/********************************************************
*   addToGroup
*
*   Call the addToGroup method of the complex behavior
*   class passing the desired entity.
********************************************************/
void ksComplex::addToGroup(ksEntity * entity)
{
    m_behavior.addToGroup(entity);
}

/********************************************************
*   clearGroup
*
*   Call the clear group method of the complex behavior
*   class, clearing the group of entities from
*   consideration when performing group behaviors.
********************************************************/
void ksComplex::clearGroup()
{
    m_behavior.clearGroup();
}

/********************************************************
*   group
*
*   Call the group method of the complex behavior class
*   so that group behaviors can be performed on this
*   complex entity.
********************************************************/
void ksComplex::group()
{
    m_behavior.groupOn();
}

/********************************************************
*   getNextPathNode
*
*   Returns the estimated next path node associated with
*   this complex entity.
********************************************************/
ksPathNode ksComplex::getNextPathNode()
{
    return m_behavior.getNextPathNode();
}
