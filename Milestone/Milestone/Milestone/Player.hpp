#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;
class Player {
private:
    string name;
    int score;
public:

    Player(){}
    Player(string name);


    void addScore(int points);
    void displayScore() ;
    int getScore();
    string getName();
    void setName(string name);
};

#endif // PLAYER_H
