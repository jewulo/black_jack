// black_jack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// https://www.youtube.com/watch?v=b8V-WIjlScA
// https://github.com/davepl/blackjack/blob/main/blackjack.cpp

#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <ctime>
#include <algorithm>    // for "std::shuffle"

enum Rank {
    ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
};

enum Suit {
    HEARTS, DIAMONDS, CLUBS, SPADES
};

class Card {
public:
    Card(Rank rank, Suit suit) : m_rank(rank), m_suit(suit) {}

    Rank get_rank() const { return m_rank; }
    Suit get_suit() const { return m_suit; }
private:
    Rank m_rank;
    Suit m_suit;
};

class Deck {
public:
    Deck()
    {
        for (unsigned int suit = HEARTS; suit <= SPADES; ++suit) {
            for (unsigned int rank = ACE; rank <= KING; ++rank) {
                m_cards.push_back(std::make_unique<Card>(static_cast<Rank>(rank), static_cast<Suit>(suit)));
            }
        }
    }

    void shuffle_deck()
    {
        std::random_device rd;      // random device
        std::mt19937 rg(rd());      // random generator
        std::shuffle(m_cards.begin(), m_cards.end(), rg);
    }

    std::unique_ptr<Card> draw_card()
    {
        if (m_cards.empty()) {
            return nullptr;
        }
        std::unique_ptr<Card> card = std::move(m_cards.back());
        m_cards.pop_back();
        return card;
    }
private:
    std::vector<std::unique_ptr<Card>> m_cards;
};

class Player {
public:
    void add_card(std::unique_ptr<Card> card)
    {
        m_hand.push_back(std::move(card));
    }

    int get_hand_value()
    {
        int value = 0;
        int aces = 0;

        for (const auto& card : m_hand) {
            int card_value = card->get_rank();
            if (card_value >= 10) {
                card_value = 10;
            }
            else if (card_value == ACE) {
                aces++;

                card_value = 11;
            }
            value += card_value;
        }

        while (value > 21 && aces > 0) {
            value -= 10;
            aces--;
        }
        return value;
    }

private:
    std::vector<std::unique_ptr<Card>> m_hand;
};

int main()
{
    Deck deck;
    deck.shuffle_deck();

    Player player;
    Player dealer;

    player.add_card(deck.draw_card());
    dealer.add_card(deck.draw_card());

    std::cout << "Player hand value: " << player.get_hand_value() << std::endl;
    std::cout << "Dealer hand value: " << dealer.get_hand_value() << std::endl;

    std::cin.get();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
