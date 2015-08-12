#ifndef CARDSTACK_H
#define CARDSTACK_H
#include "Card.h"
#include <string>
#include <vector>

class CardStack
{
public:
    CardStack();
    virtual ~CardStack();
    Card getCard(int);
    int getSize();
    void addCard(Card);
    void removeCard(int);
    void removeTop();
    void clearStack();
    bool isEmpty();
    void moveAll(CardStack *);

protected:
    std::vector<Card> cards;

private:


};

#endif // CARDSTACK_H
