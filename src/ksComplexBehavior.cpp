/*********************************************************
* Class:            ksComplexBehavior
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksComplexBehavior.cpp
*********************************************************/

#include "ksComplexBehavior.h"
#include "ksComplex.h"
#include <iostream>

/*********************************************************
*   ksComplexBehavior
*
*   Initializes the state of the complex behavior class.
*********************************************************/
ksComplexBehavior::ksComplexBehavior(ksPathFinder * path_finder, 
                                     ksWorld * world,
                                     ksComplex * vehicle)
    : m_path_finder(path_finder), m_world(world), m_vehicle(vehicle),
      m_seek(false), m_flee(false), m_pursuit(false), m_evasion(false),
      m_group_on(false), m_path_on(false), m_target_row(-1), 
      m_target_col(-1), m_target_range(0), m_vehicle_velocity(0, 0)
{
    m_current_node = vehicle->getTilePosition();
    m_next_node = m_current_node;
    m_vehicle_heading.X = 0;
    m_vehicle_heading.Y = 0;
}

/*********************************************************
*   calculate
*
*   Calculates the total steering force acting upon the
*   complex type. By assigning priority to seeking,
*   fleeing, then group behaviors, before pathfinding.
*********************************************************/
ksPathNode ksComplexBehavior::calculate()
{
/*    if (m_seek && (m_current_node.row != m_target_row || m_current_node.col != m_target_col))
    {
        // Move the current node incrementally
        moveInc(10);
        
        if (m_current_node.center.X >= (m_next_node.center.X - 2) &&
            m_current_node.center.X <= (m_next_node.center.X + 2) &&
            m_current_node.center.Y >= (m_next_node.center.Y - 2) &&
            m_current_node.center.Y <= (m_next_node.center.Y + 2))
        {
            m_current_node = m_next_node;
            m_next_node    = seek(m_target_row, m_target_col);
            
            m_tl_delta     = m_next_node.TL - m_current_node.TL;
            m_tr_delta     = m_next_node.TR - m_current_node.TR;
            m_bl_delta     = m_next_node.BL - m_current_node.BL;
            m_br_delta     = m_next_node.BR - m_current_node.BR;
            m_center_delta = m_next_node.center - m_current_node.center;
        }
    }
    else if (m_pursuit && 
            (m_current_node.row != m_pursuit_target->getTilePosition().row ||
             m_current_node.col != m_pursuit_target->getTilePosition().col))
    {
        // Move the current node incrementally
        moveInc(10);
        
        if (m_current_node.center.X >= (m_next_node.center.X - 2) &&
            m_current_node.center.X <= (m_next_node.center.X + 2) &&
            m_current_node.center.Y >= (m_next_node.center.Y - 2) &&
            m_current_node.center.Y <= (m_next_node.center.Y + 2))
        {
            m_current_node = m_next_node;
            m_next_node    = pursue(m_pursuit_target);
            
            m_tl_delta     = m_next_node.TL - m_current_node.TL;
            m_tr_delta     = m_next_node.TR - m_current_node.TR;
            m_bl_delta     = m_next_node.BL - m_current_node.BL;
            m_br_delta     = m_next_node.BR - m_current_node.BR;
            m_center_delta = m_next_node.center - m_current_node.center;
        }
    }
    else if (m_evasion)
    {
        // Move the current node incrementally
        moveInc(10);
        
        if (m_current_node.center.X >= (m_next_node.center.X - 2) &&
            m_current_node.center.X <= (m_next_node.center.X + 2) &&
            m_current_node.center.Y >= (m_next_node.center.Y - 2) &&
            m_current_node.center.Y <= (m_next_node.center.Y + 2))
        {
            m_current_node = m_next_node;
            m_next_node    = evade(m_evasion_target);
            
            m_tl_delta     = m_next_node.TL - m_current_node.TL;
            m_tr_delta     = m_next_node.TR - m_current_node.TR;
            m_bl_delta     = m_next_node.BL - m_current_node.BL;
            m_br_delta     = m_next_node.BR - m_current_node.BR;
            m_center_delta = m_next_node.center - m_current_node.center;
        }
    }
    else if (m_flee &&
            (m_current_node.row != 0 || m_current_node.col != 0) &&
            (m_current_node.row != (m_world->getWallMaxRow(m_vehicle->getWall()) - 1) ||
            m_current_node.col != (m_world->getWallMaxCol(m_vehicle->getWall()) - 1)) &&
            (m_current_node.row - m_target_row) >= -m_target_range &&
            (m_current_node.row - m_target_row) <= m_target_range &&
            (m_current_node.col - m_target_col) >= -m_target_range &&
            (m_current_node.col - m_target_col) <= m_target_range)
    {
        // Move the current node incrementally
        moveInc(10);
        
        if (m_current_node.center.X >= (m_next_node.center.X - 2) &&
            m_current_node.center.X <= (m_next_node.center.X + 2) &&
            m_current_node.center.Y >= (m_next_node.center.Y - 2) &&
            m_current_node.center.Y <= (m_next_node.center.Y + 2))
        {
            m_current_node = m_next_node;
            m_next_node    = flee(m_target_row, m_target_col);
            
            m_tl_delta     = m_next_node.TL - m_current_node.TL;
            m_tr_delta     = m_next_node.TR - m_current_node.TR;
            m_bl_delta     = m_next_node.BL - m_current_node.BL;
            m_br_delta     = m_next_node.BR - m_current_node.BR;
            m_center_delta = m_next_node.center - m_current_node.center;
        }
    }
    else if (m_group_on)
    {
        separation();
        alignment();
        cohesion();
    }
    else*/ if (m_path_on == true)
    {
        if (m_wander_path.size() > 0 && m_path_iter != m_wander_path.end())
        {
            // Move the current node incrementally
            moveInc(10);

            if (m_current_node.center.X >= ((*m_path_iter).center.X - 2) &&
                m_current_node.center.X <= ((*m_path_iter).center.X + 2) &&
                m_current_node.center.Y >= ((*m_path_iter).center.Y - 2) &&
                m_current_node.center.Y <= ((*m_path_iter).center.Y + 2))
            {
                m_current_node = (*m_path_iter);
                m_path_iter++;
                m_next_node = (*m_path_iter);

                m_tl_delta = (*m_path_iter).TL - m_current_node.TL;
                m_tr_delta = (*m_path_iter).TR - m_current_node.TR;
                m_bl_delta = (*m_path_iter).BL - m_current_node.BL;
                m_br_delta = (*m_path_iter).BR - m_current_node.BR;
                m_center_delta = (*m_path_iter).center - m_current_node.center;
            }
        }
        else
            m_path_on = false;
    }

    /*if (m_next_node != m_current_node)
    {
        moveInc(10);

        if (m_current_node.center.X >= (m_next_node.center.X - 2) &&
            m_current_node.center.X <= (m_next_node.center.X + 2) &&
            m_current_node.center.Y >= (m_next_node.center.Y - 2) &&
            m_current_node.center.Y <= (m_next_node.center.Y + 2))
        {
            m_current_node = m_next_node;

            if (!m_path_on)
            {
                // Calculating steering force using the weighted sum
                // of the active behaviors.
                ksVector2D steering_force;

                if (m_seek)
                    steering_force += seek(m_target_row, m_target_col) * 1.0;
                if (m_flee)
                    steering_force += flee(m_target_row, m_target_col) * 1.0;
                if (m_group_on)
                {
                    // Apply the group behaviors to
                    // the steering force.
                    steering_force += separation() * 1.0;
                    steering_force += alignment() * 1.0;
                    steering_force += cohesion() * 1.0;
                    std::cout << "Calculating group behavior\n"
                              << "Force: " << steering_force.Y << ", " << steering_force.X << '\n';
                }

                m_vehicle_velocity += steering_force;

                // Convert ksVector2D to a ksPathNode
                if (steering_force.X > 0.1)
                    m_vehicle_velocity.X = 1;
                else if (steering_force.X < -0.1)
                    m_vehicle_velocity.X = -1;
                if (steering_force.Y > 0.1)
                    m_vehicle_velocity.Y = 1;
                else if (steering_force.Y <= -0.1)
                    m_vehicle_velocity.Y = -1;

                m_next_node.col += m_vehicle_heading.X;
                m_next_node.row += m_vehicle_heading.Y;

                std::cout << "Next Node: " << m_next_node.row << ", " << m_next_node.col << '\n';

                // Set up the x, y position and other info of the next node.
                m_next_node = getNodePosition(m_next_node.row, m_next_node.col);
            }
            else if (m_wander_path.size() > 0 && m_path_iter != m_wander_path.end())
            {
                m_path_iter++;
                m_next_node = (*m_path_iter);
            }
            else
            {
                m_path_on = false;
            }
            
            m_tl_delta     = m_next_node.TL - m_current_node.TL;
            m_tr_delta     = m_next_node.TR - m_current_node.TR;
            m_bl_delta     = m_next_node.BL - m_current_node.BL;
            m_br_delta     = m_next_node.BR - m_current_node.BR;
            m_center_delta = m_next_node.center - m_current_node.center;
        }
    }*/

    return m_current_node;
}

/*********************************************************
*   seek
*
*   Perform the seek steering behavior using the passed
*   row and column.
*********************************************************/
ksVector2D ksComplexBehavior::seek(int row, int col)
{
/*    ksPathNode result;
    
    result.row = row - m_vehicle->getTilePosition().row;
    result.col = col - m_vehicle->getTilePosition().col;

    // Move to an adjacent node
    if (result.row > 0)
        result.row = 1;
    else if (result.row < 0)
        result.row = -1;
    if (result.col > 0)
        result.col = 1;
    else if (result.col < 0)
        result.col = -1;

    // Move relative to current position
    result.row += m_vehicle->getTilePosition().row;
    result.col += m_vehicle->getTilePosition().col;

    result.row = applyRowBoundaries(result.row);
    result.col = applyColumnBoundaries(result.col);

    result     = getNodePosition(result.row, result.col);

    return result;
*/
    ksVector2D targetPos;
    ksVector2D vehiclePos;
    ksVector2D desiredVelocity;

    targetPos.X = col;
    targetPos.Y = row;

    vehiclePos.X = m_vehicle->getTilePosition().col;
    vehiclePos.Y = m_vehicle->getTilePosition().row;

    desiredVelocity = targetPos - vehiclePos;

    desiredVelocity.normalize();

    return desiredVelocity - m_vehicle_velocity;// - m_vehicle_velocity;//(desiredVelocity - m_vehicle_velocity);
}

/********************************************************
*   flee
*
*   Perform the flee steering behavior using the passed
*   row and column. This method assumes it is in range.
*   The range gets checked in the calculate method.
********************************************************/
ksVector2D ksComplexBehavior::flee(int row, int col)
{
    /*ksPathNode result;

    result.row = m_vehicle->getTilePosition().row - row;
    result.col = m_vehicle->getTilePosition().col - col;

    // Move to an adjacent node
    if (result.row > 0)
        result.row = 1;
    else if (result.row < 0)
        result.row = -1;
    if (result.col > 0)
        result.col = 1;
    else if (result.col < 0)
        result.col = -1;

    // Move relative to current position
    result.row += m_vehicle->getTilePosition().row;
    result.col += m_vehicle->getTilePosition().col;

    result.row = applyRowBoundaries(result.row);
    result.col = applyColumnBoundaries(result.col);

    std::cout << "Fleeing: Current Row: " << result.row
              << ", Current Col: " << result.col << "\n";
    
    result     = getNodePosition(result.row, result.col);
    
    return result;*/
    ksVector2D targetPos;
    ksVector2D vehiclePos;

    targetPos.X = col;
    targetPos.Y = row;

    vehiclePos.X = m_vehicle->getTilePosition().col;
    vehiclePos.Y = m_vehicle->getTilePosition().row;

    const double panicDistanceSq = 2.0 * 2.0;

    if (vehiclePos.getDistanceSq(targetPos) > panicDistanceSq)
        return ksVector2D(0, 0);

    ksVector2D desiredVelocity = vehiclePos - targetPos;

    desiredVelocity.normalize();

    return (desiredVelocity - m_vehicle_velocity);
}

/********************************************************
*   pursue
*
*   Get the estimated future position of the target
*   entity and seek that position.
********************************************************/
ksPathNode ksComplexBehavior::pursue(ksComplex * pursuit_target)
{
    //ksPathNode next = pursuit_target->getNextPathNode();

    //m_pursuit = true;
    //m_pursuit_target = pursuit_target;

    // Seek the estimated future position of the
    // target entity.
    return ksPathNode(0, 0);//seek(next.row, next.col);

    ksVector2D evaderPos;
    ksVector2D vehiclePos;

    evaderPos.X = pursuit_target->getTilePosition().col;
    evaderPos.Y = pursuit_target->getTilePosition().row;

    vehiclePos.X = m_vehicle->getTilePosition().col;
    vehiclePos.Y = m_vehicle->getTilePosition().row;

    ksVector2D to_evader = evaderPos - vehiclePos;

    
}

/********************************************************
*   evade
*
*   Get the estimated future position of the target
*   entity and flee from that position.
********************************************************/
ksPathNode ksComplexBehavior::evade(ksComplex * evasion_target)
{
    //ksPathNode next = evasion_target->getNextPathNode();

    //m_evasion = true;
    //m_evasion_target = evasion_target;

    // Flee the estimated future position of the
    // target entity.
    return ksPathNode(0, 0);//flee(next.row, next.col);
}

/********************************************************
*   move
*
*   Use pathfinding to move the complex type on the
*   shortest path to the desired row and column.
********************************************************/
void ksComplexBehavior::move(int row, int col)
{
    m_wander_path.clear();

    m_wander_path = m_path_finder->calculatePath(m_vehicle, row, col);
    m_path_iter   = m_wander_path.begin();
    m_current_node = (*m_path_iter);
    m_path_iter++;

    m_tl_delta = (*m_path_iter).TL - m_current_node.TL;
    m_tr_delta = (*m_path_iter).TR - m_current_node.TR;
    m_bl_delta = (*m_path_iter).BL - m_current_node.BL;
    m_br_delta = (*m_path_iter).BR - m_current_node.BR;
    m_center_delta = (*m_path_iter).center - m_current_node.center;

    m_path_on     = true;
}

/********************************************************
*   addToGroup
*
*   Add an entity to the complex type's group so
*   that they can be considered when performing
*   group separation, alignment, and cohesion.
********************************************************/
void ksComplexBehavior::addToGroup(ksComplex * entity)
{
    m_group.push_back(entity);
}

/********************************************************
*   clearGroup
*
*   Clear all complex entities from the group so that
*   they may not be considered when performing group
*   behaviors.
********************************************************/
void ksComplexBehavior::clearGroup()
{
    m_group.clear();
}

/********************************************************
*   seekOn
*
*   Toggle on the seek behavior so that this complex
*   entity will seek the desired row and column.
********************************************************/
void ksComplexBehavior::seekOn(int row, int col)
{
    m_target_row = row;
    m_target_col = col;
    m_seek       = true;
    m_next_node.row += 1;
}

/********************************************************
*   seekOff
*
*   Toggle off the seek behavior for this complex entity.
********************************************************/
void ksComplexBehavior::seekOff()
{
    m_seek = false;
}

/********************************************************
*   fleeOn
*
*   Toggle on the flee behavior so that this complex
*   entity will flee from the desired row and column
*   assuming it's within range.
********************************************************/
void ksComplexBehavior::fleeOn(int row, int col, int range)
{
    m_target_row   = row;
    m_target_col   = col;
    m_target_range = range;
    m_flee         = true;
    m_next_node.row += 1;
}

/********************************************************
*   fleeOff
*
*   Toggle off the flee behavior for this complex entity.
********************************************************/
void ksComplexBehavior::fleeOff()
{
    m_flee = false;
}

/********************************************************
*   groupOn
*
*   Toggle on the group behaviors so that this complex
*   entity will have group separation, alignment and
*   cohesion within it's group.
********************************************************/
void ksComplexBehavior::groupOn()
{
    m_group_on = true;
    m_next_node.row += 1;
}

/********************************************************
*   groupOff
*
*   Toggle off the group behaviors for this complex
*   entity.
********************************************************/
void ksComplexBehavior::groupOff()
{
    m_group_on = false;
}

/********************************************************
*   getNextPathNode
*
*   Return the estimated next path node of this complex
*   entity.
********************************************************/
ksPathNode ksComplexBehavior::getNextPathNode()
{
    return m_next_node;
}

ksVector2D ksComplexBehavior::getPathHeading()
{
    return m_vehicle_heading;
}

/********************************************************
*   applyRowBoundaries
*
*   Ensure that the passed row is a valid row, and if
*   it's not, adjust it till it is.
********************************************************/
int ksComplexBehavior::applyRowBoundaries(int row)
{
    int max_row = m_world->getWallMaxRow(m_vehicle->getWall());

    if (row < 0)
        row = 0;
    else if (row >= max_row)
        row = max_row - 1;

    return row;
}

/********************************************************
*   applyColumnBoundaries
*
*   Ensure that the passed column is a valid column,
*   and if it's not, adjust it till it is.
********************************************************/
int ksComplexBehavior::applyColumnBoundaries(int col)
{
    int max_col = m_world->getWallMaxCol(m_vehicle->getWall());

    if (col < 0)
        col = 0;
    else if (col >= max_col)
        col = max_col - 1;

    return col;
}

/********************************************************
*   getNodePosition
*
*   Get the node position from ksWorld for the passed
*   row and column and set up all the memnbers of the
*   path node.
********************************************************/
ksPathNode ksComplexBehavior::getNodePosition(int row, int col)
{
    ksPathNode temp;
    ksTile position = m_world->getTilePosition(m_vehicle->getWall(), row, col,
            m_vehicle->getWidth(), m_vehicle->getHeight());

    temp.TL       = position.TL;
    temp.TR       = position.TR;
    temp.BL       = position.BL;
    temp.BR       = position.BR;
    temp.center.X = position.TL.X + ((position.TR.X - position.TL.X) / 2);
    temp.center.Y = position.TL.Y + ((position.BL.Y - position.TL.Y) / 2);
    temp.row      = row;
    temp.col      = col;

    return temp;
}

/********************************************************
*   moveInc
*
*   Move the complex entity incrementally using the 
*   difference between the current and next nodes (delta)
*   in the number of transition steps between nodes.
********************************************************/
void ksComplexBehavior::moveInc(int transition_num)
{
    // Move the current node in incremental steps
    m_current_node.TL.X     += m_tl_delta.X / transition_num;
    m_current_node.TL.Y     += m_tl_delta.Y / transition_num;
    m_current_node.TR.X     += m_tr_delta.X / transition_num;
    m_current_node.TR.Y     += m_tr_delta.Y / transition_num;
    m_current_node.BL.X     += m_bl_delta.X / transition_num;
    m_current_node.BL.Y     += m_bl_delta.Y / transition_num;
    m_current_node.BR.X     += m_br_delta.X / transition_num;
    m_current_node.BR.Y     += m_br_delta.Y / transition_num;
    m_current_node.center.X += m_center_delta.X / transition_num;
    m_current_node.center.Y += m_center_delta.Y / transition_num;
}

/********************************************************
*   separation
*
*   Perform separation on the group of complex entities.
********************************************************/
ksVector2D ksComplexBehavior::separation()
{
    ksVector2D steering;

    for (ksComplex * entity : m_group)
    {
        if (entity != m_vehicle)
        {
            ksVector2D ToAgent;
            ToAgent.X = m_vehicle->getTilePosition().col - entity->getTilePosition().col;
            ToAgent.Y = m_vehicle->getTilePosition().row - entity->getTilePosition().row;
            
            ksVector2D ToAgentNorm = ToAgent;
            ToAgent.normalize();

            steering += ToAgentNorm / ToAgent.getLength();
        }
    }

    return steering;
}

/********************************************************
*   alignment
*
*   Perform alignment on the group of complex entities.
********************************************************/
ksVector2D ksComplexBehavior::alignment()
{
    ksVector2D avgHeading;

    if (m_group.size() > 0)
    {
        for (ksComplex * entity : m_group)
            avgHeading += entity->getComplexHeading();

        avgHeading /= (double) m_group.size();
        avgHeading -= m_vehicle_heading;
    }

    return avgHeading;
}

/********************************************************
*   cohesion
*
*   Perform cohesion on the group of complex entities.
********************************************************/
ksVector2D ksComplexBehavior::cohesion()
{
    ksVector2D center;
    ksVector2D steering;

    if (m_group.size() > 0)
    {
        for (ksComplex * entity : m_group)
        {
            if (entity != m_vehicle)
            {
                ksVector2D pos;

                pos.X = entity->getTilePosition().col;
                pos.Y = entity->getTilePosition().row;
            
                center += pos;
            }
        }

        // Steer toward the center of the group
        center /= (double) (m_group.size() - 1);
        steering = seek((int) center.Y, (int) center.X);
    }

    return steering;
}
