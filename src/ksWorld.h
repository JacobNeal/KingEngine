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
#include "ksEffect.h"
#include "ksPathNode.h"
#include "defines.h"

#ifdef DESKTOP_BUILD
#include <fstream>
#endif


enum ksWorldWall
{
    TOP = 0,
    BOTTOM,
    LEFT,
    RIGHT,
    FRONT
};

class ksWorld : public sf::Drawable, public sf::Transformable
{
    public:
        //              Constructors
        ksWorld(std::string tilesheet);
        ksWorld(std::string tilesheet, int width, int height, int depth);

        //              Methods
        void            load(int width, int height, int depth, int map_row, int map_col, int map_depth, std::string name="");
        void            readTiles(std::string name);
        virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;
        void            drawWorld(sf::RenderWindow & app);
        void            addLight(ksVector2D start, ksWorldWall wall, int row, int col,
                                 sf::Color first, sf::Color second);
        void            setFirstDuration(int duration);
        void            setSecondDuration(int duration);
        void            toggleLighting();
        void            toggle2D(ksWorldWall wall);
        void            toggle3D();

        //              New Methods (refactor)
        void            calculateTilePositions();
        void            updateTilePositions();
        void            assignTilePositions(std::vector<std::vector<ksTile>> * wall,
                                            int & pos, int max_row, int max_col);
        void            updateTextureCoordinates();
        void            assignTextureCoordinates(std::vector<std::vector<ksTile>> * wall,
                                                 int & pos, int max_row, int max_col);
        sf::Vector2f    transform3D(double x, double y, double z);
        sf::Vector2f    transform3D(sf::Vector3f position);
        sf::Vector2f    transform3DWithPixelValue(int x, int y, int z);
        void            transform3DWorld(int world_width_px, 
                                      int world_height_px, int world_depth_px, 
                                      int map_row_num, int map_col_num, 
                                      int map_depth_num);
        void            transform2DWorld();
        void            applyTextureCoordinates();
        void            transformFrontWall(int & index, int map_row_num,
                                           int map_col_num);
        void            transformTopWall(int & index, int map_col_num,
                                         int map_depth_num);
        void            transformBottomWall(int & index, int map_col_num,
                                            int map_depth_num);
        void            transformLeftWall(int & index, int map_row_num,
                                          int map_depth_num);
        void            transformRightWall(int & index, int map_row_num,
                                           int map_depth_num);
        void            moveCamera(int x, int y, int z);
        void            resizeWorld(int screen_width, int screen_height);
        void            setTilesheet(std::string tilesheet);
        void            loadWorldDemo();

        //              Accessor methods
        int             getWidth() { return m_world_width_px; }
        int             getHeight() { return m_world_height_px; }
        int             getDepth() { return m_world_depth_px; }
        int             getInnerX() { return m_inner_x; }
        int             getInnerY() { return m_inner_y; }
        int             getNumberOfLights() { return m_num_of_lights; }
        bool            isWorldLighting() { return m_lighting; }
        ksTile          getTilePosition(ksWorldWall wall, int row, int col, int width, int height);
        int             getLightIntensity(ksWorldWall wall, int row, int col);
        int             getTileEvent(ksWorldWall wall, int row, int col);
        int             getWallMaxRow(ksWorldWall wall);
        int             getWallMaxCol(ksWorldWall wall);
        int             getMapCol();
        int             getMapRow();
        int             getMapDepth();

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
        ksEffect        m_effect_layer;
        bool            m_lighting;
        bool            m_2D;

        int *           m_front_num_row;
        int *           m_front_num_col;
        int *           m_left_num_row;
        int *           m_left_num_col;
        int *           m_right_num_row;
        int *           m_right_num_col;
        int *           m_top_num_row;
        int *           m_top_num_col;
        int *           m_bottom_num_row;
        int *           m_bottom_num_col;

        std::vector<std::vector<int>> * m_front_cur_evt;
        std::vector<std::vector<int>> * m_left_cur_evt;
        std::vector<std::vector<int>> * m_right_cur_evt;
        std::vector<std::vector<int>> * m_top_cur_evt;
        std::vector<std::vector<int>> * m_bottom_cur_evt;

        std::vector<std::vector<ksTile>> m_top;
        std::vector<std::vector<ksTile>> m_bottom;
        std::vector<std::vector<ksTile>> m_left;
        std::vector<std::vector<ksTile>> m_right;
        std::vector<std::vector<ksTile>> m_front;
        std::vector<std::vector<ksTile>> m_back;

        std::vector<std::vector<ksTile>> m_top_pos;
        std::vector<std::vector<ksTile>> m_bottom_pos;
        std::vector<std::vector<ksTile>> m_left_pos;
        std::vector<std::vector<ksTile>> m_right_pos;
        std::vector<std::vector<ksTile>> m_front_pos;

        std::vector<std::vector<ksTile>> * m_front_tex;
        std::vector<std::vector<ksTile>> * m_left_tex;
        std::vector<std::vector<ksTile>> * m_right_tex;
        std::vector<std::vector<ksTile>> * m_top_tex;
        std::vector<std::vector<ksTile>> * m_bottom_tex;

        std::vector<std::vector<int>>    m_top_evt;
        std::vector<std::vector<int>>    m_bottom_evt;
        std::vector<std::vector<int>>    m_left_evt;
        std::vector<std::vector<int>>    m_right_evt;
        std::vector<std::vector<int>>    m_front_evt;
        std::vector<std::vector<int>>    m_back_evt;

        std::vector<std::vector<int>>    m_top_light;
        std::vector<std::vector<int>>    m_bottom_light;
        std::vector<std::vector<int>>    m_left_light;
        std::vector<std::vector<int>>    m_right_light;
        std::vector<std::vector<int>>    m_front_light;
        std::vector<std::vector<int>>    m_back_light;
        sf::Color                        m_base_color;

        // World rendering refactor members
        int                              m_world_width_px;
        int                              m_world_height_px;
        int                              m_world_depth_px;
        int                              m_map_row_num;
        int                              m_map_col_num;
        int                              m_map_depth_num;
        int                              m_camera_x;
        int                              m_camera_y;
        int                              m_camera_z;
        std::string                      m_world_name;
};

#endif
