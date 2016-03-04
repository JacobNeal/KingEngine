#include "ksApplication.h"
#include "ksComplex.h"
#include "ksButton.h"
#include "ksPathFinder.h"
#include <iostream>

int main()
{
	ksApplication app("Regime", 800, 640);
	app.setEntityTilesheet("images/voltor_interior.png");

    app.loadWorld(8, 4, 8, "maps/exterior");

//    app.toggleWorld2D(BOTTOM);

//    Toggle the lighting in order to not see any lighting / shadows in
//    the engine.
    app.toggleWorldLighting();
    app.addLight(ksVector2D(-1, -1), LEFT, 2, 2, ksColor(255, 255, 0, 50), ksColor(80, 80, 0, 50));

    ksPathFinder path_finder(app.getWorld());
    
    ksEntity grass(app.getWorld(), BOTTOM, 1, 3, 1, 1, 11);
    app.addEntity(&grass);

    ksEntity grass2(app.getWorld(), BOTTOM, 3, 0, 1, 1, 11);
    app.addEntity(&grass2);

    ksEntity grass3(app.getWorld(), BOTTOM, 0, 0, 1, 1, 11);
    app.addEntity(&grass3);

    ksEntity grass4(app.getWorld(), BOTTOM, 6, 2, 1, 1, 11);
    app.addEntity(&grass4);

    ksEntity grass5(app.getWorld(), BOTTOM, 0, 6, 1, 1, 11);
    app.addEntity(&grass5);

    ksEntity grass6(app.getWorld(), BOTTOM, 7, 7, 1, 1, 11);
    app.addEntity(&grass6);

    ksEntity flower(app.getWorld(), BOTTOM, 1, 5, 1, 1, 31);
    flower.setAnimationLower(31);
    flower.setAnimationUpper(32);
    flower.setAnimationDelay(60);
    app.addEntity(&flower);

    ksEntity flower2(app.getWorld(), BOTTOM, 6, 0, 1, 1, 31);
    flower2.setAnimationLower(31);
    flower2.setAnimationUpper(32);
    flower2.setAnimationDelay(60);
    app.addEntity(&flower2);

    ksEntity flower3(app.getWorld(), BOTTOM, 6, 6, 1, 1, 31);
    flower3.setAnimationLower(31);
    flower3.setAnimationUpper(32);
    flower3.setAnimationDelay(60);
    app.addEntity(&flower3);
   
    ksEntity flower4(app.getWorld(), BOTTOM, 0, 1, 1, 1, 31);
    flower4.setAnimationLower(31);
    flower4.setAnimationUpper(32);
    flower4.setAnimationDelay(60);
    app.addEntity(&flower4);

    ksComplex ent(&path_finder, app.getWorld(), BOTTOM, 0, 4, 1, 2, 10);
    ent.setAnimationLower(10);
    ent.setAnimationUpper(12);
    ent.setAnimationDelay(30);
    app.addEntity(&ent);


    //ent.seek(5, 1);
    //    ent.move(5, 1);

/*    ksComplex cloud(&path_finder, app.getWorld(), LEFT, 0, 6, 2, 2, 27);
    cloud.setAnimationLower(27);
    cloud.setAnimationUpper(29);
    cloud.setAnimationDelay(30);
    app.addEntity(&cloud);

    cloud.seek(0, 0);
*/
    ksComplex chair(&path_finder, app.getWorld(), BOTTOM, 0, 4, 1, 2, 9);
    app.addEntity(&chair);
  
//    chair.pursue(&ent);  
//    chair.addToGroup(&ent);
//    chair.group();

//    ent.addToGroup(&chair);
//    ent.group();

//    chair.addToGroup(&ent);
//    chair.group();

//    chair.flee(0, 3, 1);

    ksVector2D start;
    start.X = 500;
    start.Y = 32;

//    ksButton cont(64, 64);
//    app.addControl(&cont);

	while (app.isOpen())
	{
		// Check for key input (move entity)
		if (app.getMouseDown())
        {
            ksPathNode temp = app.calculateWorldNode(app.getMousePosition().X,
                                                     app.getMousePosition().Y);
            ent.move(temp.row, temp.col);
//            chair.flee(temp.row, temp.col, 1);
//            ent.seek(temp.row, temp.col);
//            chair.move(temp.row, temp.col);
        }
        if (app.getKeyDown(ksKey::Num1))
        {
            app.toggleWorld2D(BOTTOM);
            ent.setWall(FRONT);
            grass.setWall(FRONT);
            grass2.setWall(FRONT);
            grass3.setWall(FRONT);
            grass4.setWall(FRONT);
            grass5.setWall(FRONT);
            grass6.setWall(FRONT);
            flower.setWall(FRONT);
            flower2.setWall(FRONT);
            flower3.setWall(FRONT);
            flower4.setWall(FRONT);
        }
        else if (app.getKeyDown(ksKey::Num2))
        {
            app.toggleWorld3D();
            ent.setWall(BOTTOM);
            grass.setWall(BOTTOM);
            grass2.setWall(BOTTOM);
            grass3.setWall(BOTTOM);
            grass4.setWall(BOTTOM);
            grass5.setWall(BOTTOM);
            grass6.setWall(BOTTOM);
            flower.setWall(BOTTOM);
            flower2.setWall(BOTTOM);
            flower3.setWall(BOTTOM);
            flower4.setWall(BOTTOM);
        }
    }

	return 0;
}
