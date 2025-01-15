#include "Menu.h"

Menu::Menu() {
    //MainMenu();
}

int Menu::MainMenu(ALLEGRO_DISPLAY* ventanaPrincipal){
    al_set_window_position(ventanaPrincipal, 560, 240);

    al_resize_display(ventanaPrincipal, 800, 600);
    al_set_window_title(ventanaPrincipal, "Memory EX");

    ALLEGRO_BITMAP* mainMenu = al_load_bitmap("data/img/MainMenu.png");
    ALLEGRO_BITMAP* playHover = al_load_bitmap("data/img/BotonesMenu/Hover/5Play.png");
    ALLEGRO_BITMAP* creditsHover = al_load_bitmap("data/img/BotonesMenu/Hover/6Credits.png");
    ALLEGRO_BITMAP* settingsHover = al_load_bitmap("data/img/BotonesMenu/Hover/7Settings.png");
    ALLEGRO_BITMAP* exitHover = al_load_bitmap("data/img/BotonesMenu/Hover/8Exit.png");

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(ventanaPrincipal));

    int segundo = 0;
    int x = -1, y = -1;
    int botonesMenu[] = { 0, 0, 0, 0 };

    bool running = true;
    while (running) {
        ALLEGRO_EVENT Evento;
        al_wait_for_event(event_queue, &Evento);
        al_draw_bitmap(mainMenu, 0, 0, 0);

        if (Evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
        if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            x = Evento.mouse.x;
            y = Evento.mouse.y;

            botonesMenu[0] = (x >= 300 && x <= 500 && y >= 200 && y <= 250) ? 1 : 0; // if (x >= 300 && x <= 500 && y >= 200 && y <= 250) { botonesMenu[0] = 1; } else { botonesMenu[0] = 0; }
            botonesMenu[1] = (x >= 300 && x <= 500 && y >= 300 && y <= 350) ? 1 : 0;
            botonesMenu[2] = (x >= 300 && x <= 500 && y >= 400 && y <= 450) ? 1 : 0;
            botonesMenu[3] = (x >= 300 && x <= 500 && y >= 500 && y <= 550) ? 1 : 0;
        }

        if (botonesMenu[0]) al_draw_bitmap(playHover, 300, 200, 0);
        if (botonesMenu[1]) al_draw_bitmap(creditsHover, 300, 300, 0);
        if (botonesMenu[2]) al_draw_bitmap(settingsHover, 300, 400, 0);
        if (botonesMenu[3]) al_draw_bitmap(exitHover, 300, 500, 0);
        
        if (Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (Evento.mouse.button & 1) {
                if (botonesMenu[0] == 1) {
                    return 0;
                }
                if (botonesMenu[1] == 1) {
                    return 1;
                }
                if (botonesMenu[2] == 1) {
                    return 2;
                }
                if (botonesMenu[3] == 1) {
					running = false;
                }
            }
        }
        al_flip_display();
    }

	al_destroy_bitmap(mainMenu);
	al_destroy_bitmap(playHover);
    al_destroy_bitmap(creditsHover);
	al_destroy_bitmap(settingsHover);
	al_destroy_bitmap(exitHover);
    al_destroy_event_queue(event_queue);
    return 3;
}

void Menu::CreditsMenu(ALLEGRO_DISPLAY* ventana) {
    al_set_window_title(ventana, "Credits");
    ALLEGRO_BITMAP* backround = al_load_bitmap("data/img/Wallpaper_1.png");
    ALLEGRO_BITMAP* exitNormal = al_load_bitmap("data/img/BotonesMenu/Normal/4Exit.png");
    ALLEGRO_BITMAP* exitHover = al_load_bitmap("data/img/BotonesMenu/Hover/8Exit.png");
    
    ALLEGRO_FONT* arial70 = al_load_font("data/fonts/arial.ttf", 70, 0);
    ALLEGRO_FONT* arial35 = al_load_font("data/fonts/arial.ttf", 35, 0);

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    
    al_register_event_source(event_queue, al_get_mouse_event_source());

    int sec = 0;
    int x = -1, y = -1;
    int botonExit = 0;
    bool running = true;
    while (running) {
        ALLEGRO_EVENT Evento;
        al_wait_for_event(event_queue, &Evento);
        al_draw_bitmap(backround, 0, 0, 0);
        al_draw_text(arial70, al_map_rgb(0, 0, 0), 400, 50, ALLEGRO_ALIGN_CENTER, "-- CREDITOS --");
        al_draw_text(arial35, al_map_rgb(0, 0, 0), 400, 200, ALLEGRO_ALIGN_CENTER, "Xavier Ramirez Olle");
        al_draw_text(arial35, al_map_rgb(0, 0, 0), 400, 300, ALLEGRO_ALIGN_CENTER, "Josep Maria Rubio Sala");
        al_draw_text(arial35, al_map_rgb(0, 0, 0), 400, 400, ALLEGRO_ALIGN_CENTER, "Ning ye Bao");
        al_draw_bitmap(exitNormal, 300, 500, 0);

        if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            x = Evento.mouse.x;
            y = Evento.mouse.y;

            botonExit = (x >= 300 && x <= 500 && y >= 500 && y <= 550) ? 1 : 0;
        }

        if (Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (Evento.mouse.button & 1) {
                if (botonExit) running = false;
            }
        }
        if (botonExit) al_draw_bitmap(exitHover, 300, 500, 0);

        al_flip_display();
    }
	al_destroy_bitmap(backround);
	al_destroy_bitmap(exitNormal);
	al_destroy_bitmap(exitHover);
    al_destroy_font(arial70);
    al_destroy_font(arial35);
    al_destroy_event_queue(event_queue);
    return;
}


void Menu::SettingsMenu(ALLEGRO_DISPLAY* ventana) {
    al_set_window_title(ventana, "Credits");
    ALLEGRO_BITMAP* backround = al_load_bitmap("data/img/Wallpaper_1.png");
    ALLEGRO_BITMAP* exitNormal = al_load_bitmap("data/img/BotonesMenu/Normal/4Exit.png");
    ALLEGRO_BITMAP* exitHover = al_load_bitmap("data/img/BotonesMenu/Hover/8Exit.png");

    ALLEGRO_FONT* arial70 = al_load_font("data/fonts/arial.ttf", 70, 0);
    ALLEGRO_FONT* arial35 = al_load_font("data/fonts/arial.ttf", 35, 0);

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    
    al_register_event_source(event_queue, al_get_mouse_event_source());

    int sec = 0;
    int x = -1, y = -1;
    int botonExit = 0;
    bool running = true;
    while (running) {
        ALLEGRO_EVENT Evento;
        al_wait_for_event(event_queue, &Evento);
        al_draw_bitmap(backround, 0, 0, 0);
        al_draw_text(arial70, al_map_rgb(0, 0, 0), 400, 50, ALLEGRO_ALIGN_CENTER, "-- SETTINGS --");
        al_draw_text(arial35, al_map_rgb(0, 0, 0), 400, 200, ALLEGRO_ALIGN_CENTER, "Difficulty < Hard > ");
        al_draw_text(arial35, al_map_rgb(0, 0, 0), 400, 300, ALLEGRO_ALIGN_CENTER, "Players  < 2 > ");
        al_draw_bitmap(exitNormal, 300, 500, 0);

        if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            x = Evento.mouse.x;
            y = Evento.mouse.y;

            botonExit = (x >= 300 && x <= 500 && y >= 500 && y <= 550) ? 1 : 0;
        }

        if (Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (Evento.mouse.button & 1) {
                if (botonExit) running = false;
            }
        }
        if (botonExit) al_draw_bitmap(exitHover, 300, 500, 0);

        al_flip_display();
    }
    al_destroy_bitmap(backround);
    al_destroy_bitmap(exitNormal);
    al_destroy_bitmap(exitHover);
    al_destroy_font(arial70);
    al_destroy_font(arial35);
    al_destroy_event_queue(event_queue);
    return;
}
