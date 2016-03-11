#include "ksApplication.h"
#include "ksComplex.h"
#include "ksPathFinder.h"

int main()
{
	ksApplication app("Regime", 800, 640);
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

    // Toggle the lighting in order to not see any lighting / shadows in
    // the engine.
    app.toggleWorldLighting();
    app.addLight(ksVector2D(-1, -1), LEFT, 2, 2, ksColor(255, 255, 0, 50), ksColor(80, 80, 0, 50));

    ksPathFinder path_finder(app.getWorld());
    
    std::vector<ksComplex *> entity_list;
    int entity_num = 0;

    int scenario_mode = 0;

    int emitter_row = 1;
    int emitter_col = 12; 

	while (app.isOpen())
	{
        // If the active scenario is the
        // pack of wolves scenario then
        // use the arrive complex behavior.
        if (scenario_mode == 2)
        {
            for (int count = 0; count < entity_num; ++count)
                entity_list[count]->arrive(app.getMousePosition());
            
            if (app.getKeyDown(ksKey::Space))
            {
                entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), FRONT, 
                            emitter_row, emitter_col, 1, 1, 45));
                app.addEntity(entity_list[entity_num++]);
            
                for (int count = 0; count < entity_num; ++count)
                {
                    for (int count2 = 0; count2 < entity_num; ++count2)
                    {
                        entity_list[count]->addToGroup(entity_list[count2]);
                    }
                    entity_list[count]->group();
                    entity_list[count]->avoidObstacles();
                }

                app.setText("entity_count", "Total count: " + std::to_string(entity_num));
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

            app.loadWorld(25, 20, 0, "maps/exterior_3");
            
            entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), FRONT, 
                        emitter_row, emitter_col, 1, 1, 46));

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

            app.loadWorld(25, 20, 0, "maps/exterior_2");
    
            std::vector<ksEntity *> flowers;

            int current_flower = 0;

            for (int x = 0; x < 25; ++x)
            {
                for (int y = 0; y < 20; ++y)
                {
                    if ((x % 3 == 0) && (y % 5 == 0))
                    {
                        flowers.push_back(new ksEntity(app.getWorld(), FRONT, y, x, 1, 1, 31));
                        flowers[current_flower]->setAnimationLower(31);
                        flowers[current_flower]->setAnimationUpper(32);
                        flowers[current_flower]->setAnimationDelay(60);
                        app.addEntity(flowers[current_flower++]);
                    }
                }
            }

            for (int count = 0; count < 8; ++count)
            {
                entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), FRONT, 
                            emitter_row, emitter_col, 1, 1, 45));
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
            entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), FRONT,
                        emitter_row, emitter_col, 1, 1, 35));

            // Create fox entity.
            entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), FRONT,
                        emitter_row + 5, emitter_col + 2, 1, 1, 34));

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
    }

	return 0;
}
