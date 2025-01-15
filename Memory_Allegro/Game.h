#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <string>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
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
		std::vector<Card*> flippedCards;
		ALLEGRO_TIMER* segundoTimer;
		int numPairs;
		int turns;
		int attemps = 0;
		int sec = 0;
		int timReset = 0;
		ALLEGRO_SAMPLE* wrongAnswer;
		ALLEGRO_SAMPLE* correctAnswer;
		ALLEGRO_SAMPLE* victoryMusic;
	public:
		Game();
		void InitializeGame();
		void StartGame(ALLEGRO_DISPLAY* ventana);
		void LoadCards();
		void DrawCards();
		void SetCardNames();
		void checkMatch();
		bool checkWin();
		void ResetGame();

};

