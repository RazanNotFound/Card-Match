using namespace std;
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Card.hpp"
#include "Deck.hpp"
#include "Player.hpp"

class Game {
private:
    Deck* deck;
    Player* player1;
    Player* player2;
    int gridSize;

public:
    Game();
    ~Game();
    void playTurn(Player* player1, Player* player2, Card*** grid);
    void displayPlayers();
    void initializeGame();
    void displayGrid() const;
};

#endif