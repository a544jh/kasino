#include "CardStack.h"

CardStack::CardStack()
{
    //ctor
}

Card CardStack::getCard (int i)
{
    return cards[i];
}

int CardStack::getSize()
{
    return cards.size();
}

void CardStack::addCard(Card c)
{
    cards.push_back(c);
}

void CardStack::removeCard(int c)
{
    cards.erase(cards.begin() + c);
}

void CardStack::removeTop()
{
    cards.pop_back();
}

void CardStack::clearStack()
{
    cards.clear();
}

bool CardStack::isEmpty()
{
    return cards.empty();
}

void CardStack::moveAll(CardStack * s)
{
    if (!isEmpty())
    {
        for (int i = 0; i <= getSize() - 1; i++)
        {
            s->addCard(getCard(i));
        }
        clearStack();
    }
}

CardStack::~CardStack()
{
    //dtor
}
