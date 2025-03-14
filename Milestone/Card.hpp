
#ifndef CARD_H //check if CARD_H is not defined (header guard)
#define CARD_H //define CARD_H

#include <iostream>
using namespace std;

class Card
{
private:
   int number;
   bool faceUp;
   string type;
   bool matched;

public:
    //constructore
    // Default constructor
    Card() : number(0), faceUp(false), type("Card"), matched(false) {}

    // Parameterized constructor
    Card(int number, const string& type, bool faceUp = false, bool matched = false) : number(number), faceUp(faceUp), type(type), matched(matched) {}

    //Getters and setters
    int getNumber();
    void setNumber(int number);

    virtual string getType();
    virtual void setType(string type);
    
    bool isFaceUp();
    void setFaceUp(bool state);
    
    bool isMatched();
    void setMatched(bool state);

    //methods
    void display();
    
    //destructor
    virtual ~Card() {};

};


#endif //end of guard