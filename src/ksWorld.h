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
#include <vector>

#include "ksTile.h"
#include "defines.h"

#ifdef DESKTOP_BUILD
#include <fstream>
#endif

class ksWorld : public sf::Drawable, public sf::Transformable
{
    public:
        //              Constructors
        ksWorld(std::string tilesheet);
        ksWorld(std::string tilesheet, int width, int height, int depth);

        //              Methods
        void            load(int width, int height, int depth, std::string name="");
        void            readTiles(std::string name);
        void            drawLeftTiles(int start_index);
        void            drawRightTiles(int start_index);
        void            drawTopTiles(int start_index);
        void            drawBottomTiles(int start_index);
        void            drawFrontTiles(int start_index);
        ksTile          calculateLeftPosition(int row, int col);
        ksTile          calculateRightPosition(int row, int col);
        ksTile          calculateTopPosition(int row, int col);
        ksTile          calculateBottomPosition(int row, int col);
        ksTile          calculateFrontPosition(int row, int col);
        virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;

        //              Accessor methods
        int             getWidth() { return m_width; }
        int             getHeight() { return m_height; }
        int             getDepth() { return m_depth; }
        int             getInnerX() { return m_inner_x; }
        int             getInnerY() { return m_inner_y; }

    private:
        //              Data members
        int             m_width;
        int             m_height;
        int             m_depth;
        int             m_outer_height_px;
        int             m_outer_width_px;
        int             m_inner_x;
        int             m_inner_y;
        int             m_num_of_lights;
        std::string     m_map_name;
        std::string     m_tilesheet;
        sf::VertexArray m_array;
        sf::Texture     m_texture;

        std::vector<std::vector<ksTile>> m_top;
        std::vector<std::vector<ksTile>> m_bottom;
        std::vector<std::vector<ksTile>> m_left;
        std::vector<std::vector<ksTile>> m_right;
        std::vector<std::vector<ksTile>> m_front;
        
        std::vector<std::vector<int>>    m_top_light;
        std::vector<std::vector<int>>    m_bottom_light;
        std::vector<std::vector<int>>    m_left_light;
        std::vector<std::vector<int>>    m_right_light;
        std::vector<std::vector<int>>    m_front_light;
        sf::Color                        m_base_color;
};

#endif
