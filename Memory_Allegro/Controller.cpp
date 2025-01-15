#include "Controller.h"


Controller::Controller() {
    srand(time(NULL));
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_mouse();

    ventana = al_create_display(800, 600);
    bool running = true;
    while (running) {
        switch ((MenuOptions)m.MainMenu(ventana)) {
        case PLAY:
			g.StartGame(ventana);
            break;
        case CREDITS:
            m.CreditsMenu(ventana);
            break;
        case SETTINGS:
			m.SettingsMenu(ventana);
            break;
        case EXIT:
            running = false;
            break;
        default:
            break;
        }
    }
    al_destroy_display(ventana);
    exit(0);
}
