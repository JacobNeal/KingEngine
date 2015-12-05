#include "Regime.h"

Regime::Regime(int argc, char * argv[])
	: ksRenderWindow(argc, argv),
	m_layer("portal_obj.png"),
	m_text("consolas_font_map.png", "Hello World!", 200, 200, ksColor(255, 0, 0, 255)),
	m_map(&m_debugText, "voltor.png", "voltor", 75, 40),
	m_light(ksColor(0, 0, 255, 100), ksColor(255, 255, 255, 0), 360, 10),
	m_weather(ksColor(0, 0, 255, 80), ksVector(-50, -50), 6, 15, 20, 70),
	m_log("consolas_font_map.png"),
	m_player("blacksmith.png", ksRect(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2, 64, 64))
{
	m_map.load("voltor.png", "voltor", 75, 40);

	m_log.setLogPosition(50, 50);

	play();
}

void Regime::play()
{
	// Add a key binding to the window for the 'W' key.
	addKeyBinding(ksKeyW);
	addKeyBinding(ksKeyA);
	addKeyBinding(ksKeyS);
	addKeyBinding(ksKeyD);

	m_layer.setTileSheet("voltor.png");
	m_layer.addObject(ksAbstract(ksRect(400, 400, 32, 32), 0));
	m_layer.addObject(ksAbstract(ksRect(432, 400, 32, 32), 1));
	m_layer.addObject(ksAbstract(ksRect(432, 432, 32, 32), 2));
	m_layer.addObject(ksAbstract(ksRect(400, 432, 32, 32), 3));
	m_layer.animate(0, 0, 35, 5);
	m_layer.animate(1, 1, 35, 5);
	m_layer.animate(2, 2, 35, 5);
	m_layer.animate(3, 3, 35, 5);

	// Add a light
	m_light.clear();
	m_light.resizeMap(75, 40);
	m_light.set(0, ksColor(0, 0, 255, 120), ksColor(255, 255, 0, 60), 240, 10);

	m_light.add(368, 272, 64, ksColor(255, 255, 0, 80), ksColor(255, 255, 0, 60));

	// Add text to the text log.
	m_log.insert("Welcome to KingEngine v1.0", ksColor(255, 255, 255, 255));

	while (isOpen())
	{
		// Main game logic.
		m_player.moveObject(getMapView(), m_map);
		boundCamera(m_player.getPosition().x, m_player.getPosition().y, 75, 40);

		// Updates the lighting effects.
		m_light.update();
		m_weather.update();
		m_log.update(60);
	}
}

void Regime::draw()
{
	//m_layer.drawLayer(*this);
	drawObject(&m_text);
	drawObject(&m_map);
	//drawObject(&m_layer);
	m_layer.drawLayer(*this);
	drawObject(&m_player);
	drawObject(&m_light);
	drawObject(&m_weather);
	//drawObject(&m_log);
	m_log.drawLog(*this);
}

void Regime::handleInput()
{
	if (getInput(0))
	{
		m_player.changeVelY(-WALK_VELOCITY);
	}
	if (getInput(1))
	{
		m_player.changeVelX(-WALK_VELOCITY);
	}
	if (getInput(2))
	{
		m_player.changeVelY(WALK_VELOCITY);
	}
	if (getInput(3))
	{
		m_player.changeVelX(WALK_VELOCITY);
	}

	// Touch Controls
	if (isTouchDown())
	{
		if (getTouchPosition().x < m_player.getPosition().x)
			m_player.changeVelX(-WALK_VELOCITY);
		else if (getTouchPosition().x > m_player.getPosition().x)
			m_player.changeVelX(WALK_VELOCITY);

		if (getTouchPosition().y < m_player.getPosition().y)
			m_player.changeVelY(-WALK_VELOCITY);
		else if (getTouchPosition().y > m_player.getPosition().y)
			m_player.changeVelY(WALK_VELOCITY);

		std::string temp = "P: " + std::to_string(m_player.getPosition().x) + ", " + std::to_string(m_player.getPosition().y) + " T: " + std::to_string(getTouchPosition().x) + ", " + std::to_string(getTouchPosition().y);

		m_log.insert(temp);
	}
}