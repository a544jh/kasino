#ifndef CAPTURESELECTION_H
#define CAPTURESELECTION_H
#include "Card.h"
#include "CardStack.h"


class CaptureSelection
{
    public:
        CaptureSelection(Card, CardStack);
        bool isValid();
        virtual ~CaptureSelection();
        Card getCaptureCard();
        CardStack getSelectedCards();
    protected:
    private:
        Card captureCard;
        CardStack selectedCards;
};

#endif // CAPTURESELECTION_H
