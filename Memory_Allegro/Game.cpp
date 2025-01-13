#include "Game.h"

Game::Game() {
	cards = std::vector<Card>();
	cardNames = std::vector<std::string>();
	numPairs = 9;
}

void Game::InitializeGame() {

}

void Game::StartGame(ALLEGRO_DISPLAY* ventana) {
    al_set_window_position(ventana, 100, 200);
	al_resize_display(ventana, 1200, 800);
    al_set_window_title(ventana, "Memory EX");
    ALLEGRO_BITMAP* background = al_load_bitmap("data/img/Backrounds/GiratinaBackground.png");
    ALLEGRO_BITMAP* exitNormal = al_load_bitmap("data/img/BotonesMenu/Normal/4Exit.png");
    ALLEGRO_BITMAP* exitHover = al_load_bitmap("data/img/BotonesMenu/Hover/8Exit.png");

    ALLEGRO_BITMAP* surrenderHover = al_load_bitmap("data/img/BotonesGame/hoverGame/Surrender2.png");
    ALLEGRO_BITMAP* pauseHover = al_load_bitmap("data/img/BotonesGame/hoverGame/Pause2.png");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER* segundoTimer = al_create_timer(1.0);
    al_register_event_source(queue, al_get_timer_event_source(segundoTimer));
    al_start_timer(segundoTimer);

	//ALLEGRO_BITMAP* cardFront = al_load_bitmap("data/img/Cartas/ExecutorE.png");
	//ALLEGRO_BITMAP* cardBack = al_load_bitmap("data/img/Cartas/Reverso.png");
    ALLEGRO_FONT* arial70 = al_load_font("data/fonts/arial.ttf", 70, 0);
    ALLEGRO_FONT* arial35 = al_load_font("data/fonts/arial.ttf", 35, 0);
	SetCardNames();
	LoadCards();
    
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_mouse_event_source());

    int sec = 0;
    int x = -1, y = -1;
    int botonExit = 0;
    bool running = true;
    while (running) {
        ALLEGRO_EVENT Evento;
        al_wait_for_event(event_queue, &Evento);
        al_draw_bitmap(background, 0, 0, 0);

        int segundo = 0;
        int x = -1, y = -1;
        int botonesGame[] = { 0, 0};

        /*al_wait_for_event(queue, &Evento);
        if (Evento.type == ALLEGRO_EVENT_TIMER) {
            if (Evento.timer.source == segundoTimer) {
                segundo++;
            }
        }*/
        //al_clear_to_color(al_map_rgb(segundo * 10 % 255, segundo));
        //al_draw_text(arial35, al_map_rgb(255, 255, 255), 200, 200, NULL, ("Segundo: "+ to_string(segundo)).c_str());

        if (Evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            x = Evento.mouse.x;
            y = Evento.mouse.y;

            botonesGame[0] = (x >= 375 && x <= 575 && y >= 50 && y <= 100) ? 1 : 0; // if (x >= 300 && x <= 500 && y >= 200 && y <= 250) { botonesMenu[0] = 1; } else { botonesMenu[0] = 0; }
            botonesGame[1] = (x >= 625 && x <= 825 && y >= 50 && y <= 100) ? 1 : 0;
        }

        if (botonesGame[0]) al_draw_bitmap(surrenderHover, 375, 50, 0);
        if (botonesGame[1]) al_draw_bitmap(pauseHover, 625, 50, 0);

        if (Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (Evento.mouse.button & 1) {
                if (botonesGame[0] == 1) {
                    running = false;
                }
                if (botonesGame[1] == 1) {
                    //Pausa
                }
            }
        }

		DrawCards();
        if (Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            x = Evento.mouse.x;
            y = Evento.mouse.y;
            //botonExit = (x >= 300 && x <= 500 && y >= 500 && y <= 550) ? 1 : 0;
                for (int i = 0; i < cards.size(); i++) {
                    if (x >= cards[i].getPositionTop()[0] && x <= cards[i].getPositionBottom()[0] && y >= cards[i].getPositionTop()[1] && y <= cards[i].getPositionBottom()[1]) {
                        if (Evento.mouse.button & 1) {
                            std::cout << "Posicion mouse X: " << x << " Y: " << y << std::endl;
                            std::cout << "Posicion carta: " << cards[i].getPositionTop()[0] << "." << cards[i].getPositionTop()[1] << " - " << cards[i].getPositionBottom()[0] << "." << cards[i].getPositionBottom()[1] << std::endl;
                            cards[i].Flip();
                        }
                    }
                }
        }

        if (Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (Evento.mouse.button & 1) {
                if (botonExit) running = false;
            }
        }
        al_flip_display();
    }
    al_destroy_bitmap(background);
    al_destroy_bitmap(exitNormal);
    al_destroy_bitmap(exitHover);
    al_destroy_font(arial70);
    al_destroy_event_queue(event_queue);
    return;
}



void Game::LoadCards() {
    for (int i = 0; i < numPairs; i++) {
        cards.push_back(Card("data/img/Cartas/" + cardNames[i] + ".png", cardNames[i]));
        cards.push_back(Card("data/img/Cartas/" + cardNames[i] + ".png", cardNames[i]));
    }
	auto rng = std::default_random_engine{};
	std::shuffle(cards.begin(), cards.end(), rng);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            cards[i * 6 + j].setPosition(new int[2] {50 + 200 * j, 200 + 200 * i}, new int[2] {150 + 200 * j, 350 + 200 * i});
        }
    }
}

void Game::DrawCards() {
	for (int i = 0; i < cards.size(); i++) {
		if (cards.at(i).IsFlipped()) {
			al_draw_bitmap(al_load_bitmap(cards[i].getImgFrontPath().c_str()), cards[i].getPositionTop()[0], cards[i].getPositionTop()[1], 0);
		}
		else {
			al_draw_bitmap(al_load_bitmap(cards[i].getImgBackPath().c_str()), cards[i].getPositionTop()[0], cards[i].getPositionTop()[1], 0);
		}
	}
}


void Game::SetCardNames() {
	cardNames.push_back("Arcanine");
	cardNames.push_back("Executor");
    cardNames.push_back("Gengar");
	//.push_back("Gengar");
	cardNames.push_back("Marowak");
	cardNames.push_back("Mew");
	cardNames.push_back("Nidoking");
	cardNames.push_back("Nidoqueen");
    cardNames.push_back("Pidgeot");
    cardNames.push_back("Starmie");
    cardNames.push_back("Vaporeon");
}


