#ifndef STANDARDCARD_H
#define STANDARDCARD_H

#include "Card.hpp"

class StandardCard : public Card {

public:
//constructors
    // Default constructor
    StandardCard() : Card(0, "StandardCard") {}

    // Parameterized constructor
    StandardCard(int number) : Card(number, "StandardCard") {}
    
    //method

};

#endif // STANDARDCARD_H