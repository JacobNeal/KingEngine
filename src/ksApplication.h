/********************************************************
* Class:            ksApplication
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksApplication.h
*
*   Overview:
*       Contains renderable application that interfaces
*       with all other KingEngine types.
*       Including:
*           All entities
*           All controls
*
********************************************************/

#ifndef KS_APPLICATION_H
#define KS_APPLICATION_H

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
//#include "ksWorld.h"

#define ksKey sf::Keyboard

#ifdef MOBILE_BUILD
#define getTouch getMouse
#define sf::Mouse::isButtonPressed(sf::Mouse::Left); sf::Touch::isDown(0);
#define sf::Mouse::getPosition(m_window) sf::Touch::getPosition(0, m_window)
#endif

//bool operator== (const ksPathNode & node1, const ksPathNode & node2);

class ksApplication
{
	public:
		//                    Constructors
		ksApplication();
		ksApplication(std::string app_title, int app_width, int app_height);

		//                    Methods
		bool                  isOpen();
		void                  addInput(ksKey::Key key);
		bool                  getKeyDown(ksKey::Key key);
		bool                  getMouseDown();
		ksVector2D            getMousePosition();
		double                getMouseX();
		double                getMouseY();
		void                  addEntity(ksEntity * entity);
		void                  animateEntity(int entity_number, int lower_tile, int upper_tile, int frame_delay);
        void                  addControl(ksControl * control);
        void                  addLight(ksVector2D start, ksWorldWall wall, int row, int col, ksColor first, ksColor second);
        void                  loadWorld(int width, int height, int depth, int map_row, int map_col, int map_depth, std::string name="");
        void                  loadWorldDemo();
        void                  increaseCameraDepth();
        void                  decreaseCameraDepth();
        void                  toggleWorldLighting();
        void                  toggleWorld3D();
        void                  insertText(double x, double y, 
                                         std::string name, std::string text,
                                         int size = 20, ksColor color = ksColor(255, 255, 255));
        void                  setText(std::string name, std::string text);
        void                  setTextColor(std::string name, ksColor color);
        void                  clearEntities();
        void                  addParticleEmitter(ksParticleEmitter * emitter);
        void                  addLightSystem(ksLightSystem * system);
        void                  run();
        void                  addScene(ksScene<double> * scene);
        void                  startSequence();
        void                  pauseSequence();
        void                  rotateWorldLeft(int amount);
        void                  rotateWorldRight(int amount);
    
        //                    Accessor methods
        int                   getCameraDelta();
        ksWorld *             getWorld();
        int                   getSmallestOrientation();
        sf::Font *            getFont();

		//                    Mutators
		void                  setEntityTilesheet(std::string tilesheet);
        void                  setCameraDelta(int camera_delta);

	private:
		//                    Data members
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
