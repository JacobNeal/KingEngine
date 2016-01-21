/********************************************************
* Class:            ksWorld
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksWorld.h
*
*   Overview:
*       Class that contains the map rendering features
*       to load a world in a limited 3D perspective.
*
*       Example:
*        __________________
*       |\                /|
*       | \ ____________ / |
*       |  |            |  |
*       |  |            |  |
*       |  |            |  |
*       |  /------------\  |
*       | /              \ |
*        ------------------
********************************************************/

#ifndef KS_WORLD_H
#define KS_WORLD_H

#include <SFML/Graphics.hpp>
#include "ksTile.h"
#include "defines.h"

class ksWorld : public sf::Drawable, public sf::Transformable
{
    public:
        //              Constructors
        ksWorld();

        //              Methods
        void            load(int width, int height, int depth);
        void            drawLeftTiles(int start_index);
        void            drawRightTiles(int start_index);
        void            drawFrontTiles(int start_index);
        ksTile          calculateLeftPosition(int row, int col);
        ksTile          calculateRightPosition(int row, int col);
        ksTile          calculateFrontPosition(int row, int col);
        virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;

    private:
        int             m_width;
        int             m_height;
        int             m_depth;
        int             m_outer_height_px;
        int             m_outer_width_px;
        int             m_inner_x;
        int             m_inner_y;

        int **          m_front_map;
        int **          m_back_map;
        int **          m_top_map;
        int **          m_bottom_map;
        int **          m_left_map;
        int **          m_right_map;

        sf::VertexArray m_array;
};

#endif
