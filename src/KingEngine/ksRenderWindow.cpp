/*********************************************
* Class: ksDrawableLayer	-	for SFML
*
* Purpose:
*	This class is part of the base elements
*	of the engine, so this class needs to be
*	changed in the event of future ports of
*	KingEngine.
*
*********************************************/

#include "ksRenderWindow.h"

/***************************************************
* Entry:	User wants to utilize the renderable
*			window class.
* Exit:		The renderable window is created and
*			opened.
* Purpose:	To create a renderable window for use
*			with the other components of KingEngine.
*
*			This is specific to the SFML / Windows
*			environment and is limited to the main
*			desktop platforms.
****************************************************/

ksRenderWindow::ksRenderWindow(int argc, char * argv[])
	: m_app(sf::VideoMode::getDesktopMode(), "KingEngine")
{
	m_isOpen = true;
	m_app.setFramerateLimit(30);
	m_map_view = m_app.getDefaultView();
}

/***************************************************
* Entry:	User wants to utilize the renderable
*			window class.
* Exit:		The renderable window is created and
*			opened based on the passed parameters
*			for the window title, width and height.
* Purpose:	To create a renderable window for use
*			with the other components of KingEngine.
*
*			This is specific to the SFML / Windows
*			environment and is limited to the main
*			desktop platforms.
****************************************************/

ksRenderWindow::ksRenderWindow(char * title, int width, int height)
	: m_app(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close)
{
	m_isOpen = true;
	m_app.setFramerateLimit(30);
	m_map_view = m_app.getDefaultView();
}

/***************************************************
* Entry:	The renderable window has been created.
* Exit:		The appropriate event handlers are
*			called based upon the key bindings and
*			the window returns either opened or
*			closed.
* Purpose:	To execute a main game loop in any
*			program that is instantiating this class.
*			EX:
*				ksRenderWindow app;
*
*				while (app.isOpen())
*				{
*					//Do something
*				}
*
*			This is specific to the SFML / Windows
*			environment and is limited to the main
*			desktop platforms.
****************************************************/

bool ksRenderWindow::isOpen()
{
	m_isOpen = m_app.isOpen();

	if (m_isOpen)
	{
		// Clear and display the window ahead of time.
		m_app.clear();

		// Call virtual method for draw.
		draw();

		m_app.display();

		sf::Event evt;
		m_evt = &evt;

		while (m_app.pollEvent(evt))
		{
			// Provide a way to exit the application.
			if (evt.type == sf::Event::Closed)
				m_app.close();

			if (evt.type == sf::Event::KeyPressed)
			{
				for (int count = 0; count < m_keys.size(); count++)
					if (evt.key.code == m_keys[count])
						m_key_down[count] = true;
			}

			if (evt.type == sf::Event::KeyReleased)
			{
				for (int count = 0; count < m_keys.size(); count++)
					if (evt.key.code == m_keys[count])
						m_key_down[count] = false;
			}

			if (evt.type == sf::Event::Resized)
			{
				m_map_view.setSize(evt.size.width, evt.size.height);
				m_map_view.setCenter(evt.size.width / 2, evt.size.height / 2);
				m_app.setView(m_map_view);
			}
		}

		handleInput();
	}

	return m_isOpen;
}

/***************************************************
* Entry:	The renderable window has been created.
* Exit:		A keybinding is created and points to
*			the passed function parameter.
* Purpose:	To bind a function or event to a specific
*			key on the keyboard.
*
*			This is specific to the SFML / Windows
*			environment and is limited to the main
*			desktop platforms.
****************************************************/

void ksRenderWindow::addKeyBinding(ksKey key)
{
	m_keys.push_back(key);
	m_key_down.push_back(false);
}

bool ksRenderWindow::getInput(int index)
{
	return m_key_down[index];
}

void ksRenderWindow::drawObject(ksDrawable * object)
{
	m_app.draw(*object);
}

void ksRenderWindow::drawObject(sf::Sprite * object)
{
	m_app.draw(*object);
}

void ksRenderWindow::drawObject(sf::Text * object)
{
	m_app.draw(*object);
}

void ksRenderWindow::drawObject(ksPlayer * object)
{
	m_app.draw(*object);
}

sf::View & ksRenderWindow::getMapView()
{
	return m_map_view;
}

void ksRenderWindow::boundCamera(double x, double y, double map_width, double map_height)
{
	// Center the camera
	m_map_view.setCenter(x, y);

	// Bound the camera
	if (m_map_view.getCenter().x - (m_map_view.getSize().x / 2) < 0)
		m_map_view.setCenter(m_map_view.getSize().x / 2, m_map_view.getCenter().y);

	if (m_map_view.getCenter().y - (m_map_view.getSize().y / 2) < 0)
		m_map_view.setCenter(m_map_view.getCenter().x, m_map_view.getSize().y / 2);

	if (m_map_view.getCenter().x + (m_map_view.getSize().x / 2) > (map_width * TILE_WIDTH))
		m_map_view.setCenter((map_width * TILE_WIDTH) - (m_map_view.getSize().x / 2), m_map_view.getCenter().y);

	if (m_map_view.getCenter().y + (m_map_view.getSize().y / 2) > (map_height * TILE_HEIGHT))
		m_map_view.setCenter(m_map_view.getCenter().x, (map_height * TILE_HEIGHT) - (m_map_view.getSize().y / 2));
}

bool ksRenderWindow::isTouchDown()
{
	bool temp = false;

#ifdef MOBILE_BUILD
	temp = sf::Touch::isDown(0);
#endif

	return temp;
}

sf::Vector2i ksRenderWindow::getTouchPosition()
{
	sf::Vector2i temp;

#ifdef MOBILE_BUILD
	temp = sf::Touch::getPosition(0);
#endif

	return temp;
}