#pragma once
#include "Menu.h"
#include "Game.h"

#include <iostream>

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

class Controller {
private:
	Menu m;
	Game g;
	ALLEGRO_DISPLAY* ventana;
	ALLEGRO_FONT* font;
public:
	Controller();
};
