#ifndef DECK_H
#define DECK_H


#include <iostream>
using namespace std;

class Deck {
private:
    int gridSize;
    int totalCards;
    Card** cards;
    //Card** originalCards;

public:
    void printDeckUp(); //testing
    Card** getCards();
    // Parameterized constructor
    void printDeckUp2D(Card*** grid);
    Deck(int gridSize);
    Card*** convertTo2DArray(Card** cards);
    void display2DArray(Card*** grid);
    int getGridSize();
    void setGridSize(int gridSize);
    void shuffle();
    void displayGrid() const;
    int isAllMatched(Card*** grid);
    ~Deck(); 
};

#endif
