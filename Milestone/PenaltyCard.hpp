#ifndef PENALTYCARD_H
#define PENALTYCARD_H

#include "Card.hpp"

class PenaltyCard : public Card {
private:
    int penaltyPoints;

public:
    // Default constructor
    PenaltyCard() : Card(8, "PenaltyCard") {}

    // Parameterized constructor
    PenaltyCard(int number, int penaltyPoints = -1) 
        : Card(number, "PenaltyCard"), penaltyPoints(penaltyPoints) {}

    int getPenaltyPoints() const { return penaltyPoints; }
    void setPenaltyPoints(int points) { penaltyPoints = points; }
};

#endif // PENALTYCARD_H
