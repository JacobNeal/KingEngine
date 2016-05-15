/********************************************************
* Class:			ksApplication
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksApplication.cpp
********************************************************/

#include "ksApplication.h"
#include <iostream>

/*********************************************************
*   ksApplication
*
*   Initialize the application to the default screen or 
*   desktop size, and the title to KingEngine.
*********************************************************/
ksApplication::ksApplication()
	: m_window(sf::VideoMode::getDesktopMode(), "KingEngine"),
	m_world("images/voltor_interior.png"), m_camera_depth(0), 
    m_entity_layer(&m_world, "images/default.png"), 
    m_control_layer("images/portal_obj.png"), m_mouse_released(false),
    m_emitter(nullptr), m_light_system(nullptr), m_scene_paused(false)
{
	m_window.setFramerateLimit(FRAMERATE);
    m_font = new sf::Font;
    m_font->loadFromFile("images/minecraft.ttf");
    m_gui_view = m_window.getDefaultView();
    m_current_scene = m_scenes.begin();
}

/*********************************************************
*   ksApplication
*
*   Initialize the application to the width, height and
*   application title passed.
*********************************************************/
ksApplication::ksApplication(std::string app_title, int app_width, int app_height)
	: m_window(sf::VideoMode(app_width, app_height, 32), app_title.c_str()),
	m_world("images/voltor_interior.png"), m_camera_depth(0), 
    m_entity_layer(&m_world, "images/default.png"), 
    m_control_layer("images/portal_obj.png"), m_mouse_released(false),
    m_emitter(nullptr), m_light_system(nullptr), m_scene_paused(false)
{
	m_window.setFramerateLimit(FRAMERATE);
    m_font = new sf::Font;
    m_font->loadFromFile("images/minecraft.ttf");
    m_gui_view = m_window.getDefaultView();
    m_current_scene = m_scenes.begin();
}

/*********************************************************
*   isOpen
*
*   Return whether the application is still open.
*   (This can be useful for creating a main game loop)
*********************************************************/
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
    m_window.setView(m_gui_view);
    
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
    //m_world.setPosition(400 - (((m_world.getDepth() * 2) + m_world.getWidth() * TILE_WIDTH) / 2),
    //                    320 - (((m_world.getDepth() * 2) + m_world.getHeight() * TILE_HEIGHT) / 2));

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

            if (m_evt.key.code == sf::Keyboard::Key::Up)
            {
                // if (m_emitter != nullptr)
                //     m_emitter->moveEmitter(0, 0, 5);
                m_world.moveCamera(0, 0, 1);
                
                if (m_light_system != nullptr)
                    m_light_system->updateWallShadows();
            }
            else if (m_evt.key.code == sf::Keyboard::Key::Down)
            {
                // if (m_emitter != nullptr)
                //     m_emitter->moveEmitter(0, 0, -5);
                m_world.moveCamera(0, 0, -1);
                
                if (m_light_system != nullptr)
                    m_light_system->updateWallShadows();
            }
            else if (m_evt.key.code == sf::Keyboard::Key::Right)
            {
                // if (m_emitter != nullptr)
                //     m_emitter->rotate(1.0);
                //m_world_view.rotate(1.0);
                m_world.moveCamera(20, 0, 0);
                
                if (m_light_system != nullptr)
                    m_light_system->updateWallShadows();
            }
            else if (m_evt.key.code == sf::Keyboard::Key::Left)
            {
                // if (m_emitter != nullptr)
                //     m_emitter->rotate(-1.0);
                //m_world_view.rotate(-1.0);
                m_world.moveCamera(-20, 0, 0);
                
                if (m_light_system != nullptr)
                    m_light_system->updateWallShadows();
            }
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
            // Center the world view
            //m_world_view = sf::View(sf::FloatRect(0.f, 0.f, 800, 640));
            //m_world_view.setCenter(sf::Vector2f(m_evt.size.width, m_evt.size.height) / 2.0f);
            //m_world_view.setSize(sf::Vector2f(m_evt.size.width, m_evt.size.height));
            //m_world.resizeWorld(m_evt.size.width, m_evt.size.height);
            
            double heightProportionateToWidth = (double) m_world.getHeight() / m_world.getWidth();
    
            double new_width = m_evt.size.width;
            double new_height = heightProportionateToWidth * new_width;
            float viewport_height = (float) 1.f - ((m_evt.size.height - new_height) / m_evt.size.height);
            float viewport_top = (float) ((m_evt.size.height - new_height) / 2) / m_evt.size.height;
            
            //m_world_view.reset(sf::FloatRect(0, 0, width, height));
            m_world_view.setViewport(sf::FloatRect(0.0f, viewport_top, 1.f, viewport_height));
            
            // Resize the GUI view
            m_gui_view.setCenter(sf::Vector2f(m_evt.size.width, m_evt.size.height) / 2.0f);
            m_gui_view.setSize(sf::Vector2f(m_evt.size.width, m_evt.size.height));
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

/*********************************************************
*   addInput
*
*   Add a key input to be checked for if it's pressed down
*	on each cycle of the main game loop.
*********************************************************/
void ksApplication::addInput(ksKey::Key key)
{
	m_key_down[key] = false;
}

/*********************************************************
*   getKeyInput
*
*   Return whether the passed key is down or not.
*********************************************************/
bool ksApplication::getKeyDown(ksKey::Key key)
{
	return m_key_down[key];
}

/*********************************************************
*   getMouseDown
*
*   Return whether or not the left mouse button is clicked
*   or a finger is pressed down on a touch screen device.
*********************************************************/
bool ksApplication::getMouseDown()
{
	return m_mouse_released;
}

/*********************************************************
*   getMousePosition
*
*   Return the position in vector form of the mouse
*   or touch.
*********************************************************/
ksVector2D ksApplication::getMousePosition()
{
	return ksVector2D(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y);
}

/*********************************************************
*   getMouseX
*
*   Return the x position of the mouse or touch.
*********************************************************/
double ksApplication::getMouseX()
{
	return (double)sf::Mouse::getPosition(m_window).x;
}

/*********************************************************
*   getMouseY
*
*   Return the y position of the mouse or touch.
*********************************************************/
double ksApplication::getMouseY()
{
	return (double)sf::Mouse::getPosition(m_window).y;
}

/*********************************************************
*   addEntity
*
*   Add an entity to the base game entity layer.
*********************************************************/
void ksApplication::addEntity(ksEntity * entity)
{
	m_entity_layer.addEntity(entity);
}

/*********************************************************
*   animateEntity
*
*   Set the lower and upper tile boundaries of animation
*   for a base game entity.
*********************************************************/
void ksApplication::animateEntity(int entity_number, int lower_tile, int upper_tile, int frame_delay)
{
	m_entity_layer.animate(entity_number, lower_tile, upper_tile, frame_delay);
}

/*********************************************************
*   addControl
*
*   Add a control to the base game control layer.
*********************************************************/
void ksApplication::addControl(ksControl * control)
{
    m_control_layer.addControl(control);
}

/*********************************************************
*   loadWorld
*
*   Loads the perspective game world using the passed
*   (width x height x depth) and the path to the map
*   files.
*
*   * This method will also center the world view.
*********************************************************/
void ksApplication::loadWorld(int width, int height, int depth, std::string name)
{
    m_world.load(width, height, depth, name);
    
    m_camera_depth = depth;
    
    double heightProportionateToWidth = (double) height / width;
    
    double new_width = m_window.getSize().x;
    double new_height = heightProportionateToWidth * new_width;
    float viewport_height = (float) 1.f - ((m_window.getSize().y - new_height) / m_window.getSize().y);
    float viewport_top = (float) ((m_window.getSize().y - new_height) / 2) / m_window.getSize().y;
    
    m_world_view.reset(sf::FloatRect(0, 0, width, height));
    m_world_view.setViewport(sf::FloatRect(0.0f, viewport_top, 1.f, viewport_height));
}

/*********************************************************
*   increaseCameraDepth
*
*   Increases the depth of the camera inward toward the
*   front wall of the game world.
*********************************************************/
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

/*********************************************************
*   decreaseCameraDepth
*
*   Decreases the depth of the camera backward away from
*   the front wall of the game world.
*********************************************************/
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

void ksApplication::toggleWorldLighting()
{
    m_world.toggleLighting();
}

void ksApplication::toggleWorld3D()
{
    m_world.toggle3D();
}

void ksApplication::insertText(double x, double y, std::string name, 
                               std::string text, int size, ksColor color)
{
    m_text_layer.insert(std::pair<std::string, sf::Text>(name, sf::Text(text, *m_font)));
    m_text_layer[name].setPosition(x, y);
    m_text_layer[name].setCharacterSize(size);
    m_text_layer[name].setColor(color);
}

void ksApplication::setText(std::string name, std::string text)
{
    m_text_layer[name].setString(text);
}

void ksApplication::setTextColor(std::string name, ksColor color)
{
    m_text_layer[name].setColor(color);
}

void ksApplication::clearEntities()
{
    m_entity_layer.purge();
}

/*********************************************************
*   getCameraDelta
*
*   Returns the difference between the world's depth
*   and the camera's depth.
*********************************************************/
int ksApplication::getCameraDelta()
{
    return m_camera_depth;
}

/*********************************************************
*   getWorld
*
*   Returns a pointer to a world object that contains
*   info about different events and coliidable tiles
*   in the world.
*********************************************************/
ksWorld * ksApplication::getWorld()
{
    return &m_world;
}

/*********************************************************
*   getSmallestOrientation
*
*   Returns the smallest orientation of the window, based
*   on the width and height.
*********************************************************/
int ksApplication::getSmallestOrientation()
{
    return m_window.getSize().x < m_window.getSize().y ?
        (int) m_window.getSize().x : (int) m_window.getSize().y;
}

/*********************************************************
*   getFont
*
*   Returns a reference to the font used in the application.
*********************************************************/
sf::Font * ksApplication::getFont()
{
    return m_font;
}

/*********************************************************
*   setEntityTilesheet
*
*   Set the tilesheet for the base game entity layer.
*********************************************************/
void ksApplication::setEntityTilesheet(std::string tilesheet)
{
	m_entity_layer.setTilesheet(tilesheet);
}

/*********************************************************
*   setCameraDelta
*
*   Changing the camera delta changes the distance the
*   camera is from the front wall. This gives the effect
*   of zomming in, or out on the world. Can be useful
*   for first person perspectives.
*********************************************************/
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

/*********************************************************
*   addParticleEmitter
*
*   Add a reference to a particle emitter so that it can
*   be drawn in the application window.
*********************************************************/
void ksApplication::addParticleEmitter(ksParticleEmitter * emitter)
{
    m_emitter = emitter;
}

/*********************************************************
*   addLightSystem
*
*   Add a reference to a light system so that it can be
*   drawn in the application window.
*********************************************************/
void ksApplication::addLightSystem(ksLightSystem * system)
{
    m_light_system = system;
}

/*********************************************************
*   run
*
*   Allow the developer to just run the application without
*   creating a main loop in external code.
*********************************************************/
void ksApplication::run()
{
    while (isOpen()) ;
}

void ksApplication::addScene(ksScene<double> * scene)
{
    m_scenes.push_back(scene);
    m_current_scene = m_scenes.begin();
}

void ksApplication::startSequence()
{
    m_scene_paused = false;
    
    if (m_current_scene == m_scenes.end())
        m_current_scene = m_scenes.begin();
}

void ksApplication::pauseSequence()
{
    m_scene_paused = true;
}