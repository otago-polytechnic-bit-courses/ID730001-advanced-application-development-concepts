#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>
#include <string>
#include <format>

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

class IPlayer
{
public:
    virtual std::string getName() const = 0;
    virtual Card playCard() = 0;
    virtual void receiveCard(const Card &c) = 0;
    virtual bool hasCards() const = 0;
    virtual int deckSize() const = 0;
    virtual ~IPlayer() = default;

protected:
    std::vector<Card> hand;
};

class HumanPlayer : public IPlayer
{
public:
    explicit HumanPlayer(std::string n) : name(std::move(n)) {}

    std::string getName() const override { return name; }
    bool hasCards() const override { return !hand.empty(); }
    int deckSize() const override { return static_cast<int>(hand.size()); }

    Card playCard() override
    {
        std::cout << name << ", press ENTER to draw your card...";
        std::cin.ignore();
        Card top = hand.back();
        hand.pop_back();
        std::cout << name << " draws: " << top.toString() << "\n";
        return top;
    }

    void receiveCard(const Card &c) override { hand.insert(hand.begin(), c); }

private:
    std::string name;
};

class ComputerPlayer : public IPlayer
{
public:
    explicit ComputerPlayer(std::string n) : name(std::move(n)) {}

    std::string getName() const override { return name; }
    bool hasCards() const override { return !hand.empty(); }
    int deckSize() const override { return static_cast<int>(hand.size()); }

    Card playCard() override
    {
        Card top = hand.back();
        hand.pop_back();
        std::cout << name << " (CPU) draws: " << top.toString() << "\n";
        return top;
    }

    void receiveCard(const Card &c) override { hand.insert(hand.begin(), c); }

private:
    std::string name;
};

class IPlayerFactory
{
public:
    virtual std::unique_ptr<IPlayer> createPlayer(const std::string &name) = 0;
    virtual ~IPlayerFactory() = default;
};

class HumanPlayerFactory : public IPlayerFactory
{
public:
    std::unique_ptr<IPlayer> createPlayer(const std::string &name) override
    {
        return std::make_unique<HumanPlayer>(name);
    }
};

class ComputerPlayerFactory : public IPlayerFactory
{
public:
    std::unique_ptr<IPlayer> createPlayer(const std::string &name) override
    {
        return std::make_unique<ComputerPlayer>(name);
    }
};

class FactoryWarGame
{
public:
    void startGame(IPlayerFactory &factory1, IPlayerFactory &factory2)
    {
        auto p1 = factory1.createPlayer("Alice");
        auto p2 = factory2.createPlayer("Bob (CPU)");

        std::vector<Card> deck;
        for (const auto &suit : {"Spades", "Hearts", "Clubs", "Diamonds"})
            for (int v = 2; v <= 14; ++v)
                deck.push_back({suit, v});
        std::mt19937 rng(std::random_device{}());
        std::shuffle(deck.begin(), deck.end(), rng);

        for (int i = 0; i < 26; ++i)
            p1->receiveCard(deck[i]);
        for (int i = 26; i < 52; ++i)
            p2->receiveCard(deck[i]);

        int round = 1;
        while (p1->hasCards() && p2->hasCards() && round <= 10)
        {
            std::cout << "\n── Round " << round << " ─────────────────────────\n";
            Card c1 = p1->playCard();
            Card c2 = p2->playCard();

            if (c1.value > c2.value)
            {
                p1->receiveCard(c1);
                p1->receiveCard(c2);
                std::cout << p1->getName() << " wins\n";
            }
            else if (c2.value > c1.value)
            {
                p2->receiveCard(c1);
                p2->receiveCard(c2);
                std::cout << p2->getName() << " wins\n";
            }
            else
            {
                p1->receiveCard(c1);
                p2->receiveCard(c2);
                std::cout << "Tie\n";
            }

            std::cout << std::format("Cards: {}={} {}={}\n",
                                     p1->getName(), p1->deckSize(), p2->getName(), p2->deckSize());
            ++round;
        }
    }
};

int main()
{

    ComputerPlayerFactory cpuFactory;
    ComputerPlayerFactory cpuFactory2;

    FactoryWarGame game;
    game.startGame(cpuFactory, cpuFactory2);

    return 0;
}