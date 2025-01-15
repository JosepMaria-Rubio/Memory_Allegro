#pragma once
#include <iostream>
#include<Windows.h>
#include <string>


#include<allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

class Menu {
private:

public:
	Menu();

	int MainMenu(ALLEGRO_DISPLAY* ventana);
	void SettingsMenu(ALLEGRO_DISPLAY* ventana);
	void CreditsMenu(ALLEGRO_DISPLAY* ventana);
};

enum MenuOptions {
	PLAY,
	CREDITS,
	SETTINGS,
	EXIT
};
