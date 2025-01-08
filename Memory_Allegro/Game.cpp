#include "Game.h"

Game::Game() {
}

void Game::StartGame(ALLEGRO_DISPLAY* ventana) {
    al_set_window_title(ventana, "Memory EX");
    //al_clear_to_color();
    ALLEGRO_BITMAP* backround = al_load_bitmap("data/img/Wallpaper_0.png");
    ALLEGRO_BITMAP* exitNormal = al_load_bitmap("data/img/BotonesMenu/Normal/4Exit.png");
    ALLEGRO_BITMAP* exitHover = al_load_bitmap("data/img/BotonesMenu/Hover/8Exit.png");

    ALLEGRO_FONT* arial70 = al_load_font("arial.ttf", 70, 0);
    ALLEGRO_FONT* arial35 = al_load_font("arial.ttf", 35, 0);

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
        al_draw_text(arial70, al_map_rgb(0, 0, 0), 400, 50, ALLEGRO_ALIGN_CENTER, "-- Memory EX --");
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
    al_destroy_event_queue(event_queue);
    return;
}
