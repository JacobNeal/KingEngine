#include "ksApplication.h"
#include "ksComplex.h"
#include "ksPathFinder.h"
#include "ksButton.h"
#include "ksContainer.h"
#include "ksLabel.h"

int main()
{
	ksApplication app("KingEngine", 800, 640);
	app.setEntityTilesheet("images/voltor_interior.png");

    app.insertText(53, 53, "title", "KingEngine", 30, ksColor(0, 0, 0, 200));
    app.insertText(50, 50, "title2", "KingEngine", 30, ksColor(255, 255, 255, 200));
    app.insertText(50, 85, "subtitle", "Particle Demo", 20, ksColor(0, 0, 0, 200));

    app.loadWorld(8, 4, 8, "maps/exterior");
    
    // World, Color, Location, size, num, velocity, and reach (time to live)
    // ksParticleEmitter emitter(app.getWorld(), sf::Color(0, 0, 255, 200), sf::Vector3f(0, 0, -192), 8, 20, 20, 60);
    ksParticleEmitter emitter(app.getWorld(), sf::Color(0, 0, 255, 200), sf::Vector3f(0, 0, -192), 8, 20, 20, 60);
    app.addParticleEmitter(&emitter);
    
    ksLightSystem lighting(app.getWorld(), sf::Color(0, 0, 0, 100), sf::Color(0, 0, 0, 255));
    lighting.addLight(sf::Vector3f(128, 128, 256), 256, sf::Color(255, 200, 0, 255));
    app.addLightSystem(&lighting);
    
    // Create a wrapper for a column of rows of buttons.
    ksContainer column(800, 640, ksAlign::COLUMN, ksColor(0, 0, 0, 0));
    app.addControl(&column);
    
    // Create the first row
    ksContainer row1(640, 96, ksAlign::ROW);
    
    ksButton button1(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    ksButton button2(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    ksButton button3(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    
    row1.addControl(&button1);
    row1.addControl(&button2);
    row1.addControl(&button3);
    
    // Create the second row
    ksContainer row2(640, 96, ksAlign::ROW);
    
    ksButton button4(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    ksButton button5(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    ksButton button6(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    
    row2.addControl(&button4);
    row2.addControl(&button5);
    row2.addControl(&button6);
    
    // Create the third row
    ksContainer row3(640, 96, ksAlign::ROW);
    
    ksButton button7(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    ksButton button8(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    ksButton button9(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    
    row3.addControl(&button7);
    row3.addControl(&button8);
    row3.addControl(&button9);
    
    // Add the rows to the column.
    column.addControl(&row1);
    column.addControl(&row2);
    column.addControl(&row3);

    ksPathFinder path_finder(app.getWorld());
    
    std::vector<ksComplex *> entity_list;
    int entity_num = 0;

    int scenario_mode = 0;

    int emitter_x = 400;
    int emitter_z = 128;
    
    // Run the app without a main loop
    //app.run();

    while (app.isOpen())
    {
        if (button1.isPressed())
        {
            button1.setText("Clicked.");
        }
    }

	return 0;
}
