#include "Card.h"

Card::Card(std::string imgFrontPath, std::string cardName) {
	this->imgFrontPath = imgFrontPath;
	imgBackPath = "data/img/Cartas/Reverso.png";
	this->cardName = cardName;
	isFlipped = false;
	isFound = false;
}

void Card::Flip() {
	isFlipped = !isFlipped;
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

int* Card::getPositionTop() {
	return positionTop;
}

int* Card::getPositionBottom() {
	return positionBottom;
}