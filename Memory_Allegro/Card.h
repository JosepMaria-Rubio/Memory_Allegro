#pragma once
#include<allegro5/allegro.h>
#include <string>
#include <random>
class Card {
	private:
		std::string imgFrontPath;
		std::string imgBackPath;
		std::string cardName;
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
		int* getPositionTop();
		int* getPositionBottom();
};

