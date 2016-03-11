/********************************************************
* Class:            ksWorld
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksWorld.cpp
********************************************************/

#include "ksWorld.h"
#include <iostream>

/********************************************************
*   ksWorld
*
*   Initialize the world without any map loaded.
********************************************************/
ksWorld::ksWorld(std::string tilesheet)
    : m_width(0), m_height(0), m_depth(0), m_inner_x(0), m_inner_y(0), 
      m_num_of_lights(0), m_tilesheet(tilesheet), m_lighting(true), m_2D(false)
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
      m_tilesheet(tilesheet), m_lighting(true)
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

    load(m_width, m_height, m_depth);
}

/********************************************************
*   load
*
*   Load a map with (width x height x depth) values.
********************************************************/
void ksWorld::load(int width, int height, int depth, std::string name)
{
    m_width  = width  > 0 ? width  : 1;
    m_height = height > 0 ? height : 1;
    m_depth  = depth  > 0 ? depth  : 0;

    m_array.clear();

    if (name != "")
        readTiles(name);

    m_array.setPrimitiveType(sf::Triangles);

    m_outer_width_px = ((m_depth * 2) + m_width) * TILE_WIDTH;
    m_outer_height_px = ((m_depth * 2) + m_height) * TILE_HEIGHT;

    m_inner_x = (m_outer_width_px / 2) - ((m_width * TILE_WIDTH) / 2);
    m_inner_y = (m_outer_height_px / 2) - ((m_height * TILE_HEIGHT) / 2);

    calculateTilePositions();
    updateTilePositions();
    updateTextureCoordinates();
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
*   calculateLeftPosition
*
*   Calculate a tile's 4 points on the left wall.
********************************************************/
ksTile ksWorld::calculateLeftPosition(int row, int col)
{
    ksTile tile;
    ksTile front = calculateFrontPosition(row, 0);

    double row_tl_y = (m_outer_height_px / m_height) * row;
    double row_bl_y = (m_outer_height_px / m_height) * (row + 1);

    tile.TL.X = (col * TILE_WIDTH);
    tile.TR.X = ((col + 1) * TILE_WIDTH);
    tile.BL.X = tile.TL.X;
    tile.BR.X = tile.TR.X;

    tile.TL.Y = row_tl_y + (((front.TL.Y - row_tl_y) / m_depth) * col);
    tile.TR.Y = row_tl_y + (((front.TL.Y - row_tl_y) / m_depth) * (col + 1));
    tile.BL.Y = row_bl_y + (((front.BL.Y - row_bl_y) / m_depth) * col);
    tile.BR.Y = row_bl_y + (((front.BL.Y - row_bl_y) / m_depth) * (col + 1));

    return tile;
}

/********************************************************
*   calculateRightPosition
*
*   Calculate a tile's 4 points on the right wall.
********************************************************/
ksTile ksWorld::calculateRightPosition(int row, int col)
{
    ksTile tile;
    ksTile front = calculateFrontPosition(row, m_width - 1);

    double row_tr_y = (m_outer_height_px / m_height) * row;
    double row_br_y = (m_outer_height_px / m_height) * (row + 1);

    tile.TL.X = m_inner_x + (m_width * TILE_WIDTH) + (col * TILE_WIDTH);
    tile.TR.X = m_inner_x + (m_width * TILE_WIDTH) + ((col + 1) * TILE_WIDTH);
    tile.BL.X = tile.TL.X;
    tile.BR.X = tile.TR.X;

    tile.TL.Y = row_tr_y + (((front.TR.Y - row_tr_y) / m_depth) * (m_depth - col));
    tile.TR.Y = row_tr_y + (((front.TR.Y - row_tr_y) / m_depth) * ((m_depth - col) - 1));
    tile.BL.Y = row_br_y + (((front.BR.Y - row_br_y) / m_depth) * (m_depth - col));
    tile.BR.Y = row_br_y + (((front.BR.Y - row_br_y) / m_depth) * ((m_depth - col) - 1));

    return tile;
}

/********************************************************
*   calculateTopPosition
*
*   Calculate a tile's 4 points on the top wall.
********************************************************/
ksTile ksWorld::calculateTopPosition(int row, int col)
{
    ksTile tile;
    ksTile front = calculateFrontPosition(0, col);

    double col_tl_x = (m_outer_width_px / m_width) * col;
    double col_tr_x = (m_outer_width_px / m_width) * (col + 1);

    tile.TL.Y = (row * TILE_HEIGHT);
    tile.BL.Y = ((row + 1) * TILE_HEIGHT);
    tile.TR.Y = tile.TL.Y;
    tile.BR.Y = tile.BL.Y;

    tile.TL.X = col_tl_x + (((front.TL.X - col_tl_x) / m_depth) * row);
    tile.BL.X = col_tl_x + (((front.TL.X - col_tl_x) / m_depth) * (row + 1));
    tile.TR.X = col_tr_x + (((front.TR.X - col_tr_x) / m_depth) * row);
    tile.BR.X = col_tr_x + (((front.TR.X - col_tr_x) / m_depth) * (row + 1));

    return tile;
}

/********************************************************
*   calculateBottomPosition
*
*   Calculate a tile's 4 points on the bottom wall.
********************************************************/
ksTile ksWorld::calculateBottomPosition(int row, int col)
{
    ksTile tile;
    ksTile front = calculateFrontPosition(m_height - 1, col);

    double col_bl_x = (m_outer_width_px / m_width) * col;
    double col_br_x = (m_outer_width_px / m_width) * (col + 1);

    tile.TL.Y = m_inner_y + (m_height * TILE_HEIGHT) + (row * TILE_HEIGHT);
    tile.BL.Y = m_inner_y + (m_height * TILE_HEIGHT) + ((row + 1) * TILE_HEIGHT);
    tile.TR.Y = tile.TL.Y;
    tile.BR.Y = tile.BL.Y;

    tile.TL.X = col_bl_x + (((front.BL.X - col_bl_x) / m_depth) * (m_depth - row));
    tile.BL.X = col_bl_x + (((front.BL.X - col_bl_x) / m_depth) * ((m_depth - row) - 1));
    tile.TR.X = col_br_x + (((front.BR.X - col_br_x) / m_depth) * (m_depth - row));
    tile.BR.X = col_br_x + (((front.BR.X - col_br_x) / m_depth) * ((m_depth - row) - 1));

    return tile;
}

/********************************************************
*   calculateFrontPosition
*
*   Calculate a tile's 4 points on the front wall.
********************************************************/
ksTile ksWorld::calculateFrontPosition(int row, int col)
{
    ksTile tile;

    tile.TL.X = (col * TILE_WIDTH) + m_inner_x;
    tile.TL.Y = (row * TILE_HEIGHT) + m_inner_y;
    
    tile.TR.X = ((col + 1) * TILE_WIDTH) + m_inner_x;
    tile.TR.Y = tile.TL.Y;

    tile.BL.X = tile.TL.X;
    tile.BL.Y = ((row + 1) * TILE_HEIGHT) + m_inner_x;

    tile.BR.X = tile.TR.X;
    tile.BR.Y = tile.BL.Y;

    return tile;
}

ksPathNode ksWorld::calculateFrontNode(int screen_x, int screen_y)
{
    ksPathNode node;
    ksTile     position;

    node.row = (screen_y - m_inner_y) / TILE_HEIGHT;
    node.col = (screen_x - m_inner_x) / TILE_WIDTH;

    position = calculateFrontPosition(node.row, node.col);

    node.TL  = position.TL;
    node.TR  = position.TR;
    node.BL  = position.BL;
    node.BR  = position.BR;

    std::cout << "Position: " << node.row << ", " << node.col << "\n";

    return node;
}

ksPathNode ksWorld::calculateBottomNode(int screen_x, int screen_y)
{
    ksPathNode node;
    ksTile     position;

    node.row = ((screen_y - m_inner_y - (m_height * TILE_HEIGHT)) / TILE_HEIGHT) - 1;
    node.col = (screen_x * m_width) / m_outer_width_px;

    position = calculateBottomPosition(node.row, node.col);

    node.TL  = position.TL;
    node.TR  = position.TR;
    node.BL  = position.BL;
    node.BR  = position.BR;

    std::cout << "Position: " << node.row << ", " << node.col << "\n";
    
    return node;
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
        temp = calculateTopPosition(row, col);

        end.X = temp.TL.X + (fabs(temp.TR.X - temp.TL.X) / 2);
        end.Y = temp.TL.Y + (fabs(temp.TR.Y - temp.TL.Y) / 2);
    }
    else if (wall == BOTTOM)
    {
        if (m_depth <= 0)
            return;
        
        m_bottom_light[row][col] = 3;
        
        temp = calculateBottomPosition(row, col);
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

        temp = calculateLeftPosition(row, col);
        end.X = temp.TL.X + (fabs(temp.TR.X - temp.TL.X) / 2);
        end.Y = temp.TL.Y + (fabs(temp.TL.Y - temp.TR.Y) / 2);
    }
    else if (wall == RIGHT)
    {
        if (m_depth <= 0)
            return;
        
        m_right_light[row][col] = 3;
        
        temp = calculateRightPosition(row, col);
        end.X = temp.TL.X + (fabs(temp.TR.X - temp.TL.X) / 2);
        end.Y = temp.TL.Y + (fabs(temp.TR.Y - temp.TL.Y) / 2);
    }
    else if (wall == FRONT)
    {
        m_front_light[row][col] = 3;
        
        temp = calculateFrontPosition(row, col);
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

void ksWorld::rotateLeft()
{
    m_front_tex      = &m_left;
    m_front_num_row  = &m_height;
    m_front_num_col  = &m_depth;

    m_left_tex       = &m_back;
    m_left_num_row   = &m_height;
    m_left_num_col   = &m_width;

    m_right_tex      = &m_front;
    m_right_num_row  = &m_height;
    m_right_num_col  = &m_width;

    m_top_tex        = &m_top;
    m_top_num_row    = &m_depth;
    m_top_num_col    = &m_width;

    m_bottom_tex     = &m_bottom;
    m_bottom_num_row = &m_depth;
    m_bottom_num_col = &m_width;

    m_2D = false;

    calculateTilePositions();
    updateTilePositions();
    updateTextureCoordinates();
}

void ksWorld::rotateRight()
{
    m_front_tex      = &m_right;
    m_front_num_row  = &m_height;
    m_front_num_col  = &m_depth;

    m_left_tex       = &m_front;
    m_left_num_row   = &m_height;
    m_left_num_col   = &m_width;

    m_right_tex      = &m_back;
    m_right_num_row  = &m_height;
    m_right_num_col  = &m_width;

    m_top_tex        = &m_top;
    m_top_num_row    = &m_depth;
    m_top_num_col    = &m_width;

    m_bottom_tex     = &m_bottom;
    m_bottom_num_row = &m_depth;
    m_bottom_num_col = &m_width;

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

        for (int col = 0; col < (*m_front_num_col); ++col)
            m_front_pos[row][col] = calculateFrontPosition(row, col);
    }

    // Left
    m_left_pos.resize((*m_left_num_row));

    for (int row = 0; row < (*m_left_num_row); ++row)
    {
        m_left_pos[row].resize((*m_left_num_col));

        for (int col = 0; col < (*m_left_num_col); ++col)
            m_left_pos[row][col] = calculateLeftPosition(row, col);
    }

    // Right
    m_right_pos.resize((*m_right_num_row));

    for (int row = 0; row < (*m_right_num_row); ++row)
    {
        m_right_pos[row].resize((*m_right_num_col));

        for (int col = 0; col < (*m_right_num_col); ++col)
            m_right_pos[row][col] = calculateRightPosition(row, col);
    }

    // Top
    m_top_pos.resize((*m_top_num_row));

    for (int row = 0; row < (*m_top_num_row); ++row)
    {
        m_top_pos[row].resize((*m_top_num_col));

        for (int col = 0; col < (*m_top_num_col); ++col)
            m_top_pos[row][col] = calculateTopPosition(row, col);
    }

    // Bottom
    m_bottom_pos.resize((*m_bottom_num_row));

    for (int row = 0; row < (*m_bottom_num_row); ++row)
    {
        m_bottom_pos[row].resize((*m_bottom_num_col));

        for (int col = 0; col < (*m_bottom_num_col); ++col)
            m_bottom_pos[row][col] = calculateBottomPosition(row, col);
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
