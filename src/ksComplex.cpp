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
ksComplex::ksComplex(ksPathFinder * path_finder, ksWorldWall wall, int row, int col,
                     int w, int h, int current_tile) :
                     ksEntity(wall, row, col, w, h, current_tile)
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
    if (m_path.size() > 0 && m_path_iter != m_path.end())
    {
        int diff_x = (*m_path_iter).center.X - m_current_node.center.X;
        int diff_y = (*m_path_iter).center.Y - m_current_node.center.Y;

        if (diff_x < 0)
        {
            m_current_node.TL.X     -= ENTITY_MOVE_DELTA;
            m_current_node.TR.X     -= ENTITY_MOVE_DELTA;
            m_current_node.BR.X     -= ENTITY_MOVE_DELTA;
            m_current_node.BL.X     -= ENTITY_MOVE_DELTA;
            m_current_node.center.X -= ENTITY_MOVE_DELTA;
        }
        else if (diff_x > 0)
        {
            m_current_node.TL.X     += ENTITY_MOVE_DELTA;
            m_current_node.TR.X     += ENTITY_MOVE_DELTA;
            m_current_node.BR.X     += ENTITY_MOVE_DELTA;
            m_current_node.BL.X     += ENTITY_MOVE_DELTA;
            m_current_node.center.X += ENTITY_MOVE_DELTA;
        }

        if (diff_y < 0)
        {
            m_current_node.TL.Y     -= ENTITY_MOVE_DELTA;
            m_current_node.TR.Y     -= ENTITY_MOVE_DELTA;
            m_current_node.BR.Y     -= ENTITY_MOVE_DELTA;
            m_current_node.BL.Y     -= ENTITY_MOVE_DELTA;
            m_current_node.center.Y -= ENTITY_MOVE_DELTA;
        }
        else if (diff_y > 0)
        {
            m_current_node.TL.Y     += ENTITY_MOVE_DELTA;
            m_current_node.TR.Y     += ENTITY_MOVE_DELTA;
            m_current_node.BR.Y     += ENTITY_MOVE_DELTA;
            m_current_node.BL.Y     += ENTITY_MOVE_DELTA;
            m_current_node.center.Y += ENTITY_MOVE_DELTA;
        }

        if (m_current_node.center.X >= ((*m_path_iter).center.X - 2) &&
            m_current_node.center.X <= ((*m_path_iter).center.X + 2) &&
            m_current_node.center.Y >= ((*m_path_iter).center.Y - 2) &&
            m_current_node.center.Y <= ((*m_path_iter).center.Y + 2))
        {
            m_current_node = (*m_path_iter);
            m_path_iter++;
        }

        m_position.TL = m_current_node.TL;
        m_position.TR = m_current_node.TR;
        m_position.BL = m_current_node.BL;
        m_position.BR = m_current_node.BR;
    
//        std::cout << "Entity at: " << m_current_node.center.X << ", " << m_current_node.center.Y << '\n';
//        std::cout << "Node at:   " << (*m_path_iter).row << ", " << (*m_path_iter).col << '\n';
    }
}

/********************************************************
*   move
*
*   Sets the path of the complex type using the A*
*   path finder as the default form of movement.
********************************************************/
void ksComplex::move(int row, int col)
{
    m_path.clear();

    m_path          = m_path_finder->calculatePath(this, row, col);
    m_path_iter     = m_path.begin();
    m_current_node  = (*m_path_iter);
}
