/********************************************************
* Class:            ksComplex
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksComplex.cpp
********************************************************/

#include "ksComplex.h"
#include <iostream>

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
                     m_loop_path(false), m_path_on(false), m_start_row(row), m_start_col(col), 
                     m_finish_row(0), m_finish_col(0), m_tag(false)
{
    m_path_finder = path_finder;

    ksTile temp = world->getTilePosition(wall, row, col, w, h);

    m_position  = temp.TL;
    m_velocity  = ksVector2D(0, 0);
    m_heading   = ksVector2D(0, 0);
}

/********************************************************
*   update
*
*   Updates the current position of the complex type
*   relative to its path.
********************************************************/
void ksComplex::update()
{
    if (m_path_on == true)
    {
        if (m_path.size() > 0 && m_path_iter != m_path.end())
        {
            // Take 10 steps between nodes.
            int transition = 10;

            // Move entity incrementally toward the next node.
            m_current_node.TL.X     += m_tl_delta.X / transition;
            m_current_node.TL.Y     += m_tl_delta.Y / transition;
            m_current_node.TR.X     += m_tr_delta.X / transition;
            m_current_node.TR.Y     += m_tr_delta.Y / transition;
            m_current_node.BL.X     += m_bl_delta.X / transition;
            m_current_node.BL.Y     += m_bl_delta.Y / transition;
            m_current_node.BR.X     += m_br_delta.X / transition;
            m_current_node.BR.Y     += m_br_delta.Y / transition;
            m_current_node.center.X += m_center_delta.X / transition;
            m_current_node.center.Y += m_center_delta.Y / transition;

            if (m_current_node.center.X >= ((*m_path_iter).center.X - 2) &&
                m_current_node.center.X <= ((*m_path_iter).center.X + 2) &&
                m_current_node.center.Y >= ((*m_path_iter).center.Y - 2) &&
                m_current_node.center.Y <= ((*m_path_iter).center.Y + 2))
            {
                m_current_node = (*m_path_iter);
                m_path_iter++;
                
                m_tl_delta = (*m_path_iter).TL - m_current_node.TL;
                m_tr_delta = (*m_path_iter).TR - m_current_node.TR;
                m_bl_delta = (*m_path_iter).BL - m_current_node.BL;
                m_br_delta = (*m_path_iter).BR - m_current_node.BR;
                m_center_delta = (*m_path_iter).center - m_current_node.center;
            }
        }
        else if (m_loop_path)
        {
            // Reverse the list of path nodes.     
            m_path.reverse();

            m_path_iter = m_path.begin();
            m_current_node = (*m_path_iter);
            m_path_iter++;

            m_tl_delta = (*m_path_iter).TL - m_current_node.TL;
            m_tr_delta = (*m_path_iter).TR - m_current_node.TR;
            m_bl_delta = (*m_path_iter).BL - m_current_node.BL;
            m_br_delta = (*m_path_iter).BR - m_current_node.BR;
            m_center_delta = (*m_path_iter).center - m_current_node.center;
        }
    }
    else
    {
        // New update
        float time = m_elapsed_time.getElapsedTime().asSeconds();
        
        ksVector2D steering_force = m_behavior.calculatePrioritizedForce();
        ksVector2D acceleration   = steering_force / 1.0; // a = F / m
        m_velocity               += acceleration * time; // v = a * t

        m_velocity.truncate(150); // Results in 5 pixels / frame (150 pixels / sec * 1 sec / 30 frames)
    
        m_position               += m_velocity * time; // p = v * t

        if (m_velocity.getLengthSq() > 0.00000001)
        {
            m_heading = VecNormalize(m_velocity);
            m_side = m_heading.getPerpendicularVector();
        }

        m_elapsed_time.restart();

        // Loop entity around boundaries.
        if (m_position.X >= 800)
            m_position.X = 1;
        if (m_position.X <= 0)
            m_position.X = 799;
        if (m_position.Y >= 640)
            m_position.Y = 1;
        if (m_position.Y <= 0)
            m_position.Y = 639;

        m_current_node.TL   = m_position;
        m_current_node.TR.X = m_position.X + 32;
        m_current_node.TR.Y = m_position.Y;
        m_current_node.BR.X = m_position.X + 32;
        m_current_node.BR.Y = m_position.Y + 64;
        m_current_node.BL.X = m_position.X;
        m_current_node.BL.Y = m_position.Y + 64;
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
    m_path_on   = true;
    m_loop_path = loop;
    m_path      = m_path_finder->calculatePath(this, row, col);
    m_path_iter = m_path.begin();
    m_current_node = (*m_path_iter);
    m_path_iter++;

    m_tl_delta = (*m_path_iter).TL - m_current_node.TL;
    m_tr_delta = (*m_path_iter).TR - m_current_node.TR;
    m_bl_delta = (*m_path_iter).BL - m_current_node.BL;
    m_br_delta = (*m_path_iter).BR - m_current_node.BR;
    m_center_delta = (*m_path_iter).center - m_current_node.center;
}

/********************************************************
*   seek
*
*   Call the seekOn method of the complex behavior class
*   passing the desired row and column.
********************************************************/
void ksComplex::seek(ksVector2D vect)
{
    m_behavior.seekOn(vect);
}

/********************************************************
*   flee
*
*   Call the fleeOn method of the complex behavior class
*   passing the desired row, column, and range.
********************************************************/
void ksComplex::flee(ksVector2D vect)
{
    m_behavior.fleeOn(vect);
}

void ksComplex::arrive(ksVector2D vect)
{
    m_behavior.arriveOn(vect);
}

/********************************************************
*   pursue
*
*   Call the pursue method of the complex behavior class
*   passing the desired entity.
********************************************************/
void ksComplex::pursue(ksComplex * entity)
{
    m_behavior.pursuitOn(entity);
}

/********************************************************
*   evade
*
*   Call the evade method of the complex behavior class
*   passing the desired entity.
********************************************************/
void ksComplex::evade(ksComplex * entity)
{
    m_behavior.evasionOn(entity);
}

/********************************************************
*   addToGroup
*
*   Call the addToGroup method of the complex behavior
*   class passing the desired entity.
********************************************************/
void ksComplex::addToGroup(ksComplex * entity)
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

void ksComplex::avoidObstacles()
{
    m_behavior.obstacleOn();
}

void ksComplex::tag()
{
    m_tag = true;
}

void ksComplex::untag()
{
    m_tag = false;
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

ksVector2D ksComplex::getHeading()
{
    return m_heading;
}

ksVector2D ksComplex::getVelocity()
{
    return m_velocity;
}

ksVector2D ksComplex::getPosition()
{
    return m_position;
}

ksVector2D ksComplex::getSide()
{
    return m_side;
}

bool ksComplex::getTag()
{
    return m_tag;
}

