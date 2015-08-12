#ifndef DECK_H
#define DECK_H

#include <CardStack.h>


class Deck : public CardStack
{
    public:
        Deck();
        virtual ~Deck();
        void fillDeck();
        void shuffle();
        Card drawTop();
    protected:
    private:
};

#endif // DECK_H
