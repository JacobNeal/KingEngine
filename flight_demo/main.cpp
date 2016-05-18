#include <ksApplication.h>
#include "ksComplex.h"
#include "ksPathFinder.h"
#include "ksButton.h"
#include "ksContainer.h"
#include "ksScene.h"
#include "ksAudioTrack.h"
#include "ksImageControl.h"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

int main()
{
	ksApplication app("FlightDemo", 800, 640);
	app.setEntityTilesheet("images/flight_demo.png");

    app.insertText(53, 53, "title", "FlightDemo", 30, ksColor(0, 0, 0, 200));
    app.insertText(50, 50, "title2", "FlightDemo", 30, ksColor(255, 255, 255, 200));
    app.insertText(650, 53, "health", "Health: 100", 20, ksColor(255, 255, 255, 200));
    
    // Keep track of the player ship's health
    int health = 100;

    // Load the space world.
    app.loadWorld(800, 400, 1600, 4, 8, 16, "maps/space");
    
    ksLightSystem lighting(app.getWorld(), sf::Color(255, 0, 0, 100), sf::Color(0, 0, 255, 0));
    app.addLightSystem(&lighting);
    
    // Create a wrapper for a column of rows of buttons.
    ksContainer column(800, 400, ksAlign::COLUMN, ksColor(0, 0, 0, 255), 0);
    app.addControl(&column);
    
    double container_alpha = 255.0;

    ksPathFinder path_finder(app.getWorld());
    
    ksAudioTrack track("audio/sorrow.ogg", 120, 100);
    
    ksImageControl cockpit("images/cockpit.png", 0, 300, 800, 100);
    app.addControl(&cockpit);
    
    ksImageControl target("images/target.png", 384, 184, 32, 32);
    app.addControl(&target);
    
    double game_over_opacity = 0.0;
    
    double title_alpha = 0.0;
    
    ksScene<double> title_fade_in;
    title_fade_in.addTransition(ksTransition<double>(&title_alpha, 200.0, 120));
    
    ksScene<double> title_fade_out;
    title_fade_out.addTransition(ksTransition<double>(&title_alpha, 0.0, 120));
    title_fade_out.addTransition(ksTransition<double>(&container_alpha, 0.0, 120));

    app.addScene(&title_fade_in);
    app.addScene(&title_fade_out);
    
    // Add enemy ships.
    std::vector<ksComplex *> entity_list;
    int entity_num = 0;
    
    for (int count = 0; count < 8; ++count)
    {
        entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), 400, 150, 1600, 2, 2, 1));
        app.addEntity(entity_list[entity_num++]);
    }
    
    for (int count = 0; count < entity_num; ++count)
    {
        for (int count2 = 0; count2 < entity_num; ++count2)
        {
            entity_list[count]->addToGroup(entity_list[count2]);
            entity_list[count]->arrive(ksVector2D(400, 0));
        }
        entity_list[count]->group();
        entity_list[count]->avoidObstacles();
    }

    while (app.isOpen())
    {
        // Reset the light base color.   
        //lighting.setLightColor(ksColor(255, 0, 0, 0));
        
        // Shoot from the player ship
        if (app.getKeyDown(ksKey::Space))
        {
        }
        
        // Move the player ship left or right
        if (app.getKeyDown(ksKey::Left))
        {
            //app.getWorld()->setRotation(-5);
            //lighting.rotate(-5);
            app.rotateWorldLeft(20);
        }
            //app.rotateWorldLeft(20);
        else if (app.getKeyDown(ksKey::Right))
        {
            //app.getWorld()->setRotation(5);
            //lighting.rotate(5);
            app.rotateWorldRight(20);
        }
            //app.rotateWorldRight(20);
      
        for (int count = 0; count < entity_num; ++count)
        {
            entity_list[count]->arrive(ksVector2D(400, 0));
            
            if (entity_list[count]->Z() <= 0)
            {
                // Damage the player ship
                health--;
                
                // Move entity back
                entity_list[count]->moveEntity(0, 0, -1599);
                
                // Set light base color to red for damage.
                lighting.setLightColor(ksColor(255, 0, 0, 100));
            }   
        }
        
        if (title_fade_in.isDone())
            track.update();
        
        column.setColor(ksColor(0, 0, 0, container_alpha));
        
        if (health > 0)
            app.setText("health", "Health: " + std::to_string(health));
        else
            app.setText("health", "Game Over.");
    }

	return 0;
}
