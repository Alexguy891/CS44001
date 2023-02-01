// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cctype>

using std::cout; using std::cin; using std::endl;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
   Game():playersCount_(0), movesCount_(0), playerWon_(noWinner){}

   // template method
   void playGame(const int playersCount = 0) {
        playersCount_ = playersCount;
        movesCount_=0;

        initializeGame();

        for(int i=0; !endOfGame(); i = (i+1) % playersCount_ ){
	        makeMove(i);
            if (i==playersCount_-1) 
                ++movesCount_; 
        }

        printWinner();
    }

    virtual ~Game(){}
protected:
    // primitive operations
    virtual void initializeGame() = 0;
    virtual void makeMove(int player) = 0;
    virtual void printWinner() = 0;
    virtual bool endOfGame() { return playerWon_ != noWinner;} // this is a hook
                   // returns true if winner is decided
    static const int noWinner=-1;

    int playersCount_;
    int movesCount_;
    int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
    // implementing concrete methods
    void initializeGame(){
        playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
    }

    void makeMove(int player) {
        if (movesCount_ > minMoves_){ 
	        const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
	        if (chance < movesCount_) playerWon_= player;
        }
   }

   void printWinner(){
        cout << "Monopoly, player "<< playerWon_<< " won in "
	        << movesCount_<< " moves." << endl;
   }

private:
    static const int numPlayers_ = 8; // max number of players
    static const int minMoves_ = 20; // nobody wins before minMoves_
    static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess: public Game {
public:
    void initializeGame(){
        playersCount_ = numPlayers_; // initalize players
        for(int i=0; i < numPlayers_; ++i) 
	        experience_[i] = rand() % maxExperience_ + 1; 
   }

   void makeMove(int player){
        if (movesCount_ > minMoves_){
	        const int chance = (rand() % maxMoves_) / experience_[player];

	        if (chance < movesCount_)
                playerWon_= player;
        }
    }

   void printWinner(){
        cout << "Chess, player " << playerWon_ 
	        << " with experience " << experience_[playerWon_]
	        << " won in "<< movesCount_ << " moves over"
	        << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
            << endl;
    }

private:
    static const int numPlayers_ = 2;
    static const int minMoves_ = 2; // nobody wins before minMoves_
    static const int maxMoves_ = 100; // somebody wins before maxMoves_
    static const int maxExperience_ = 5; // player's experience
                              // the higher, the greater probability of winning
    int experience_[numPlayers_]; 
};

class Dice: public Game {
public:  
    // implementing concrete methods
    void initializeGame(){
        playersCount_ = numPlayers_; // initialize players

        for(auto &i: passArr_) // initialize passArr to all false
            i = false;
    }

    void makeMove(int player) {
        if(movesCount_ == maxMoves_ || passArr_[0] && passArr_[1]) { // check if reached max rounds or both passed
            playerWon_ = scores_[0] > scores_[1] ? 0 : 1;
        }

        if(player == 1) // determines if user or computer
            cout << "You ";
        else
            cout << "Round " << movesCount_ + 1 << ": Computer ";

        if(!passArr_[player]) { // check if player passed
            cout << "rolled: ";

            int rolls[numRolls_];
            int total = 0;

            for(auto &i: rolls) { // calculate dice rolls
                i = rand() % maxRoll_ + 1;
                total += i;
                cout << i << " ";
            }

            if(total > scores_[player]) // set high score
                scores_[player] = total;
        } else
            cout << "passed, ";

        if(player == 0) // determine printing computer or user scores
            cout << "computer's, ";
        else
            cout << "your ";

        cout << "score = " << scores_[player] << endl;

        if(!passArr_[player] && player == 1 && movesCount_ < maxMoves_ - 1) { // check if user pased or reached end
            cout << "Roll again? [y/n] ";
            char c;
            cin >> c;

            if(tolower(c) == 'n') // set pass arr if user passed
                passArr_[player] = true;
            
            cout << endl;
        } else if (!passArr_[player] && player == 0) { // random computer pass
            passArr_[player] = rand() % 2; // 0 roll again, 1 pass 
        }
    }

   void printWinner(){ // print winner
        if(playerWon_ > 0) // print winner if player won
            cout << "You won!\n\n";
        else
            cout << "You lose!\n\n";
    }

private:
    static const int numPlayers_ = 2; // max number of players
    static const int maxMoves_ = 3; // somebody wins before maxMoves_
    static const int numRolls_ = 5; // number of dice rolled
    static const int maxRoll_ = 6; // holds highest number on die
    bool passArr_[numPlayers_]; // holds rounds passed
    int scores_[numPlayers_]; // holds high scores
};

int main() {
    srand(time(nullptr));

    Game* gp = nullptr;

    // play chess 8 times
    for (int i = 0; i < 8; ++i){ 
        gp = new Chess;
        gp->playGame(); 
        delete gp;
    }
      

    // play monopoly 8 times
    for (int i = 0; i < 8; ++i){
        gp = new Monopoly;
        gp->playGame(); 
        delete gp;
    }

    // play dice 8 times
    for (int i = 0; i < 8; ++i){
        gp = new Dice;
        gp->playGame(); 
        delete gp;
    }
}

