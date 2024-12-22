#include "Menu.h"

Menu::Menu() {
    MainMenu();
}

void Menu::MainMenu() {
    ALLEGRO_DISPLAY* ventana = al_create_display(800, 600);
    ALLEGRO_FONT* arial = al_load_font("arial.ttf", 70, 0);
    al_set_window_title(ventana, "Memory EX");

    ALLEGRO_BITMAP* mainMenu = al_load_bitmap("data/img/MainMenu.png");
    ALLEGRO_BITMAP* playHover = al_load_bitmap("data/img/BotonesMenu/Hover/5Play.png");
    ALLEGRO_BITMAP* creditsHover = al_load_bitmap("data/img/BotonesMenu/Hover/6Credits.png");
    ALLEGRO_BITMAP* settingsHover = al_load_bitmap("data/img/BotonesMenu/Hover/7Settings.png");
    ALLEGRO_BITMAP* exitHover = al_load_bitmap("data/img/BotonesMenu/Hover/8Exit.png");

    ALLEGRO_TIMER* segundoTimer = al_create_timer(1.0);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(segundoTimer);
    int segundo = 0;
    int x = -1, y = -1;
    int botonesMenu[] = { 0, 0, 0, 0 };

    while (true) {
        ALLEGRO_EVENT Evento;
        al_wait_for_event(event_queue, &Evento);
        //al_clear_to_color(blanco);
        al_draw_bitmap(mainMenu, 0, 0, 0);

        if (Evento.type == ALLEGRO_EVENT_TIMER) {
            if (Evento.timer.source == segundoTimer)
                segundo++;
        }
        if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            x = Evento.mouse.x;
            y = Evento.mouse.y;

            botonesMenu[0] = (x >= 300 && x <= 500 && y >= 200 && y <= 250) ? 1 : 0; // if (x >= 300 && x <= 500 && y >= 200 && y <= 250) { botonesMenu[0] = 1; } else { botonesMenu[0] = 0; }
            botonesMenu[1] = (x >= 300 && x <= 500 && y >= 300 && y <= 350) ? 1 : 0;
            botonesMenu[2] = (x >= 300 && x <= 500 && y >= 400 && y <= 450) ? 1 : 0;
            botonesMenu[3] = (x >= 300 && x <= 500 && y >= 500 && y <= 550) ? 1 : 0;
        }

        if (Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (Evento.mouse.button & 1) {
                if (botonesMenu[0] == 1) cout << "Diste click en Play" << endl;
                if (botonesMenu[1] == 1) cout << "Diste click en Creditos" << endl;
                if (botonesMenu[2] == 1) cout << "Diste click en Settings" << endl;
                if (botonesMenu[3] == 1) cout << "Diste click en Exit" << endl;
            }
        }

        if (botonesMenu[0]) al_draw_bitmap(playHover, 300, 200, 0);
        if (botonesMenu[1]) al_draw_bitmap(creditsHover, 300, 300, 0);
        if (botonesMenu[2]) al_draw_bitmap(settingsHover, 300, 400, 0);
        if (botonesMenu[3]) {
            al_draw_bitmap(exitHover, 300, 500, 0);
            if (Evento.mouse.button & 1) {
                exit(0);
            }
        }
        al_flip_display();
    }
    return;
}