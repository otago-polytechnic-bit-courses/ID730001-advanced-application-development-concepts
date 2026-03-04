# Week 02

---

## Important Links

| Section        | Link        |
| -------------- | ----------- |
| Previous Class | [Week 01]() |
| Next Class     | [Week 03]() |

---

## Design Patterns

**Design patterns** are reusable solutions to common software design problems. They provide a way to structure code that is flexible, maintainable, and scalable. There are many different design patterns, but they can be broadly categorised into three types:

- **Behavioural Patterns**: Focus on communication between objects and how they interact. Examples: Observer, Strategy, Command.
- **Creational Patterns**: Focus on object creation. Examples: Singleton, Factory, Builder.
- **Structural Patterns**: Focus on how classes and objects are composed into larger structures. Examples: Adapter, Decorator, Composite.

We are going to use **War** as an example to demonstrate these patterns. War is a simple card game where two players each have a deck of cards. Each player draws a card, and the player with the higher card wins the round. The game continues until one player has all the cards.

---

### Strategy Pattern

The Strategy pattern is a behavioural design pattern that allows you to define a family of algorithms, encapsulate each one, and make them interchangeable. The algorithm can vary independently from the clients that use it.

In War, we can use the Strategy pattern to define different strategies for how a player chooses which card to play, e.g., always playing a random card, or always playing the highest card available.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>

struct Card
{
    // Omitted for brevity. Same as previous examples
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
                std::cout << " => " << alice.getName() << " wins the round!\n";
            }
            else if (c2.value > c1.value)
            {
                bob.receiveCard(c1);
                bob.receiveCard(c2);
                std::cout << " => " << bob.getName() << " wins the round!\n";
            }
            else
            {
                alice.receiveCard(c1);
                bob.receiveCard(c2);
                std::cout << "  => Tie! Each player keeps their card.\n";
            }

            std::cout << "  Cards: " << alice.getName() << "=" << alice.deckSize()
                      << "  " << bob.getName() << "=" << bob.deckSize() << "\n\n";
            ++round;
        }

        if (alice.deckSize() > bob.deckSize())
            std::cout << alice.getName() << " wins the game!\n";
        else if (bob.deckSize() > alice.deckSize())
            std::cout << bob.getName() << " wins the game!\n";
        else
            std::cout << "The game is a draw!\n";
    }
};

int main()
{
    WarGame game;
    game.play();
    return 0;
}
```

---

### Observer Pattern

The Observer pattern is a behavioural design pattern that defines a one-to-many dependency between objects so that when one object changes state, all its dependents are notified automatically.

In War, we can use the Observer pattern to notify interested parties whenever a round ends, e.g.,  a scoreboard that tracks wins, and a logger that records what happened.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <format>

struct Card
{
    // Omitted for brevity. Same as previous examples
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
```

---

### Factory Pattern

The Factory pattern is a creational design pattern that provides an interface for creating objects, allowing subclasses to decide which concrete class to instantiate.

In War, we can use the Factory pattern to create different types of players — a human player who is prompted for input, and a computer player who plays automatically.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>
#include <string>
#include <format>

struct Card
{
    // Omitted for brevity. Same as previous examples
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
                std::cout << p1->getName() << " wins!\n";
            }
            else if (c2.value > c1.value)
            {
                p2->receiveCard(c1);
                p2->receiveCard(c2);
                std::cout << p2->getName() << " wins!\n";
            }
            else
            {
                p1->receiveCard(c1);
                p2->receiveCard(c2);
                std::cout << "Tie!\n";
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
```

---

### Singleton Pattern

The Singleton pattern is a creational design pattern that restricts the instantiation of a class to a single instance and provides a global point of access to that instance.

In War, we can use the Singleton pattern for a `GameManager` that controls the overall flow of the application, ensuring only one game session is active at a time. The modern C++ approach uses a local static variable, which is thread-safe by default since C++11.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <format>

struct Card
{
    // Omitted for brevity. Same as previous examples
};

class GameManager
{
public:
    static GameManager &getInstance()
    {
        static GameManager instance;
        return instance;
    }

    GameManager(const GameManager &) = delete;
    GameManager &operator=(const GameManager &) = delete;

    void startGame(const std::string &p1Name, const std::string &p2Name)
    {
        if (running)
        {
            std::cout << "A game is already in progress!\n";
            return;
        }
        running = true;
        gamesPlayed++;
        std::cout << std::format("── Game {} starting: {} vs {} ──\n",
                                 gamesPlayed, p1Name, p2Name);
        runGame(p1Name, p2Name);
        running = false;
    }

    int getGamesPlayed() const { return gamesPlayed; }

private:
    GameManager() = default;

    bool running = false;
    int gamesPlayed = 0;

    void runGame(const std::string &p1Name, const std::string &p2Name)
    {
        std::vector<Card> deck;
        for (const auto &suit : {"Spades", "Hearts", "Clubs", "Diamonds"})
            for (int v = 2; v <= 14; ++v)
                deck.push_back({suit, v});
        std::mt19937 rng(std::random_device{}());
        std::shuffle(deck.begin(), deck.end(), rng);

        std::vector<Card> hand1(deck.begin(), deck.begin() + 26);
        std::vector<Card> hand2(deck.begin() + 26, deck.end());

        int w1 = 0, w2 = 0;
        for (int round = 1; round <= 5; ++round)
        {
            Card c1 = hand1.back();
            hand1.pop_back();
            Card c2 = hand2.back();
            hand2.pop_back();

            std::cout << std::format("  Round {}: {} [{}] vs {} [{}]  =>  ",
                                     round, p1Name, c1.toString(), p2Name, c2.toString());

            if (c1.value > c2.value)
            {
                ++w1;
                std::cout << p1Name << " wins\n";
            }
            else if (c2.value > c1.value)
            {
                ++w2;
                std::cout << p2Name << " wins\n";
            }
            else
            {
                std::cout << "Tie\n";
            }
        }

        std::cout << std::format("Result => {} wins: {}  {} wins: {}\n\n",
                                 p1Name, w1, p2Name, w2);
    }
};

int main()
{

    GameManager::getInstance().startGame("Alice", "Bob");
    GameManager::getInstance().startGame("Carol", "Dave");

    std::cout << std::format("Total games played: {}\n",
                             GameManager::getInstance().getGamesPlayed());
    return 0;
}
```

---

### Builder Pattern

The Builder pattern is a creational design pattern that constructs complex objects step by step. The key idea is that the same construction process can create different representations, and you don't need to pass a huge list of parameters to a constructor.

In War, we can use the Builder pattern to configure a game session, specifying the number of rounds to play, whether to shuffle, house rules, and so on, before the game starts.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <stdexcept>
#include <format>

struct Card
{
    // Omitted for brevity. Same as previous examples
};

struct GameConfig
{
    std::string player1Name = "Player 1";
    std::string player2Name = "Player 2";
    int maxRounds = 26;
    bool shuffleDeck = true;
    bool tieGoesToP1 = false;
    bool verbose = true;
};

class GameConfigBuilder
{
public:
    GameConfigBuilder &setPlayer1(const std::string &name)
    {
        config.player1Name = name;
        return *this;
    }

    GameConfigBuilder &setPlayer2(const std::string &name)
    {
        config.player2Name = name;
        return *this;
    }

    GameConfigBuilder &setMaxRounds(int rounds)
    {
        if (rounds < 1 || rounds > 26)
            throw std::invalid_argument("Rounds must be between 1 and 26");
        config.maxRounds = rounds;
        return *this;
    }

    GameConfigBuilder &withShuffle(bool shuffle)
    {
        config.shuffleDeck = shuffle;
        return *this;
    }

    GameConfigBuilder &withTieRuleP1()
    {
        config.tieGoesToP1 = true;
        return *this;
    }

    GameConfigBuilder &withVerboseOutput(bool v)
    {
        config.verbose = v;
        return *this;
    }

    GameConfig build() const
    {
        return config;
    }

private:
    GameConfig config;
};

class BuilderWarGame
{
public:
    void play(const GameConfig &cfg)
    {
        if (cfg.verbose)
            std::cout << std::format("Starting game: {} vs {}  ({} rounds, shuffle={})\n\n",
                                     cfg.player1Name, cfg.player2Name, cfg.maxRounds, cfg.shuffleDeck);

        std::vector<Card> deck;
        for (const auto &suit : {"Spades", "Hearts", "Clubs", "Diamonds"})
            for (int v = 2; v <= 14; ++v)
                deck.push_back({suit, v});

        if (cfg.shuffleDeck)
        {
            std::mt19937 rng(std::random_device{}());
            std::shuffle(deck.begin(), deck.end(), rng);
        }

        std::vector<Card> hand1(deck.begin(), deck.begin() + 26);
        std::vector<Card> hand2(deck.begin() + 26, deck.end());

        int w1 = 0, w2 = 0;
        for (int round = 1; round <= cfg.maxRounds; ++round)
        {
            Card c1 = hand1.back();
            hand1.pop_back();
            Card c2 = hand2.back();
            hand2.pop_back();

            std::string outcome;
            if (c1.value > c2.value)
            {
                ++w1;
                outcome = cfg.player1Name + " wins";
            }
            else if (c2.value > c1.value)
            {
                ++w2;
                outcome = cfg.player2Name + " wins";
            }
            else
            {

                if (cfg.tieGoesToP1)
                {
                    ++w1;
                    outcome = "Tie => " + cfg.player1Name + " (house rule)";
                }
                else
                {
                    outcome = "Tie";
                }
            }

            if (cfg.verbose)
                std::cout << std::format("Round {:2}: {} vs {}  =>  {}\n",
                                         round, c1.toString(), c2.toString(), outcome);
        }

        std::cout << std::format("\nFinal: {} = {}  {} = {}\n",
                                 cfg.player1Name, w1, cfg.player2Name, w2);
    }
};

int main()
{

    GameConfig cfg = GameConfigBuilder()
                         .setPlayer1("Alice")
                         .setPlayer2("Bob")
                         .setMaxRounds(10)
                         .withShuffle(true)
                         .withTieRuleP1()
                         .withVerboseOutput(true)
                         .build();

    BuilderWarGame game;
    game.play(cfg);

    return 0;
}
```

---

## Exercises

Learning to use AI tools is an important skill. While AI tools are powerful, you must be aware of the following:

- If you provide an AI tool with a prompt that is not refined enough, it may generate a not-so-useful response
- Do not trust the AI tool's responses blindly. You must still use your judgement and may need to do additional research to determine if the response is correct
- Acknowledge what AI tool you have used. If you use AI to help you with a file, include a comment block at the top of the file

Here is an example comment block:

```cpp
/*
 * Brief description of what this file does
 *
 * AI Assistance: This file was developed with assistance from [AI Tool Name]
 *
 * Prompts used:
 * - "Your first prompt here"
 * - "Your second prompt here"
 *
 * Usage: Describe how you used the AI responses to help you with your work
 */
```

---

### Task 1

Extend the Strategy pattern example by adding a third draw strategy: `LowestCardStrategy`, which always plays the lowest card in the player's hand. Wire it into the game alongside `RandomStrategy` and `HighestCardStrategy` and observe how the win rates differ across strategies.

---

### Task 2

Extend the Observer pattern example by adding a `StreakObserver` that tracks the longest consecutive winning streak for each player. It should print the result at the end of the game in the format:

```
Alice longest streak: 4
Bob longest streak: 2
```

---

### Task 3

Extend the Builder pattern example with two new configuration options: `setNumDecks(int n)` which combines `n` standard 52-card decks into one before splitting, and `setAcesHigh(bool)` which, when false, treats Aces as value 1 instead of 14. Update the game logic to respect these settings.
