#ifndef CARD_H
#define CARD_H
#include <string>
using namespace std;


class Card
{
    public:
        enum Suit {spades, hearts, diamonds, clubs};
        Card();
        Card(int, Suit);
        string toString();
        string suitString(Suit);
        string rankString(int);
        int getRank();
        int getHandValue();
        int getTableValue();
        virtual ~Card();

    protected:
    private:
        int card_rank;
        Suit card_suit;
};

#endif // CARD_H
