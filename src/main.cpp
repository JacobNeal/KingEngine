#include "ksApplication.h"
#include "ksComplex.h"
#include "ksButton.h"
#include "ksPathFinder.h"
#include <iostream>

int main()
{
	ksApplication app("Regime", 800, 640);
	app.setEntityTilesheet("images/voltor_interior.png");

    app.insertText(50, 50, "title", "KingTravel", 30, ksColor(0, 0, 0, 75));
    app.insertText(50, 80, "subtitle", "Simulation", 20, ksColor(0, 0, 0, 50));

//    app.loadWorld(8, 4, 8, "maps/exterior");
    app.loadWorld(25, 20, 0, "maps/exterior_2");

//    app.toggleWorld2D(BOTTOM);

//    Toggle the lighting in order to not see any lighting / shadows in
//    the engine.
    app.toggleWorldLighting();
    app.addLight(ksVector2D(-1, -1), LEFT, 2, 2, ksColor(255, 255, 0, 50), ksColor(80, 80, 0, 50));

    ksPathFinder path_finder(app.getWorld());
    
    ksEntity grass(app.getWorld(), FRONT, 1, 3, 1, 1, 11);
    app.addEntity(&grass);

    ksEntity grass2(app.getWorld(), FRONT, 3, 0, 1, 1, 11);
    app.addEntity(&grass2);

    ksEntity grass3(app.getWorld(), FRONT, 0, 0, 1, 1, 11);
    app.addEntity(&grass3);

    ksEntity grass4(app.getWorld(), FRONT, 6, 2, 1, 1, 11);
    app.addEntity(&grass4);

    ksEntity grass5(app.getWorld(), FRONT, 0, 6, 1, 1, 11);
    app.addEntity(&grass5);

    ksEntity grass6(app.getWorld(), FRONT, 7, 7, 1, 1, 11);
    app.addEntity(&grass6);

    ksEntity flower(app.getWorld(), FRONT, 1, 5, 1, 1, 31);
    flower.setAnimationLower(31);
    flower.setAnimationUpper(32);
    flower.setAnimationDelay(60);
    app.addEntity(&flower);

    ksEntity flower2(app.getWorld(), FRONT, 6, 0, 1, 1, 31);
    flower2.setAnimationLower(31);
    flower2.setAnimationUpper(32);
    flower2.setAnimationDelay(60);
    app.addEntity(&flower2);

    ksEntity flower3(app.getWorld(), FRONT, 6, 6, 1, 1, 31);
    flower3.setAnimationLower(31);
    flower3.setAnimationUpper(32);
    flower3.setAnimationDelay(60);
    app.addEntity(&flower3);
   
    ksEntity flower4(app.getWorld(), FRONT, 0, 1, 1, 1, 31);
    flower4.setAnimationLower(31);
    flower4.setAnimationUpper(32);
    flower4.setAnimationDelay(60);
    app.addEntity(&flower4);

    std::vector<ksComplex *> entity_list;
    int entity_num = 8;

    int scenario_mode = 2;

    int emitter_row = 1;
    int emitter_col = 12; 

    for (int count = 0; count < entity_num; ++count)
    {
        entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), FRONT, 
                    emitter_row, emitter_col, 1, 1, 45));
        app.addEntity(entity_list[count]);
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

    app.insertText(600, 50, "entity_count", "Total count: " + std::to_string(entity_num), 
            20, ksColor(0, 0, 0, 100));

	while (app.isOpen())
	{
        // If the active scenario is the
        // pack of wolves scenario then
        // use the arrive complex behavior.
        if (scenario_mode == 2)
        {
            for (int count = 0; count < entity_num; ++count)
                entity_list[count]->arrive(app.getMousePosition());
        }

        // Check for key input (move entity)
		if (app.getMouseDown())
        {
//            ksPathNode temp = app.calculateWorldNode(app.getMousePosition().X,
//                                                     app.getMousePosition().Y);
            //ent.move(temp.row, temp.col);
            //chair.seek(app.getMousePosition());
            //chair2.seek(app.getMousePosition());
//            ent.arrive(app.getMousePosition());
//            chair.flee(temp.row, temp.col, 1);
//            ent.seek(app.getMousePosition());
//            chair.move(temp.row, temp.col);
        }
        if (app.getKeyDown(ksKey::Num1))
        {
            //**************************************************
            //      Patrolling Guard Scenario
            //
            //**************************************************
            
            app.clearEntities();
            entity_list.clear();
            entity_num = 0;

            entity_list.push_back(new ksComplex(&path_finder, app.getWorld(), FRONT, 
                        emitter_row, emitter_col, 1, 2, 10));

            // Set up the guard's animation
            entity_list[entity_num]->setAnimationLower(10);
            entity_list[entity_num]->setAnimationUpper(12);
            entity_list[entity_num]->setAnimationDelay(45);
            
            app.addEntity(entity_list[entity_num++]);

            entity_list[0]->move(10, 9);

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

            app.clearEntities();
            entity_list.clear();
            entity_num = 0;

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
            
            app.clearEntities();
            entity_list.clear();
            entity_num = 0;

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
        else if (app.getKeyDown(ksKey::Space))
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
        else if (app.getKeyDown(ksKey::Left))
            app.rotateWorldLeft();
        else if (app.getKeyDown(ksKey::Right))
            app.rotateWorldRight();
    }

	return 0;
}
