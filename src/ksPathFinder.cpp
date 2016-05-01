/********************************************************
* Class:            ksPathFinder
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksPathFinder.cpp
********************************************************/

#include "ksPathFinder.h"
#include <iostream>

/********************************************************
*   ksPathFinder
*
*   Initializes a pointer to the instance of ksWorld
*   so that checks for collidable tiles can be made.
********************************************************/
ksPathFinder::ksPathFinder(ksWorld * world)
    : m_world(world)
{ }

/********************************************************
*   calculatePath
*
*   Calculates the shortest path from start to finish
*   using the A* pathfinding algorithm and the Manhattan
*   heuristic.
********************************************************/
std::list<ksPathNode> ksPathFinder::calculatePath(ksEntity * entity, int finish_row, int finish_col)
{
    ksPathNode current_node;
    std::vector<ksPathNode> adjacent_nodes;
    std::list<ksPathNode>::iterator iter;
    std::list<ksPathNode> navigated_nodes;
    
    m_entity = entity;

    current_node = createPathNode((int) entity->Y() / TILE_WIDTH,
                                  (int) entity->X() / TILE_WIDTH);
    
    // If the end goal isn't reachable, don't even try.
    if (m_world->getTileEvent(BOTTOM, finish_row, finish_col) != 0)
    {
        navigated_nodes.push_back(current_node);
        return navigated_nodes;
    }
    
    m_finish     = createPathNode(finish_row, finish_col);
    m_start      = current_node;

    m_closed.clear();
    m_open.clear();

    m_open.push_back(current_node);

    do
    {
        current_node = getNodeWithLowestCost();

        // Add the current node to the closed list.
        m_closed.push_back(current_node);

        // Remove the current node from the open list.
        iter = std::find(m_open.begin(), m_open.end(), current_node);

        if (iter != m_open.end())
            iter = m_open.erase(iter);

        // If the closed list contains the destination.
        if (foundInClosed(m_finish))
            break;

        findAdjacentNodes(current_node, adjacent_nodes);

        for (ksPathNode node : adjacent_nodes)
        {
            int tentative_g = current_node.g_score + 1;

            // If the closed list does not contain the adjacent node.
            if (!foundInClosed(node))
            {
                // If the open list does not contain the adjacent node.
                if (!foundInOpen(node))
                {
                    if (node.parent != nullptr)
                        delete node.parent;
                    
                    node.parent = new ksPathNode(current_node);
                    node.g_score = current_node.g_score + 1;
                    node.f_score = node.g_score + getHeuristicValue(node, m_finish);
                    m_open.push_back(node);
                }
                else if (tentative_g < node.g_score)
                {
                    if (node.parent != nullptr)
                        delete node.parent;

                    node.parent  = new ksPathNode(current_node);
                    node.g_score = node.parent->g_score + 1;
                    node.f_score = node.g_score + getHeuristicValue(node, m_finish);
                }
            }
        }

        adjacent_nodes.clear();

    } while (!m_open.empty());

    iter = std::find(m_closed.begin(), m_closed.end(), current_node);

    if (iter != m_closed.end())
    {
        m_finish.parent = (*iter).parent;

        ksPathNode * current_ptr = &m_finish;

        while (current_ptr != nullptr && (*current_ptr) != m_start)
        {
            navigated_nodes.push_front((*current_ptr));
            std::cout << "Node: " << (*current_ptr).row << ", " << (*current_ptr).col << '\n';

            current_ptr = current_ptr->parent;
        }
    }

    return navigated_nodes;
}

/********************************************************
*   getNodeWithLowestCost
*
*   Returns the node with the lowest F score, where
*   F = G (movement cost) + H (heuristic) from the open
*   list of path nodes.
********************************************************/
ksPathNode ksPathFinder::getNodeWithLowestCost()
{
    ksPathNode lowest_node;
    lowest_node.g_score = -1;

    // Set a large number for the initial value of F.
    int lowest_f = 30000;

    for (ksPathNode node : m_open)
    {
        if (node.parent != nullptr)
            node.g_score = node.parent->g_score + 1;
        
        node.f_score = node.g_score + getHeuristicValue(node, m_finish);

        if (node.f_score <= lowest_f)
        {
            lowest_node = node;
            lowest_f    = node.f_score;
        }
    }

    return lowest_node;
}

/********************************************************
*   findAdjacentNodes
*
*   Edits the adjacency list passed with the nodes
*   adjacent to the node being evaluated.
********************************************************/
void ksPathFinder::findAdjacentNodes(ksPathNode current,
        std::vector<ksPathNode> & adjacent)
{
    // Top
    if ((current.row - 1) >= 0 && m_world->getTileEvent(BOTTOM, current.row - 1, current.col) == 0)
    {
        ksPathNode top = createPathNode(current.row - 1, current.col);
        top.parent  = new ksPathNode(current);
        top.g_score = current.g_score + 1;

        adjacent.push_back(top);
    }

    // Left
    if ((current.col - 1) >= 0 && m_world->getTileEvent(BOTTOM, current.row, current.col - 1) == 0)
    {
        ksPathNode left = createPathNode(current.row, current.col - 1);
        left.parent  = new ksPathNode(current);
        left.g_score = current.g_score + 1;

        adjacent.push_back(left);
    }

    int max_row = m_world->getWallMaxRow(BOTTOM);
    int max_col = m_world->getWallMaxCol(BOTTOM);

    // Bottom
    if ((current.row + 1) < max_row && m_world->getTileEvent(BOTTOM, current.row + 1, current.col) == 0)
    {
        ksPathNode bottom = createPathNode(current.row + 1, current.col);
        bottom.parent  = new ksPathNode(current);
        bottom.g_score = current.g_score + 1;

        adjacent.push_back(bottom);
    }
        
    // Right
    if ((current.col + 1) < max_col && m_world->getTileEvent(BOTTOM, current.row, current.col + 1) == 0)
    {
        ksPathNode right = createPathNode(current.row, current.col + 1);
        right.parent  = new ksPathNode(current);
        right.g_score = current.g_score + 1;

        adjacent.push_back(right);
    }
}

/********************************************************
*   getHeuristicValue
*
*   Calculates and returns the heuristic value between
*   the current path node and the finish node using
*   the Manhattan heuristic.
********************************************************/
int ksPathFinder::getHeuristicValue(ksPathNode current, ksPathNode finish)
{
    int heuristic = std::abs(finish.row - current.row) + std::abs(finish.col - current.col);

    return heuristic;
}

bool ksPathFinder::foundInClosed(ksPathNode current)
{
    bool found = false;

    for (ksPathNode node : m_closed)
    {
        if (current.row  == node.row &&
            current.col  == node.col)
        {
            found = true;
            break;
        }
    }

    return found;
}

bool ksPathFinder::foundInOpen(ksPathNode current)
{
    bool found = false;

    for (ksPathNode node : m_open)
    {
        if (current.row == node.row &&
            current.col == node.col)
        {
            found = true;
            break;
        }
    }

    return found;
}

ksPathNode ksPathFinder::createPathNode(int row, int col)
{
    ksPathNode node;

    double left_x = ((double) col / m_world->getMapCol()) * TILE_WIDTH;
    double top_y  = 1.0 - ((double) m_entity->getHeight() / m_world->getHeight());
    double z      = ((double) row / m_world->getMapRow()) * TILE_WIDTH;

    sf::Vector2f top_left       = m_world->transform3D(left_x, top_y, z);
    sf::Vector2f top_right      = m_world->transform3D(left_x + m_entity->getWidth(), top_y, z);
    sf::Vector2f bottom_right   = m_world->transform3D(left_x + m_entity->getWidth(), 
                                  top_y + m_entity->getHeight(), z);
    sf::Vector2f bottom_left    = m_world->transform3D(left_x, top_y + m_entity->getHeight(), z);

    node.TL.X     = top_left.x;
    node.TL.Y     = top_left.y;
    node.TR.X     = top_right.x;
    node.TR.Y     = top_right.y;
    node.BR.X     = bottom_right.x;
    node.BR.Y     = bottom_right.y;
    node.BL.X     = bottom_left.x;
    node.BL.Y     = bottom_left.y;

    node.center.X = node.TL.X + ((node.TR.X - node.TL.X) / 2);
    node.center.Y = node.TL.Y + ((node.BL.Y - node.TL.Y) / 2);
    node.row      = row;
    node.col      = col;
    node.g_score  = 0;
    node.f_score  = 0;

    return node;
}
