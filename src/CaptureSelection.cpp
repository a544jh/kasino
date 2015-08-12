#include "CaptureSelection.h"
#include <algorithm>

CaptureSelection::CaptureSelection(Card c, CardStack sc)
{
    captureCard = c;
    selectedCards = sc;
    //ctor
}

bool CaptureSelection::isValid()
{
    int i;
    std::vector<int> tableValues;
    int sameValue;
    int sum = 0;
    for (i=0;i<=selectedCards.getSize() -1;i++)
    {
        tableValues.push_back(selectedCards.getCard(i).getTableValue());
    }
    sameValue = std::count(tableValues.begin(), tableValues.end(), captureCard.getHandValue());
    for(std::vector<int>::iterator j=tableValues.begin(); j != tableValues.end(); j++)
    {
        sum += *j;
    }
    if (captureCard.getHandValue() == sum)
        return true;
    //Q, (Q + 9 + 3)
    else if ((sameValue + 1) * captureCard.getHandValue() == sum && sameValue >= 1)
        return true;
    //Q, (Q + Q + Q)
    else if (sameValue * captureCard.getHandValue() == sum && sameValue > 1)
        return true;
    else
        return false;

}

Card CaptureSelection::getCaptureCard()
{
    return captureCard;
}

CardStack CaptureSelection::getSelectedCards()
{
    return selectedCards;
}

CaptureSelection::~CaptureSelection()
{
    //dtor
}
