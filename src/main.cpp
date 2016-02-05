#include "ksApplication.h"
#include "ksComplex.h"
#include "ksButton.h"
#include "ksPathFinder.h"
#include <iostream>

int main()
{
	ksApplication app("Regime", 800, 640);
	app.setEntityTilesheet("images/voltor_interior.png");

	// Add keys to be checked for
	app.addInput(ksKey::W);
	app.addInput(ksKey::A);
	app.addInput(ksKey::S);
	app.addInput(ksKey::D);

    std::string last_move = "up";

    //app.loadWorld(15, 10, 5, "maps/interior");
    app.loadWorld(8, 4, 8, "maps/interior_3");

    ksPathFinder path_finder(app.getWorld());

    ksComplex ent(&path_finder, BOTTOM, 0, 0, 2, 2, 10);
	app.addEntity(&ent);

    ksComplex chair(&path_finder, BOTTOM, 3, 0, 1, 2, 9);
    app.addEntity(&chair); 
    
    ksVector2D start;
    start.X = 500;
    start.Y = 32;

    app.addLight(start, LEFT, 2, 2, ksColor(255, 255, 0, 50), ksColor(80, 80, 0, 50));
    
    //ksButton cont(64, 64);
    //app.addControl(&cont);

	while (app.isOpen())
	{
		// Check for key input (move entity)
		if (app.getMouseDown())
        {
//            if (ent.getDepth() < 5)
//            {
//                ent.move(0, 0, 1);
//                app.setCameraDelta(5);
//            }

            //ent.setPath(path_finder.calculatePath(app.getWorld(), &ent, 6, 6));
            ent.move(6, 6);

        /*    ksVector2D start;
            start.X = app.getMousePosition().X;
            start.Y = app.getMousePosition().Y;

            app.addLight(start, LEFT, 2, 2, ksColor(255, 255, 0, 50), ksColor(80, 80, 0, 50));*/

//            app.animateEntity(0, 12, 17, 5);
//            last_move = "up";
        }
        if (app.getKeyDown(ksKey::Num1))
        {
            app.setCameraDelta(5);
        }
        else if (app.getKeyDown(ksKey::Num2))
        {
//            if (ent.getDepth() > 0)
//            {
//                ent.move(0, 0, -1);
                app.setCameraDelta(4);
//            }

//            app.animateEntity(0, 3, 8, 5);
//            last_move = "down";
        }
        else if (app.getKeyDown(ksKey::Num3))
        {
            app.setCameraDelta(3);
        }
        else if (app.getKeyDown(ksKey::Num4))
        {
            app.setCameraDelta(2);
        }
        else if (app.getKeyDown(ksKey::Num5))
        {
            app.setCameraDelta(1);
        }
  //          if (last_move == "up")
    //            app.animateEntity(0, 9, 11, 45);
      //      else if (last_move == "down")
        //        app.animateEntity(0, 0, 2, 30);
          //  else if (last_move == "right")
            //    app.animateEntity(0, 18, 20, 45);
           // else if (last_move == "left")
             //   app.animateEntity(0, 27, 29, 45);
    }

	return 0;
}
