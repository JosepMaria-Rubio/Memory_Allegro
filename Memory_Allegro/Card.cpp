#include "Card.h"

Card::Card() {
}

Card::Card(std::string imgFrontPath, std::string cardName) {
	this->imgFrontPath = imgFrontPath;
	imgBackPath = "data/img/Cartas/Reverso.png";
	currentImg = al_load_bitmap(imgBackPath.c_str());
	this->cardName = cardName;
	isFlipped = false;
	isFound = false;
	for (int i = 0; i < 2; i++) {
		positionTop[i] = 0;
		positionBottom[i] = 0;
	}
}

void Card::Flip() {
	if (isFlipped) {
		currentImg = al_load_bitmap(imgBackPath.c_str());
		isFlipped = false;
	}
	else {
		currentImg = al_load_bitmap(imgFrontPath.c_str());
		isFlipped = true;
	}
}

bool Card::IsFlipped() {
	return isFlipped;
}

bool Card::IsFound() {
	return isFound;
}

void Card::setPosition(int* positionTop, int* positionBottom) {
	for (int i = 0; i < 2; i++) {
		this->positionTop[i] = positionTop[i];
		this->positionBottom[i] = positionBottom[i];
	}
}



std::string Card::getImgFrontPath() {
	return imgFrontPath;
}

std::string Card::getImgBackPath() {
	return imgBackPath;
}

ALLEGRO_BITMAP* Card::getcurrentImg() {
	return currentImg;
}

int* Card::getPositionTop() {
	return positionTop;
}

int* Card::getPositionBottom() {
	return positionBottom;
}