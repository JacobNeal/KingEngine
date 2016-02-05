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
      m_num_of_lights(0), m_tilesheet(tilesheet)
{
   m_texture.loadFromFile(tilesheet);
   m_base_color = sf::Color(50, 50, 50);
}

/********************************************************
*   ksWorld
*
*   Initialize the world based on the passed width,
*   height and depth values defining the world.
********************************************************/
ksWorld::ksWorld(std::string tilesheet, int width, int height, int depth)
    : m_width(width), m_height(height), m_depth(depth), m_inner_x(0), m_inner_y(0),
      m_tilesheet(tilesheet)
{
    if (m_depth < 0)
        m_depth = 0;

    m_texture.loadFromFile(tilesheet);
    m_base_color = sf::Color(50, 50, 50);

    //load(m_width, m_height, m_depth);
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

    std::cout << "World loaded.\n";

    m_array.setPrimitiveType(sf::Quads);
    
    // FRONT + LEFT + RIGHT + TOP + BOTTOM
    m_array.resize((m_width * m_height * 4) + (m_height * m_depth * 4) + (m_height * m_depth * 4) +
                   (m_width * m_depth * 4) + (m_width * m_depth * 4));

    m_outer_width_px = ((m_depth * 2) + m_width) * TILE_WIDTH;
    m_outer_height_px = ((m_depth * 2) + m_height) * TILE_HEIGHT;

    m_inner_x = (m_outer_width_px / 2) - ((m_width * TILE_WIDTH) / 2);
    m_inner_y = (m_outer_height_px / 2) - ((m_height * TILE_HEIGHT) / 2);

    drawFrontTiles(0);
    drawLeftTiles(m_width * m_height * 4);
    drawRightTiles((m_width * m_height * 4) + (m_height * m_depth * 4));
    drawTopTiles((m_width * m_height * 4) + (m_height * m_depth * 4) + 
                 (m_height * m_depth * 4));
    drawBottomTiles((m_width * m_height * 4) + (m_height * m_depth * 4) + 
                    (m_height * m_depth * 4) + (m_width * m_depth * 4));
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
}

/********************************************************
*   drawLeftTiles
*
*   Draw all of the tiles on the left wall with their
*   respective lighting.
********************************************************/
void ksWorld::drawLeftTiles(int start_index)
{
    for (int row = 0; row < m_height; ++row)
    {
        for (int col = 0; col < m_depth; ++col)
        {
            ksTile tile = calculateLeftPosition(row, col);
            
            int r = m_base_color.r + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_left_light[row][col]);
            int g = m_base_color.g + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_left_light[row][col]);
            int b = m_base_color.b + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_left_light[row][col]);
            
            if (r > 255)
                r = 255;
            if (g > 255)
                g = 255;
            if (b > 255)
                b = 255;

            m_array[start_index].position       = sf::Vector2f(tile.TL.X, tile.TL.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_left[row][col].TL.X, m_left[row][col].TL.Y);

            m_array[start_index].position       = sf::Vector2f(tile.TR.X, tile.TR.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_left[row][col].TR.X, m_left[row][col].TR.Y);

            m_array[start_index].position       = sf::Vector2f(tile.BR.X, tile.BR.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_left[row][col].BR.X, m_left[row][col].BR.Y);

            m_array[start_index].position       = sf::Vector2f(tile.BL.X, tile.BL.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_left[row][col].BL.X, m_left[row][col].BL.Y);
        }
    }
}

/********************************************************
*   drawRightTiles
*
*   Draw all of the tiles on the right wall with their
*   respective lighting.
********************************************************/
void ksWorld::drawRightTiles(int start_index)
{
    for (int row = 0; row < m_height; ++row)
    {
        for (int col = 0; col < m_depth; ++col)
        {
            ksTile tile = calculateRightPosition(row, col);
            
            int r = m_base_color.r + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_right_light[row][col]);
            int g = m_base_color.g + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_right_light[row][col]);
            int b = m_base_color.b + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_right_light[row][col]);
            
            if (r > 255)
                r = 255;
            if (g > 255)
                g = 255;
            if (b > 255)
                b = 255;
            
            m_array[start_index].position       = sf::Vector2f(tile.TL.X, tile.TL.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_right[row][col].TL.X, m_right[row][col].TL.Y);
            
            m_array[start_index].position       = sf::Vector2f(tile.TR.X, tile.TR.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_right[row][col].TR.X, m_right[row][col].TR.Y);

            m_array[start_index].position       = sf::Vector2f(tile.BR.X, tile.BR.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_right[row][col].BR.X, m_right[row][col].BR.Y);

            m_array[start_index].position       = sf::Vector2f(tile.BL.X, tile.BL.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_right[row][col].BL.X, m_right[row][col].BL.Y);
        }
    }
}

/********************************************************
*   drawTopTiles
*
*   Draw all of the tiles on the top wall with their
*   respective lighting.
********************************************************/
void ksWorld::drawTopTiles(int start_index)
{
    for (int row = 0; row < m_depth; ++row)
    {
        for (int col = 0; col < m_width; ++col)
        {
            ksTile tile = calculateTopPosition(row, col);
            
            int r = m_base_color.r + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_top_light[row][col]);
            int g = m_base_color.g + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_top_light[row][col]);
            int b = m_base_color.b + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_top_light[row][col]);
            
            if (r > 255)
                r = 255;
            if (g > 255)
                g = 255;
            if (b > 255)
                b = 255;
            
            m_array[start_index].position       = sf::Vector2f(tile.TL.X, tile.TL.Y);
            m_array[start_index].color          = sf::Color(r, g, b);;
            m_array[start_index++].texCoords    = sf::Vector2f(m_top[row][col].TL.X, m_top[row][col].TL.Y);
            
            m_array[start_index].position       = sf::Vector2f(tile.TR.X, tile.TR.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_top[row][col].TR.X, m_top[row][col].TR.Y);

            m_array[start_index].position       = sf::Vector2f(tile.BR.X, tile.BR.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_top[row][col].BR.X, m_top[row][col].BR.Y);

            m_array[start_index].position       = sf::Vector2f(tile.BL.X, tile.BL.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_top[row][col].BL.X, m_top[row][col].BL.Y);
        }
    }
}

/********************************************************
*   drawBottomTiles
*
*   Draw all the tiles on the bottom wall with their
*   respective lighting.
********************************************************/
void ksWorld::drawBottomTiles(int start_index)
{
    for (int row = 0; row < m_depth; ++row)
    {
        for (int col = 0; col < m_width; ++col)
        {
            ksTile tile = calculateBottomPosition(row, col);
            
            int r = m_base_color.r + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_bottom_light[row][col]);
            int g = m_base_color.g + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_bottom_light[row][col]);
            int b = m_base_color.b + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_bottom_light[row][col]);
            
            if (r > 255)
                r = 255;
            if (g > 255)
                g = 255;
            if (b > 255)
                b = 255;

            m_array[start_index].position       = sf::Vector2f(tile.TL.X, tile.TL.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_bottom[row][col].TL.X, m_bottom[row][col].TL.Y);
            
            m_array[start_index].position       = sf::Vector2f(tile.TR.X, tile.TR.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_bottom[row][col].TR.X, m_bottom[row][col].TR.Y);

            m_array[start_index].position       = sf::Vector2f(tile.BR.X, tile.BR.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_bottom[row][col].BR.X, m_bottom[row][col].BR.Y);

            m_array[start_index].position       = sf::Vector2f(tile.BL.X, tile.BL.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_bottom[row][col].BL.X, m_bottom[row][col].BL.Y);
        }
    }
}

/********************************************************
*   drawFrontTiles
*
*   Draw all the tiles on the front wall with their
*   respective lighting.
********************************************************/
void ksWorld::drawFrontTiles(int start_index)
{
    for (int row = 0; row < m_height; ++row)
    {
        for (int col = 0; col < m_width; ++col)
        {
            ksTile tile = calculateFrontPosition(row, col);
            
            int r = m_base_color.r + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_front_light[row][col]);
            int g = m_base_color.g + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_front_light[row][col]);
            int b = m_base_color.b + (m_num_of_lights * LIGHT_INTENSITY_MULT) + (50 * m_front_light[row][col]);
            
            if (r > 255)
                r = 255;
            if (g > 255)
                g = 255;
            if (b > 255)
                b = 255;

            m_array[start_index].position       = sf::Vector2f(tile.TL.X, tile.TL.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_front[row][col].TL.X, m_front[row][col].TL.Y);
            
            m_array[start_index].position       = sf::Vector2f(tile.TR.X, tile.TR.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_front[row][col].TR.X, m_front[row][col].TR.Y);

            m_array[start_index].position       = sf::Vector2f(tile.BR.X, tile.BR.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_front[row][col].BR.X, m_front[row][col].BR.Y);

            m_array[start_index].position       = sf::Vector2f(tile.BL.X, tile.BL.Y);
            m_array[start_index].color          = sf::Color(r, g, b);
            m_array[start_index++].texCoords    = sf::Vector2f(m_front[row][col].BL.X, m_front[row][col].BL.Y);
        }
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

void ksWorld::addLight(ksVector2D start, ksWorldWall wall, int row, int col,
                       sf::Color first, sf::Color second)
{
    ksTile temp;
    ksVector2D end;

    if (wall == TOP)
    {
        m_top_light[row][col] = 3;
        temp = calculateTopPosition(row, col);

        end.X = temp.TL.X + (fabs(temp.TR.X - temp.TL.X) / 2);
        end.Y = temp.TL.Y + (fabs(temp.TR.Y - temp.TL.Y) / 2);
    }
    else if (wall == BOTTOM)
    {
        m_bottom_light[row][col] = 3;
        
        temp = calculateBottomPosition(row, col);
        end.X = temp.TL.X + (fabs(temp.TR.X - temp.TL.X) / 2);
        end.Y = temp.TL.Y + (fabs(temp.TR.Y - temp.TL.Y) / 2);
    }
    else if (wall == LEFT)
    {
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

    m_effect_layer.addLight(start, end, TILE_WIDTH, first, second);
    m_num_of_lights += 6;
    
    drawFrontTiles(0);
    drawLeftTiles(m_width * m_height * 4);
    drawRightTiles((m_width * m_height * 4) + (m_height * m_depth * 4));
    drawTopTiles((m_width * m_height * 4) + (m_height * m_depth * 4) + 
                 (m_height * m_depth * 4));
    drawBottomTiles((m_width * m_height * 4) + (m_height * m_depth * 4) + 
                    (m_height * m_depth * 4) + (m_width * m_depth * 4));
}

/********************************************************
*   getTilePosition
*
*   Returns the position of a tile in the 3D perspective
*   relative to the passed width, height, and depth.
********************************************************/
const ksTile & ksWorld::getTilePosition(ksWorldWall wall, int row, int col, int width, int height)
{
    ksTile tile1, tile2, tile3, tile4, tile5;
    
    if (wall == FRONT)
    {
        tile1 = calculateFrontPosition(row, col);
        tile2 = calculateFrontPosition(row + height, col);
        tile3 = calculateFrontPosition(row + height, col + width);
        tile4 = calculateFrontPosition(row, col + width);
        
        tile5.TL = tile1.TL;
        tile5.TR = tile2.TR;
        tile5.BR = tile3.BR;
        tile5.BL = tile4.BL;
    }
    else if (wall == TOP)
    {
        tile1 = calculateTopPosition(row, col);
        tile2 = calculateTopPosition(row + height, col);
        tile3 = calculateTopPosition(row + height, col + width);
        tile4 = calculateTopPosition(row, col + width);
        
        tile5.TL = tile1.TL;
        tile5.TR = tile2.TR;
        tile5.BR = tile3.BR;
        tile5.BL = tile4.BL;
    }
    else if (wall == BOTTOM)
    {
        tile1 = calculateBottomPosition(row, col);
        tile2 = calculateBottomPosition(row, col + width);
        tile3 = calculateRightPosition(m_height - height, row);

        tile5.BL   = tile1.BL;
        tile5.BR   = tile2.BR;
        tile5.TL.X = tile5.BL.X;
        tile5.TL.Y = tile3.TR.Y;
        tile5.TR.X = tile5.BR.X;
        tile5.TR.Y = tile5.TL.Y;
    }
    else if (wall == LEFT)
    {
        tile1 = calculateLeftPosition(row, col);
        tile2 = calculateLeftPosition(row + height, col);
        tile3 = calculateLeftPosition(row + height, col + width);
        tile4 = calculateLeftPosition(row, col + width);
        
        tile5.TL = tile1.TL;
        tile5.TR = tile2.TR;
        tile5.BR = tile3.BR;
        tile5.BL = tile4.BL;
    }
    else if (wall == RIGHT)
    {
        tile1 = calculateRightPosition(row, col);
        tile2 = calculateRightPosition(row + height, col);
        tile3 = calculateRightPosition(row + height, col + width);
        tile4 = calculateRightPosition(row, col + width);
        
        tile5.TL = tile1.TL;
        tile5.TR = tile2.TR;
        tile5.BR = tile3.BR;
        tile5.BL = tile4.BL;
    }

    return tile5;
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
    if (wall == FRONT)
        return m_front_evt[row][col];
    else if (wall == BOTTOM)
        return m_bottom_evt[row][col];
    else if (wall == LEFT)
        return m_left_evt[row][col];
    else if (wall == RIGHT)
        return m_right_evt[row][col];
    else
        return m_top_evt[row][col];
}
