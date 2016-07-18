////////////////////////////////////////////////////////////
//
// KingEngine
// The MIT License (MIT)
// Copyright (c) 2016 Beyond Parallel
//
// Permission is hereby granted, free of charge, to any person 
// obtaining a copy of this software and associated documentation 
// files (the "Software"), to deal in the Software without restriction, 
// including without limitation the rights to use, copy, modify, merge, 
// publish, distribute, sublicense, and/or sell copies of the Software, 
// and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be 
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ksComplex.h"
#include <iostream>

////////////////////////////////////////////////////////////
ksComplex::ksComplex(ksPathFinder * path_finder, ksWorld * world, int x, int y, int z,
                     int w, int h, int current_tile) :
                     ksEntity(world, x, y, z, w, h, current_tile),
                     m_behavior(path_finder, world, this),
                     m_loop_path(false), m_path_on(false), m_start_row(0), m_start_col(0), 
                     m_finish_row(0), m_finish_col(0), m_bounding_radius((w * TILE_WIDTH) / 2),
                     m_tag(false), m_behavior_on(true)
{
    m_path_finder = path_finder;

    sf::Vector2f temp_vect = world->transform3DWithPixelValue(x, y, z);
    
    m_position.X = temp_vect.x;
    m_position.Y = temp_vect.y;
    m_velocity  = ksVector2D(0, 0);
    m_heading   = ksVector2D(0, 0);
    
    updateScreenPosition();
}

////////////////////////////////////////////////////////////
void ksComplex::update()
{
    if (m_behavior_on)
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

            //m_velocity.truncate(150); // Results in 5 pixels / frame (150 pixels / sec * 1 sec / 30 frames)
            m_velocity.truncate(300); // Results in 10 pixels / frame (300  pixels / sec * 1 sec / 30 frames)
        
            m_position               += m_velocity * time; // p = v * t

            if (m_velocity.getLengthSq() > 0.00000001)
            {
                m_heading = VecNormalize(m_velocity);
                m_side = m_heading.getPerpendicularVector();
            }

            m_elapsed_time.restart();

            // Loop entity around boundaries.
            if (m_position.X > m_world->getWidth())
                m_position.X = m_world->getWidth();
            if (m_position.X < 0)
                m_position.X = 0;
            if (m_position.Y > m_world->getDepth())
                m_position.Y = m_world->getDepth();
            if (m_position.Y < 0)
                m_position.Y = 0;

            m_x = m_position.X;
            m_z = m_position.Y;
            
            // Update the position of the complex entity on
            // the screen.
            updateScreenPosition();
        }
    }
}

////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////
void ksComplex::seek(ksVector2D vect)
{
    m_behavior.seekOn(vect);
}

////////////////////////////////////////////////////////////
void ksComplex::flee(ksVector2D vect)
{
    m_behavior.fleeOn(vect);
}

////////////////////////////////////////////////////////////
void ksComplex::arrive(ksVector2D vect)
{
    m_behavior.arriveOn(vect);
}

////////////////////////////////////////////////////////////
void ksComplex::pursue(ksComplex * entity)
{
    m_behavior.pursuitOn(entity);
}

////////////////////////////////////////////////////////////
void ksComplex::evade(ksComplex * entity)
{
    m_behavior.evasionOn(entity);
}

////////////////////////////////////////////////////////////
void ksComplex::addToGroup(ksComplex * entity)
{
    m_behavior.addToGroup(entity);
}

////////////////////////////////////////////////////////////
void ksComplex::clearGroup()
{
    m_behavior.clearGroup();
}

////////////////////////////////////////////////////////////
void ksComplex::group()
{
    m_behavior.groupOn();
}

////////////////////////////////////////////////////////////
void ksComplex::avoidObstacles()
{
    m_behavior.obstacleOn();
}

////////////////////////////////////////////////////////////
void ksComplex::tag()
{
    m_tag = true;
}

////////////////////////////////////////////////////////////
void ksComplex::untag()
{
    m_tag = false;
}

////////////////////////////////////////////////////////////
ksPathNode ksComplex::getNextPathNode()
{
    return m_behavior.getNextPathNode();
}

////////////////////////////////////////////////////////////
ksVector2D ksComplex::getHeading()
{
    return m_heading;
}

////////////////////////////////////////////////////////////
ksVector2D ksComplex::getVelocity()
{
    return m_velocity;
}

////////////////////////////////////////////////////////////
ksVector2D ksComplex::getPosition()
{
    return m_position;
}

////////////////////////////////////////////////////////////
ksVector2D ksComplex::getSide()
{
    return m_side;
}

////////////////////////////////////////////////////////////
bool ksComplex::getTag()
{
    return m_tag;
}

////////////////////////////////////////////////////////////
int ksComplex::getBoundingRadius()
{
    return m_bounding_radius;
}

////////////////////////////////////////////////////////////
void ksComplex::toggleBehavior()
{
    m_behavior_on = !m_behavior_on;
}

// void ksComplex::moveEntity(int x, int y, int z)
// {
//     //m_position.X = x;
//     //m_position.Y = z;
//     m_x = x;
//     m_y = y;
//     m_z = z;
    
//     // Update the position of the entity on the screen.
//     updateScreenPosition();
// }