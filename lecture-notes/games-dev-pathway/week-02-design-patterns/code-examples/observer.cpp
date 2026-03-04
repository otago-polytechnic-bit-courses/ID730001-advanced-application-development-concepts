#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
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

class Deck
{
public:
    Deck()
    {
        for (const auto &suit : {"Spades", "Hearts", "Clubs", "Diamonds"})
            for (int v = 2; v <= 14; ++v)
                cards.push_back({suit, v});
        std::mt19937 rng(std::random_device{}());
        std::shuffle(cards.begin(), cards.end(), rng);
    }
    Card draw()
    {
        Card c = cards.back();
        cards.pop_back();
        return c;
    }
    bool isEmpty() const { return cards.empty(); }
    void addCard(const Card &c) { cards.insert(cards.begin(), c); }
    int size() const { return static_cast<int>(cards.size()); }

private:
    std::vector<Card> cards;
};

struct RoundResult
{
    int round;
    Card card1;
    Card card2;
    std::string player1Name;
    std::string player2Name;
    std::string winner;
};

class IGameObserver
{
public:
    virtual void onRoundEnd(const RoundResult &result) = 0;
    virtual ~IGameObserver() = default;
};

class Scoreboard : public IGameObserver
{
public:
    void onRoundEnd(const RoundResult &result) override
    {
        if (result.winner == result.player1Name)
            ++wins1;
        else if (result.winner == result.player2Name)
            ++wins2;
        else
            ++ties;
    }

    void printSummary(const std::string &p1, const std::string &p2) const
    {
        std::cout << "\n── Scoreboard ──────────────────────\n";
        std::cout << std::format("{}: {} wins\n", p1, wins1);
        std::cout << std::format("{}: {} wins\n", p2, wins2);
        std::cout << std::format("Ties: {}\n", ties);
    }

private:
    int wins1 = 0, wins2 = 0, ties = 0;
};

class RoundLogger : public IGameObserver
{
public:
    void onRoundEnd(const RoundResult &result) override
    {
        std::cout << std::format("[Round {:2}]  {} ({}) vs {} ({})  =>  {}\n",
                                 result.round,
                                 result.player1Name, result.card1.toString(),
                                 result.player2Name, result.card2.toString(),
                                 result.winner);
    }
};

class ObserverWarGame
{
public:
    void addObserver(IGameObserver *obs) { observers.push_back(obs); }

    void play()
    {
        Deck source;
        Deck deck1, deck2;

        for (int i = 0; i < 26; ++i)
            deck1.addCard(source.draw());
        for (int i = 0; i < 26; ++i)
            deck2.addCard(source.draw());

        const std::string p1 = "Alice";
        const std::string p2 = "Bob";
        int round = 1;

        while (!deck1.isEmpty() && !deck2.isEmpty() && round <= 30)
        {
            Card c1 = deck1.draw();
            Card c2 = deck2.draw();

            RoundResult result{round, c1, c2, p1, p2, ""};

            if (c1.value > c2.value)
            {
                result.winner = p1;
                deck1.addCard(c1);
                deck1.addCard(c2);
            }
            else if (c2.value > c1.value)
            {
                result.winner = p2;
                deck2.addCard(c1);
                deck2.addCard(c2);
            }
            else
            {
                result.winner = "Tie";
                deck1.addCard(c1);
                deck2.addCard(c2);
            }

            notify(result);
            ++round;
        }

        for (auto *obs : observers)
        {
            if (auto *sb = dynamic_cast<Scoreboard *>(obs))
                sb->printSummary(p1, p2);
        }
    }

private:
    std::vector<IGameObserver *> observers;

    void notify(const RoundResult &result)
    {
        for (auto *obs : observers)
            obs->onRoundEnd(result);
    }
};

int main()
{
    RoundLogger logger;
    Scoreboard board;

    ObserverWarGame game;
    game.addObserver(&logger);
    game.addObserver(&board);
    game.play();

    return 0;
}