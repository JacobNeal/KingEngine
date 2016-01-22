/********************************************************
* Class:            ksWorld
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksWorld.cpp
********************************************************/

#include "ksWorld.h"

/********************************************************
*   ksWorld
*
*   Initialize the world without any map loaded.
********************************************************/
ksWorld::ksWorld()
    : m_width(0), m_height(0), m_depth(0), m_inner_x(0), m_inner_y(0)
{
}

/********************************************************
*   ksWorld
*
*   Initialize the world based on the passed width,
*   height and depth values defining the world.
********************************************************/
ksWorld::ksWorld(int width, int height, int depth)
    : m_width(width), m_height(height), m_depth(depth)
{
    if (m_depth < 0)
        m_depth = 0;

    load(m_width, m_height, m_depth);
}

/********************************************************
*   load
*
*   Load a map with (width x height x depth) values.
********************************************************/
void ksWorld::load(int width, int height, int depth)
{
    m_width = width;
    m_height = height;
    m_depth = depth > 0 ? depth : 0;

    m_array.clear();

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
    drawTopTiles((m_width * m_height * 4) + (m_height * m_depth * 4) + (m_height * m_depth * 4));
    drawBottomTiles((m_width * m_height * 4) + (m_height * m_depth * 4) + (m_height * m_depth * 4) + (m_width * m_depth * 4));
}

/********************************************************
*   drawLeftTiles
*
*   Calculate the position of all tiles on the left
*   wall.
********************************************************/
void ksWorld::drawLeftTiles(int start_index)
{
    for (int row = 0; row < m_height; ++row)
    {
        for (int col = 0; col < m_depth; ++col)
        {
            ksTile tile = calculateLeftPosition(row, col);
            
            m_array[start_index].position = sf::Vector2f(tile.TL.X, tile.TL.Y);
            m_array[start_index++].color  = sf::Color(255, 0, 0);
            
            m_array[start_index].position = sf::Vector2f(tile.TR.X, tile.TR.Y);
            m_array[start_index++].color  = sf::Color(0, 255, 0);

            m_array[start_index].position = sf::Vector2f(tile.BR.X, tile.BR.Y);
            m_array[start_index++].color  = sf::Color(0, 0, 255);

            m_array[start_index].position = sf::Vector2f(tile.BL.X, tile.BL.Y);
            m_array[start_index++].color  = sf::Color(255, 255, 0);
        }
    }
}

void ksWorld::drawRightTiles(int start_index)
{
    for (int row = 0; row < m_height; ++row)
    {
        for (int col = 0; col < m_depth; ++col)
        {
            ksTile tile = calculateRightPosition(row, col);

            m_array[start_index].position = sf::Vector2f(tile.TL.X, tile.TL.Y);
            m_array[start_index++].color  = sf::Color(255, 0, 0);

            m_array[start_index].position = sf::Vector2f(tile.TR.X, tile.TR.Y);
            m_array[start_index++].color  = sf::Color(0, 255, 0);

            m_array[start_index].position = sf::Vector2f(tile.BR.X, tile.BR.Y);
            m_array[start_index++].color  = sf::Color(0, 0, 255);

            m_array[start_index].position = sf::Vector2f(tile.BL.X, tile.BL.Y);
            m_array[start_index++].color  = sf::Color(255, 255, 0);
        }
    }
}

void ksWorld::drawTopTiles(int start_index)
{
    for (int row = 0; row < m_depth; ++row)
    {
        for (int col = 0; col < m_width; ++col)
        {
            ksTile tile = calculateTopPosition(row, col);

            m_array[start_index].position = sf::Vector2f(tile.TL.X, tile.TL.Y);
            m_array[start_index++].color  = sf::Color(255, 0, 0);

            m_array[start_index].position = sf::Vector2f(tile.TR.X, tile.TR.Y);
            m_array[start_index++].color  = sf::Color(0, 255, 0);

            m_array[start_index].position = sf::Vector2f(tile.BR.X, tile.BR.Y);
            m_array[start_index++].color  = sf::Color(0, 0, 255);

            m_array[start_index].position = sf::Vector2f(tile.BL.X, tile.BL.Y);
            m_array[start_index++].color  = sf::Color(255, 255, 0);
        }
    }
}

void ksWorld::drawBottomTiles(int start_index)
{
    for (int row = 0; row < m_depth; ++row)
    {
        for (int col = 0; col < m_width; ++col)
        {
            ksTile tile = calculateBottomPosition(row, col);

            m_array[start_index].position = sf::Vector2f(tile.TL.X, tile.TL.Y);
            m_array[start_index++].color  = sf::Color(255, 0, 0);

            m_array[start_index].position = sf::Vector2f(tile.TR.X, tile.TR.Y);
            m_array[start_index++].color  = sf::Color(0, 255, 0);

            m_array[start_index].position = sf::Vector2f(tile.BR.X, tile.BR.Y);
            m_array[start_index++].color  = sf::Color(0, 0, 255);

            m_array[start_index].position = sf::Vector2f(tile.BL.X, tile.BL.Y);
            m_array[start_index++].color  = sf::Color(255, 255, 0);
        }
    }
}

void ksWorld::drawFrontTiles(int start_index)
{
    for (int row = 0; row < m_height; ++row)
    {
        for (int col = 0; col < m_width; ++col)
        {
            ksTile tile = calculateFrontPosition(row, col);

            m_array[start_index].position = sf::Vector2f(tile.TL.X, tile.TL.Y);
            m_array[start_index++].color  = sf::Color(255, 0, 0);
            
            m_array[start_index].position = sf::Vector2f(tile.TR.X, tile.TR.Y);
            m_array[start_index++].color  = sf::Color(0, 255, 0);

            m_array[start_index].position = sf::Vector2f(tile.BR.X, tile.BR.Y);
            m_array[start_index++].color  = sf::Color(0, 0, 255);

            m_array[start_index].position = sf::Vector2f(tile.BL.X, tile.BL.Y);
            m_array[start_index++].color  = sf::Color(255, 255, 0); 
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
*
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

void ksWorld::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_array, states);
}
