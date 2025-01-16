#pragma once
#include<allegro5/allegro.h>
#include <string>
#include <random>

/**
 * @class Card
 * @brief Represents a card in a card matching game.
 *
 * The Card class encapsulates the properties and behaviors of a card used in a card matching game.
 * Each card has a front image, a back image, a name, and positional information. The card can be
 * flipped to reveal its front image, and it can be marked as found when matched with another card.
 *
 * Attributes:
 * - imgFrontPath: Path to the image file for the front of the card.
 * - imgBackPath: Path to the image file for the back of the card.
 * - cardName: Name of the card.
 * - currentImg: Pointer to the current image being displayed (either front or back).
 * - isFlipped: Boolean indicating whether the card is currently flipped to show the front image.
 * - isFound: Boolean indicating whether the card has been matched and found.
 * - positionTop: Array holding the top position coordinates of the card.
 * - positionBottom: Array holding the bottom position coordinates of the card.
 *
 * Methods:
 * - Card(): Default constructor.
 * - Card(std::string imgFrontPath, std::string cardName): Parameterized constructor.
 * - void Flip(): Flips the card to show the opposite side.
 * - bool IsFlipped(): Returns whether the card is flipped.
 * - bool IsFound(): Returns whether the card has been found.
 * - void setPosition(int* positionTop, int* positionBottom): Sets the position of the card.
 * - std::string getImgFrontPath(): Returns the path to the front image.
 * - std::string getImgBackPath(): Returns the path to the back image.
 * - std::string getName(): Returns the name of the card.
 * - void setMatched(): Marks the card as found.
 * - ALLEGRO_BITMAP* getcurrentImg(): Returns the current image being displayed.
 * - bool checkName(std::string nameOther): Checks if the given name matches the card's name.
 * - int* getPositionTop(): Returns the top position coordinates.
 * - int* getPositionBottom(): Returns the bottom position coordinates.
 */

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

