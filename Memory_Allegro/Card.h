#pragma once
#include<allegro5/allegro.h>
#include <string>
#include <random>
class Card {
	private:
		std::string imgFrontPath;
		std::string imgBackPath;
		std::string cardName;
		ALLEGRO_BITMAP* currentImg;
		bool isFlipped;
		bool isFound;
		int positionTop[2];
		int positionBottom[2];
	public:
		Card();
		Card(std::string imgFrontPath, std::string cardName);
		void Flip();
		bool IsFlipped();
		bool IsFound();
		void setPosition(int* positionTop, int* positionBottom);
		std::string getImgFrontPath();
		std::string getImgBackPath();
		std::string getName();
		void setMatched();
		ALLEGRO_BITMAP* getcurrentImg();
		bool checkName(std::string nameOther);
		int* getPositionTop();
		int* getPositionBottom();
};

