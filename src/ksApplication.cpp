/********************************************************
* Class:			ksApplication
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksApplication.cpp
********************************************************/

#include "ksApplication.h"

/*********************************************************
*   ksApplication
*
*   Initialize the application to the default screen or 
*   desktop size, and the title to KingEngine.
*********************************************************/
ksApplication::ksApplication()
	: m_window(sf::VideoMode::getDesktopMode(), "KingEngine"),
	m_entity_layer("images/default.png"), m_control_layer("images/portal_obj.png"),
    m_mouse_released(false)
{
	m_window.setFramerateLimit(FRAMERATE);
}

/*********************************************************
*   ksApplication
*
*   Initialize the application to the width, height and
*   application title passed.
*********************************************************/
ksApplication::ksApplication(char * app_title, int app_width, int app_height)
	: m_window(sf::VideoMode(app_width, app_height, 32), app_title),
	m_entity_layer("images/default.png"), m_control_layer("images/portal_obj.png"),
    m_mouse_released(false)
{
	m_window.setFramerateLimit(FRAMERATE);
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
    m_window.draw(m_world);
	m_entity_layer.drawLayer(m_window);
	m_control_layer.drawLayer(m_window);
    m_window.display();

	m_entity_layer.depressEntity();
    m_control_layer.depressControl();

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
            else
            {
                if (m_entity_layer.pressEntity(sf::Mouse::getPosition(m_window).x,
				    sf::Mouse::getPosition(m_window).y))
			    {
				    m_mouse_released = false;
			    }
            }
		}
		else
			m_mouse_released = false;
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

void ksApplication::loadWorld(int width, int height, int depth)
{
    m_world.load(width, height, depth);
}

/*********************************************************
*   setEntityTilesheet
*
*   Set the tilesheet for the base game entity layer.
*********************************************************/
void ksApplication::setEntityTilesheet(char * tilesheet)
{
	m_entity_layer.setTilesheet(tilesheet);
}
