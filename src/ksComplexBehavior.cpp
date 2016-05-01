/*********************************************************
* Class:            ksComplexBehavior
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksComplexBehavior.cpp
*********************************************************/

#include "ksComplexBehavior.h"
#include "ksComplex.h"
#include <iostream>
#include <limits>
#include <math.h>

/*********************************************************
*   ksComplexBehavior
*
*   Initializes the state of the complex behavior class.
*********************************************************/
ksComplexBehavior::ksComplexBehavior(ksPathFinder * path_finder, 
                                     ksWorld * world,
                                     ksComplex * vehicle)
    : m_path_finder(path_finder), m_world(world), m_vehicle(vehicle),
      m_seek(false), m_flee(false), m_pursuit(false), m_offset_pursuit(false),
      m_evasion(false), m_group_on(false), m_path_on(false), m_obstacle(false), 
      m_arrive(false), m_pursuit_offset(0, 0), m_steering_force(0, 0), 
      m_target_row(-1), m_target_col(-1), m_target_range(0),
      m_vehicle_velocity(0, 0)
{
    m_current_node = vehicle->getTilePosition();
    m_next_node = m_current_node;
    m_vehicle_heading.X = 0;
    m_vehicle_heading.Y = 0;
}

/*********************************************************
*   calculateForce
*
*   Calculates the force using the weighted sums method.
*********************************************************/
ksVector2D ksComplexBehavior::calculateForce()
{
    ksVector2D steering_force;

    if (m_group_on)
    {
        // Tag neighbors if within 50 pixel view distance
        for (ksComplex * entity : m_group)
        {
            entity->untag();

            ksVector2D to = entity->getPosition() - m_vehicle->getPosition();

            double range = 50 + entity->getBoundingRadius(); // 50 (view distance) + entity->bounding radius

            if ((entity != m_vehicle) && (to.getLengthSq() < range * range))
                entity->tag();
        }

        steering_force += separation() * 1.0;
        steering_force += cohesion() * 2.0; //2.0
        steering_force += alignment() * 1.0;
    }
    if (m_obstacle)
    {
        ksVector2D temp = obstacleAvoidance() * 10.0;
        steering_force += temp;
        std::cout << "Obstacle Force: " << temp.X << ", " << temp.Y << '\n';
    }
    if (m_seek)
        steering_force += seek(m_target) * 1.0;
    if (m_arrive)
        steering_force += arrive(m_target) * 1.0;
    if (m_flee)
        steering_force += flee(m_target) * 1.0;
    if (m_pursuit)
        steering_force += pursue(m_pursuit_target) * 1.0;
    if (m_offset_pursuit)
        steering_force += offsetPursue(m_pursuit_target, m_pursuit_offset) * 1.0;
    if (m_evasion)
        steering_force += evade(m_evasion_target) * 0.01;

    steering_force.truncate(400.0); // Max force: 2.0

    return steering_force;
}

/*********************************************************
*   calculatePrioritizedForce
*
*   Calculates the steering force using the prioritized
*   sum of the weighted behaviors.
*********************************************************/
ksVector2D ksComplexBehavior::calculatePrioritizedForce()
{
    m_steering_force.zero();

    ksVector2D steering_force;

    // Tag neighbors if within 50 pixel view distance
    for (ksComplex * entity : m_group)
    {
        entity->untag();

        ksVector2D to = entity->getPosition() - m_vehicle->getPosition();

        double range = 50 + entity->getBoundingRadius(); // 50 (view distance) + entity->bounding radius

        if ((entity != m_vehicle) && (to.getLengthSq() < range * range))
            entity->tag();
    }

    if (m_obstacle)
    {
        steering_force = obstacleAvoidance() * 10.0;

        if (!accumulateForce(steering_force))
            return m_steering_force;
    }

    if (m_evasion)
    {
        steering_force = evade(m_evasion_target) * 1.0;

        if (!accumulateForce(steering_force))
            return m_steering_force;
    }
    
    if (m_flee)
    {
        steering_force = flee(m_target) * 1.0;

        if (!accumulateForce(steering_force))
            return m_steering_force;
    }
    
    if (m_group_on)
    {
        steering_force = separation() * 1.0;

        if (!accumulateForce(steering_force))
            return m_steering_force;

        steering_force = cohesion() * 0.5;

        if (!accumulateForce(steering_force))
            return m_steering_force;
    
        steering_force = alignment() * 1.0;

        if (!accumulateForce(steering_force))
            return m_steering_force;
    }

    if (m_seek)
    {
        steering_force = seek(m_target) * 1.0;

        if (!accumulateForce(steering_force))
            return m_steering_force;
    }

    if (m_arrive)
    {
        steering_force = arrive(m_target) * 1.0;

        if (!accumulateForce(steering_force))
            return m_steering_force;
    }

    if (m_pursuit)
    {
        steering_force = pursue(m_pursuit_target) * 1.0;

        if (!accumulateForce(steering_force))
            return m_steering_force;
    }

    return m_steering_force;
}

/*********************************************************
*   seek
*
*   Perform the seek steering behavior using the passed
*   vector position.
*********************************************************/
ksVector2D ksComplexBehavior::seek(ksVector2D position)
{
    // Max speed = 150 (5 pixels per frame)
    ksVector2D desired_velocity = VecNormalize(position - m_vehicle->getPosition()) * 150;

    return (desired_velocity - m_vehicle->getVelocity());
}

/********************************************************
*   flee
*
*   Perform the flee steering behavior using the passed
*   vector. This method calculates the panic distance
*   and uses the squared value to determine whether or
*   not it should fleee.
*   The range gets checked in the calculate method.
********************************************************/
ksVector2D ksComplexBehavior::flee(ksVector2D position)
{
    // Only consider the position if it's within
    // the panic distance.
    double panic_dist_sq = 100.0 * 100.0;

    if (VecDistanceSq(m_vehicle->getPosition(), position) > panic_dist_sq)
        return ksVector2D(0, 0);

    // Max speed = 150 (5 pixels per frame)
    ksVector2D desired_velocity = VecNormalize(m_vehicle->getPosition() - position) * 150;

    return (desired_velocity - m_vehicle->getVelocity());
}

/*********************************************************
*   arrive
*
*   Performs the arrive steering behavior using the
*   passed vector position.
*********************************************************/
ksVector2D ksComplexBehavior::arrive(ksVector2D position)
{
    ksVector2D to_target = position - m_vehicle->getPosition();

    double distance = to_target.getLength();

    if (distance > 0)
    {
        double deceleration = 0.3;

        double speed = distance / deceleration;

        if (speed > 150.0) // Max speed: 150
            speed = 150.0;

        ksVector2D desired_velocity = to_target * speed / distance;

        return (desired_velocity - m_vehicle->getVelocity());
    }

    return ksVector2D(0, 0);
}

/********************************************************
*   pursue
*
*   Get the estimated future position of the target
*   entity and seek that position.
********************************************************/
ksVector2D ksComplexBehavior::pursue(ksComplex * pursuit_target)
{
    ksVector2D to_evader = m_pursuit_target->getPosition() - m_vehicle->getPosition();

    double relative_heading = m_vehicle->getHeading().getDotProduct(m_pursuit_target->getHeading());

    // Seek the evader's current position if it's ahead and facing
    // the agent.
    if ((to_evader.getDotProduct(m_vehicle->getHeading()) > 0) &&
        (relative_heading < -0.95))
        return seek(m_pursuit_target->getPosition());

    // If the evader's not ahead, then we predict where it will be
    double look_ahead = to_evader.getLength() / 
                        (150 + m_pursuit_target->getVelocity().getLength()); // Max speed: 150

    // Seek the evader's predicted future position.
    return seek(m_pursuit_target->getPosition() + 
                m_pursuit_target->getVelocity() * look_ahead);
}

/*********************************************************
*   offsetPursue
*
*   Gets the vector force that will pursue the desired
*   target at a particular offset away from it.
*********************************************************/
ksVector2D ksComplexBehavior::offsetPursue(ksComplex * pursuit_target, ksVector2D offset)
{
    return ksVector2D(0, 0);
}

/********************************************************
*   evade
*
*   Get the estimated future position of the target
*   entity and flee from that position.
********************************************************/
ksVector2D ksComplexBehavior::evade(ksComplex * evasion_target)
{
    ksVector2D to_pursuer = m_evasion_target->getPosition() - m_vehicle->getPosition();

    // Only consider pursuers if they are within
    // the threat range.
    double threat_range = 200.0;//100.0;

    if (to_pursuer.getLengthSq() > threat_range * threat_range)
        return ksVector2D(0, 0);

    double look_ahead = to_pursuer.getLength() /
                        (150 + m_evasion_target->getVelocity().getLength()); // Max speed: 150

    // Flee the pursuer's predicted future position.
    return flee(m_evasion_target->getPosition() +
                m_evasion_target->getVelocity() * look_ahead);
}

/*********************************************************
*   obstacleAvoidance
*
*   Calculates a steering force that will avoid nearby
*   obstacles and entities, based on who is in the group
*   and who it closest by.
*********************************************************/
ksVector2D ksComplexBehavior::obstacleAvoidance()
{
    // detection_length = min_detection + (m_vehicle.speed / max_speed) * min_detection
    double detection_length = 40.0 + (m_vehicle->getVelocity().getLength() / 150) * 40.0;

    // Tag neighbors if within 50 pixel view distance
    for (ksComplex * entity : m_group)
    {
        entity->untag();

        ksVector2D to = entity->getPosition() - m_vehicle->getPosition();

        double range = detection_length + entity->getBoundingRadius(); // detection_length + entity->bounding radius

        if ((entity != m_vehicle) && (to.getLengthSq() < range * range))
            entity->tag();
    }

    ksComplex * closest_obstacle = nullptr;

    double dist_to_closest = std::numeric_limits<double>::max();

    ksVector2D local_pos_closest;

    for (ksComplex * entity : m_group)
    {
        if (entity->getTag())
        {
            ksVector2D local_pos = getPointToLocalSpace(entity->getPosition(),
                                                     m_vehicle->getHeading(),
                                                     m_vehicle->getSide(),
                                                     m_vehicle->getPosition());
            if (local_pos.X >= 0)
            {
                // entity->bounding radius + m_vehicle->bounding radius
                double expanded_radius = entity->getBoundingRadius() + 
                                         m_vehicle->getBoundingRadius(); 

                if (fabs(local_pos.Y) < expanded_radius)
                {
                    double sqrt_part = sqrt((expanded_radius * expanded_radius) -
                                            (local_pos.Y * local_pos.Y));
                    double intersection = local_pos.X - sqrt_part;

                    if (intersection <= 0.0)
                        intersection = local_pos.X + sqrt_part;

                    if (intersection < dist_to_closest)
                    {
                        dist_to_closest = intersection;

                        closest_obstacle = entity;

                        local_pos_closest = local_pos;
                    }
                }
            }
        }
    }

    ksVector2D steering_force;

    if (closest_obstacle != nullptr)
    {
        double multiplier = 1.0 + (detection_length - local_pos_closest.X) / detection_length;

        // (closest_obstacle->bounding radius - local_pos_closest.Y) * mutiplier
        steering_force.Y = (closest_obstacle->getBoundingRadius() - local_pos_closest.Y) * 
                            multiplier;

        double braking_weight = 0.2;

        // (closest_obstacle->bounding radius - local_pos_closest.X) * braking_weight
        steering_force.X = (closest_obstacle->getBoundingRadius() - local_pos_closest.X) * 
                            braking_weight;
    }

    return getVectorToWorldSpace(steering_force, m_vehicle->getHeading(), m_vehicle->getSide());
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
void ksComplexBehavior::seekOn(ksVector2D vect)
{
    m_target = vect;
    m_seek = true;
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
void ksComplexBehavior::fleeOn(ksVector2D vect)
{
    m_target       = vect;
    m_flee         = true;
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

/*********************************************************
*   arriveOn
*
*   Toggle on the arrive behavior for this complex entity.
*********************************************************/
void ksComplexBehavior::arriveOn(ksVector2D vect)
{
    m_arrive = true;
    m_target = vect;
}

/*********************************************************
*   arriveOff
*
*   Toggle off the arrive behavior for this complex entity.
*********************************************************/
void ksComplexBehavior::arriveOff()
{
    m_arrive = false;
}

/*********************************************************
*   pursuitOn
*
*   Toggle on the pursuit behavior for this complex entity.
*********************************************************/
void ksComplexBehavior::pursuitOn(ksComplex * vehicle)
{
    m_pursuit_target = vehicle;
    m_pursuit = true;
}

/*********************************************************
*   pursuitOff
*
*   Toggle off the pursuit behavior for this complex entity.
*********************************************************/
void ksComplexBehavior::pursuitOff()
{
    m_pursuit = false;
}

/*********************************************************
*   offsetPursuitOn
*
*   Toggle on the offset pursuit behavior for this complex
*   entity.
*********************************************************/
void ksComplexBehavior::offsetPursuitOn(ksComplex * vehicle, ksVector2D offset)
{
    m_offset_pursuit = true;
    m_pursuit_target = vehicle;
}

/*********************************************************
*   offsetPursuitOff
*
*   Toggle off the offset pursuit behavior for this complex
*   entity.
*********************************************************/
void ksComplexBehavior::offsetPursuitOff()
{
    m_offset_pursuit = false;
}

/*********************************************************
*   evasionOn
*
*   Toggle on the evasion behavior for this complex entity.
*********************************************************/
void ksComplexBehavior::evasionOn(ksComplex * vehicle)
{
    m_evasion_target = vehicle;
    m_evasion = true;
}

/*********************************************************
*   evasionOff
*
*   Toggle off the evasion behavior for this complex entity.
*********************************************************/
void ksComplexBehavior::evasionOff()
{
    m_evasion = false;
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

/*********************************************************
*   obstacleOn
*
*   Toggle on the obstacle avoidance behavior for this
*   complex entity.
*********************************************************/
void ksComplexBehavior::obstacleOn()
{
    m_obstacle = true;
}

/*********************************************************
*   obstacleOff
*
*   Toggle off the obstacle avoidance behavior for this
*   complex entity.
*********************************************************/
void ksComplexBehavior::obstacleOff()
{
    m_obstacle = false;
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

/*********************************************************
*   getPathHeading
*
*   Returns the path heading of the vehicle.
*********************************************************/
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
    int max_row = m_world->getWallMaxRow(BOTTOM);

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
    int max_col = m_world->getWallMaxCol(BOTTOM);

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
    ksTile position = m_world->getTilePosition(BOTTOM, row, col,
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

/*********************************************************
*   accumulateForce
*
*   Allow for the next added force to be added if there's
*   enough remaining force relative to the maximum
*   steering force. If there isn't enough remaining
*   force, then fill the remainder of the steering force
*   with the incoming force. Returns false if there
*   wasn't enough remaining force.
*********************************************************/
bool ksComplexBehavior::accumulateForce(ksVector2D force)
{
    double magnitude = m_steering_force.getLength();

    double mag_remaining = 400.0 - magnitude; // Max force: 400.0

    if (mag_remaining > 0.0)
    {
        if (force.getLength() < mag_remaining)
            m_steering_force += force;
        else
            m_steering_force += VecNormalize(force) * mag_remaining;
    }
    else
        return false;

    return true;
}

/*********************************************************
*   getPointToLocalSpace
*
*   Converts a point, heading, side and position to
*   local space for behavior based calculations.
*********************************************************/
ksVector2D ksComplexBehavior::getPointToLocalSpace(ksVector2D point, ksVector2D heading,
                                                   ksVector2D side, ksVector2D position)
{
    double transform_x = -position.getDotProduct(heading);
    double transform_y = -position.getDotProduct(side);

    // Create transformation matrix
    double transform_11 = heading.X;
    double transform_12 = side.X;

    double transform_21 = heading.Y;
    double transform_22 = side.Y;

    double transform_31 = transform_x;
    double transform_32 = transform_y;

    // Apply the transform to the point
    double temp_x = (transform_11 * point.X) + (transform_21 * point.Y) + transform_31;
    double temp_y = (transform_12 * point.X) + (transform_22 * point.Y) + transform_32;

    point.X = temp_x;
    point.Y = temp_y;

    return point;
}

/*********************************************************
*   getPointToWorldSpace
*
*   Converts a point, heading, side, and position to
*   world space for behavior based calculations.
*********************************************************/
ksVector2D ksComplexBehavior::getPointToWorldSpace(ksVector2D point, ksVector2D heading,
                                                   ksVector2D side, ksVector2D position)
{
    return ksVector2D(0, 0);
}

/*********************************************************
*   getVectorToWorldSpace
*
*   Returns a vector to world space relative to the passed
*   vector, heading, and side.
*********************************************************/
ksVector2D ksComplexBehavior::getVectorToWorldSpace(ksVector2D vect, ksVector2D heading,
                                                    ksVector2D side)
{
    double transform_11 = (1 * vect.X) + (0 * side.X) + (0 * 0);
    double transform_12 = (1 * vect.Y) + (0 * side.Y) + (0 * 0);
    //double transform_13 = (1 * 0) + (0 * 0) + (0 * 1);

    double transform_21 = (0 * vect.X) + (1 * side.X) + (0 * 0);
    double transform_22 = (0 * vect.Y) + (1 * side.Y) + (0 * 0);
    //double transform_23 = (0 * 0) + (1 * 0) + (0 * 1);

    double transform_31 = (0 * vect.X) + (0 * side.X) + (1 * 0);
    double transform_32 = (0 * vect.Y) + (0 * side.Y) + (1 * 0);
    //double transform_33 = (0 * 0) + (0 * 0) + (1 * 1);

    double temp_x = (transform_11 * vect.X) + (transform_21 * vect.Y) + transform_31;
    double temp_y = (transform_12 * vect.X) + (transform_22 * vect.Y) + transform_32;

    vect.X = temp_x;
    vect.Y = temp_y;

    return vect;
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
        if ((entity != m_vehicle) && entity->getTag() && (entity != m_evasion_target))
        {
            ksVector2D ToAgent = m_vehicle->getPosition() - entity->getPosition();
            
            steering += VecNormalize(ToAgent) / ToAgent.getLength();
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
    ksVector2D avg_heading;

    int neighbor_count = 0;

    for (ksComplex * entity : m_group)
    {
        if ((entity != m_vehicle) && entity->getTag() && (entity != m_evasion_target))
        {
            avg_heading += entity->getHeading();

            ++neighbor_count;
        }
    }

    if (neighbor_count > 0)
    {
        avg_heading /= (double) neighbor_count;
        avg_heading -= m_vehicle->getHeading();
    }

    return avg_heading;
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

    int neighbor_count = 0;

    for (ksComplex * entity : m_group)
    {
        if ((entity != m_vehicle) && entity->getTag() && (entity != m_evasion_target))
        {
            center += entity->getPosition();
            ++neighbor_count;
        }
    }

    if (neighbor_count > 0)
    {
        center /= (double) neighbor_count;
        steering = seek(center);
    }

    return VecNormalize(steering);
}
