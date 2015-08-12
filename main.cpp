#include <iostream>
#include <sstream>
#include "Card.h"
#include "CardStack.h"
#include "Deck.h"
#include "Player.h"
#include "CaptureSelection.h"

using namespace std;

void initializeGame();
void prepareRound();
void dealCards();
void printStats();
void makeMove();
void advancePlayer();
bool trail();
bool capture();
bool allHandsEmpty();
void checkSweeps();

void printCards(CardStack);
// create the deck, players and table
Deck deck;
CardStack table;
std::vector<Player> players;
Player * activePlayer;
int activePlayerNo;

int main()
{
    initializeGame();
    prepareRound();

    while (true)
    {
        printStats();
        makeMove();
        advancePlayer();
        if (allHandsEmpty())
        {
            dealCards();
            cout << "--- Dealing cards---" << endl;
        }
    }

    return 0;
}

void initializeGame()
{
    players.push_back(Player ("Player 1"));
    players.push_back(Player ("Player 2"));
    activePlayerNo = 0;
    activePlayer =  &players[activePlayerNo];
}


void prepareRound()
{
    int i;
    for (i=0; i<=players.size() - 1; i++)
    {
        players[i].getHand()->clearStack();
    }
    deck.clearStack();
    table.clearStack();
    deck.fillDeck();
    deck.shuffle();
    dealCards();
    for (i=0; i <=3; i++)
    {
        table.addCard(deck.drawTop());
    }
}


void dealCards()
{
    int i;
    int j;
    for (i=0; i<=players.size() - 1; i++)
    {
        for (j=0; j<=3; j++)
        {
            players[i].drawCard(&deck);
        }
    }
}

void printStats()
{
    cout << "--- " << activePlayer->getName() << " in turn ---" << endl << endl;
    cout << "Deck:" << deck.getSize() << endl;
    for (int i=0; i <= players.size() -1 ; i++)
    {
        cout << players[i].getName() << ": " << players[i].getCaptured()->getSize() << " cards  " << players[i].getScore() << " points" << endl;
    }
    cout << endl;
    cout << "Table:" << endl;
    printCards(table);
    cout << endl;
    cout << "You have:" << endl;
    printCards(*activePlayer->getHand());
}

void makeMove()
{
    string input;
    std::stringstream ss;
    int choice;
    cout << endl;
    bool moveMade = false;
    do
    {
        cout << "1:Capture 2:Trail >";
        getline(cin,input);
        stringstream(input) >> choice;
        switch (choice)
        {
        case 1:
            moveMade = capture();
            break;
        case 2:
            moveMade = trail();
            break;
        default:
            cout << "Invalid entry" << endl;
            break;

        }
    }
    while (!moveMade);

}

bool trail()
{
    int selectedCard;
    string input;
    cout << "Select card >";
    getline(cin,input);
    stringstream(input) >> selectedCard;
    if (selectedCard >=1 && selectedCard <= activePlayer->getHand()->getSize())
    {
        activePlayer->moveToTable(selectedCard - 1, &table);
        return true;
    }

    else
    {
        cout << "Invalid card" << endl;
        return false;
    }
}

bool capture()
{
    int selectedCaptureCard;
    int addToSelection;
    bool continueSelection;
    bool captureMade = false;
    Card capturingCard;
    CardStack selection;
    string input;
    cout << "You have:" << endl;
    printCards(*activePlayer->getHand());
    cout << "Select card to capture with >";
    getline(cin,input);
    stringstream(input) >> selectedCaptureCard;
    if (selectedCaptureCard >=1 && selectedCaptureCard <= activePlayer->getHand()->getSize())
    {
        capturingCard = activePlayer->getHand()->getCard(selectedCaptureCard - 1);

        do
        {
            cout << endl << "Capturing with: " << capturingCard.toString() << endl;
            cout << "Table:" << endl;
            printCards(table);
            cout << endl;
            cout << table.getSize() + 1 << " Capture!" << endl;
            cout << table.getSize() + 2 << " Cancel" << endl;
            cout << endl;
            cout << "Selection:" << endl;
            printCards(selection);
            cout << endl << "Select card >";
            getline(cin,input);
            stringstream(input) >> addToSelection;
            // Add to selection
            if (addToSelection <= table.getSize())
            {
                selection.addCard(table.getCard(addToSelection - 1));
                table.removeCard(addToSelection - 1);
                continueSelection = true;
            }
            // Capture
            else if (addToSelection == table.getSize() + 1)
            {
                CaptureSelection cSelection (capturingCard,selection);
                if (cSelection.isValid())
                {
                    activePlayer->makeCapture(cSelection, selectedCaptureCard - 1);
                    captureMade = true;
                    checkSweeps();
                    continueSelection = false;
                }
                else
                {
                    cout << "Invalid capture" << endl;
                    selection.moveAll(&table);
                    continueSelection = true;
                }
            }
            // Cancel
            else if (addToSelection == table.getSize() + 2)
            {
                selection.moveAll(&table);
                continueSelection = false;
            }
            else if (addToSelection > table.getSize() + 2)
            {
                cout << "Invalid choice" << endl;
                continueSelection = true;
            }
        }
        while (continueSelection);
    }
    else
    {
        cout << "Invalid card" << endl;
    }

    return captureMade;
}

bool allHandsEmpty()
{
    int i;
    bool anyHandHasCards = false;
    for (i=0; i<=players.size()-1; i++)
    {
        if (!(players[i].getHand()->isEmpty()))
            anyHandHasCards = true;
    }
    return !anyHandHasCards;
}

void advancePlayer()
{
    if (activePlayerNo < players.size() - 1)
        activePlayerNo++;
    else
        activePlayerNo = 0;
    activePlayer = &players[activePlayerNo];
}

void printCards(CardStack c)
{
    string s;
    int i;
    for (i = 0; i <= c.getSize() - 1; i++)
    {
        cout << i + 1 << " "<< c.getCard(i).toString() << endl;
    }
}


void checkSweeps()
{
    if (table.isEmpty())
    {
        activePlayer->addSweeps(1);
        activePlayer->addScore(1);
        cout << "---Sweep added!---" << endl;
        int playersWithSweeps = 0;
        for (int i = 0; i<=players.size() - 1; i++)
        {
            if (players[i].getSweeps() >= 1)
            {
                playersWithSweeps++;
            }
        }
        if (playersWithSweeps == players.size())
        {
            for (int i = 0; i<=players.size() - 1; i++)
            {
                players[i].removeSweeps(1);
                players[i].removeScore(1);
            }
            cout << "---Removing one sweep from all players---" << endl;
        }
    }
}
