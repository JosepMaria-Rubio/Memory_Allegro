#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <string>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Card.h"

using namespace std;

class Game {
	private:
		std::vector<std::string> cardNames;
		std::vector<Card> cards;
		int numPairs;
		int turns;
		//ALLEGRO_TIMER* timer;
	public:
		Game();
		void InitializeGame();
		void StartGame(ALLEGRO_DISPLAY* ventana);
		void LoadCards();
		void DrawCards();
		void SetCardNames();
};

