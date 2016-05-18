/********************************************************
* Class:            ksWorld
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksWorld.cpp
********************************************************/

#include "ksWorld.h"
#include <iostream>
#include <math.h>

/********************************************************
*   ksWorld
*
*   Initialize the world without any map loaded.
********************************************************/
ksWorld::ksWorld(std::string tilesheet)
    : m_width(0), m_height(0), m_depth(0), m_inner_x(0), m_inner_y(0), 
      m_num_of_lights(0), m_tilesheet(tilesheet), m_lighting(true), m_2D(false),
      m_world_width_px(0), m_world_height_px(0), m_world_depth_px(0),
      m_map_row_num(0), m_map_col_num(0), m_map_depth_num(0),
      m_camera_x(0), m_camera_y(0), m_camera_z(0)
{
    m_texture.loadFromFile(tilesheet);
    m_base_color = sf::Color(50, 50, 50);

    m_front_tex  = &m_front;
    m_left_tex   = &m_left;
    m_right_tex  = &m_right;
    m_top_tex    = &m_top;
    m_bottom_tex = &m_bottom;

    m_front_cur_evt  = &m_front_evt;
    m_left_cur_evt   = &m_left_evt;
    m_right_cur_evt  = &m_right_evt;
    m_top_cur_evt    = &m_top_evt;
    m_bottom_cur_evt = &m_bottom_evt;
    
    m_front_num_row  = &m_height;
    m_front_num_col  = &m_width;
    m_left_num_row   = &m_height;
    m_left_num_col   = &m_depth;
    m_right_num_row  = &m_height;
    m_right_num_col  = &m_depth;
    m_top_num_row    = &m_depth;
    m_top_num_col    = &m_width;
    m_bottom_num_row = &m_depth;
    m_bottom_num_col = &m_width;
}

/********************************************************
*   ksWorld
*
*   Initialize the world based on the passed width,
*   height and depth values defining the world.
********************************************************/
ksWorld::ksWorld(std::string tilesheet, int width, int height, int depth)
    : m_width(width), m_height(height), m_depth(depth), m_inner_x(0), m_inner_y(0),
      m_tilesheet(tilesheet), m_lighting(true), m_2D(false)
{
    if (m_depth < 0)
        m_depth = 0;

    m_texture.loadFromFile(tilesheet);
    m_base_color = sf::Color(50, 50, 50);

    m_front_tex  = &m_front;
    m_left_tex   = &m_left;
    m_right_tex  = &m_right;
    m_top_tex    = &m_top;
    m_bottom_tex = &m_bottom;

    m_front_cur_evt  = &m_front_evt;
    m_left_cur_evt   = &m_left_evt;
    m_right_cur_evt  = &m_right_evt;
    m_top_cur_evt    = &m_top_evt;
    m_bottom_cur_evt = &m_bottom_evt;
    
    m_front_num_row  = &m_height;
    m_front_num_col  = &m_width;
    m_left_num_row   = &m_height;
    m_left_num_col   = &m_depth;
    m_right_num_row  = &m_height;
    m_right_num_col  = &m_depth;
    m_top_num_row    = &m_depth;
    m_top_num_col    = &m_width;
    m_bottom_num_row = &m_depth;
    m_bottom_num_col = &m_width;

    //load(m_width, m_height, m_depth);
}

/********************************************************
*   load
*
*   Load a map with (width x height x depth) values.
********************************************************/
void ksWorld::load(int width, int height, int depth, int map_row, int map_col, int map_depth, std::string name)
{
    m_width  = map_col;
    m_height = map_row;
    m_depth  = map_depth;
    m_world_name = name;

    //m_world_width_px  = 800;
    //m_world_height_px = 640;
    m_world_width_px  = width;
    m_world_height_px = height;
    //m_world_depth_px  = 256;
    m_world_depth_px  = depth;
    m_map_row_num     = 4;
    m_map_col_num     = 8;
    m_map_depth_num   = 8;
    m_camera_x        = m_world_width_px / 2;
    m_camera_y        = m_world_height_px / 2;
    m_camera_z        = m_world_depth_px;
    
    m_array.clear();

    if (name != "")
        readTiles(m_world_name);

    m_array.setPrimitiveType(sf::Triangles);

    // m_outer_width_px = ((m_depth * 2) + m_width) * TILE_WIDTH;
    // m_outer_height_px = ((m_depth * 2) + m_height) * TILE_HEIGHT;

    // m_inner_x = (m_outer_width_px / 2) - ((m_width * TILE_WIDTH) / 2);
    // m_inner_y = (m_outer_height_px / 2) - ((m_height * TILE_HEIGHT) / 2);

    transform3DWorld(m_world_width_px, m_world_height_px, m_world_depth_px,
                     m_map_row_num, m_map_col_num, m_map_depth_num);
    //calculateTilePositions();
    //updateTilePositions();
    //updateTextureCoordinates();
}

/********************************************************
*   readTiles
*
*   Read in the tiles off of all of the maps for the
*   different walls, as well as the light maps for each
*   wall.
********************************************************/
void ksWorld::readTiles(std::string name)
{
    m_map_name = name;

    /*          Front Side           */
    std::ifstream map(m_map_name + "/_front.ks");

    if (map.is_open())
    {
        m_front.resize(m_height);
        m_front_light.resize(m_height);

        int tile_type = -1;
    
        for (int row = 0; row < m_height; ++row)
        {
            m_front[row].resize(m_width);
            m_front_light[row].resize(m_width);

            for (int col = 0; col < m_width && !map.eof(); ++col)
            {
                map >> tile_type;

                int type_x = ((tile_type - (TILE_PER_LINE * (tile_type / TILE_PER_LINE)))
                               * TILE_WIDTH) / 2;
                int type_y = ((tile_type / TILE_PER_LINE) * TILE_HEIGHT) / 2;
                int type_w = TILE_WIDTH / 2;
                int type_h = TILE_HEIGHT / 2;

                m_front[row][col].TL = ksVector2D(type_x, type_y);
                m_front[row][col].TR = ksVector2D(type_x + type_w, type_y);
                m_front[row][col].BR = ksVector2D(type_x + type_w, type_y + type_h);
                m_front[row][col].BL = ksVector2D(type_x, type_y + type_h);

                m_front_light[row][col] = 0;
            }
        }

        map.close();
    }

    /*          Front Side Evt      */
    map.open(m_map_name + "/_front_evt.ks");

    if (map.is_open())
    {
        int temp = 0;
        m_front_evt.resize(m_height);
        
        for (int row = 0; row < m_height; ++row)
        {
            m_front_evt[row].resize(m_width);

            for (int col = 0; col < m_width && !map.eof(); ++col)
            {
                map >> temp;
                m_front_evt[row][col] = temp;
            }
        }

        map.close();
    }

    /*          Left Side           */
    map.open(m_map_name + "/_left.ks");

    if (map.is_open())
    {
        m_left.resize(m_height);
        m_left_light.resize(m_height);

        int tile_type = -1;
    
        for (int row = 0; row < m_height; ++row)
        {
            m_left[row].resize(m_depth);
            m_left_light[row].resize(m_depth);
            
            for (int col = 0; col < m_depth && !map.eof(); ++col)
            {
                map >> tile_type;

                int type_x = ((tile_type - (TILE_PER_LINE * (tile_type / TILE_PER_LINE)))
                               * TILE_WIDTH) / 2;
                int type_y = ((tile_type / TILE_PER_LINE) * TILE_HEIGHT) / 2;
                int type_w = TILE_WIDTH / 2;
                int type_h = TILE_HEIGHT / 2;

                m_left[row][col].TL = ksVector2D(type_x, type_y);
                m_left[row][col].TR = ksVector2D(type_x + type_w, type_y);
                m_left[row][col].BR = ksVector2D(type_x + type_w, type_y + type_h);
                m_left[row][col].BL = ksVector2D(type_x, type_y + type_h);

                m_left_light[row][col] = 0;
            }
        }

        map.close();
    }

    /*          Left Side Evt      */
    map.open(m_map_name + "/_left_evt.ks");

    if (map.is_open())
    {
        int temp = 0;
        m_left_evt.resize(m_height);
        
        for (int row = 0; row < m_height; ++row)
        {
            m_left_evt[row].resize(m_depth);

            for (int col = 0; col < m_depth && !map.eof(); ++col)
            {
                map >> temp;
                m_left_evt[row][col] = temp;
            }
        }

        map.close();
    }
    
    /*          Right Side           */
    map.open(m_map_name + "/_right.ks");

    if (map.is_open())
    {
        m_right.resize(m_height);
        m_right_light.resize(m_height);

        int tile_type = -1;
    
        for (int row = 0; row < m_height; ++row)
        {
            m_right[row].resize(m_depth);
            m_right_light[row].resize(m_depth);
            
            for (int col = 0; col < m_depth && !map.eof(); ++col)
            {
                map >> tile_type;

                int type_x = ((tile_type - (TILE_PER_LINE * (tile_type / TILE_PER_LINE)))
                               * TILE_WIDTH) / 2;
                int type_y = ((tile_type / TILE_PER_LINE) * TILE_HEIGHT) / 2;
                int type_w = TILE_WIDTH / 2;
                int type_h = TILE_HEIGHT / 2;

                m_right[row][col].TL = ksVector2D(type_x, type_y);
                m_right[row][col].TR = ksVector2D(type_x + type_w, type_y);
                m_right[row][col].BR = ksVector2D(type_x + type_w, type_y + type_h);
                m_right[row][col].BL = ksVector2D(type_x, type_y + type_h);
            
                m_right_light[row][col] = 0;
            }
        }

        map.close();
    }
    
    /*          Right Side Evt      */
    map.open(m_map_name + "/_right_evt.ks");

    if (map.is_open())
    {
        int temp = 0;
        m_right_evt.resize(m_height);
        
        for (int row = 0; row < m_height; ++row)
        {
            m_right_evt[row].resize(m_depth);

            for (int col = 0; col < m_depth && !map.eof(); ++col)
            {
                map >> temp;
                m_right_evt[row][col] = temp;
            }
        }

        map.close();
    }

    /*          Top Side           */
    map.open(m_map_name + "/_top.ks");

    if (map.is_open())
    {
        m_top.resize(m_depth);
        m_top_light.resize(m_depth);

        int tile_type = -1;
    
        for (int row = 0; row < m_depth; ++row)
        {
            m_top[row].resize(m_width);
            m_top_light[row].resize(m_width);
            
            for (int col = 0; col < m_width && !map.eof(); ++col)
            {
                map >> tile_type;

                int type_x = ((tile_type - (TILE_PER_LINE * (tile_type / TILE_PER_LINE)))
                               * TILE_WIDTH) / 2;
                int type_y = ((tile_type / TILE_PER_LINE) * TILE_HEIGHT) / 2;
                int type_w = TILE_WIDTH / 2;
                int type_h = TILE_HEIGHT / 2;

                m_top[row][col].TL = ksVector2D(type_x, type_y);
                m_top[row][col].TR = ksVector2D(type_x + type_w, type_y);
                m_top[row][col].BR = ksVector2D(type_x + type_w, type_y + type_h);
                m_top[row][col].BL = ksVector2D(type_x, type_y + type_h);
            
                m_top_light[row][col] = 0;
            }
        }

        map.close();
    }

    /*          Top Side Evt      */
    map.open(m_map_name + "/_top_evt.ks");

    if (map.is_open())
    {
        int temp = 0;
        m_top_evt.resize(m_depth);
        
        for (int row = 0; row < m_depth; ++row)
        {
            m_top_evt[row].resize(m_width);

            for (int col = 0; col < m_width && !map.eof(); ++col)
            {
                map >> temp;
                m_top_evt[row][col] = temp;
            }
        }

        map.close();
    }

    /*          Bottom Side           */
    map.open(m_map_name + "/_bottom.ks");

    if (map.is_open())
    {
        m_bottom.resize(m_depth);
        m_bottom_light.resize(m_depth);

        int tile_type = -1;
    
        for (int row = 0; row < m_depth; ++row)
        {
            m_bottom[row].resize(m_width);
            m_bottom_light[row].resize(m_width);
            
            for (int col = 0; col < m_width && !map.eof(); ++col)
            {
                map >> tile_type;

                int type_x = ((tile_type - (TILE_PER_LINE * (tile_type / TILE_PER_LINE)))
                               * TILE_WIDTH) / 2;
                int type_y = ((tile_type / TILE_PER_LINE) * TILE_HEIGHT) / 2;
                int type_w = TILE_WIDTH / 2;
                int type_h = TILE_HEIGHT / 2;

                m_bottom[row][col].TL = ksVector2D(type_x, type_y);
                m_bottom[row][col].TR = ksVector2D(type_x + type_w, type_y);
                m_bottom[row][col].BR = ksVector2D(type_x + type_w, type_y + type_h);
                m_bottom[row][col].BL = ksVector2D(type_x, type_y + type_h);
            
                m_bottom_light[row][col] = 0;
            }
        }

        map.close();
    }

    /*          Bottom Side Evt      */
    map.open(m_map_name + "/_bottom_evt.ks");

    if (map.is_open())
    {
        int temp = 0;
        m_bottom_evt.resize(m_depth);
        
        for (int row = 0; row < m_depth; ++row)
        {
            m_bottom_evt[row].resize(m_width);

            for (int col = 0; col < m_width && !map.eof(); ++col)
            {
                map >> temp;
                m_bottom_evt[row][col] = temp;
            }
        }

        map.close();
    }

    /*          Back Side           */
    map.open(m_map_name + "/_back.ks");

    if (map.is_open())
    {
        m_back.resize(m_height);
        m_back_light.resize(m_height);

        int tile_type = -1;
    
        for (int row = 0; row < m_height; ++row)
        {
            m_back[row].resize(m_width);
            m_back_light[row].resize(m_width);
            
            for (int col = 0; col < m_width && !map.eof(); ++col)
            {
                map >> tile_type;

                int type_x = ((tile_type - (TILE_PER_LINE * (tile_type / TILE_PER_LINE)))
                               * TILE_WIDTH) / 2;
                int type_y = ((tile_type / TILE_PER_LINE) * TILE_HEIGHT) / 2;
                int type_w = TILE_WIDTH / 2;
                int type_h = TILE_HEIGHT / 2;

                m_back[row][col].TL = ksVector2D(type_x, type_y);
                m_back[row][col].TR = ksVector2D(type_x + type_w, type_y);
                m_back[row][col].BR = ksVector2D(type_x + type_w, type_y + type_h);
                m_back[row][col].BL = ksVector2D(type_x, type_y + type_h);
            
                m_back_light[row][col] = 0;
            }
        }

        map.close();
    }
    
    /*          Back Side Evt      */
    map.open(m_map_name + "/_back_evt.ks");

    if (map.is_open())
    {
        int temp = 0;
        m_back_evt.resize(m_height);
        
        for (int row = 0; row < m_height; ++row)
        {
            m_back_evt[row].resize(m_width);

            for (int col = 0; col < m_width && !map.eof(); ++col)
            {
                map >> temp;
                m_back_evt[row][col] = temp;
            }
        }

        map.close();
    }
}

/********************************************************
*   draw
*
*   Call the SFML draw in order to draw this layer to
*   the screen.
********************************************************/
void ksWorld::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_array, states);
}

/********************************************************
*   drawWorld
*
*   Draws the world along with the overlaying effect
*   layer for lighting.
********************************************************/
void ksWorld::drawWorld(sf::RenderWindow & app)
{
    app.draw(*this);
    app.draw(m_effect_layer);
}

/*********************************************************
*   addLight
*
*   Adds a light projecting from a start position to
*   a particular tile on a wall. If the start position
*   is set to 0, 0 then the projection beam will disappear.
*********************************************************/
void ksWorld::addLight(ksVector2D start, ksWorldWall wall, int row, int col,
                       sf::Color first, sf::Color second)
{
    ksTile temp;
    ksVector2D end;

    if (wall == TOP)
    {
        if (m_depth <= 0)
            return;

        m_top_light[row][col] = 3;
//        temp = calculateTopPosition(row, col);

        end.X = temp.TL.X + (fabs(temp.TR.X - temp.TL.X) / 2);
        end.Y = temp.TL.Y + (fabs(temp.TR.Y - temp.TL.Y) / 2);
    }
    else if (wall == BOTTOM)
    {
        if (m_depth <= 0)
            return;
        
        m_bottom_light[row][col] = 3;
        
//        temp = calculateBottomPosition(row, col);
        end.X = temp.TL.X + (fabs(temp.TR.X - temp.TL.X) / 2);
        end.Y = temp.TL.Y + (fabs(temp.TR.Y - temp.TL.Y) / 2);
    }
    else if (wall == LEFT)
    {
        if (m_depth <= 0)
            return;
        
        for (int outer_row = row - 2; outer_row < (row + 3); ++outer_row)
        {
            for (int outer_col = col - 2; outer_col < (col + 3); ++outer_col)
            {
                if (outer_row >= 0 && 
                    outer_col >= 0 &&
                    outer_row < m_height &&
                    outer_col < m_depth)
                {
                    m_left_light[outer_row][outer_col] += 1;
                }
            }
        }

        for (int outer_row = row - 1; outer_row < (row + 2); ++outer_row)
        {
            for (int outer_col = col - 1; outer_col < (col + 2); ++outer_col)
            {
                if (outer_row >= 0 && 
                    outer_col >= 0 &&
                    outer_row < m_height &&
                    outer_col < m_depth)
                {
                    m_left_light[outer_row][outer_col] += 1;
                }
            }
        }

        m_left_light[row][col] += 1;

//        temp = calculateLeftPosition(row, col);
        end.X = temp.TL.X + (fabs(temp.TR.X - temp.TL.X) / 2);
        end.Y = temp.TL.Y + (fabs(temp.TL.Y - temp.TR.Y) / 2);
    }
    else if (wall == RIGHT)
    {
        if (m_depth <= 0)
            return;
        
        m_right_light[row][col] = 3;
        
//        temp = calculateRightPosition(row, col);
        end.X = temp.TL.X + (fabs(temp.TR.X - temp.TL.X) / 2);
        end.Y = temp.TL.Y + (fabs(temp.TR.Y - temp.TL.Y) / 2);
    }
    else if (wall == FRONT)
    {
        m_front_light[row][col] = 3;
        
//        temp = calculateFrontPosition(row, col);
        end.X = temp.TL.X + (fabs(temp.TR.X - temp.TL.X) / 2);
        end.Y = temp.TL.Y + (fabs(temp.TR.Y - temp.TL.Y) / 2);
    }

    if (start.X != -1 && start.Y != -1)
        m_effect_layer.addLight(start, end, TILE_WIDTH, first, second);
    
    m_num_of_lights += 6;
    
    //drawFrontTiles(0);
    //drawLeftTiles(m_width * m_height * 4);
    //drawRightTiles((m_width * m_height * 4) + (m_height * m_depth * 4));
    //drawTopTiles((m_width * m_height * 4) + (m_height * m_depth * 4) + 
    //             (m_height * m_depth * 4));
    //drawBottomTiles((m_width * m_height * 4) + (m_height * m_depth * 4) + 
    //                (m_height * m_depth * 4) + (m_width * m_depth * 4));
}

void ksWorld::toggleLighting()
{
    m_lighting = !m_lighting;
}

void ksWorld::toggle2D(ksWorldWall wall)
{
    switch (wall)
    {
        case FRONT:
            m_front_tex     = &m_front;
            m_front_num_row = &m_height;
            m_front_num_col = &m_width;
            m_front_cur_evt = &m_front_evt;
            break;
        
        case LEFT:
            m_front_tex     = &m_left;
            m_front_num_row = &m_height;
            m_front_num_col = &m_depth;
            m_front_cur_evt = &m_left_evt;
            break;

        case RIGHT:
            m_front_tex     = &m_right;
            m_front_num_row = &m_height;
            m_front_num_col = &m_depth;
            m_front_cur_evt = &m_right_evt;
            break;

        case TOP:
            m_front_tex     = &m_top;
            m_front_num_row = &m_depth;
            m_front_num_col = &m_width;
            m_front_cur_evt = &m_top_evt;
            break;

        case BOTTOM:
            m_front_tex     = &m_bottom;
            m_front_num_row = &m_depth;
            m_front_num_col = &m_width;
            m_front_cur_evt = &m_bottom_evt;
            break;

        default:
            m_front_tex     = &m_front;
            m_front_num_row = &m_height;
            m_front_num_col = &m_width;
            m_front_cur_evt = &m_front_evt;
    }

    // Set flag for 2D perspective.
    m_2D = true;

    calculateTilePositions();
    updateTilePositions();
    updateTextureCoordinates();
}

void ksWorld::toggle3D()
{
    m_front_tex     = &m_front;
    m_front_num_row = &m_height;
    m_front_num_col = &m_width;
    m_front_cur_evt = &m_front_evt;

    // Set flag for 3D perspective.
    m_2D = false;

    calculateTilePositions();
    updateTilePositions();
    updateTextureCoordinates();
}

void ksWorld::calculateTilePositions()
{
    // Front
    m_front_pos.resize((*m_front_num_row));

    for (int row = 0; row < (*m_front_num_row); ++row)
    {
        m_front_pos[row].resize((*m_front_num_col));

//        for (int col = 0; col < (*m_front_num_col); ++col)
//            m_front_pos[row][col] = calculateFrontPosition(row, col);
    }

    // Left
    m_left_pos.resize((*m_left_num_row));

    for (int row = 0; row < (*m_left_num_row); ++row)
    {
        m_left_pos[row].resize((*m_left_num_col));

//        for (int col = 0; col < (*m_left_num_col); ++col)
//            m_left_pos[row][col] = calculateLeftPosition(row, col);
    }

    // Right
    m_right_pos.resize((*m_right_num_row));

    for (int row = 0; row < (*m_right_num_row); ++row)
    {
        m_right_pos[row].resize((*m_right_num_col));

//        for (int col = 0; col < (*m_right_num_col); ++col)
//            m_right_pos[row][col] = calculateRightPosition(row, col);
    }

    // Top
    m_top_pos.resize((*m_top_num_row));

    for (int row = 0; row < (*m_top_num_row); ++row)
    {
        m_top_pos[row].resize((*m_top_num_col));

//        for (int col = 0; col < (*m_top_num_col); ++col)
//            m_top_pos[row][col] = calculateTopPosition(row, col);
    }

    // Bottom
    m_bottom_pos.resize((*m_bottom_num_row));

    for (int row = 0; row < (*m_bottom_num_row); ++row)
    {
        m_bottom_pos[row].resize((*m_bottom_num_col));

//        for (int col = 0; col < (*m_bottom_num_col); ++col)
//            m_bottom_pos[row][col] = calculateBottomPosition(row, col);
    }
}

void ksWorld::updateTilePositions()
{
    int array_pos = 0;

    m_array.clear();
    
    if (m_2D)
        m_array.resize((*m_front_num_row) * (*m_front_num_col) * 6);
    else
        m_array.resize(((*m_front_num_row) * (*m_front_num_col) * 6) +
                       ((*m_left_num_row) * (*m_left_num_col) * 6) +
                       ((*m_right_num_row) * (*m_right_num_col) * 6) +
                       ((*m_top_num_row) * (*m_top_num_col) * 6) + 
                       ((*m_bottom_num_row) * (*m_bottom_num_col) * 6));

    // Front wall
    assignTilePositions(&m_front_pos, array_pos, (*m_front_num_row), (*m_front_num_col));

    // If in 3D perspective
    if (!m_2D)
    {
        // Left wall
        assignTilePositions(&m_left_pos, array_pos, (*m_left_num_row), (*m_left_num_col));
        
        // Right wall
        assignTilePositions(&m_right_pos, array_pos, (*m_right_num_row), (*m_right_num_col));

        // Top wall
        assignTilePositions(&m_top_pos, array_pos, (*m_top_num_row), (*m_top_num_col));

        // Bottom wall
        assignTilePositions(&m_bottom_pos, array_pos, (*m_bottom_num_row), (*m_bottom_num_col));
    }
}

void ksWorld::assignTilePositions(std::vector<std::vector<ksTile>> * wall,
                                  int & pos, int max_row, int max_col)
{
    for (int row = 0; row < max_row; ++row)
    {
        for (int col = 0; col < max_col; ++col)
        {
            m_array[pos++].position = sf::Vector2f((*wall)[row][col].TL.X, (*wall)[row][col].TL.Y);
            m_array[pos++].position = sf::Vector2f((*wall)[row][col].TR.X, (*wall)[row][col].TR.Y);
            m_array[pos++].position = sf::Vector2f((*wall)[row][col].BR.X, (*wall)[row][col].BR.Y);
            m_array[pos++].position = sf::Vector2f((*wall)[row][col].BR.X, (*wall)[row][col].BR.Y);
            m_array[pos++].position = sf::Vector2f((*wall)[row][col].BL.X, (*wall)[row][col].BL.Y);
            m_array[pos++].position = sf::Vector2f((*wall)[row][col].TL.X, (*wall)[row][col].TL.Y);
        }
    }
}

void ksWorld::updateTextureCoordinates()
{
    int array_pos = 0;

    // Front wall
    assignTextureCoordinates(m_front_tex, array_pos, (*m_front_num_row), (*m_front_num_col));

    // If in 3D perspective
    if (!m_2D)
    {
        // Left wall
        assignTextureCoordinates(m_left_tex, array_pos, (*m_left_num_row), (*m_left_num_col));
        
        // Right wall
        assignTextureCoordinates(m_right_tex, array_pos, (*m_right_num_row), (*m_right_num_col));

        // Top wall
        assignTextureCoordinates(m_top_tex, array_pos, (*m_top_num_row), (*m_top_num_col));

        // Bottom wall
        assignTextureCoordinates(m_bottom_tex, array_pos, (*m_bottom_num_row), (*m_bottom_num_col));
    }
}

void ksWorld::assignTextureCoordinates(std::vector<std::vector<ksTile>> * wall,
                                       int & pos, int max_row, int max_col)
{
    for (int row = 0; row < max_row; ++row)
    {
        for (int col = 0; col < max_col; ++col)
        {
            m_array[pos++].texCoords = sf::Vector2f((*wall)[row][col].TL.X, (*wall)[row][col].TL.Y);
            m_array[pos++].texCoords = sf::Vector2f((*wall)[row][col].TR.X, (*wall)[row][col].TR.Y);
            m_array[pos++].texCoords = sf::Vector2f((*wall)[row][col].BR.X, (*wall)[row][col].BR.Y);
            m_array[pos++].texCoords = sf::Vector2f((*wall)[row][col].BR.X, (*wall)[row][col].BR.Y);
            m_array[pos++].texCoords = sf::Vector2f((*wall)[row][col].BL.X, (*wall)[row][col].BL.Y);
            m_array[pos++].texCoords = sf::Vector2f((*wall)[row][col].TL.X, (*wall)[row][col].TL.Y);
        }
    }
}

/********************************************************
*   transform3D
*
*   Returns the transformed (x, y, z) position to a
*   2D drawable coordinate.
********************************************************/
sf::Vector2f ksWorld::transform3D(double x, double y, double z)
{
    int pos_x = x * m_world_width_px;
    int pos_y = y * m_world_height_px;
    int pos_z = z * m_world_depth_px;

    sf::Vector2f position;

    position.x = ((m_camera_z * (pos_x - m_camera_x)) / (m_camera_z + pos_z)) + m_camera_x;
    position.y = ((m_camera_z * (pos_y - m_camera_y)) / (m_camera_z + pos_z)) + m_camera_y;
    
    return position;
}

/********************************************************
*   transform3D
*
*   Returns the transformed (x, y, z) position to a
*   2D drawable coordinate.
********************************************************/
sf::Vector2f ksWorld::transform3D(sf::Vector3f position)
{
    sf::Vector2f screen_position;
    
    position.x = ((m_camera_z * (position.x - m_camera_x)) / (m_camera_z + position.z)) +
        m_camera_x;
    position.y = ((m_camera_z * (position.y - m_camera_y)) / (m_camera_z + position.z)) +
        m_camera_y;
    
    return screen_position;
}

/********************************************************
*   transform3DWithPixelValue
*
*   Returns the transformed (x, y, z) position to a
*   2D drawable coordinate.
********************************************************/
sf::Vector2f ksWorld::transform3DWithPixelValue(int x, int y, int z)
{
    sf::Vector2f position;

    position.x = ((m_camera_z * (x - m_camera_x)) / (m_camera_z + z)) +
        m_camera_x;
    position.y = ((m_camera_z * (y - m_camera_y)) / (m_camera_z + z)) +
        m_camera_y;

    return position;
}

/********************************************************
*   render3DWorld
*
*   Renders the 3D world, based on the transformed
*   coordinates of a read in map.
********************************************************/
void ksWorld::transform3DWorld(int world_width_px, int world_height_px, 
                               int world_depth_px, int map_row_num, 
                               int map_col_num, int map_depth_num)
{
    // Set world data, for use in transformations
    // and accessor methods.
    m_world_width_px    = world_width_px;
    m_world_height_px   = world_height_px;
    m_world_depth_px    = world_depth_px;
    m_map_row_num       = map_row_num;
    m_map_col_num       = map_col_num;
    m_map_depth_num     = map_depth_num;

    int index = 0;
    m_array.clear();
    m_array.resize((map_row_num * map_col_num * 6) +
                   (map_col_num * map_depth_num * 12) +
                   (map_row_num * map_depth_num * 12));

    // Transform all the world walls
    transformFrontWall(index, map_row_num, map_col_num);
    transformTopWall(index, map_col_num, map_depth_num);
    transformBottomWall(index, map_col_num, map_depth_num);
    transformLeftWall(index, map_row_num, map_depth_num);
    transformRightWall(index, map_row_num, map_depth_num);
}

/********************************************************
*   transform2DWorld
*
*   Transforms the world into a flat 2D plain of the
*   front wall.
********************************************************/
void ksWorld::transform2DWorld()
{
    transform3DWorld(m_world_width_px, m_world_height_px, 1, m_map_row_num, m_map_col_num, m_map_depth_num);
}

void ksWorld::applyTextureCoordinates()
{
    int index = 0;
    m_array.clear();
    m_array.resize((m_map_row_num * m_map_col_num * 6) +
                   (m_map_col_num * m_map_depth_num * 12) +
                   (m_map_row_num * m_map_depth_num * 12));

    // 
    for (int row = 0; row < m_map_row_num; ++row)
    {
        for (int col = 0; col < m_map_col_num; ++col)
        {
            m_array[index].texCoords     = sf::Vector2f(m_front[row][col].TL.X,
                                                        m_front[row][col].TL.Y);
            m_array[index + 1].texCoords = sf::Vector2f(m_front[row][col].TR.X,
                                                        m_front[row][col].TR.Y);
            m_array[index + 2].texCoords = sf::Vector2f(m_front[row][col].BR.X,
                                                        m_front[row][col].BR.Y);
            m_array[index + 3].texCoords = sf::Vector2f(m_front[row][col].BL.X,
                                                        m_front[row][col].BL.Y);
            m_array[index + 4].texCoords = sf::Vector2f(m_front[row][col].TL.X,
                                                        m_front[row][col].TL.Y);
            m_array[index + 5].texCoords = sf::Vector2f(m_front[row][col].BR.X,
                                                        m_front[row][col].BR.Y);
        }
    }
}

/********************************************************
*   transformFrontWall
*
*   Renders the front wall of the 3D world, based on the 
*   coordinates of: map/_front.ks
********************************************************/
void ksWorld::transformFrontWall(int & index, int map_row_num, int map_col_num)
{
    for (int row = 0; row < map_row_num; ++row)
    {
        for (int col = 0; col < map_col_num; ++col)
        {
            m_array[index].position      = transform3D((double) col / map_col_num,
                                                      (double) row / map_row_num, 1.0);
            m_array[index].texCoords     = sf::Vector2f(m_front[row][col].TL.X,
                                                        m_front[row][col].TL.Y);

            m_array[index + 1].position  = transform3D((double) (col + 1) / map_col_num,
                                                      (double) row / map_row_num, 1.0);
            m_array[index + 1].texCoords = sf::Vector2f(m_front[row][col].TR.X,
                                                        m_front[row][col].TR.Y);

            m_array[index + 2].position  = transform3D((double) (col + 1) / map_col_num,
                                                      (double) (row + 1) / map_row_num, 1.0);
            m_array[index + 2].texCoords = sf::Vector2f(m_front[row][col].BR.X,
                                                        m_front[row][col].BR.Y);

            m_array[index + 3].position  = transform3D((double) col / map_col_num,
                                                      (double) (row + 1) / map_row_num, 1.0);
            m_array[index + 3].texCoords = sf::Vector2f(m_front[row][col].BL.X,
                                                        m_front[row][col].BR.Y);

            m_array[index + 4] = m_array[index];
            m_array[index + 5] = m_array[index + 2];
            
            index += 6;
        }
    }
}

/********************************************************
*   transformTopWall
*
*   Renders the top wall of the 3D world, based on the 
*   coordinates of: map/_top.ks
********************************************************/
void ksWorld::transformTopWall(int & index, int map_col_num, int map_depth_num)
{
    for (int depth = 0; depth < map_depth_num; ++depth)
    {
        for (int col = 0; col < map_col_num; ++col)
        {
            m_array[index].position      = transform3D((double) col / map_col_num, 0.0,
                                                      (double) depth / map_depth_num);
            m_array[index].texCoords     = sf::Vector2f(m_top[depth][col].TL.X,
                                                        m_top[depth][col].TL.Y);

            m_array[index + 1].position  = transform3D((double) (col + 1) / map_col_num, 0.0,
                                                      (double) depth / map_depth_num);
            m_array[index + 1].texCoords = sf::Vector2f(m_top[depth][col].TR.X,
                                                        m_top[depth][col].TR.Y);

            m_array[index + 2].position  = transform3D((double) (col + 1) / map_col_num, 0.0,
                                                      (double) (depth + 1) / map_depth_num);
            m_array[index + 2].texCoords = sf::Vector2f(m_top[depth][col].BR.X,
                                                        m_top[depth][col].BR.Y);

            m_array[index + 3].position  = transform3D((double) col / map_col_num, 0.0,
                                                      (double) (depth + 1) / map_depth_num);
            m_array[index + 3].texCoords = sf::Vector2f(m_top[depth][col].BL.X,
                                                        m_top[depth][col].BL.Y);

            m_array[index + 4] = m_array[index];
            m_array[index + 5] = m_array[index + 2];

            index += 6;
        }
    }
}

/********************************************************
*   transformBottomWall
*
*   Renders the bottom wall of the 3D world, based on the 
*   coordinates of: map/_bottom.ks
********************************************************/
void ksWorld::transformBottomWall(int & index, int map_col_num, int map_depth_num)
{
    for (int depth = 0; depth < map_depth_num; ++depth)
    {
        for (int col = 0; col < map_col_num; ++col)
        {
            m_array[index].position = transform3D((double) col / map_col_num, 1.0,
                                                  (double) depth / map_depth_num);
            m_array[index].texCoords = sf::Vector2f(m_bottom[depth][col].TL.X,
                                                    m_bottom[depth][col].TL.Y);

            m_array[index + 1].position = transform3D((double) (col + 1) / map_col_num, 1.0,
                                                      (double) depth / map_depth_num);
            m_array[index + 1].texCoords = sf::Vector2f(m_bottom[depth][col].TR.X,
                                                        m_bottom[depth][col].TR.Y);

            m_array[index + 2].position = transform3D((double) (col + 1) / map_col_num, 1.0,
                                                      (double) (depth + 1) / map_depth_num);
            m_array[index + 2].texCoords = sf::Vector2f(m_bottom[depth][col].BR.X,
                                                        m_bottom[depth][col].BR.Y);

            m_array[index + 3].position = transform3D((double) col / map_col_num, 1.0,
                                                      (double) (depth + 1) / map_depth_num);
            m_array[index + 3].texCoords = sf::Vector2f(m_bottom[depth][col].BL.X,
                                                        m_bottom[depth][col].BL.Y);

            m_array[index + 4] = m_array[index];
            m_array[index + 5] = m_array[index + 2];

            index += 6;
        }
    }
}

/********************************************************
*   transformLeftWall
*
*   Renders the left wall of the 3D world, based on the 
*   coordinates of: map/_left.ks
********************************************************/
void ksWorld::transformLeftWall(int & index, int map_row_num, int map_depth_num)
{
    for (int row = 0; row < map_row_num; ++row)
    {
        for (int depth = 0; depth < map_depth_num; ++depth)
        {
            m_array[index].position = transform3D(0.0, (double) row / map_row_num,
                                                  (double) depth / map_depth_num);
            m_array[index].texCoords = sf::Vector2f(m_left[row][depth].TL.X,
                                                    m_left[row][depth].TL.Y);

            m_array[index + 1].position = transform3D(0.0, (double) row / map_row_num,
                                                      (double) (depth + 1) / map_depth_num);
            m_array[index + 1].texCoords = sf::Vector2f(m_left[row][depth].TR.X,
                                                        m_left[row][depth].TR.Y);

            m_array[index + 2].position = transform3D(0.0, (double) (row + 1) / map_row_num,
                                                      (double) (depth + 1) / map_depth_num);
            m_array[index + 2].texCoords = sf::Vector2f(m_left[row][depth].BR.X,
                                                        m_left[row][depth].BR.Y);

            m_array[index + 3].position = transform3D(0.0, (double) (row + 1) / map_row_num,
                                                      (double) depth / map_depth_num);
            m_array[index + 3].texCoords = sf::Vector2f(m_left[row][depth].BL.X,
                                                        m_left[row][depth].BL.Y);

            m_array[index + 4] = m_array[index];
            m_array[index + 5] = m_array[index + 2];

            index += 6;
        }
    }
}

/********************************************************
*   transformRightWall
*
*   Renders the right wall of the 3D world, based on the 
*   coordinates of: map/_right.ks
********************************************************/
void ksWorld::transformRightWall(int & index, int map_row_num, int map_depth_num)
{
    for (int row = 0; row < map_row_num; ++row)
    {
        for (int depth = 0; depth < map_depth_num; ++depth)
        {
            m_array[index].position = transform3D(1.0, (double) row / map_row_num,
                                                  (double) depth / map_depth_num);
            m_array[index].texCoords = sf::Vector2f(m_right[row][depth].TL.X,
                                                    m_right[row][depth].TL.Y);

            m_array[index + 1].position = transform3D(1.0, (double) row / map_row_num,
                                                      (double) (depth + 1) / map_depth_num);
            m_array[index + 1].texCoords = sf::Vector2f(m_right[row][depth].TR.X,
                                                        m_right[row][depth].TR.Y);
    
            m_array[index + 2].position = transform3D(1.0, (double) (row + 1) / map_row_num,
                                                      (double) (depth + 1) / map_depth_num);
            m_array[index + 2].texCoords = sf::Vector2f(m_right[row][depth].BR.X,
                                                        m_right[row][depth].BR.Y);

            m_array[index + 3].position = transform3D(1.0, (double) (row + 1) / map_row_num,
                                                      (double) depth / map_depth_num);
            m_array[index + 3].texCoords = sf::Vector2f(m_right[row][depth].BL.X,
                                                        m_right[row][depth].BL.Y);

            m_array[index + 4] = m_array[index];
            m_array[index + 5] = m_array[index + 2];

            index += 6;
        }
    }
}

/********************************************************
*   moveCamera
*
*   Move the camera's perspective by the passed
*   (x, y, z) values.
********************************************************/
void ksWorld::moveCamera(int x, int y, int z)
{
    m_camera_x += x;
    m_camera_y += y;
    //m_camera_z += z;
    std::cout << "Map depth: " << m_map_depth_num << '\n';
    m_map_depth_num -= z;
    m_camera_z += (z * 32);
    std::cout << "New Map depth: " << m_map_depth_num << '\n';
    
    transform3DWorld(m_world_width_px, m_world_height_px, m_world_depth_px,
        m_map_row_num, m_map_col_num, m_map_depth_num);
}

/********************************************************
*   resizeWorld
*
*   Resize the world to the new screen width and height.
********************************************************/
void ksWorld::resizeWorld(int screen_width, int screen_height)
{
    int old_proportion = m_world_width_px * m_world_height_px;
    int new_proportion = screen_width / screen_height;
    
    int new_depth = (old_proportion / new_proportion) * m_world_depth_px;
    
    load(screen_width, screen_height, new_depth, m_map_row_num, m_map_col_num, m_map_depth_num, m_world_name);
}

/********************************************************
*   getTilePosition
*
*   Returns the position of a tile in the 3D perspective
*   relative to the passed width, height, and depth.
********************************************************/
ksTile ksWorld::getTilePosition(ksWorldWall wall, int row, int col, int width, int height)
{
    ksTile tile;
    
    switch (wall)
    {
        case FRONT:
            tile.TL = m_front_pos[row][col].TL;
            tile.TR = m_front_pos[row][col + width - 1].TR;
            tile.BR = m_front_pos[row + height - 1][col + width - 1].BR;
            tile.BL = m_front_pos[row + height - 1][col].BL;
            break;

        case LEFT:
            tile.TL = m_left_pos[row][col].TL;
            tile.TR = m_left_pos[row][col + width - 1].TR;
            tile.BR = m_left_pos[row + height - 1][col + width - 1].BR;
            tile.BL = m_left_pos[row + height - 1][col].BL;
            break;

        case RIGHT:
            tile.TL = m_right_pos[row][col].TL;
            tile.TR = m_right_pos[row][col + width - 1].TR;
            tile.BR = m_right_pos[row + height - 1][col + width - 1].BR;
            tile.BL = m_right_pos[row + height - 1][col].BL;
            break;

        case TOP:
            tile.TL = m_top_pos[row][col].TL;
            tile.TR = m_top_pos[row][col + width - 1].TR;
            tile.BR = m_top_pos[row + height - 1][col + width - 1].BR;
            tile.BL = m_top_pos[row + height - 1][col].BL;
            break;
        
        case BOTTOM:
            tile.BL   = m_bottom_pos[row][col].BL;
            tile.BR   = m_bottom_pos[row][col + width - 1].BR;
            tile.TL.X = tile.BL.X;
            tile.TL.Y = m_right_pos[m_height - height][row].TR.Y;
            tile.TR.X = tile.BR.X;
            tile.TR.Y = tile.TL.Y;
            break;

        default:
            tile.TL = m_front_pos[row][col].TL;
            tile.TR = m_front_pos[row][col + width - 1].TR;
            tile.BR = m_front_pos[row + height - 1][col + width - 1].BR;
            tile.BL = m_front_pos[row + height - 1][col].BL;
    }

    return tile;
}

int ksWorld::getLightIntensity(ksWorldWall wall, int row, int col)
{
    if (wall == FRONT)
        return m_front_light[row][col];
    else if (wall == BOTTOM)
        return m_bottom_light[row][col];
    else if (wall == LEFT)
        return m_left_light[row][col];
    else if (wall == RIGHT)
        return m_right_light[row][col];
    else
        return m_top_light[row][col];
}

int ksWorld::getTileEvent(ksWorldWall wall, int row, int col)
{
    int evt;

    switch (wall)
    {
        case FRONT:
            evt = (*m_front_cur_evt)[row][col];
            break;

        case LEFT:
            evt = (*m_left_cur_evt)[row][col];
            break;

        case RIGHT:
            evt = (*m_right_cur_evt)[row][col];
            break;

        case TOP:
            evt = (*m_top_cur_evt)[row][col];
            break;

        case BOTTOM:
            evt = (*m_bottom_cur_evt)[row][col];
            break;

        default:
            evt = (*m_front_cur_evt)[row][col];
    }

    return evt;
}

int ksWorld::getWallMaxRow(ksWorldWall wall)
{
    if (wall == BOTTOM || wall == TOP)
        return m_depth;
    else if (wall == FRONT || wall == LEFT || wall == RIGHT)
        return m_height;
    
    return 0;
}

int ksWorld::getWallMaxCol(ksWorldWall wall)
{
    if (wall == BOTTOM || wall == TOP)
        return m_width;
    else if (wall == LEFT || wall == RIGHT)
        return m_depth;
    else if (wall == FRONT)
        return m_width;

    return 0;
}

int ksWorld::getMapCol()
{
    return m_map_col_num;
}

int ksWorld::getMapRow()
{
    return m_map_row_num;
}

int ksWorld::getMapDepth()
{
    return m_map_depth_num;
}

void ksWorld::setTilesheet(std::string tilesheet)
{
    if (!m_texture.loadFromFile(tilesheet))
        std::cout << "ERROR (ksWorld): Couldn't load tilesheet\n";
}

/********************************************************
*   loadWorldDemo
*
*   Fill the world with a demo map, rather than using
*   File IO to read in the tiles on the walls.
*
*   This is used for demonstrating the engine on
*   platforms that don't currently have the same File IO 
*   support as the desktop platforms like the current 
*   SFML build on Android and iOS.
********************************************************/
void ksWorld::loadWorldDemo()
{
    // Set the demo world to
    // this particular size.
    m_width  = 8;
    m_height = 4;
    m_depth  = 8;
    
    m_world_width_px  = 800;
    m_world_height_px = 400;
    m_world_depth_px  = 800;
    
    m_map_row_num   = 4;
    m_map_col_num   = 8;
    m_map_depth_num = 8;
    
    // Front wall
    // 09 09 09 09 09 09 09 09
    // 09 09 09 09 09 09 09 09
    // 10 10 10 10 10 10 10 10
    // 33 34 34 34 34 34 34 35
    int front[4][8] = {{9, 9, 9, 9, 9, 9, 9, 9},
                       {9, 9, 9, 9, 9, 9, 9, 9},
                       {10, 10, 10, 10, 10, 10, 10, 10},
                       {33, 34, 34, 34, 34, 34, 34, 35}};
    
    // Bottom wall
    // 10 10 10 10 10 10 10 10
    // 10 10 10 10 10 10 10 10
    // 10 10 10 10 10 10 10 10
    // 10 10 10 10 10 10 10 10
    // 10 10 10 10 10 10 10 10
    // 10 10 10 10 10 10 10 10
    // 10 10 10 10 10 10 10 10
    // 10 10 10 10 10 10 10 10
    int bottom[8][8] = {{10, 10, 10, 10, 10, 10, 10, 10},
                        {10, 10, 10, 10, 10, 10, 10, 10},
                        {10, 10, 10, 10, 10, 10, 10, 10},
                        {10, 10, 10, 10, 10, 10, 10, 10},
                        {10, 10, 10, 10, 10, 10, 10, 10},
                        {10, 10, 10, 10, 10, 10, 10, 10},
                        {10, 10, 10, 10, 10, 10, 10, 10},
                        {10, 10, 10, 10, 10, 10, 10, 10}};
                        
    // Top wall
    // 09 09 09 09 09 09 09 09
    // 09 09 09 09 09 09 09 09
    // 09 09 09 09 09 09 09 09
    // 09 09 09 09 09 09 09 09
    // 09 09 09 09 09 09 09 09
    // 09 09 09 09 09 09 09 09
    // 09 09 09 09 09 09 09 09
    // 09 09 09 09 09 09 09 09
    int top[8][8] = {{9, 9, 9, 9, 9, 9, 9, 9},
                     {9, 9, 9, 9, 9, 9, 9, 9},
                     {9, 9, 9, 9, 9, 9, 9, 9},
                     {9, 9, 9, 9, 9, 9, 9, 9},
                     {9, 9, 9, 9, 9, 9, 9, 9},
                     {9, 9, 9, 9, 9, 9, 9, 9},
                     {9, 9, 9, 9, 9, 9, 9, 9},
                     {9, 9, 9, 9, 9, 9, 9, 9}};
                        
    // Left wall
    // 09 09 09 09 09 09 09 09
    // 09 09 09 09 09 09 09 09
    // 10 10 10 10 10 10 10 10
    // 33 34 34 34 34 34 34 34
    int left[4][8] = {{9, 9, 9, 9, 9, 9, 9, 9},
                      {9, 9, 9, 9, 9, 9, 9, 9},
                      {10, 10, 10, 10, 10, 10, 10, 10},
                      {33, 34, 34, 34, 34, 34, 34, 34}};
                      
    // Right wall
    // 09 09 09 09 09 09 09 09
    // 09 09 09 09 09 09 09 09
    // 10 10 10 10 10 10 10 10
    // 33 34 34 34 34 34 34 34
    int right[4][8] = {{9, 9, 9, 9, 9, 9, 9, 9},
                       {9, 9, 9, 9, 9, 9, 9, 9},
                       {10, 10, 10, 10, 10, 10, 10, 10},
                       {33, 34, 34, 34, 34, 34, 34, 34}};
      
    // Front Wall
    m_front.resize(m_map_row_num);
                     
    for (int row = 0; row < m_map_row_num; ++row)
    {
        m_front[row].resize(m_map_col_num);
        
        for (int col = 0; col < m_map_col_num; ++col)
        {
            int tile_type = front[row][col];
            int type_x = ((tile_type - (TILE_PER_LINE * (tile_type / TILE_PER_LINE)))
                            * TILE_WIDTH) / 2;
            int type_y = ((tile_type / TILE_PER_LINE) * TILE_HEIGHT) / 2;
            int type_w = TILE_WIDTH / 2;
            int type_h = TILE_HEIGHT / 2;
            
            m_front[row][col].TL = ksVector2D(type_x, type_y);
            m_front[row][col].TR = ksVector2D(type_x + type_w, type_y);
            m_front[row][col].BR = ksVector2D(type_x + type_w, type_y + type_h);
            m_front[row][col].BL = ksVector2D(type_x, type_y + type_h);
        }
    }
    
    // Bottom Wall
    m_bottom.resize(m_map_depth_num);
                     
    for (int row = 0; row < m_map_depth_num; ++row)
    {
        m_bottom[row].resize(m_map_col_num);
        
        for (int col = 0; col < m_map_col_num; ++col)
        {
            int tile_type = bottom[row][col];
            int type_x = ((tile_type - (TILE_PER_LINE * (tile_type / TILE_PER_LINE)))
                            * TILE_WIDTH) / 2;
            int type_y = ((tile_type / TILE_PER_LINE) * TILE_HEIGHT) / 2;
            int type_w = TILE_WIDTH / 2;
            int type_h = TILE_HEIGHT / 2;
            
            m_bottom[row][col].TL = ksVector2D(type_x, type_y);
            m_bottom[row][col].TR = ksVector2D(type_x + type_w, type_y);
            m_bottom[row][col].BR = ksVector2D(type_x + type_w, type_y + type_h);
            m_bottom[row][col].BL = ksVector2D(type_x, type_y + type_h);
        }
    }
    
    // Top Wall
    m_top.resize(m_map_depth_num);
                     
    for (int row = 0; row < m_map_depth_num; ++row)
    {
        m_top[row].resize(m_map_col_num);
        
        for (int col = 0; col < m_map_col_num; ++col)
        {
            int tile_type = top[row][col];
            int type_x = ((tile_type - (TILE_PER_LINE * (tile_type / TILE_PER_LINE)))
                            * TILE_WIDTH) / 2;
            int type_y = ((tile_type / TILE_PER_LINE) * TILE_HEIGHT) / 2;
            int type_w = TILE_WIDTH / 2;
            int type_h = TILE_HEIGHT / 2;
            
            m_top[row][col].TL = ksVector2D(type_x, type_y);
            m_top[row][col].TR = ksVector2D(type_x + type_w, type_y);
            m_top[row][col].BR = ksVector2D(type_x + type_w, type_y + type_h);
            m_top[row][col].BL = ksVector2D(type_x, type_y + type_h);
        }
    }
    
    // Left Wall
    m_left.resize(m_map_row_num);
                     
    for (int row = 0; row < m_map_row_num; ++row)
    {
        m_left[row].resize(m_map_depth_num);
        
        for (int col = 0; col < m_map_depth_num; ++col)
        {
            int tile_type = left[row][col];
            int type_x = ((tile_type - (TILE_PER_LINE * (tile_type / TILE_PER_LINE)))
                            * TILE_WIDTH) / 2;
            int type_y = ((tile_type / TILE_PER_LINE) * TILE_HEIGHT) / 2;
            int type_w = TILE_WIDTH / 2;
            int type_h = TILE_HEIGHT / 2;
            
            m_left[row][col].TL = ksVector2D(type_x, type_y);
            m_left[row][col].TR = ksVector2D(type_x + type_w, type_y);
            m_left[row][col].BR = ksVector2D(type_x + type_w, type_y + type_h);
            m_left[row][col].BL = ksVector2D(type_x, type_y + type_h);
        }
    }
    
    // Right Wall
    m_right.resize(m_map_row_num);
                     
    for (int row = 0; row < m_map_row_num; ++row)
    {
        m_right[row].resize(m_map_depth_num);
        
        for (int col = 0; col < m_map_depth_num; ++col)
        {
            int tile_type = right[row][col];
            int type_x = ((tile_type - (TILE_PER_LINE * (tile_type / TILE_PER_LINE)))
                            * TILE_WIDTH) / 2;
            int type_y = ((tile_type / TILE_PER_LINE) * TILE_HEIGHT) / 2;
            int type_w = TILE_WIDTH / 2;
            int type_h = TILE_HEIGHT / 2;
            
            m_right[row][col].TL = ksVector2D(type_x, type_y);
            m_right[row][col].TR = ksVector2D(type_x + type_w, type_y);
            m_right[row][col].BR = ksVector2D(type_x + type_w, type_y + type_h);
            m_right[row][col].BL = ksVector2D(type_x, type_y + type_h);
        }
    }
    
    // Update the camera position to the
    // demo world's data.
    m_camera_x        = m_world_width_px / 2;
    m_camera_y        = m_world_height_px / 2;
    m_camera_z        = m_world_depth_px;
    
    // Clear any existing data from the vertex array.
    m_array.clear();

    // Set the primitive type of the vertex array
    m_array.setPrimitiveType(sf::Triangles);

    // Calculate the coordinates for the 3D world.
    transform3DWorld(m_world_width_px, m_world_height_px, m_world_depth_px,
                     m_map_row_num, m_map_col_num, m_map_depth_num);
}