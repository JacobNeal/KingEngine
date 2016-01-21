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

	ksEntity ent(64, 64, 64, 64, 0);
	app.addEntity(&ent);

    ksButton cont(64, 64);
    app.addControl(&cont);

	while (app.isOpen())
	{
		// Check for key input (move entity)
		if (app.getKeyDown(ksKey::W))
        {
			ent.move(0, -1);
            app.animateEntity(0, 0, 1, 20);
        }
		else if (app.getKeyDown(ksKey::S))
        {
			ent.move(0, 10);
            app.animateEntity(0, 0, 1, 5);
        }
		else if (app.getKeyDown(ksKey::A))
        {
			ent.move(-5, 0);
            app.animateEntity(0, 0, 1, 15);
        }
		else if (app.getKeyDown(ksKey::D))
        {
			ent.move(5, 0);
            app.animateEntity(0, 0, 1, 15);
        }
        else
        {
            app.animateEntity(0, 0, 0, 15);
        }

		if (ent.isPressed())
			std::cout << "Entity pressed!\n";

        if (cont.isPressed())
            std::cout << "Pressed the button!\n";

		if (app.getMouseDown())
			ent.setPosition(app.getMousePosition());
    }

	return 0;
}
