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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ksApplication.h"
#include <iostream>

////////////////////////////////////////////////////////////
ksApplication::ksApplication()
	: m_window(sf::VideoMode::getDesktopMode(), "KingEngine"),
	m_world("images/voltor_interior2.png"), m_camera_depth(0), 
    m_entity_layer(&m_world, "images/default.png"), 
    m_control_layer("images/portal_obj.png"), m_mouse_released(false),
    m_emitter(nullptr), m_light_system(nullptr), m_scene_paused(false)
{
	m_window.setFramerateLimit(FRAMERATE);
    m_font = new sf::Font;
    
    m_font->loadFromFile("images/minecraft.ttf");
    ((sf::Texture&)m_font->getTexture(12U)).setSmooth(false);
    
    m_gui_view = m_window.getDefaultView();
    m_current_scene = m_scenes.begin();
}

////////////////////////////////////////////////////////////
ksApplication::ksApplication(std::string app_title, int app_width, int app_height)
	: m_window(sf::VideoMode(app_width, app_height, 32), app_title.c_str()),
	m_world("images/voltor_interior2.png"), m_camera_depth(0), 
    m_entity_layer(&m_world, "images/default.png"), 
    m_control_layer("images/portal_obj.png"), m_mouse_released(false),
    m_emitter(nullptr), m_light_system(nullptr), m_scene_paused(false)
{
	m_window.setFramerateLimit(FRAMERATE);
    m_font = new sf::Font;
    
    m_font->loadFromFile("images/minecraft.ttf");
    ((sf::Texture&)m_font->getTexture(12U)).setSmooth(false);
    
    m_gui_view = m_window.getDefaultView();
    m_current_scene = m_scenes.begin();
}

////////////////////////////////////////////////////////////
bool ksApplication::isOpen()
{
	// do updates
	m_window.clear();
    m_window.setView(m_world_view);
    m_world.drawWorld(m_window);

//    m_window.setView(m_window.getDefaultView());
        
    m_entity_layer.drawLayer(m_window);
    
    if (m_light_system != nullptr)
        m_window.draw(*m_light_system);
    
    if (m_emitter != nullptr)
    {
        m_emitter->update();
        m_window.draw(*m_emitter);
    }
    
    //m_window.setView(m_window.getDefaultView());
    //m_window.setView(m_gui_view);
    
	m_control_layer.drawLayer(m_window);
    
    for (std::map<std::string, sf::Text>::iterator iter = m_text_layer.begin();
         iter != m_text_layer.end(); iter++)
    {
        m_window.draw(iter->second);
    }

    m_window.display();

	m_entity_layer.depressEntity();
    m_control_layer.depressControl();

    m_mouse_released = false;

	// check for closed window / app
	if (m_window.pollEvent(m_evt))
	{
		if (m_evt.type == sf::Event::KeyPressed)
		{
			for (std::map<ksKey::Key, bool>::iterator it = m_key_down.begin();
				it != m_key_down.end(); ++it)
			{
				if (m_evt.key.code == it->first)
					m_key_down[it->first] = true;
			}
            // if (m_evt.key.code == sf::Keyboard::Key::Right)
            // {
            //     rotateWorldLeft(20);
            // }
            // else if (m_evt.key.code == sf::Keyboard::Key::Left)
            // {
            //     rotateWorldRight(20);
            // }
		}
		else if (m_evt.type == sf::Event::KeyReleased)
		{
			for (std::map<ksKey::Key, bool>::iterator it = m_key_down.begin();
				it != m_key_down.end(); ++it)
			{
				if (m_evt.key.code == it->first)
					m_key_down[it->first] = false;
			}
		}
        else if (m_evt.type == sf::Event::Resized)
        {
            double heightProportionateToWidth = (double) m_world.getHeight() / m_world.getWidth();
    
            double new_width = m_evt.size.width;
            double new_height = heightProportionateToWidth * new_width;
            float viewport_height = (float) 1.f - ((m_evt.size.height - new_height) / m_evt.size.height);
            float viewport_top = (float) ((m_evt.size.height - new_height) / 2) / m_evt.size.height;
            
            //m_world_view.reset(sf::FloatRect(0, 0, width, height));
            m_world_view.setViewport(sf::FloatRect(0.0f, viewport_top, 1.f, viewport_height));
        }
		else if (m_evt.type == sf::Event::Closed)
			m_window.close();

		if (m_evt.type == sf::Event::MouseButtonReleased)
		{
			m_mouse_released = true;

			if (m_control_layer.pressControl(sf::Mouse::getPosition(m_window).x,
                sf::Mouse::getPosition(m_window).y))
            {
                m_mouse_released = false;
            }
            else if (m_entity_layer.pressEntity(sf::Mouse::getPosition(m_window).x,
	           sf::Mouse::getPosition(m_window).y))
			{
                m_mouse_released = false;
            }
		}
		else
			m_mouse_released = false;
	}
    
    if (!m_scene_paused)
    {
        // Update the current scene
        if (m_current_scene != m_scenes.end())
            (*m_current_scene)->update();
        
        // Advance current scene if it's finished.
        if (m_current_scene != m_scenes.end() && (*m_current_scene)->isDone())
            ++m_current_scene;
    }

	return m_window.isOpen();
}

////////////////////////////////////////////////////////////
void ksApplication::addInput(ksKey::Key key)
{
	m_key_down[key] = false;
}

////////////////////////////////////////////////////////////
bool ksApplication::getKeyDown(ksKey::Key key)
{
	return m_key_down[key];
}

////////////////////////////////////////////////////////////
bool ksApplication::getMouseDown()
{
	return m_mouse_released;
}

////////////////////////////////////////////////////////////
ksVector2D ksApplication::getMousePosition()
{
	return ksVector2D(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y);
}

////////////////////////////////////////////////////////////
double ksApplication::getMouseX()
{
	return (double)sf::Mouse::getPosition(m_window).x;
}

////////////////////////////////////////////////////////////
double ksApplication::getMouseY()
{
	return (double)sf::Mouse::getPosition(m_window).y;
}

////////////////////////////////////////////////////////////
void ksApplication::addEntity(ksEntity * entity)
{
	m_entity_layer.addEntity(entity);
}

////////////////////////////////////////////////////////////
void ksApplication::animateEntity(int entity_number, int lower_tile, int upper_tile, int frame_delay)
{
	m_entity_layer.animate(entity_number, lower_tile, upper_tile, frame_delay);
}

////////////////////////////////////////////////////////////
void ksApplication::addControl(ksControl * control)
{
    m_control_layer.addControl(control);
}

////////////////////////////////////////////////////////////
void ksApplication::loadWorld(int width, int height, int depth, int map_row, int map_col, int map_depth, std::string name)
{
    m_world.load(width, height, depth, map_row, map_col, map_depth, name);
    
    m_camera_depth = depth;
    
    double heightProportionateToWidth = (double) height / width;
    
    double new_width = m_window.getSize().x;
    double new_height = heightProportionateToWidth * new_width;
    float viewport_height = (float) 1.f - ((m_window.getSize().y - new_height) / m_window.getSize().y);
    float viewport_top = (float) ((m_window.getSize().y - new_height) / 2) / m_window.getSize().y;
    
    m_world_view.reset(sf::FloatRect(0, 0, width, height));
    m_world_view.setViewport(sf::FloatRect(0.0f, viewport_top, 1.f, viewport_height));
}

////////////////////////////////////////////////////////////
void ksApplication::loadWorldDemo()
{
    // Load the world demo.
    m_world.loadWorldDemo();
    
    m_camera_depth = m_world.getDepth();
    
    int width = m_world.getWidth();
    int height = m_world.getHeight();
    
    double heightProportionateToWidth = (double) height / width;
    
    double new_width = m_window.getSize().x;
    double new_height = heightProportionateToWidth * new_width;
    float viewport_height = (float) 1.f - ((m_window.getSize().y - new_height) / m_window.getSize().y);
    float viewport_top = (float) ((m_window.getSize().y - new_height) / 2) / m_window.getSize().y;
    
    m_world_view.reset(sf::FloatRect(0, 0, width, height));
    m_world_view.setViewport(sf::FloatRect(0.0f, viewport_top, 1.f, viewport_height));
}

////////////////////////////////////////////////////////////
void ksApplication::increaseCameraDepth()
{
    sf::Vector2f top_left = m_world.transform3D(0.0, 0.0, 0.125);
    sf::Vector2f top_right = m_world.transform3D(1.0, 0.0, 0.125);
    sf::Vector2f bottom_left = m_world.transform3D(0.0, 1.0, 0.125);

    int width = top_right.x - top_left.x;
    int height = bottom_left.y - top_left.y;

    double scale = (double) (width + height) / (800 + 640);
    
    m_world_view.zoom(scale);
}

////////////////////////////////////////////////////////////
void ksApplication::decreaseCameraDepth()
{
    sf::Vector2f top_left = m_world.transform3D(0.0, 0.0, -0.125);
    sf::Vector2f top_right = m_world.transform3D(1.0, 0.0, -0.125);
    sf::Vector2f bottom_left = m_world.transform3D(0.0, 1.0, -0.125);

    int width = top_right.x - top_left.x;
    int height = bottom_left.y - top_left.y;

    double scale = (double) (width + height) / (800 + 640);
    
    m_world_view.zoom(scale);
}

////////////////////////////////////////////////////////////
void ksApplication::toggleWorldLighting()
{
    m_world.toggleLighting();
}

////////////////////////////////////////////////////////////
void ksApplication::toggleWorld3D()
{
    m_world.toggle3D();
}

////////////////////////////////////////////////////////////
void ksApplication::insertText(double x, double y, std::string name, 
                               std::string text, int size, ksColor color)
{
    m_text_layer.insert(std::pair<std::string, sf::Text>(name, sf::Text(text, *m_font)));
    m_text_layer[name].setPosition(x, y);
    m_text_layer[name].setCharacterSize(size);
    m_text_layer[name].setColor(color);
}

////////////////////////////////////////////////////////////
void ksApplication::setText(std::string name, std::string text)
{
    m_text_layer[name].setString(text);
}

////////////////////////////////////////////////////////////
void ksApplication::setTextColor(std::string name, ksColor color)
{
    m_text_layer[name].setColor(color);
}

////////////////////////////////////////////////////////////
void ksApplication::clearEntities()
{
    m_entity_layer.purge();
}

////////////////////////////////////////////////////////////
int ksApplication::getCameraDelta()
{
    return m_camera_depth;
}

////////////////////////////////////////////////////////////
ksWorld * ksApplication::getWorld()
{
    return &m_world;
}

////////////////////////////////////////////////////////////
int ksApplication::getSmallestOrientation()
{
    return m_window.getSize().x < m_window.getSize().y ?
        (int) m_window.getSize().x : (int) m_window.getSize().y;
}

////////////////////////////////////////////////////////////
sf::Font * ksApplication::getFont()
{
    return m_font;
}

////////////////////////////////////////////////////////////
void ksApplication::setEntityTilesheet(std::string tilesheet)
{
	m_entity_layer.setTilesheet(tilesheet);
    m_world.setTilesheet(tilesheet);
}

////////////////////////////////////////////////////////////
void ksApplication::setCameraDelta(int camera_delta)
{
    if (camera_delta > 0 && camera_delta <= m_world.getDepth())
    {
        int current_area = (m_world.getWidth() + m_camera_depth) *
                           (m_world.getHeight() + m_camera_depth);

        m_camera_depth   = camera_delta;

        int new_area     = (m_world.getWidth() + m_camera_depth) *
                           (m_world.getHeight() + m_camera_depth);

        m_world_view.zoom((float) new_area / current_area);
    }
}

////////////////////////////////////////////////////////////
void ksApplication::addParticleEmitter(ksParticleEmitter * emitter)
{
    m_emitter = emitter;
}

////////////////////////////////////////////////////////////
void ksApplication::addLightSystem(ksLightSystem * system)
{
    m_light_system = system;
}

////////////////////////////////////////////////////////////
void ksApplication::run()
{
    while (isOpen()) ;
}

////////////////////////////////////////////////////////////
void ksApplication::addScene(ksScene<double> * scene)
{
    m_scenes.push_back(scene);
    m_current_scene = m_scenes.begin();
}

////////////////////////////////////////////////////////////
void ksApplication::startSequence()
{
    m_scene_paused = false;
    
    if (m_current_scene == m_scenes.end())
        m_current_scene = m_scenes.begin();
}

////////////////////////////////////////////////////////////
void ksApplication::pauseSequence()
{
    m_scene_paused = true;
}

////////////////////////////////////////////////////////////
void ksApplication::rotateWorldLeft(int amount)
{
    m_world.moveCamera(-amount, 0, 0);

    if (m_light_system != nullptr)
        m_light_system->updateWallShadows();
        
    m_entity_layer.updateScreenPosition();
}

////////////////////////////////////////////////////////////
void ksApplication::rotateWorldRight(int amount)
{
    m_world.moveCamera(amount, 0, 0);

    if (m_light_system != nullptr)
        m_light_system->updateWallShadows();
        
    m_entity_layer.updateScreenPosition();
}