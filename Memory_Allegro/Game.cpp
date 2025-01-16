#include "Game.h"
#include <windows.h>
// Constructor: Game
// Description: Initializes a new instance of the Game class, setting up the necessary vectors for cards, card names, 
//              and flipped cards, and initializing the number of pairs to 9.
// Parameters: None
// Returns: None
Game::Game() {
    cards = std::vector<Card>();
    cardNames = std::vector<std::string>();
    flippedCards = std::vector<Card*>();
    numPairs = 9;
}

// Function: StartGame
    // Description: Initializes and starts the game by setting up the display, loading resources, 
    //              and entering the main game loop to handle events and render the game.
    // Parameters: 
    //   - ALLEGRO_DISPLAY* ventana: Pointer to the Allegro display object.
    // Returns: void
void Game::StartGame(ALLEGRO_DISPLAY* ventana) {
    al_set_window_position(ventana, 360, 140);
	al_resize_display(ventana, 1200, 800);
    al_set_window_title(ventana, "Memory EX");
    //Imagenes Game
    ALLEGRO_BITMAP* background = al_load_bitmap("data/img/Backrounds/GiratinaBackground.png");
    ALLEGRO_BITMAP* surrenderHover = al_load_bitmap("data/img/BotonesGame/hoverGame/Surrender2.png");
    ALLEGRO_BITMAP* pauseHover = al_load_bitmap("data/img/BotonesGame/hoverGame/Pause2.png");
    ALLEGRO_BITMAP* playAgain1 = al_load_bitmap("data/img/botonesGame/normalGame/playAgain1.png");
    ALLEGRO_BITMAP* quit1 = al_load_bitmap("data/img/botonesGame/normalGame/quit1.png");
    ALLEGRO_BITMAP* playAgain2 = al_load_bitmap("data/img/botonesGame/hoverGame/playAgain2.png");
    ALLEGRO_BITMAP* quit2 = al_load_bitmap("data/img/botonesGame/hoverGame/quit2.png");
    ALLEGRO_BITMAP* continue1 = al_load_bitmap("data/img/botonesGame/normalGame/continue1.png");
    ALLEGRO_BITMAP* continue2 = al_load_bitmap("data/img/botonesGame/hoverGame/continue2.png");
    ALLEGRO_BITMAP* youWin = al_load_bitmap("data/img/youWin.png");
    //Audios
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(1);
    wrongAnswer = al_load_sample("data/music/WrongAnswerSound.mp3");
    correctAnswer = al_load_sample("data/music/CorrectAnswerSound.mp3");
    victoryMusic = al_load_sample("data/music/VictoryMusic.mp3");
    //Fuentes
    ALLEGRO_FONT* arial70 = al_load_font("data/fonts/arial.ttf", 70, 0);
    ALLEGRO_FONT* arial35 = al_load_font("data/fonts/arial.ttf", 35, 0);
    //Tiempo
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	segundoTimer = al_create_timer(1.0);

	LoadCards();
    al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    int x = -1, y = -1;
    int botonesGame[] = { 0, 0, 0, 0 };
    turns = 0;
    bool isRunning = true;
    bool isPaused = true;
	attemps = 0;
    sec = 0;
    al_start_timer(segundoTimer);
    while (isRunning) {
        ALLEGRO_EVENT Evento;
        al_wait_for_event(event_queue, &Evento);
        al_draw_bitmap(background, 0, 0, 0);
        al_draw_text(arial35, al_map_rgb(0, 0, 0), 70, 55, NULL, (to_string(attemps)).c_str());  // Imprimir texto
        DrawCards();
        x = Evento.mouse.x;
        y = Evento.mouse.y;
        if (Evento.type == ALLEGRO_EVENT_TIMER) {
            if (Evento.timer.source == segundoTimer) {
                sec++;
                timReset++;
            }
        }
        al_draw_text(arial35, al_map_rgb(0, 0, 0), 1080, 55, NULL, (to_string(sec)).c_str());

        if (Evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            isRunning = false;
        }

        if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            botonesGame[0] = (x >= 375 && x <= 575 && y >= 50 && y <= 100) ? 1 : 0; 
            botonesGame[1] = (x >= 625 && x <= 825 && y >= 50 && y <= 100) ? 1 : 0;
        }
        if(!isPaused) al_draw_bitmap(continue1, 625, 50, 0);

        if (botonesGame[0]) al_draw_bitmap(surrenderHover, 375, 50, 0);
        if (botonesGame[1]) {
                if(isPaused) al_draw_bitmap(pauseHover, 625, 50, 0);
                else al_draw_bitmap(continue2, 625, 50, 0);
        }


        if (Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (Evento.mouse.button & 1) {
                if (botonesGame[0] == 1) {
                    isRunning = false;
                }
                if (botonesGame[1] == 1) {
                    if (isPaused) {
                        al_stop_timer(segundoTimer);
                        isPaused = false;
                    }
                    else {
                        al_start_timer(segundoTimer);
                        isPaused = true;
                    }
                }
            }
        }

        if (isPaused) {
            if (Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                for (int i = 0; i < cards.size(); i++) {
                    if (x >= cards[i].getPositionTop()[0] && x <= cards[i].getPositionBottom()[0] && y >= cards[i].getPositionTop()[1] && y <= cards[i].getPositionBottom()[1]) {
                        if (Evento.mouse.button & 1 && flippedCards.size() < 2 && !cards[i].IsFlipped()) {
                            cards[i].Flip();
                            flippedCards.push_back(&cards[i]);
                            timReset = 0;
                            //std::cout << flippedCards[flippedCards.size() - 1].getName() << flippedCards.size() << std::endl;
                        }
                    }
                }
            }
            if (flippedCards.size() >= 2 && timReset == 1) {
                checkMatch();
            }
        }

		if (checkWin()) {
            al_play_sample(victoryMusic, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            al_draw_bitmap(youWin, 350, 250, 0);
            al_stop_timer(segundoTimer);

            al_draw_bitmap(playAgain1, 500, 450, 0);
            al_draw_bitmap(quit1, 500, 550, 0);

            if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
                botonesGame[2] = (x >= 500 && x <= 700 && y >= 450 && y <= 500) ? 1 : 0;
                botonesGame[3] = (x >= 500 && x <= 700 && y >= 550 && y <= 600) ? 1 : 0;
            }
            if (botonesGame[2]) al_draw_bitmap(playAgain2, 500, 450, 0);
            if (botonesGame[3]) al_draw_bitmap(quit2, 500, 550, 0);
              
            if (Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (Evento.mouse.button & 1) {
                    if (botonesGame[2] == 1) {
                        ResetGame();
                        al_start_timer(segundoTimer); // Reinicia el temporizador
                    }
                    if (botonesGame[3] == 1) {
                        isRunning = false;
                    }
                }
            }
		}
        al_flip_display();
    }
    al_destroy_bitmap(background);
    al_destroy_bitmap(pauseHover);
    al_destroy_bitmap(surrenderHover);
    al_destroy_bitmap(playAgain1);
    al_destroy_bitmap(playAgain2);
    al_destroy_bitmap(quit1);
    al_destroy_bitmap(quit2);
    al_destroy_bitmap(continue1);
    al_destroy_bitmap(continue2);
    al_destroy_bitmap(youWin);

    
    al_destroy_sample(wrongAnswer);
    al_destroy_sample(correctAnswer);
    al_destroy_sample(victoryMusic);
    al_uninstall_audio();
    al_destroy_font(arial70);
    al_destroy_font(arial35);
    al_destroy_event_queue(event_queue);
    for (int i = 0; i < cards.size(); i++) {
        al_destroy_bitmap(cards[i].getcurrentImg());
    }
	al_destroy_timer(segundoTimer);
	cards.clear();
	cardNames.clear();
    return;
}


/**
 * @brief Loads and initializes the cards for the game.
 * 
 * This function sets the seed for random number generation based on the current time,
 * shuffles the card names, creates pairs of cards, shuffles the cards, and sets their positions
 * on the game board.
 */
void Game::LoadCards() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine{ seed };
    SetCardNames();
    std::shuffle(cardNames.begin(), cardNames.end(), rng);
    for (int i = 0; i < numPairs; i++) {
        cards.push_back(Card("data/img/Cartas/" + cardNames[i] + ".png", cardNames[i]));
        cards.push_back(Card("data/img/Cartas/" + cardNames[i] + ".png", cardNames[i]));
    }
    
    std::shuffle(cards.begin(), cards.end(), rng);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            cards[i * 6 + j].setPosition(new int[2] {50 + 200 * j, 200 + 200 * i}, new int[2] {150 + 200 * j, 350 + 200 * i});
        }
    }
}



/**
 * @brief Draws the cards on the game board.
 * 
 * This function iterates through the vector of cards and draws each card's current image
 * at its specified position on the game board using the Allegro library's drawing functions.
 */
void Game::DrawCards() {
	for (int i = 0; i < cards.size(); i++) {
		al_draw_bitmap(cards[i].getcurrentImg(), cards[i].getPositionTop()[0], cards[i].getPositionTop()[1], 0);
	}
}


/**
 * @brief Sets the names of the cards to be used in the game.
 * 
 * This function initializes the cardNames vector with a predefined list of card names.
 * These names are used to load the corresponding card images and create pairs of cards
 * for the memory game.
 */
void Game::SetCardNames() {
    cardNames.push_back("Arcanine");
    cardNames.push_back("Executor");
    cardNames.push_back("Gengar");
    cardNames.push_back("Marowak");
    cardNames.push_back("Mew");
    cardNames.push_back("Vaporeon");
    cardNames.push_back("Nidoking");
    cardNames.push_back("Nidoqueen");
    cardNames.push_back("Pidgeot");
    cardNames.push_back("Starmie");
    cardNames.push_back("Mewtwo");
    cardNames.push_back("Charmander");
    cardNames.push_back("Bulbasaur");
    cardNames.push_back("Aerodactyl");
    cardNames.push_back("Pikachu");
    cardNames.push_back("Blastoise");
    cardNames.push_back("Moltres");
    cardNames.push_back("Zapdos");
    cardNames.push_back("Gyarados");
    cardNames.push_back("Machamp");
    cardNames.push_back("Celebi");
    cardNames.push_back("Squirtel");
}

/**
 * @brief Checks if the two flipped cards match.
 * 
 * This function compares the names of the two flipped cards. If they match, it sets them as matched
 * and plays the correct answer sound. If they do not match, it flips them back and plays the wrong answer sound.
 * The function also increments the attempt counter if the cards do not match.
 */
void Game::checkMatch() {
    if (!flippedCards[0]->checkName(flippedCards[1]->getName())) {
        flippedCards[0]->Flip();
        flippedCards[1]->Flip();
        al_play_sample(wrongAnswer, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
        attemps++;

    }
    else {
        flippedCards[0]->setMatched();
        flippedCards[1]->setMatched();
        al_play_sample(correctAnswer, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

    }
    flippedCards.erase(flippedCards.begin());
    flippedCards.erase(flippedCards.begin());
}

/**
 * @brief Checks if the player has won the game.
 * 
 * This function iterates through the vector of cards and checks if all cards have been found.
 * If all cards are found, it returns true indicating the player has won the game.
 * Otherwise, it returns false.
 */
bool Game::checkWin() {
    for (int i = 0; i < cards.size(); i++) {
        if (!cards[i].IsFound()) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Resets the game to its initial state.
 * 
 * This function stops all audio samples, destroys all card bitmaps, clears the card and flipped card vectors,
 * resets the game variables (turns, seconds, timer reset, attempts), and reloads the cards to start a new game.
 */
void Game::ResetGame()
{
    al_stop_samples();
    for (int i = 0; i < cards.size(); i++) {
        al_destroy_bitmap(cards[i].getcurrentImg());
    }
    cards.clear();
    flippedCards.clear();
    turns = 0;
    sec = 0;
    timReset = 0;
    al_start_timer(segundoTimer); 
    attemps = 0;
    LoadCards();
}


