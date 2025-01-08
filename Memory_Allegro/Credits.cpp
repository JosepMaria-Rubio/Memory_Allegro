#include "Credits.h"


Credits::Credits()
{
    CreditsDisplay();
}

void Credits::CreditsDisplay()
{
    ALLEGRO_DISPLAY* ventanaCreditos = al_create_display(800, 600);
    ALLEGRO_FONT* arial70 = al_load_font("arial.ttf", 70, 0);
    ALLEGRO_FONT* arial35 = al_load_font("arial.ttf", 35, 0);
    al_set_window_title(ventanaCreditos, "Credits");

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    //al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(ventanaCreditos)); 


    bool running = true;
    while (running) {
        al_draw_text(arial70, al_map_rgb(255, 255, 255),400,50, ALLEGRO_ALIGN_CENTER, "-- CREDITOS --");
        al_draw_text(arial35, al_map_rgb(255, 255, 255), 400, 200, ALLEGRO_ALIGN_CENTER, "Xavier Ramirez Olle");
        al_draw_text(arial35, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "Josep Maria Rubio Sala");
        al_draw_text(arial35, al_map_rgb(255, 255, 255), 400, 400, ALLEGRO_ALIGN_CENTER, "Ning ye Bao");


        al_flip_display();

        ALLEGRO_EVENT ev;
        while (al_get_next_event(event_queue, &ev)) {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                running = false; // Salir del bucle si se presiona el botón de cerrar
            }
        }
    }
    al_destroy_font(arial70);
    al_destroy_font(arial35);
    al_destroy_display(ventanaCreditos);
    al_destroy_event_queue(event_queue);
    Menu();
}
