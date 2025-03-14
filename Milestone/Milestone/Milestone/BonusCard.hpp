#ifndef BONUSCARD_H
#define BONUSCARD_H

#include "Card.hpp"

class BonusCard : public Card {
private:
    int bonusPoints;

public:
    // Default constructor
    BonusCard() : Card(7, "BonusCard") {}

    // Parameterized constructor
    BonusCard(int number, int bonusPoints = 10) 
        : Card(number, "BonusCard"), bonusPoints(bonusPoints) {}

    int getBonusPoints() const { return bonusPoints; }
    void setBonusPoints(int points) { bonusPoints = points; }
};

#endif // BONUSCARD_H
