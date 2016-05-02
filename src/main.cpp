#include "ksApplication.h"
#include "ksComplex.h"
#include "ksPathFinder.h"

int main()
{
	ksApplication app("KingTravel", 800, 640);
	app.setEntityTilesheet("images/voltor_interior.png");

    app.insertText(50, 50, "title", "KingTravel", 30, ksColor(0, 0, 0, 100));
    app.insertText(50, 80, "subtitle", "Simulation", 20, ksColor(0, 0, 0, 75));

    app.insertText(350, 50, "scenario", "", 20, ksColor(0, 0, 0, 100));
    app.insertText(350, 70, "scenario_description", "", 20, ksColor(0, 0, 0, 100));

    app.insertText(600, 50, "entity_count", "", 20, ksColor(0, 0, 0, 100));

    // Directions displayed on screen
    app.insertText(50, 120, "scenario_directions1", "Press 1 for patrolling guard scenario",
                   20, ksColor(0, 0, 0, 75));
    app.insertText(50, 140, "scenario_directions2", "Press 2 for pack of wolves scenario",
                   20, ksColor(0, 0, 0, 75));
    app.insertText(50, 160, "scenario_directions3", "Press 3 for rabbit and fox scenario",
                   20, ksColor(0, 0, 0, 75));

    app.loadWorld(8, 4, 8, "maps/exterior");
    
    // World, Color, Location, size, num, velocity, and reach (time to live)
    ksParticleEmitter emitter(app.getWorld(), sf::Color(0, 0, 255, 200), sf::Vector3f(0, 0, -192), 8, 20, 20, 60);
    app.addParticleEmitter(&emitter);
    
    ksLightSystem lighting(app.getWorld(), sf::Color(0, 0, 0, 100), sf::Color(0, 0, 0, 255));
    lighting.addLight(sf::Vector3f(0, 0, 64), 256, sf::Color(255, 200, 0, 200));
    app.addLightSystem(&lighting);

    ksPathFinder path_finder(app.getWorld());
    
    std::vector<ksComplex *> entity_list;
    int entity_num = 0;

    int scenario_mode = 0;

    int emitter_x = 400;
    int emitter_z = 128;

	while (app.isOpen())
	{
        // If the active scenario is the
        // pack of wolves scenario then
        // use the arrive complex behavior.
        if (scenario_mode == 2)
        {
            for (int count = 0; count < entity_num; ++count)
                entity_list[count]->arrive(ksVector2D(0, 128));
            
            if (app.getKeyDown(ksKey::Space))
            {
                entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), emitter_x, 640,
                            emitter_z, 32, 32, 45));
                app.addEntity(entity_list[entity_num++]);
            
                for (int count = 0; count < entity_num; ++count)
                {
                    for (int count2 = 0; count2 < entity_num; ++count2)
                    {
                        entity_list[count]->addToGroup(entity_list[count2]);
                        entity_list[count]->arrive(ksVector2D(0, 128));
                    }
                    entity_list[count]->group();
                    entity_list[count]->avoidObstacles();
                }

                app.setText("entity_count", "Total count: " + std::to_string(entity_num));
            }
        }
        else if (scenario_mode == 4)
        {
            for (int count = 1; count < 9; ++count)
                entity_list[count]->arrive(entity_list[0]->getTilePosition().center);
        }
        else if (scenario_mode == 1)
        {
            if (app.getMouseDown())
            {
                int row = (int) app.getMousePosition().Y / 32;
                int col = (int) app.getMousePosition().X / 32;

                entity_list[0]->move(row, col, true);
            }
        }

        // Get key input
        if (app.getKeyDown(ksKey::Num1))
        {
            //**************************************************
            //      Patrolling Guard Scenario
            //
            //**************************************************

            app.setText("scenario", "Scenario 1");
            app.setText("scenario_description", "Patrolling Guard");
            app.setText("scenario_directions1", "");
            app.setText("scenario_directions2", "");
            app.setText("scenario_directions3", "");

            app.clearEntities();
            entity_list.clear();
            entity_num = 0;

            app.loadWorld(25, 20, 0, "maps/exterior");
            
            entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), emitter_x, 640, 
                        emitter_z, 32, 32, 46));

            app.addEntity(entity_list[entity_num++]);

            entity_list[0]->move(1, 2, true);

            // Update total entity count text
            app.setText("entity_count", "Total count: " + std::to_string(entity_num));
        
            scenario_mode = 1;
        }
        else if (app.getKeyDown(ksKey::Num2))
        {
            //**************************************************
            //      Pack of Wolves Scenario
            //
            //**************************************************

            app.setText("scenario", "Scenario 2");
            app.setText("scenario_description", "Pack of Wolves");
            app.setText("scenario_directions1", "Press spacebar to add more entities.");
            app.setText("scenario_directions2", "");
            app.setText("scenario_directions3", "");
            
            app.clearEntities();
            entity_list.clear();
            entity_num = 0;

            app.loadWorld(8, 4, 8, "maps/exterior");
    
            std::vector<ksEntity *> flowers;

            int current_flower = 0;

            for (int x = 0; x < 25; ++x)
            {
                for (int y = 0; y < 20; ++y)
                {
                    if ((x % 3 == 0) && (y % 5 == 0))
                    {
                        flowers.push_back(new ksEntity(app.getWorld(), x * TILE_WIDTH, 640, 
                            y * TILE_HEIGHT, 32, 32, 31));
                        flowers[current_flower]->setAnimationLower(31);
                        flowers[current_flower]->setAnimationUpper(32);
                        flowers[current_flower]->setAnimationDelay(60);
                        app.addEntity(flowers[current_flower++]);
                    }
                }
            }

            for (int count = 0; count < 8; ++count)
            {
                entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), emitter_x, 640,
                            emitter_z, 32, 32, 45));
                app.addEntity(entity_list[entity_num++]);
            }
            
            for (int count = 0; count < entity_num; ++count)
            {
                for (int count2 = 0; count2 < entity_num; ++count2)
                {
                    entity_list[count]->addToGroup(entity_list[count2]);
                    entity_list[count]->arrive(ksVector2D(0, 128));
                }
                entity_list[count]->group();
                entity_list[count]->avoidObstacles();
            }

            // Update total entity count text
            app.setText("entity_count", "Total count: " + std::to_string(entity_num));
        
            scenario_mode = 2;
        }
        else if (app.getKeyDown(ksKey::Num3))
        {
            //**************************************************
            //      Rabbit and Fox Scenario
            //
            //**************************************************
            
            app.setText("scenario", "Scenario 3");
            app.setText("scenario_description", "Rabbit and Fox");
            app.setText("scenario_directions1", "");
            app.setText("scenario_directions2", "");
            app.setText("scenario_directions3", "");
            
            app.clearEntities();
            entity_list.clear();
            entity_num = 0;

            app.loadWorld(25, 20, 0, "maps/exterior_2");

            // Create rabbit entity.
            entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), emitter_x, 640,
                        emitter_z, 32, 32, 35));

            // Create fox entity.
            entity_list.push_back(new ksComplex(&path_finder, app.getWorld(),
                        emitter_x + 160, 640, emitter_z + 64, 32, 32, 34));

            // Set the rabbit to evade the fox,
            // and the fox to pursue the rabbit.
            entity_list[entity_num]->evade(entity_list[entity_num + 1]);
            entity_list[entity_num + 1]->pursue(entity_list[entity_num]);

            app.addEntity(entity_list[entity_num++]);
            app.addEntity(entity_list[entity_num++]);

            // Update the total entity count text
            app.setText("entity_count", "Total count: " + std::to_string(entity_num));

            scenario_mode = 3;
        }
        else if (app.getKeyDown(ksKey::Num4))
        {
            //**************************************************
            //      Hybrid Scenario
            //**************************************************

            app.setText("scenario", "Scenario 4");
            app.setText("scenario_description", "Hyrbid");
            app.setText("scenario_directions1", "");
            app.setText("scenario_directions2", "");
            app.setText("scenario_directions3", "");

            app.clearEntities();
            entity_list.clear();
            entity_num = 0;

            app.loadWorld(25, 20, 0, "maps/exterior_2");

            // Create guard
            entity_list.push_back(new ksComplex(&path_finder, app.getWorld(),
                        emitter_x, 640, emitter_z, 32, 64, 10));

            app.addEntity(entity_list[entity_num++]);

            entity_list[0]->setAnimationLower(10);
            entity_list[0]->setAnimationUpper(12);
            entity_list[0]->setAnimationDelay(45);

            entity_list[0]->move(12, 2, true);

            std::vector<ksEntity *> flowers;

            int current_flower = 0;

            for (int x = 0; x < 25; ++x)
            {
                for (int y = 0; y < 20; ++y)
                {
                    if ((x % 3 == 0) && (y % 5 == 0))
                    {
                        flowers.push_back(new ksEntity(app.getWorld(), x * TILE_WIDTH, 640, 
                            y * TILE_HEIGHT, 32, 32, 31));
                        flowers[current_flower]->setAnimationLower(31);
                        flowers[current_flower]->setAnimationUpper(32);
                        flowers[current_flower]->setAnimationDelay(60);
                        app.addEntity(flowers[current_flower++]);
                    }
                }
            }

            for (int count = 1; count < 9; ++count)
            {
                entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), 
                            emitter_x, 640, emitter_z, 32, 32, 45));
                app.addEntity(entity_list[entity_num++]);
            }
            
            for (int count = 0; count < entity_num; ++count)
            {
                for (int count2 = 0; count2 < entity_num; ++count2)
                {
                    entity_list[count]->addToGroup(entity_list[count2]);
                }
                entity_list[count]->group();
                entity_list[count]->avoidObstacles();
            }

            // Update total entity count text
            app.setText("entity_count", "Total count: " + std::to_string(entity_num));

            scenario_mode = 4;
        }
        else if (app.getMouseDown())
        {
            app.increaseCameraDepth();
        }
    }

	return 0;
}
