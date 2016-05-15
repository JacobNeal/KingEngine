#include "ksApplication.h"
#include "ksComplex.h"
#include "ksPathFinder.h"
#include "ksButton.h"
#include "ksContainer.h"
#include "ksTransition.h"
#include "ksScene.h"
#include "ksAudioTrack.h"
#include <string>
#include <vector>

int main()
{
	ksApplication app("KingEngine", 800, 640);
	app.setEntityTilesheet("images/voltor_interior2.png");

    app.insertText(53, 53, "title", "KingEngine", 30, ksColor(0, 0, 0, 200));
    app.insertText(50, 50, "title2", "KingEngine", 30, ksColor(255, 255, 255, 200));
    app.insertText(50, 85, "subtitle", "Particle Demo", 20, ksColor(0, 0, 0, 200));

    app.loadWorld(800, 400, 800, "maps/exterior");
    
    // World, Color, Location, size, num, velocity, and reach (time to live)
    // ksParticleEmitter emitter(app.getWorld(), sf::Color(0, 0, 255, 200), sf::Vector3f(0, 0, -192), 8, 20, 20, 60);
    ksParticleEmitter emitter(app.getWorld(), sf::Color(0, 0, 255, 200), sf::Vector3f(0, 0, -600), 8, 20, 20, 60);
    app.addParticleEmitter(&emitter);
    
    // Sunny day
    // ksLightSystem lighting(app.getWorld(), sf::Color(0, 0, 0, 100), sf::Color(0, 0, 0, 255));
    // lighting.addLight(sf::Vector3f(128, 128, 800), 256, sf::Color(255, 200, 0, 255));
    
    // Nightime
    ksLightSystem lighting(app.getWorld(), sf::Color(0, 0, 255, 120), sf::Color(0, 0, 255, 60));
    //lighting.addLight(sf::Vector3f(128, 128, 800), 256, sf::Color(255, 255, 200, 255));
    app.addLightSystem(&lighting);
    
    // Create a wrapper for a column of rows of buttons.
    ksContainer column(800, 640, ksAlign::COLUMN, ksColor(0, 0, 0, 0), 0);
    app.addControl(&column);
    
    double container_alpha = 255.0;
    
    // // Create the first row
    // ksContainer row1(640, 96, ksAlign::ROW);
    
    // ksButton button1(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    // ksButton button2(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    // ksButton button3(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    
    // row1.addControl(&button1);
    // row1.addControl(&button2);
    // row1.addControl(&button3);
    
    // // Create the second row
    // ksContainer row2(640, 96, ksAlign::ROW);
    
    // ksButton button4(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    // ksButton button5(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    // ksButton button6(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    
    // row2.addControl(&button4);
    // row2.addControl(&button5);
    // row2.addControl(&button6);
    
    // // Create the third row
    // ksContainer row3(640, 96, ksAlign::ROW);
    
    // ksButton button7(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    // ksButton button8(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    // ksButton button9(app.getFont(), "Click me", 96, 64, ksColor(30, 30, 30));
    
    // row3.addControl(&button7);
    // row3.addControl(&button8);
    // row3.addControl(&button9);
    
    // // Add the rows to the column.
    // column.addControl(&row1);
    // column.addControl(&row2);
    // column.addControl(&row3);

    ksPathFinder path_finder(app.getWorld());

    int emitter_x = 400;
    int emitter_z = 400;
    
    double alpha_value = 255.0;
    double alpha_value2 = 255.0;
    
    ksScene<double> scene;
    
    // 60 frames / (30 frames / sec) = 2 seconds
    scene.addTransition(ksTransition<double>(&alpha_value, 0, 30));
    scene.addTransition(ksTransition<double>(&alpha_value2, 0, 60));
    
    double alpha_value3 = 255.0;
    double alpha_value4 = 255.0;
    
    ksScene<double> scene2;
    
    scene2.addTransition(ksTransition<double>(&alpha_value3, 0, 30));
    scene2.addTransition(ksTransition<double>(&alpha_value4, 0, 60));
    
    ksAudioTrack track("audio/sorrow.ogg", 120, 100);
    
    double title_alpha = 0.0;
    double sun_z_position = 800.0;
    
    ksScene<double> title_fade_in;
    title_fade_in.addTransition(ksTransition<double>(&title_alpha, 200.0, 120));
    
    ksScene<double> title_fade_out;
    title_fade_out.addTransition(ksTransition<double>(&title_alpha, 0.0, 120));
    title_fade_out.addTransition(ksTransition<double>(&container_alpha, 0.0, 120));
    //title_fade_out.addTransition(ksTransition<double>(&sun_z_position, 800.0, 120));

    app.addScene(&title_fade_in);
    app.addScene(&title_fade_out);
    
    ksEntity tree(app.getWorld(), 600, 0, 800, 2, 4, 18);
    app.addEntity(&tree);
    
    // ksComplex ent(&path_finder, app.getWorld(), 400, 200, 32, 1, 2, 10);
    ksComplex ent(&path_finder, app.getWorld(), 400, 200, 32, 2, 2, 30);
    app.addEntity(&ent);
    ent.setAnimationLower(27);
    ent.setAnimationUpper(29);
    ent.setAnimationDelay(30);
    ent.toggleBehavior();
    
    // Add wolves.
    std::vector<ksComplex *> entity_list;
    int entity_num = 0;
    
    for (int count = 0; count < 8; ++count)
    {
        entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), emitter_x, 200, emitter_z, 2, 2, 30));
        entity_list[entity_num]->setAnimationLower(30);
        entity_list[entity_num]->setAnimationUpper(35);
        entity_list[entity_num]->setAnimationDelay(5);
        app.addEntity(entity_list[entity_num++]);
    }
    
    for (int count = 0; count < entity_num; ++count)
    {
        for (int count2 = 0; count2 < entity_num; ++count2)
        {
            entity_list[count]->addToGroup(entity_list[count2]);
            //entity_list[count]->pursue(&ent);
            entity_list[count]->arrive(ksVector2D(ent.X(), ent.Z()));
        }
        entity_list[count]->group();
        entity_list[count]->avoidObstacles();
    }
    
    // Run the app without a main loop
    //app.run();

    while (app.isOpen())
    {
        if (app.getKeyDown(ksKey::Space))
        {
            app.pauseSequence();
        }
        else if (app.getKeyDown(ksKey::Return))
        {
            app.startSequence();
        }
        
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
        
        if (title_fade_in.isDone())
            track.update();
        
        if (title_fade_in.isDone() && !title_fade_out.isDone())
        {
            // Get the sun's position.
            //ksVector3f temp = lighting.getLightPosition(0);
            
            // Update the sun's z coordinate.
            //temp.z = sun_z_position;
            
            // Update the position of the light source.
            //lighting.setLightPosition(0, temp.x, temp.y, temp.z);
            //lighting.addLight(sf::Vector3f(128, 128, sun_z_position), 256, sf::Color(255, 200, 0, 255));
        }
        
        app.setTextColor("title", ksColor(0, 0, 0, title_alpha));
        app.setTextColor("title2", ksColor(255, 255, 255, title_alpha));
        app.setTextColor("subtitle", ksColor(0, 0, 0, title_alpha));
        column.setColor(ksColor(0, 0, 0, container_alpha));
        //ent.animate();
    }

	return 0;
}
