#ifndef REGIME_H
#define REGIME_H

#include "ksWorld.hpp"
#include "ksPlayer.hpp"
#include <iostream>

class Regime : public ksRenderWindow
{
public:
	Regime(int argc, char * argv[]);

	// Override virtual methods from ksRenderWindow.
	void draw();
	void handleInput();

	// Main game loop of application.
	void play();

private:
	ksText              m_text;
	ksAbstractLayer     m_layer;
	ksMap               m_map;
	ksEffect            m_light;
	ksParticleEngine    m_weather;
	ksTextLog			m_log;
	ksPlayer			m_player;

	sf::Font			m_font;
	sf::Text			m_debugText;

	ksDrawable			m_test;
	//ksMenu				m_menu;
};

#endif