#ifndef PLAYER_H
#define PLAYER_H
#include "Deck.h"
#include "CardStack.h"
#include "CaptureSelection.h"

class Player
{
    public:
        Player();
        Player (string);
        string getName();
        virtual ~Player();
        bool drawCard(Deck *);
        CardStack * getHand();
        CardStack * getCaptured();
        int getScore();
        void addScore(int);
        void removeScore(int);
        int getSweeps();
        void addSweeps(int);
        void removeSweeps(int);
        void moveToTable(int, CardStack *);
        void makeCapture(CaptureSelection,int);
    protected:
    private:
        string name;
        int sweeps;
        int score;
        bool isAI;
        CardStack hand;
        CardStack captured;
};

#endif // PLAYER_H
