#include "Card.h"

Card::Card(int r, Suit s)
{
    card_rank=r;
    card_suit=s;
    //ctor
}

Card::Card()
{

}


string Card::suitString(Suit s)
{
    if (s == spades)
        return "spades";
    else if (s == hearts)
        return "hearts";
    else if (s == diamonds)
        return "diamonds";
    else
        return "clubs";

}

string Card::rankString(int r)
{
    if (1 == r)       return "ace";
    else if (2 == r)  return "two";
    else if (3 == r)  return "three";
    else if (4 == r)  return "four";
    else if (5 == r)  return "five";
    else if (6 == r)  return "six";
    else if (7 == r)  return "seven";
    else if (8 == r)  return "eight";
    else if (9 == r)  return "nine";
    else if (10 == r) return "ten";
    else if (11 == r) return "jack";
    else if (12 == r) return "queen";
    else
        return "king";

}


string Card::toString()
{
    return rankString(card_rank) + " of " + suitString(card_suit);
}

int Card::getRank()
{
    return card_rank;
}

int Card::getHandValue()
{
    if (card_rank == 1)
    {
        return 14;
    }
    else if (card_rank == 2 && card_suit == spades)
    {
        return 15;
    }
    else if (card_rank == 10 && card_suit == diamonds)
    {
        return 16;
    }
    else
        return card_rank;
}

int Card::getTableValue()
{
    return card_rank;
}

Card::~Card()
{
    //dtor
}

