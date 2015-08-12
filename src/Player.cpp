#include "Player.h"

Player::Player()
{
    score = 0;
    sweeps = 0;
    //ctor
}

Player::Player(string n)
{
    name=n;
    score = 0;
    sweeps = 0;
}

string Player::getName()
{
    return name;
}

CardStack * Player::getHand()
{
    return &hand;
}

CardStack * Player::getCaptured()
{
    return &captured;
}

int Player::getScore()
{
    return score;
}

void Player::addScore(int s)
{
    score += s;
}

void Player::removeScore(int s)
{
    score -= s;
}

int Player::getSweeps()
{
    return sweeps;
}

void Player::addSweeps(int s)
{
    sweeps += s;
}

void Player::removeSweeps(int s)
{
    sweeps -= s;
}

bool Player::drawCard(Deck * deck)
{
    if (deck->getSize() > 0)
    {
        hand.addCard(deck->drawTop());

        return true;
    }
    else
        return false;
}


void Player::moveToTable(int c, CardStack * s)
{
    s->addCard(hand.getCard(c));
    hand.removeCard(c);
}

void Player::makeCapture(CaptureSelection sel, int c)
{
    captured.addCard(sel.getCaptureCard());
    sel.getSelectedCards().moveAll(&captured);
    hand.removeCard(c);
}

Player::~Player()
{
    //dtor
}
