/*********************************************
* Class: ksRenderWindow		-	for SFML
*
* Purpose:
*	This class is part of the base elements
*	of the engine, so this class needs to be
*	changed in the event of future ports of
*	KingEngine.
*
*********************************************/

#ifndef KS_RENDER_WINDOW_H
#define KS_RENDER_WINDOW_H

// MOBILE_BUILD for mobile or
// DESKTOP_BUILD for all else
#define WINDOWS_BUILD

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "ksDrawable.h"
#include "ksPlayer.h"

typedef void(*ksEvent)();

#define ksKey  sf::Keyboard::Key
#define ksKeyW sf::Keyboard::W
#define ksKeyA sf::Keyboard::A
#define ksKeyS sf::Keyboard::S
#define ksKeyD sf::Keyboard::D

class ksRenderWindow
{
public:
	ksRenderWindow(int argc, char * argv[]);
	ksRenderWindow(char * title, int width, int height);
	bool isOpen();

	// Add keybindings that call the passed function when keys are pressed.
	void addKeyBinding(ksKey key);
	bool getInput(int index);

	//void setDrawFunction(void(*draw)());

	void drawObject(ksDrawable * object);
	void drawObject(sf::Sprite * object);
	void drawObject(sf::Text * object);
	void drawObject(ksPlayer * object);

	sf::View & getMapView();
	void boundCamera(double x, double y, double map_width, double map_height);

	virtual void draw() = 0;
	virtual void handleInput() = 0;

	bool isTouchDown();
	sf::Vector2i getTouchPosition();

private:
	sf::RenderWindow	m_app;
	sf::Event *			m_evt;
	sf::View			m_map_view;
	bool				m_isOpen;

	std::vector<sf::Keyboard::Key> m_keys;
	std::vector<bool>			   m_key_down;
};

#endif