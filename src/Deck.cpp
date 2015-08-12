#include "Deck.h"
#include <random>
#include <time.h>


Deck::Deck()
{

    //ctor
}

void Deck::fillDeck()
{
    int r;
    int s;

    for (r = 1; r <= 13; r++)
    {
        for (s = Card::spades; s <= Card::clubs; s++)
        {
            Card nextcard (r, Card::Suit(s));
            cards.push_back(nextcard);
        }
    }

}

void Deck::shuffle()
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution (0,51);
    generator.seed(time(NULL));

    int i;
    for(i = 0; i <= 51; i++)
    {
        int rnd = distribution(generator);
        Card tmp = cards[rnd];
        cards[rnd] = cards[i];
        cards[i] = tmp;
    }

}

Card Deck::drawTop()
{
    Card card = cards.back();
    cards.pop_back();
    return card;
}



Deck::~Deck()
{
    //dtor
}
