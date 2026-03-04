#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>

struct Card
{
    std::string suit;
    int value;

    std::string toString() const
    {
        std::string name;
        if (value == 11)
            name = "Jack";
        else if (value == 12)
            name = "Queen";
        else if (value == 13)
            name = "King";
        else if (value == 14)
            name = "Ace";
        else
            name = std::to_string(value);
        return name + " of " + suit;
    }
};

class Deck
{
public:
    Deck()
    {
        for (const auto &suit : {"Spades", "Hearts", "Clubs", "Diamonds"})
        {
            for (int value = 2; value <= 14; ++value)
            {
                cards.push_back({suit, value});
            }
        }
        shuffle();
    }

    void shuffle()
    {
        std::mt19937 rng(std::random_device{}());
        std::shuffle(cards.begin(), cards.end(), rng);
    }

    Card draw()
    {
        if (cards.empty())
            throw std::runtime_error("Deck is empty");
        Card top = cards.back();
        cards.pop_back();
        return top;
    }

    bool isEmpty() const { return cards.empty(); }
    int size() const { return static_cast<int>(cards.size()); }

    void addCard(const Card &card) { cards.insert(cards.begin(), card); }

private:
    std::vector<Card> cards;
};

class IDrawStrategy
{
public:
    virtual Card chooseCard(Deck &deck) = 0;
    virtual ~IDrawStrategy() = default;
};

class RandomStrategy : public IDrawStrategy
{
public:
    Card chooseCard(Deck &deck) override
    {
        return deck.draw();
    }
};

class HighestCardStrategy : public IDrawStrategy
{
public:
    Card chooseCard(Deck &deck) override
    {

        std::vector<Card> hand;
        while (!deck.isEmpty())
            hand.push_back(deck.draw());

        std::sort(hand.begin(), hand.end(),
                  [](const Card &a, const Card &b)
                  { return a.value < b.value; });

        Card best = hand.back();
        hand.pop_back();

        for (const auto &c : hand)
            deck.addCard(c);
        return best;
    }
};

class Player
{
public:
    Player(std::string name, std::unique_ptr<IDrawStrategy> strategy)
        : name(std::move(name)), strategy(std::move(strategy)) {}

    std::string getName() const { return name; }
    int deckSize() const { return deck.size(); }
    bool hasCards() const { return !deck.isEmpty(); }

    Card playCard() { return strategy->chooseCard(deck); }
    void receiveCard(const Card &c) { deck.addCard(c); }

    void dealHalf(Deck &source, int count)
    {
        for (int i = 0; i < count; ++i)
            deck.addCard(source.draw());
    }

private:
    std::string name;
    Deck deck;
    std::unique_ptr<IDrawStrategy> strategy;
};

class WarGame
{
public:
    void play()
    {
        Deck source;

        Player alice("Alice (Random)", std::make_unique<RandomStrategy>());
        Player bob("Bob (Highest)", std::make_unique<HighestCardStrategy>());

        alice.dealHalf(source, 26);
        bob.dealHalf(source, 26);

        int round = 1;
        while (alice.hasCards() && bob.hasCards() && round <= 50)
        {
            Card c1 = alice.playCard();
            Card c2 = bob.playCard();

            std::cout << "Round " << round << ": "
                      << alice.getName() << " plays " << c1.toString()
                      << "  vs  "
                      << bob.getName() << " plays " << c2.toString() << "\n";

            if (c1.value > c2.value)
            {
                alice.receiveCard(c1);
                alice.receiveCard(c2);
                std::cout << " => " << alice.getName() << " wins the round\n";
            }
            else if (c2.value > c1.value)
            {
                bob.receiveCard(c1);
                bob.receiveCard(c2);
                std::cout << " => " << bob.getName() << " wins the round\n";
            }
            else
            {
                alice.receiveCard(c1);
                bob.receiveCard(c2);
                std::cout << "  => Tie. Each player keeps their card.\n";
            }

            std::cout << "  Cards: " << alice.getName() << "=" << alice.deckSize()
                      << "  " << bob.getName() << "=" << bob.deckSize() << "\n\n";
            ++round;
        }

        if (alice.deckSize() > bob.deckSize())
            std::cout << alice.getName() << " wins the game\n";
        else if (bob.deckSize() > alice.deckSize())
            std::cout << bob.getName() << " wins the game\n";
        else
            std::cout << "The game is a draw\n";
    }
};

int main()
{
    WarGame game;
    game.play();
    return 0;
}