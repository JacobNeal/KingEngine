#include "ksApplication.h"
#include "ksComplex.h"
#include "ksPathFinder.h"
#include "ksButton.h"
#include "ksContainer.h"
#include "ksTransition.h"
#include "ksScene.h"
#include "ksAudioTrack.h"
#include "ksImageControl.h"
#include <string>
#include <vector>
#include <iostream>

int main()
{
	ksApplication app("KingEngine", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
	app.setEntityTilesheet("images/voltor_interior2.png");

    //app.loadWorld(800, 400, 800, 4, 8, 8, "maps/exterior");
    app.loadWorldDemo();
    
    // World, Color, Location, size, num, velocity, and reach (time to live)
    // ksParticleEmitter emitter(app.getWorld(), sf::Color(0, 0, 255, 200), sf::Vector3f(0, 0, -192), 8, 20, 20, 60);
    ksParticleEmitter emitter(app.getWorld(), sf::Color(0, 0, 255, 200), sf::Vector3f(0, 0, -600), 8, 20, 20, 60);
    app.addParticleEmitter(&emitter);
    
    // Sunny day
    ksLightSystem lighting(app.getWorld(), sf::Color(0, 0, 0, 100), sf::Color(0, 0, 0, 255));
    lighting.addLight(sf::Vector3f(128, 128, 0), 256, sf::Color(255, 200, 0, 255));
    
    // Nightime
    // ksLightSystem lighting(app.getWorld(), sf::Color(0, 0, 255, 120), sf::Color(0, 0, 255, 60));
    // //lighting.addLight(sf::Vector3f(128, 128, 800), 256, sf::Color(255, 255, 200, 255));
    app.addLightSystem(&lighting);
    
    // Create a wrapper for a column of rows of buttons.
    ksContainer background(800, 400, ksAlign::CENTER, ksColor(255, 255, 255, 255), 0);
    app.addControl(&background);
    
    ksContainer container_foreground(800, 400, ksAlign::CENTER, ksColor(255, 255, 255, 0), 0);
    app.addControl(&container_foreground);
    
    ksImageControl title("images/KingEngineLogo.png", 14, 40, 771, 320);
    
    ksButton btn_fore(app.getFont(), "Something", 100, 35);
    container_foreground.addControl(&title);
    
    double container_opacity = 1.0;
    
    // Create the directions message.
    ksContainer container_message(480, 128, ksAlign::COLUMN, ksColor(0, 0, 0, 120), 300, 20);
    app.addControl(&container_message);
    
    ksLabel lbl_message(app.getFont(), "Welcome to this KingEngine demonstration!", 0, 0);
    ksLabel lbl_message2(app.getFont(), "These angry villagers are chasing after the player.", 0, 0);
    ksLabel lbl_message3(app.getFont(), "Move around using WASD.", 0, 0);
    ksButton btn_accept(app.getFont(), "Ok", 96, 32);
    container_message.addControl(&lbl_message);
    container_message.addControl(&lbl_message2);
    container_message.addControl(&lbl_message3);
    container_message.addControl(&btn_accept);
    container_message.setVisibility(false);
    
    container_message.setPosition(0, 0);
    
    double executive_diagram_opacity = 0.0;

    ksPathFinder path_finder(app.getWorld());

    int emitter_x = 400;
    int emitter_z = 400;
    
    ksAudioTrack track("audio/a_theme_among_themes.ogg", 120, 100);
    bool transitioning = false;
    
    double title_opacity = 0.0;
    double sun_z_position = 0.0;
    
    ksScene<double> title_fade_in;
    title_fade_in.addTransition(ksTransition<double>(&title_opacity, 1.0, 120));
    
    ksScene<double> title_pause;
    title_pause.addTransition(ksTransition<double>(&title_opacity, 1.0, 240));
    
    ksScene<double> title_fade_out;
    title_fade_out.addTransition(ksTransition<double>(&title_opacity, 0.0, 120));
    title_fade_out.addTransition(ksTransition<double>(&container_opacity, 0.0, 120));
    title_fade_out.addTransition(ksTransition<double>(&sun_z_position, 801.0, 150));

    app.addScene(&title_fade_in);
    app.addScene(&title_pause);
    app.addScene(&title_fade_out);
    
    bool sequence_paused = false;
    
    ksEntity tree(app.getWorld(), 600, 0, 800, 2, 4, 18);
    app.addEntity(&tree);
    
    // ksComplex ent(&path_finder, app.getWorld(), 400, 200, 32, 1, 2, 10);
    ksComplex ent(&path_finder, app.getWorld(), 400, 200, 32, 2, 2, 30);
    app.addEntity(&ent);
    ent.setAnimationLower(27);
    ent.setAnimationUpper(29);
    ent.setAnimationDelay(30);
    ent.toggleBehavior();
    
    // Add angry villagers.
    std::vector<ksComplex *> entity_list;
    int entity_num = 0;
    
    for (int count = 0; count < 4; ++count)
    {
        entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), emitter_x, 200, emitter_z, 2, 2, 66));
        entity_list[entity_num]->setAnimationLower(66);
        entity_list[entity_num]->setAnimationUpper(71);
        entity_list[entity_num]->setAnimationDelay(5);
        app.addEntity(entity_list[entity_num++]);
    }
    
    for (int count = 0; count < entity_num; ++count)
    {
        for (int count2 = 0; count2 < entity_num; ++count2)
        {
            entity_list[count]->addToGroup(entity_list[count2]);
            entity_list[count]->arrive(ksVector2D(ent.X(), ent.Z()));
        }
        entity_list[count]->group();
        entity_list[count]->avoidObstacles();
    }
    
    // Flowers
    std::vector<ksEntity *> flower_list;
    int flower_num = 0;
    
    for (int col = 0; col < app.getWorld()->getMapCol(); ++col)
    {
        for (int depth = 0; depth < app.getWorld()->getMapDepth(); ++depth)
        {
            flower_list.push_back(new ksEntity(app.getWorld(), col * 100, 300, depth * 100, 1, 1, 31));
            flower_list[flower_num]->setAnimationLower(31);
            flower_list[flower_num]->setAnimationUpper(32);
            flower_list[flower_num]->setAnimationDelay(30);
            app.addEntity(flower_list[flower_num++]);
        }
    }
    
    // Run the app without a main loop
    //app.run();

    while (app.isOpen())
    {
        if (app.getKeyDown(ksKey::Space))
        {
            // Start or pause the sequence of scenes.
            if (sequence_paused)
                app.startSequence();
            else
                app.pauseSequence();
            
            // Toggle the sequence paused boolean.
            sequence_paused = !sequence_paused;
        }
        else if (app.getKeyDown(ksKey::Return))
            container_message.setVisibility(false);
        else if (app.getKeyDown(ksKey::Left))
            app.rotateWorldLeft(20);
        else if (app.getKeyDown(ksKey::Right))
            app.rotateWorldRight(20);
        
        // Set default animation for player
        ent.setAnimationLower(27);
        ent.setAnimationUpper(29);
        ent.setAnimationDelay(30);
        
        if (app.getKeyDown(ksKey::W))
        {
            if ((ent.Z() + 50) < app.getWorld()->getDepth())
                ent.moveEntity(0, 0, 50);
            
            ent.setAnimationLower(37);
            ent.setAnimationUpper(42);
            ent.setAnimationDelay(5);
        }
        if (app.getKeyDown(ksKey::S))
        {
            if ((ent.Z() - 50) > 0)
                ent.moveEntity(0, 0, -50);
                
            ent.setAnimationLower(30);
            ent.setAnimationUpper(35);
            ent.setAnimationDelay(5);
        }
        if (app.getKeyDown(ksKey::A))
        {
            if ((ent.X() - 25) > 0)
                ent.moveEntity(-25, 0, 0);
                
            ent.setAnimationLower(55);
            ent.setAnimationUpper(60);
            ent.setAnimationDelay(5);
        }
        if (app.getKeyDown(ksKey::D))
        {
            if ((ent.X() + 25) < app.getWorld()->getWidth())
                ent.moveEntity(25, 0, 0);
                
            ent.setAnimationLower(46);
            ent.setAnimationUpper(51);
            ent.setAnimationDelay(5);
        }
        
        for (int count = 0; count < entity_num; ++count)
        {
            entity_list[count]->arrive(ksVector2D(ent.X(), ent.Z()));
        }
        
        if (title_fade_in.isDone() && !transitioning)
        {
            track.transitionTrack("audio/the_honeymoon.ogg");
            transitioning = true;
        }
        
        track.update();
        
        if (title_pause.isDone() && !title_fade_out.isDone())
        {
            // Get the sun's position.
            ksVector3f temp = lighting.getLightPosition(0);
            
            // Update the sun's z coordinate.
            temp.z = sun_z_position;
            
            // Update the position of the light source.
            lighting.setLightPosition(0, temp.x, temp.y, temp.z);
            //lighting.addLight(sf::Vector3f(128, 128, sun_z_position), 256, sf::Color(255, 200, 0, 255));
        }
        
        if (title_fade_out.isDone())
        {
            container_message.setVisibility(true);
            //executive_diagram.setVisibility(true);
        }
        
        //app.setTextColor("subtitle", ksColor(0, 0, 0, title_alpha));
        background.setOpacity(container_opacity);
        container_foreground.setOpacity(title_opacity);
    }

	return 0;
}
