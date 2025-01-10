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
    ALLEGRO_BITMAP* backround = al_load_bitmap("data/img/Backrounds/Giratina.png");
    ALLEGRO_BITMAP* exitNormal = al_load_bitmap("data/img/BotonesMenu/Normal/4Exit.png");
    ALLEGRO_BITMAP* exitHover = al_load_bitmap("data/img/BotonesMenu/Hover/8Exit.png");
	ALLEGRO_BITMAP* cardFront = al_load_bitmap("data/img/Cartas/ExecutorEX.png");
	ALLEGRO_BITMAP* cardBack = al_load_bitmap("data/img/Cartas/Reverso.png");
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
        al_draw_bitmap(backround, 0, 0, 0);
        //al_draw_text(arial70, al_map_rgb(0, 0, 0), 400, 50, ALLEGRO_ALIGN_CENTER, "-- Memory EX --");
        //al_draw_bitmap(exitNormal, 300, 500, 0);
		DrawCards();
        if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            x = Evento.mouse.x;
            y = Evento.mouse.y;

            //botonExit = (x >= 300 && x <= 500 && y >= 500 && y <= 550) ? 1 : 0;
            if (Evento.mouse.button & 1) {
                std::cout << x << "\n";
                std::cout << y << "\n";
                for (int i = 0; i < cards.size(); i++) {
                    if (x >= cards[i].getPositionTop()[0] && x <= cards[i].getPositionBottom()[0] && y >= cards[i].getPositionTop()[1] && y <= cards[i].getPositionBottom()[1]) {
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
        //if (botonExit) al_draw_bitmap(exitHover, 300, 500, 0);

        al_flip_display();
    }
    al_destroy_bitmap(backround);
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
            cards[i + j].setPosition(new int[2] {50 + 200 * j, 200 + 200 * i}, new int[2] {150 + 200 * j, 350 + 200 * i});
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
	//.push_back("Gengar");
	cardNames.push_back("Marowak");
	cardNames.push_back("Mew");
	cardNames.push_back("Nidoking");
	cardNames.push_back("Nidoqueen");
    cardNames.push_back("Pidgeot");
    cardNames.push_back("Starmie");
    cardNames.push_back("Vaporeon");
}

