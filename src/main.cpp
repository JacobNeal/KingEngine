#include "ksApplication.h"
#include "ksButton.h"
#include <iostream>

int main()
{
	ksApplication app("Regime", 800, 640);
	app.setEntityTilesheet("images/portal_obj.png");

	// Add keys to be checked for
	app.addInput(ksKey::W);
	app.addInput(ksKey::A);
	app.addInput(ksKey::S);
	app.addInput(ksKey::D);

    int world_width     = 15;
    int world_height    = 10;
    int world_depth     = 5;

    app.loadWorld(world_width, world_height, world_depth, "maps/interior");
	//ksEntity ent(64, 64, 64, 64, 0);
	//app.addEntity(&ent);

    //ksButton cont(64, 64);
    //app.addControl(&cont);

	while (app.isOpen())
	{
		// Check for key input (move entity)
		if (app.getKeyDown(ksKey::W))
        {
            app.increaseCameraDepth();
        }
		else if (app.getKeyDown(ksKey::S))
        {
            app.decreaseCameraDepth();
        }
		else if (app.getKeyDown(ksKey::A))
        {
        }
		else if (app.getKeyDown(ksKey::D))
        {
        }
        else if (app.getKeyDown(ksKey::Up))
        {
            if (world_depth < 5)
            {
                world_depth++;
                app.loadWorld(world_width, world_height, world_depth);
            }
        }
        else if (app.getKeyDown(ksKey::Down))
        {
            if (world_depth > 0)
            {
                world_depth--;
                app.loadWorld(world_width, world_height, world_depth);
            }
        }
    }

	return 0;
}
