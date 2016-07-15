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

#ifndef KS_APPLICATION_H
#define KS_APPLICATION_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <list>
#include <map>
#include "ksEntityLayer.h"
#include "ksControlLayer.h"
#include "ksPathFinder.h"
#include "ksParticleEmitter.h"
#include "ksLightSystem.h"
#include "defines.h"
#include "ksScene.h"
#include <iostream>

#define ksKey sf::Keyboard

#ifdef MOBILE_BUILD
#define getTouch getMouse
#define sf::Mouse::isButtonPressed(sf::Mouse::Left); sf::Touch::isDown(0);
#define sf::Mouse::getPosition(m_window) sf::Touch::getPosition(0, m_window)
#endif

////////////////////////////////////////////////////////////
/// \brief Contains renderable application that interfaces
///        with all other KingEngine types.
///
////////////////////////////////////////////////////////////
class ksApplication
{
	public:
        ////////////////////////////////////////////////////////////
        /// \brief Default Constructor
        ///
        /// Initialize the application to the default screen or desktop 
        /// size, and the title to KingEngine.
        ///
        ////////////////////////////////////////////////////////////
        ksApplication();

        ////////////////////////////////////////////////////////////
        /// \brief Construct the application using the passed title,
        /// width and height.
        ///
        /// \param app_title    Title of the application window
        /// \param app_width    Width of the application window
        /// \param app_height   Height of the application window
        ///
        ////////////////////////////////////////////////////////////
        ksApplication(std::string app_title, int app_width, int app_height);

        ////////////////////////////////////////////////////////////
        /// \brief Return whether or not the application is open.
        ///
        /// This can be useful for creating a main game loop.
        ///
        ////////////////////////////////////////////////////////////
        bool isOpen();

        ////////////////////////////////////////////////////////////
        /// \brief Add a key input to be checked for if it's pressed
        /// down on each cycle of the main game loop.
        ///
        /// \param key  The new key to check for.
        ///
        ////////////////////////////////////////////////////////////
        void addInput(ksKey::Key key);

        ////////////////////////////////////////////////////////////
        /// \brief Return whether the passed key is down or not.
        ///
        /// \param key  The new key to check for.
        ///
        ////////////////////////////////////////////////////////////
        bool getKeyDown(ksKey::Key key);

        ////////////////////////////////////////////////////////////
        /// \brief Return whether or not the left mouse button is clicked
        /// or a finger is pressed down on a touch screen device.
        ///
        ////////////////////////////////////////////////////////////
        bool getMouseDown();

        ////////////////////////////////////////////////////////////
        /// \brief Return the position in vector form of the mouse 
        /// or touch.
        ///
        ////////////////////////////////////////////////////////////
        ksVector2D getMousePosition();

        ////////////////////////////////////////////////////////////
        /// \brief Return the x position of the mouse or touch.
        ///
        ////////////////////////////////////////////////////////////
        double getMouseX();

        ////////////////////////////////////////////////////////////
        /// \brief Return the y position of the mouse or touch.
        ///
        ////////////////////////////////////////////////////////////
        double getMouseY();

        ////////////////////////////////////////////////////////////
        /// \brief Add an entity to the base game entity layer.
        ///
        /// \param entity   The entity to be added
        ///
        ////////////////////////////////////////////////////////////
        void addEntity(ksEntity * entity);

        ////////////////////////////////////////////////////////////
        /// \brief Set the lower and upper tile boundaries of the 
        /// animation of a base game entity.
        ///
        /// \param entity_number    The index of the entity that is being animated.
        /// \param lower_tile       The lower boundary of the tile animation.
        /// \param upper_tile       The upper boundary of the tile animation.
        /// \param frame_delay      The number of cycles between each frame.
        ///
        ////////////////////////////////////////////////////////////
        void animateEntity(int entity_number, int lower_tile, int upper_tile, int frame_delay);

        ////////////////////////////////////////////////////////////
        /// \brief Add a control to the base game control layer.
        ///
        /// \param control  The control to be added.
        ///
        ////////////////////////////////////////////////////////////
        void addControl(ksControl * control);

        ////////////////////////////////////////////////////////////
        /// \brief Loads the perspective game world using the passed
        /// width x height x depth) and the path to the map
        /// files.
        ///
        /// \param width     The width of the world in pixels.
        /// \param height    The height of the world in pixels.
        /// \param depth     The depth of the world in pixels.
        /// \param map_row   The number of rows in the map being loaded.
        /// \param map_col   The number of columns in the map being loaded.
        /// \param map_depth The number of units of depth in the loaded map.
        /// \param name      The name of the map being loaded.
        ///
        ////////////////////////////////////////////////////////////
        void loadWorld(int width, int height, int depth, int map_row, int map_col, int map_depth, std::string name="");

        ////////////////////////////////////////////////////////////
        /// \brief Loads the demo of the world to run on other platforms
        /// that don't currently have the same support for File IO,
        /// like iOS and Android.
        ///
        ////////////////////////////////////////////////////////////
        void loadWorldDemo();

        ////////////////////////////////////////////////////////////
        /// \brief Increases the depth of the camera inward toward the
        /// front wall of the game world.
        ///
        ////////////////////////////////////////////////////////////
        void increaseCameraDepth();

        ////////////////////////////////////////////////////////////
        /// \brief Decreases the depth of the camera backward away from
        /// the front wall of the game world.
        ///
        ////////////////////////////////////////////////////////////
        void decreaseCameraDepth();

        ////////////////////////////////////////////////////////////
        /// \brief Toggle on / off the world lighting.
        ///
        ////////////////////////////////////////////////////////////
        void toggleWorldLighting();

        ////////////////////////////////////////////////////////////
        /// \brief Toggle on the 3D effect of the world.
        ///
        ////////////////////////////////////////////////////////////
        void toggleWorld3D();

        ////////////////////////////////////////////////////////////
        /// \brief Insert a line of text into the application window.
        ///
        /// \param x     The x pixel position to display the text.
        /// \param y     The y pixel position to display the text.
        /// \param name  The identifying name of this text.
        /// \param text  The text to be displayed.
        /// \param size  The pixel size of the text.
        /// \param color The color of the text.
        ///
        ////////////////////////////////////////////////////////////
        void insertText(double x, double y, std::string name, std::string text,
                        int size = 20, ksColor color = ksColor(255, 255, 255));
        
        ////////////////////////////////////////////////////////////
        /// \brief Change the text of one of the lines of text being
        /// displayed on the application window.
        ///
        /// \param name  The identifying name of this text.
        /// \param text  The string of text to change this line to.
        ///
        ////////////////////////////////////////////////////////////
        void setText(std::string name, std::string text);

        ////////////////////////////////////////////////////////////
        /// \brief Change the color of one of the lines of text being
        /// displayed on the application window.
        ///
        /// \param name   The identifying name of this text.
        /// \param color  The color to change this line to.
        ///
        ////////////////////////////////////////////////////////////
        void setTextColor(std::string name, ksColor color);

        ////////////////////////////////////////////////////////////
        /// \brief Clear all of the associated references from
        /// the base game entity layer.
        ///
        ////////////////////////////////////////////////////////////
        void clearEntities();

        ////////////////////////////////////////////////////////////
        /// \brief Add a reference to a particle emitter so that it can
        /// be drawn in the application window.
        ///
        /// \param emitter  The reference to the particle emitter.
        ////////////////////////////////////////////////////////////
        void addParticleEmitter(ksParticleEmitter * emitter);

        ////////////////////////////////////////////////////////////
        /// \brief Add a reference to a light system so that it can be
        /// drawn in the application window.
        ///
        /// \param system  The reference to the light system.
        ////////////////////////////////////////////////////////////
        void addLightSystem(ksLightSystem * system);

        ////////////////////////////////////////////////////////////
        /// \brief Allows the developer to just run the application without
        /// creating a main loop in external code.
        ///
        ////////////////////////////////////////////////////////////
        void run();

        ////////////////////////////////////////////////////////////
        /// \brief Adds a scene to be executed.
        ///
        /// \param scene  The scene to be added.
        ///
        /// \see startSequence, pauseSequence
        ///
        ////////////////////////////////////////////////////////////
        void addScene(ksScene<double> * scene);

        ////////////////////////////////////////////////////////////
        /// \brief Starts the sequence of scenes executing linearly.
        ///
        /// \see pauseSequence, addScene
        ///
        ////////////////////////////////////////////////////////////
        void startSequence();

        ////////////////////////////////////////////////////////////
        /// \brief Pauses the sequence of scenes that are currently
        /// being run.
        ///
        /// \see startSequence, addScene
        ///
        ////////////////////////////////////////////////////////////
        void pauseSequence();

        ////////////////////////////////////////////////////////////
        /// \brief Moves the camera to the left, rotating it in opposite
        /// direction.
        ///
        /// \param amount  How much to move the camera.
        ///
        /// \see rotateWorldRight
        ///
        ////////////////////////////////////////////////////////////
        void rotateWorldLeft(int amount);

        ////////////////////////////////////////////////////////////
        /// \brief Moves the camera to the right, rotating it in opposite
        /// direction.
        ///
        /// \param amount  How much to move the camera.
        ///
        /// \see rotateWorldLeft
        ///
        ////////////////////////////////////////////////////////////
        void rotateWorldRight(int amount);

        ////////////////////////////////////////////////////////////
        /// \brief Moves the camera to the left, rotating it in opposite
        /// direction.
        ///
        /// \param amount  How much to move the camera.
        ///
        /// \see rotateWorldRight
        ///
        ////////////////////////////////////////////////////////////
        int getCameraDelta();


        ////////////////////////////////////////////////////////////
        /// \brief Returns the difference between the world's depth and 
        /// the camera's depth.
        ///
        ////////////////////////////////////////////////////////////
        ksWorld * getWorld();

        ////////////////////////////////////////////////////////////
        /// \brief Returns the smallest orientation of the window, based
        /// on the width and height.
        ///
        ////////////////////////////////////////////////////////////
        int getSmallestOrientation();

        ////////////////////////////////////////////////////////////
        /// \brief Returns a reference to the font currently being
        /// used to draw lines of text into the application.
        ///
        ////////////////////////////////////////////////////////////
        sf::Font * getFont();

        ////////////////////////////////////////////////////////////
        /// \brief Set the tilesheet for the base game entity layer.
        ///
        /// \param tilesheet  The tilesheet for the entity layer.
        ///
        ////////////////////////////////////////////////////////////
        void setEntityTilesheet(std::string tilesheet);

        ////////////////////////////////////////////////////////////
        /// \brief Changing the camera delta changes the distance the
        /// camera is from the front wall. This gives the effect
        /// of zomming in, or out on the world. Can be useful
        /// for first person perspectives.
        ///
        /// \param camera_delta  The distance between the camera data
        /// the front wall.
        ///
        ////////////////////////////////////////////////////////////
        void setCameraDelta(int camera_delta);

	private:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        sf::RenderWindow      m_window;
        ksWorld               m_world;
        int                   m_camera_depth;
        ksEntityLayer         m_entity_layer;
        ksControlLayer        m_control_layer;
        std::map<ksKey::Key, bool> m_key_down;
        bool                  m_mouse_released;
        sf::Event             m_evt;
        sf::View              m_world_view;
        sf::View              m_gui_view;
        sf::Font *            m_font;
        std::map<std::string, sf::Text> m_text_layer;
        ksParticleEmitter *   m_emitter;
        ksLightSystem *       m_light_system;
        std::list<ksScene<double> *> m_scenes;
        std::list<ksScene<double> *>::iterator m_current_scene;
        bool                  m_scene_paused;
};

#endif
