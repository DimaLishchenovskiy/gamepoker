#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

string dealCard();
bool checkDuplicate(const string hand[], const string dealer[], const string aCard);
void dealDealer(string dealer[], const string hand[]);
void dealHand(string hand[], const string dealer[]);
string findWinner(const string hand[], const string dealer[]);

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    // MENU
    int option = 0;
    bool stop = false;
    string hand[2] = {"", ""};
    string dealer[5] = {"", "", "", "", ""};

    while (!stop)
    {
        cout << "********* MENU *********" << endl;
        cout << "\nChoose option: " << endl;
        cout << "\n(1) Start game" << endl;
        cout << "(2) Quit" << endl;
        cin >> option;

        if (option == 1)
        {
            dealHand(hand, dealer);
            cout << "Player's Hand:" << endl;
            for (int i = 0; i < 2; i++)
                cout << (i + 1) << " - " << hand[i] << endl;

            dealDealer(dealer, hand);
            cout << "Dealer's Hand:" << endl;
            for (int i = 0; i < 5; i++)
                cout << (i + 1) << " - " << dealer[i] << endl;

            string winner = findWinner(hand, dealer);
            cout << "Winner: " << winner << endl;

            // Pause program
            cin.ignore(256, '\n');
            cout << endl << "Hit return to continue...";
            cin.get();
            system("CLS");
        }
        else if (option == 2)
        {
            stop = true;
        }
        else
        {
            cout << "Error, try again!" << endl;
        }
    }

    return 0;
}

string dealCard()
{
    string card;
    int aSuit = (rand() % 4) + 1;
    int aCard = (rand() % 13) + 1;
    string face;

    switch (aSuit)
    {
    case 1: face = " of Hearts"; break;
    case 2: face = " of Spades"; break;
    case 3: face = " of Diamonds"; break;
    case 4: face = " of Clubs"; break;
    }

    string value;

    switch (aCard)
    {
    case 1: value = "Ace"; break;
    case 2: value = "2"; break;
    case 3: value = "3"; break;
    case 4: value = "4"; break;
    case 5: value = "5"; break;
    case 6: value = "6"; break;
    case 7: value = "7"; break;
    case 8: value = "8"; break;
    case 9: value = "9"; break;
    case 10: value = "10"; break;
    case 11: value = "Jack"; break;
    case 12: value = "Queen"; break;
    case 13: value = "King"; break;
    }

    card = value + face;

    return card;
}

bool checkDuplicate(const string hand[], const string dealer[], const string aCard)
{
    for (int i = 0; i < 5; i++)
    {
        if (dealer[i] == aCard)
            return true;
    }

    for (int i = 0; i < 2; i++)
    {
        if (hand[i] == aCard)
            return true;
    }

    return false;
}

void dealDealer(string dealer[], const string hand[])
{
    for (int i = 0; i < 5; i++)
    {
        string j = dealCard();
        if (checkDuplicate(hand, dealer, j))
            i--;
        else
            dealer[i] = j;
    }
}

void dealHand(string hand[], const string dealer[])
{
    for (int i = 0; i < 2; i++)
    {
        string j = dealCard();
        if (checkDuplicate(hand, dealer, j))
            i--;
        else
            hand[i] = j;
    }
}

string findWinner(const string hand[], const string dealer[])
{
    string result = "Sorry, better luck next time!";

    bool straightFlush = false;
    bool fourOfAKind = false;
    bool fullHouse = false;
    bool flush = false;
    bool straight = false;
    bool threeOfAKind = false;
    bool twoPair = false;
    bool onePair = false;

    enum {
        PAIR = 1,
        TWO_PAIR,
        THREE_OF_A_KIND,
        FULL_HOUSE,
        FOUR_OF_A_KIND = 6
    };

    int cards[2][5] = { {0} };
    int cards2[2][5] = { {0} };

    for (int i = 0; i < 5; i++)
    {
        if (hand[i].substr(0, 2) == "10")
        {
            cards[0][i] = 10;
        }
        else if (hand[i].substr(0, 1) == "A")
        {
            cards[0][i] = 1;
        }
        else if (hand[i].substr(0, 1) == "J")
        {
            cards[0][i] = 11;
        }
        else if (hand[i].substr(0, 1) == "Q")
        {
            cards[0][i] = 12;
        }
        else if (hand[i].substr(0, 1) == "K")
        {
            cards[0][i] = 13;
        }
        else
        {
            stringstream stream(hand[i].substr(0, 1));
            stream >> cards[0][i];
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (dealer[i].substr(0, 2) == "10")
        {
            cards2[0][i] = 10;
        }
        else if (dealer[i].substr(0, 1) == "A")
        {
            cards2[0][i] = 1;
        }
        else if (dealer[i].substr(0, 1) == "J")
        {
            cards2[0][i] = 11;
        }
        else if (dealer[i].substr(0, 1) == "Q")
        {
            cards2[0][i] = 12;
        }
        else if (dealer[i].substr(0, 1) == "K")
        {
            cards2[0][i] = 13;
        }
        else
        {
            stringstream stream(dealer[i].substr(0, 1));
            stream >> cards2[0][i];
        }
    }

    enum { HEARTS, SPADES, DIAMONDS, CLUBS };

    for (int i = 0; i < 5; i++)
    {
        if (hand[i].find("Hearts") != -1)
        {
            cards[1][i] = HEARTS;
        }
        else if (hand[i].find("Spades") != -1)
        {
            cards[1][i] = SPADES;
        }
        else if (hand[i].find("Diamonds") != -1)
        {
            cards[1][i] = DIAMONDS;
        }
        else
        {
            cards[1][i] = CLUBS;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (dealer[i].find("Hearts") != -1)
        {
            cards2[1][i] = HEARTS;
        }
        else if (dealer[i].find("Spades") != -1)
        {
            cards2[1][i] = SPADES;
        }
        else if (dealer[i].find("Diamonds") != -1)
        {
            cards2[1][i] = DIAMONDS;
        }
        else
        {
            cards2[1][i] = CLUBS;
        }
    }

 vector<int> winners(0);
    for(int i = 0; i < 4; i++) {
        for(int j = i; j < 4; j++) {
            if(cards[0][i] == cards[0][j + 1])
                winners.push_back(cards[0][i]);
        }
    }
    if(winners.size() == FOUR_OF_A_KIND)
        fourOfAKind = true;
    else if(winners.size() == FULL_HOUSE)
        fullHouse = true;
    else if(winners.size() == THREE_OF_A_KIND)
        threeOfAKind = true;
    else if(winners.size() == TWO_PAIR)
        twoPair = true;
    else if(winners.size() == PAIR)
        onePair = true;
 
    // Looks for a straight
    vector<int> orderCards(0);
    for(int i = 0; i < 5; i++)
        orderCards.push_back(cards[0][i]);
    // Bubble sort algorithm
    bool swapped = true;
    int j = 0;
    int tmp;
    while(swapped) {
        swapped = false;
        j++;
        for(int i = 0; i < (orderCards.size() - j); i++) {
            if(orderCards[i] > orderCards[i + 1]) {
                tmp = orderCards[i];
                orderCards[i] = orderCards[i + 1];
                orderCards[i + 1] = tmp;
                swapped = true;
            }
        }
    }
    int checkStraight = orderCards.back();
    while(checkStraight != orderCards.front()) {
        checkStraight--;
    }
    if(checkStraight == (orderCards.back() - (orderCards.size() - 1))) {
        straight = true;
    } else if((orderCards[0] == 1) &&
            (orderCards[1] == 10) &&
            (orderCards[2] == 11) &&
            (orderCards[3] == 12) &&
            (orderCards[4] == 13)) {
                straight = true;
    }
 
    // Looks for a flush
    for(int i = 0; i < 7; i++) {
        if(cards[1][i] == cards2[1][i + 1]) {
            flush = true;
        } else {
            flush = false;
            break;
        }
    }
 

 if((straight == true) && (flush == true))
        straightFlush = true;
 
    if(straightFlush == true)
        result = "You have a Straight Flush!";
    else if(fourOfAKind == true)
        result = "You have a Four Of A Kind!";
    else if(fullHouse == true)
        result = "You have a Full House!";
    else if(flush == true)
        result = "You have a Flush!";
    else if(straight == true)
        result = "You have a Straight!";
    else if(threeOfAKind == true)
        result = "You have a Three Of A Kind!";
    else if(twoPair == true)
        result = "You have a Two Pair!";
    else if(onePair == true)
        result = "You have a Pair!";
 
    return result;

    return result; 
}
