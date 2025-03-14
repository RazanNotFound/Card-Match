//Card
#include "Game.hpp"
#include "Deck.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include "PenaltyCard.hpp"
#include "BonusCard.hpp"
#include "StandardCard.hpp"
#include <iostream>


using namespace std;


//getters and setters

//number

int Card::getNumber() {
    return number;
}
void Card::setNumber(int number) {
    this->number=number;
}

//face up
bool Card::isFaceUp() {
    return faceUp;
}
void Card::setFaceUp(bool state){ 
    faceUp = state; 
}

//type
void Card::setType(string type) {
    this->type=type;
}
string Card::getType() {
    return this->type;
}

//matched
bool Card::isMatched(){
    return matched;
}
void Card::setMatched(bool state){
    matched = state;
}


//methods
void Card::display() {
    string up = "|_*_|";
    if (isFaceUp() == true && isMatched() == false){
        cout << "|_" << getNumber() << "_|";
    }
    else if (isMatched() == true){
        cout << "|___|";
    }
    else{
        cout << up;
    }
}



//----------------------------------------------------------------------------
//DECK

Deck::Deck(int gridSize) : gridSize(gridSize), totalCards(gridSize * gridSize) {

    cards = new Card*[totalCards]; 

    int number = 1;
    for (int i = 0; i < totalCards-4; i +=2) {
        cards[i] = new StandardCard(number);     // First card
        cards[i + 1] = new StandardCard(number); // Matching pair
        number++;
    }
    cards[totalCards-4] = new BonusCard();
    cards[totalCards-3] = new BonusCard();
    cards[totalCards-2] = new PenaltyCard();
    cards[totalCards-1] = new PenaltyCard();
}

// Deck.cpp

Card** Deck::getCards() {
    return cards; // Return the array of Card pointers
}
//testing
void Deck::printDeckUp() {
    cout << "Deck of Cards: " << endl;
    for (int i = 0; i < totalCards; i++) {
        cards[i]->setFaceUp(true);
        cards[i]->display();
        cout << " ";
        if ((i + 1) % 4 == 0) {
            cout << endl;
        }
    }
    for (int i = 0; i < totalCards; i++) {
        cards[i]->setFaceUp(false);
    }
}
void Deck::printDeckUp2D(Card*** grid) {
    cout << "Deck of Cards (2D): " << endl;
    int rows = getGridSize();
    int cols = getGridSize();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j]->setFaceUp(true);
            grid[i][j]->display();
            cout << " "; 
        }
        cout << endl;
    }

    //reset the face up state of the cards
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j]->setFaceUp(false);
        }
    }
}

Card*** Deck::convertTo2DArray( Card** cards) {
        int rows = getGridSize();
        int cols = getGridSize();
        Card*** grid = new Card**[rows];
        for (int i = 0; i < rows; i++) {
            grid[i] = new Card*[cols];
            for (int j = 0; j < cols; j++) {
                grid[i][j] = cards[i * cols + j]; // Fill 2D array from 1D array
            }
        }
        return grid;
    }


// Destructor: Deletes all card objects
Deck::~Deck() {
    for (int i = 0; i < totalCards; i++) {
        delete cards[i];
    }
    delete[] cards;
}

int Deck::getGridSize(){
    return gridSize;
}

void Deck::setGridSize(int gridSize){
    this->gridSize=gridSize;
}

// Shuffles the deck
void Deck::shuffle() {
    srand(time(0));
    for (int i = 0; i < totalCards; i++) {
        int j = rand() % totalCards;
        Card* temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

// Displays the grid of cards
void Deck::displayGrid() const {
    for (int i = 0; i < totalCards; i++) {
        cards[i]->display();
        cout << " ";
        if ((i + 1) % gridSize == 0) {
            cout << endl;
        }
    }
}

void Deck::display2DArray(Card*** grid) {
    for (int i = 0; i < getGridSize(); i++) {
        for (int j = 0; j < getGridSize(); j++) {
            grid[i][j]->display(); // Call the display method of each Card
            cout << " "; // Add space between cards
        }
        cout << endl; // New line after each row
    }
}

int Deck::isAllMatched(Card*** grid) {
    int count = 0;
    for (int i = 0; i < getGridSize(); i++) {
        for (int j = 0; j < getGridSize(); j++) {
            if (grid[i][j]->isMatched()==false) {
                count++;
            }
        }
    }
    return count;
}


//----------------------------------------------------------------------------
//PLAYER


Player::Player(string name): name(name), score(0) {}


void Player::addScore(int points) {
    score += points;
}

void Player::displayScore() {
    cout << name << "'s score: " << score << endl;
}

int Player::getScore() {
    return score;
}

string Player::getName() {
    return name;
}

void Player::setName(string name) {
    this->name = name;
}
void getWinner(Player* player1, Player* player2) {
    cout << "____________________________________";
    cout << "Game Over!" << endl;
    cout << "____________________________________";
    cout << player1->getName() << "'s score: " << player1->getScore() << endl;
    cout << player2->getName() << "'s score: " << player2->getScore() << endl;
    if (player1->getScore() > player2->getScore()) {
        cout << player1->getName() << " wins!" << endl;
    } else if (player1->getScore() < player2->getScore()) {
        cout << player2->getName() << " wins!" << endl;
    } else {
        cout << "It's a tie!" << endl;
    }
}



//-----------------------------------------------------------------------------
//GAME

Game::Game(): gridSize(4){
    deck = new Deck(gridSize);
    player1 = new Player("Player 1");
    player2 = new Player("Player 2");
}



Game::~Game() {
    delete deck;
    delete player1;
    delete player2;
}

void Game::displayPlayers(){
        cout<<"Player 1: " << player1->getName()<< endl <<"Score: "<<player1->getScore() << endl <<"Player 2: " << player2->getName() << endl << "Score: " << player2->getScore() << endl;

}

void Game::playTurn(Player* player1, Player* player2, Card*** grid) {

    int flag = 0;

    int row1, col1, row2, col2;
    int gridSize = deck->getGridSize();
    Player* currentPlayer = player1;
    
    while (deck->isAllMatched(grid) >1) { // while unmatched cards is greater than 1
        
    
    cout << currentPlayer->getName() << "'s turn! Score: " << currentPlayer->getScore() << endl;

    // Coordinates of first card
    cout << "Enter coordinates of the first card: "<<endl;
    cout << "row: ";
    cin >> row1;
    cout << "column: ";
    cin >> col1;

    //is card a a valid choice? keep looping until valid
    while (row1 < 0 || row1 >= gridSize || col1 < 0 || col1 >= gridSize || grid[row1][col1] == nullptr || grid[row1][col1]->isFaceUp()) {
        cout << "Invalid choice. Try again: ";
        cout << "row: ";
        cin >> row1;
        cout << "column: ";
        cin >> col1;
    }

    //set face up of picked card
    grid[row1][col1]->setFaceUp(true);
    deck->display2DArray(grid);

    // Second card coordinates
    cout << "Enter coordinates of the first card: "<<endl;
    cout << "row: ";
    cin >> row2;
    cout << "column: ";
    cin >> col2;
    while (row2 < 0 || row2 >= gridSize || col2 < 0 || col2 >= gridSize || grid[row2][col2] == nullptr || grid[row2][col2]->isFaceUp() || (row1 == row2 && col1 == col2)) {
        cout << "Invalid choice. Try again: ";
        cout << "row: ";
        cin >> row1;
        cout << "column: ";
        cin >> col1;
    }
    grid[row2][col2]->setFaceUp(true);
    deck->display2DArray(grid);


    // Check match
  
    // Match logic
    if (grid[row1][col1]->getNumber() == grid[row2][col2]->getNumber() && grid[row1][col1]->getType() == "StandardCard" && grid[row2][col2]->getType() == "StandardCard") { //case both cards are standard
        cout << "Match! Score updated." << endl;
        grid[row1][col1]->setMatched(true);
        grid[row2][col2]->setMatched(true);
        currentPlayer->addScore(1);
        flag =2;

    } else if(grid[row1][col1]->getType() == "BonusCard" && grid[row2][col2]->getType() == "BonusCard"){ //case two cards are bonus
     grid[row1][col1]->setMatched(true);
     grid[row2][col2]->setMatched(true);

     cout << "Bonus Match :D You may either gain +2 points or gain one point and another turn" << endl;
        cout << "1. +2 points" << endl;
        cout << "2. Another turn" << endl;
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "+2 points added." << endl;
            currentPlayer->addScore(2);
        } else {
            cout << "Take another turn!" << endl;
            currentPlayer->addScore(1);
            flag = 2;
        }
    
    } else if (grid[row1][col1]->getType() == "BonusCard" && grid[row2][col2]->getType() == "StandardCard" || grid[row1][col1]->getType() == "StandardCard" && grid[row2][col2]->getType() == "BonusCard") { //case one card is a bonus
        cout << "Bonus Match! Score updated." << endl;
        currentPlayer->addScore(1);
        if (grid[row1][col1]->getType() == "BonusCard"){
            grid[row1][col1]->setMatched(true); //bonus card should be set as matched
            grid[row2][col2]->setFaceUp(false); //other card hidden again
        } else{
            grid[row2][col2]->setMatched(true); //card 2 is the bonus card, so it should be set as matched
            grid[row1][col1]->setFaceUp(false); //other card hidden again
        }
    }
    else if (grid[row1][col1]->getType() == "PenaltyCard" && grid[row2][col2]->getType() == "PenaltyCard") { //case two cards are a penalty
        cout << "Penalty Match :( You may either skip a turn or lose points." << endl;
        cout << "1. Skip a turn" << endl;
        cout << "2. Lose points" << endl;
        
        
        int choice;
        cin >> choice;
        if (choice == 2) {
            cout << "Points deducted." << endl;
            currentPlayer->addScore(-2);
        } else {
            currentPlayer->addScore(-1);
            cout << "Skipping turn." << endl;
            flag = 1;
        }
        grid[row1][col1]->setFaceUp(true);
        grid[row1][col1]->setMatched(true);
        grid[row2][col2]->setFaceUp(true);
        grid[row2][col2]->setMatched(true);


    }
    else if (grid[row1][col1]->getType() == "PenaltyCard" && grid[row2][col2]->getType() == "StandardCard" || grid[row1][col1]->getType() == "StandardCard" && grid[row2][col2]->getType() == "PenaltyCard") {
    cout << "Penalty Match! Score deducted." << endl;
    currentPlayer->addScore(-1);
    if (grid[row1][col1]->getType() == "PenaltyCard") {
        grid[row1][col1]->setMatched(true);
        grid[row2][col2]->setFaceUp(false);
    } else {
        grid[row2][col2]->setMatched(true);
        grid[row1][col1]->setFaceUp(false);
    }
    }
    else if (grid[row1][col1]->getType() == "PenaltyCard" && grid[row2][col2]->getType() == "BonusCard" || grid[row1][col1]->getType() == "BonusCard" && grid[row2][col2]->getType() == "PenaltyCard") {
        cout << "Penalty and bonus matched. No change in points." << endl;
        grid[row1][col1]->setFaceUp(true);
        grid[row1][col1]->setMatched(true);
        grid[row2][col2]->setFaceUp(true);
        grid[row2][col2]->setMatched(true);
    }
     else { //case no match
        cout << "No match. Cards will be flipped back." << endl;
        grid[row1][col1]->setFaceUp(false);
        grid[row2][col2]->setFaceUp(false);
    }

         cout << currentPlayer->getName() << "'s score: " << currentPlayer->getScore() << endl;

        cout << "Press Enter to Continue\n";
        cin.ignore();
        cin.get(); // normal cin >> doesnt work for Enter key




        // 2 cases for the following if statements, penalty and bonus.
        // if penalty, flag is set to 1, swaps turns normally then opp player should play atleast 2 turns in a row
        // flag is incremented to 2 to prevent a swap again aka skip turn. it skips turn then is incremented to 3, after which it is reset to 0 to be normal

        // if bonus, its set to 2 to immediately prevent a swap and play an extra turn then incremented to 3 to swap normally again and ofc reset after to 0

        // not sure what would h  appen or what should happen for the case if penalty is rolled then immediately after the opp rolls a bonus turn.


        if (flag!=2) //1 runs // flag = 2 // flag = 3
            {
            if (currentPlayer == player1) {
                currentPlayer = player2;

            } else {
                currentPlayer = player1;

            }


        }
        if (flag!=0)
        {
            flag++;
        }else if (flag==3)
        {
            flag = 0;
        }

    }


    getWinner(player1, player2);
}


void Game::initializeGame() {
    cout << "Initializing the game..." << endl;
    //testing
    displayPlayers();
    Card** cards = deck->getCards(); 
    deck->shuffle();
    // Get the cards array from the deck
    Card*** grid = deck->convertTo2DArray(cards);
    //displayGrid();

    deck->display2DArray(grid);
    deck->printDeckUp2D(grid); //testing
    //displayGrid();
    playTurn(player1, player2, grid);
    //playTurn(player2, grid);
}


void Game::displayGrid() const {
    deck->displayGrid();
}

//-----------------------------------------------------------------------------
//MAIN METHOD
int main() {
    Game game;
    game.initializeGame();
    
    return 0;
}


