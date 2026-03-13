# Week 02 — Design Patterns

## Navigation

|            | Link                                                                                                                            |
| ---------- | ------------------------------------------------------------------------------------------------------------------------------- |
| ← Previous | [Week 01 - Git, Programming Paradigms & C++](./lecture-notes/games-dev-pathway/week-01-git-programming-paradigms-c++/README.md)   |
| → Next     | [Week 03 - Processes, Threads & Concurrency](./lecture-notes/games-dev-pathway/week-03-processes-threading-concurrency/README.md) |

---

## 1. Design Patterns

A **design pattern** is a reusable solution to a common software design problem. Patterns are not finished code — they are templates you adapt to your situation.

| Category        | Focus                                | Examples                      |
| --------------- | ------------------------------------ | ----------------------------- |
| **Behavioural** | How objects communicate and interact | Observer, Strategy, Command   |
| **Creational**  | How objects are created              | Singleton, Factory, Builder   |
| **Structural**  | How classes and objects are composed | Adapter, Decorator, Composite |

Throughout this week we use the card game **War** as a running example. In War, two players each draw a card and the higher card wins the round. Play continues until one player holds all the cards.

---

### 1.1 Strategy Pattern

The Strategy pattern defines a family of algorithms, encapsulates each one in its own class, and makes them interchangeable. Clients use the algorithm through a common interface without knowing which concrete strategy is active.

**War use case:** swap in different card-selection strategies (random, highest, lowest) without changing the `Player` or game-loop code.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>

// --- Data types -----------------------------------------------------------

struct Card
{
    std::string suit;
    int value;

    // Convert a card to a human-readable string, e.g. "Ace of Spades"
    std::string toString() const
    {
        std::string name;
        if (value == 11) name = "Jack";
        else if (value == 12) name = "Queen";
        else if (value == 13) name = "King";
        else if (value == 14) name = "Ace";
        else name = std::to_string(value);
        return name + " of " + suit;
    }
};

// --- Deck -----------------------------------------------------------------

class Deck
{
public:
    // Build a full 52-card deck and shuffle it immediately
    Deck()
    {
        for (const auto& suit : {"Spades", "Hearts", "Clubs", "Diamonds"})
            for (int value = 2; value <= 14; ++value)
                cards.push_back({suit, value});
        shuffle();
    }

    void shuffle()
    {
        // std::random_device{} gives hardware entropy so every run is different
        std::mt19937 rng(std::random_device{}());
        std::shuffle(cards.begin(), cards.end(), rng);
    }

    // Remove and return the top card; throw if the deck is empty
    Card draw()
    {
        if (cards.empty()) throw std::runtime_error("Deck is empty");
        Card top = cards.back();
        cards.pop_back();
        return top;
    }

    bool isEmpty() const { return cards.empty(); }
    int  size()    const { return static_cast<int>(cards.size()); }

    // Add a card to the bottom of the deck (winner's cards go here)
    void addCard(const Card& card) { cards.insert(cards.begin(), card); }

private:
    std::vector<Card> cards;
};

// --- Strategy interface ---------------------------------------------------

// Pure abstract base class — all draw strategies must implement chooseCard()
class IDrawStrategy
{
public:
    virtual Card chooseCard(Deck& deck) = 0;
    virtual ~IDrawStrategy() = default;   // virtual destructor — always required in base classes
};

// --- Concrete strategies --------------------------------------------------

// RandomStrategy: just draw the top card (the deck is already shuffled)
class RandomStrategy : public IDrawStrategy
{
public:
    Card chooseCard(Deck& deck) override
    {
        return deck.draw();
    }
};

// HighestCardStrategy: look at every card, keep the highest, return the rest
class HighestCardStrategy : public IDrawStrategy
{
public:
    Card chooseCard(Deck& deck) override
    {
        // Empty the deck into a local hand so we can inspect all cards
        std::vector<Card> hand;
        while (!deck.isEmpty()) hand.push_back(deck.draw());

        // Sort ascending so the last element is the highest card
        std::sort(hand.begin(), hand.end(),
            [](const Card& a, const Card& b) { return a.value < b.value; });

        Card best = hand.back();
        hand.pop_back();          // remove the card we're about to play

        // Put the remaining cards back into the deck
        for (const auto& c : hand) deck.addCard(c);
        return best;
    }
};

// --- Player ---------------------------------------------------------------

class Player
{
public:
    // Constructor takes ownership of the strategy via unique_ptr
    // unique_ptr means exactly one owner; it frees memory automatically
    Player(std::string name, std::unique_ptr<IDrawStrategy> strategy)
        : name(std::move(name)), strategy(std::move(strategy)) {}

    std::string getName()  const { return name; }
    int         deckSize() const { return deck.size(); }
    bool        hasCards() const { return !deck.isEmpty(); }

    // Delegate to whichever strategy is currently active
    Card playCard()             { return strategy->chooseCard(deck); }
    void receiveCard(const Card& c) { deck.addCard(c); }

    // Deal count cards from an external source deck into this player's deck
    void dealHalf(Deck& source, int count)
    {
        for (int i = 0; i < count; ++i) deck.addCard(source.draw());
    }

private:
    std::string                    name;
    Deck                           deck;
    std::unique_ptr<IDrawStrategy> strategy;  // owned strategy
};

// --- Game -----------------------------------------------------------------

class WarGame
{
public:
    void play()
    {
        Deck source;

        // Each player gets a different strategy — swap these to experiment
        Player alice("Alice (Random)",  std::make_unique<RandomStrategy>());
        Player bob("Bob (Highest)",     std::make_unique<HighestCardStrategy>());

        alice.dealHalf(source, 26);
        bob.dealHalf(source, 26);

        int round = 1;
        // Cap at 50 rounds to avoid infinite loops on ties
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
                alice.receiveCard(c1); alice.receiveCard(c2);
                std::cout << " => " << alice.getName() << " wins the round!\n";
            }
            else if (c2.value > c1.value)
            {
                bob.receiveCard(c1); bob.receiveCard(c2);
                std::cout << " => " << bob.getName() << " wins the round!\n";
            }
            else
            {
                // Tie: each player keeps their own card
                alice.receiveCard(c1); bob.receiveCard(c2);
                std::cout << "  => Tie! Each player keeps their card.\n";
            }

            std::cout << "  Cards: " << alice.getName() << "=" << alice.deckSize()
                      << "  "        << bob.getName()   << "=" << bob.deckSize() << "\n\n";
            ++round;
        }

        // Whoever holds more cards at the end wins
        if      (alice.deckSize() > bob.deckSize()) std::cout << alice.getName() << " wins the game!\n";
        else if (bob.deckSize() > alice.deckSize()) std::cout << bob.getName()   << " wins the game!\n";
        else                                        std::cout << "The game is a draw!\n";
    }
};

int main()
{
    WarGame game;
    game.play();
    return 0;
}
```

#### Key terms

| Term                                     | Meaning                                                         |
| ---------------------------------------- | --------------------------------------------------------------- |
| `IDrawStrategy`                          | Abstract interface — declares what every strategy must do       |
| `RandomStrategy` / `HighestCardStrategy` | Concrete strategies — each provides a different implementation  |
| `std::unique_ptr`                        | Smart pointer with single ownership; memory freed automatically |
| `std::move`                              | Transfers ownership of a `unique_ptr` to a new owner            |

📖 Reference: [Strategy Pattern — Refactoring Guru](https://refactoring.guru/design-patterns/strategy)

---

### 1.2 Observer Pattern

The Observer pattern defines a one-to-many dependency: when one object (the **subject**) changes state, all registered **observers** are notified automatically. Observers can be added or removed at runtime without touching the subject.

**War use case:** notify a scoreboard and a logger at the end of every round — neither class needs to know about the other.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <format>

// --- Data types (Card, Deck) same as Strategy example --------------------

struct Card { std::string suit; int value; std::string toString() const; };

class Deck
{
public:
    Deck()
    {
        for (const auto& suit : {"Spades", "Hearts", "Clubs", "Diamonds"})
            for (int v = 2; v <= 14; ++v)
                cards.push_back({suit, v});
        std::mt19937 rng(std::random_device{}());
        std::shuffle(cards.begin(), cards.end(), rng);
    }
    Card draw()
    {
        Card c = cards.back(); cards.pop_back(); return c;
    }
    bool isEmpty() const { return cards.empty(); }
    void addCard(const Card& c) { cards.insert(cards.begin(), c); }
    int size() const { return static_cast<int>(cards.size()); }
private:
    std::vector<Card> cards;
};

// --- Event data -----------------------------------------------------------

// RoundResult bundles everything observers need to know about a completed round
struct RoundResult
{
    int         round;
    Card        card1;
    Card        card2;
    std::string player1Name;
    std::string player2Name;
    std::string winner;   // player name, or "Tie"
};

// --- Observer interface ---------------------------------------------------

// Any class that wants to listen to game events must implement onRoundEnd()
class IGameObserver
{
public:
    virtual void onRoundEnd(const RoundResult& result) = 0;
    virtual ~IGameObserver() = default;
};

// --- Concrete observers ---------------------------------------------------

// Scoreboard: counts wins and ties across the whole game
class Scoreboard : public IGameObserver
{
public:
    void onRoundEnd(const RoundResult& result) override
    {
        if      (result.winner == result.player1Name) ++wins1;
        else if (result.winner == result.player2Name) ++wins2;
        else                                          ++ties;
    }

    void printSummary(const std::string& p1, const std::string& p2) const
    {
        std::cout << "\n── Scoreboard ──────────────────────\n";
        std::cout << std::format("{}: {} wins\n", p1, wins1);
        std::cout << std::format("{}: {} wins\n", p2, wins2);
        std::cout << std::format("Ties: {}\n",        ties);
    }

private:
    int wins1 = 0, wins2 = 0, ties = 0;
};

// RoundLogger: prints a one-line summary immediately after each round
class RoundLogger : public IGameObserver
{
public:
    void onRoundEnd(const RoundResult& result) override
    {
        // {:2} pads the round number to 2 characters for aligned output
        std::cout << std::format("[Round {:2}]  {} ({}) vs {} ({})  =>  {}\n",
            result.round,
            result.player1Name, result.card1.toString(),
            result.player2Name, result.card2.toString(),
            result.winner);
    }
};

// --- Game (subject) -------------------------------------------------------

class ObserverWarGame
{
public:
    // Register any observer at runtime — game doesn't care what it does
    void addObserver(IGameObserver* obs) { observers.push_back(obs); }

    void play()
    {
        Deck source;
        Deck deck1, deck2;

        // Split the deck evenly between the two players
        for (int i = 0; i < 26; ++i) deck1.addCard(source.draw());
        for (int i = 0; i < 26; ++i) deck2.addCard(source.draw());

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
                deck1.addCard(c1); deck1.addCard(c2);
            }
            else if (c2.value > c1.value)
            {
                result.winner = p2;
                deck2.addCard(c1); deck2.addCard(c2);
            }
            else
            {
                result.winner = "Tie";
                deck1.addCard(c1); deck2.addCard(c2);
            }

            // Tell every registered observer what just happened
            notify(result);
            ++round;
        }

        // Print the scoreboard summary at the end
        // dynamic_cast checks the runtime type — returns nullptr if not a Scoreboard
        for (auto* obs : observers)
            if (auto* sb = dynamic_cast<Scoreboard*>(obs))
                sb->printSummary(p1, p2);
    }

private:
    std::vector<IGameObserver*> observers;  // raw pointers — we don't own these

    // Send the result to every observer in registration order
    void notify(const RoundResult& result)
    {
        for (auto* obs : observers) obs->onRoundEnd(result);
    }
};

int main()
{
    RoundLogger logger;
    Scoreboard  board;

    ObserverWarGame game;
    game.addObserver(&logger);  // logger sees each round first
    game.addObserver(&board);   // board updates second
    game.play();

    return 0;
}
```

#### Key terms

| Term            | Meaning                                                                         |
| --------------- | ------------------------------------------------------------------------------- |
| `IGameObserver` | Abstract observer interface                                                     |
| `RoundResult`   | Data bundle passed to every observer when a round ends                          |
| `addObserver`   | Registers an observer at runtime                                                |
| `notify`        | Loops over all observers and calls `onRoundEnd`                                 |
| `dynamic_cast`  | Safely downcasts a base pointer to a derived type; returns `nullptr` on failure |

📖 Reference: [Observer Pattern — Refactoring Guru](https://refactoring.guru/design-patterns/observer)

---

### 1.3 Factory Pattern

The Factory pattern provides an interface for creating objects, letting subclasses decide which concrete class to instantiate. Callers create objects through the factory without knowing the exact type.

**War use case:** create `HumanPlayer` or `ComputerPlayer` objects through a common factory interface — swap the factory to change who is playing.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>
#include <string>
#include <format>

// --- Card (same as previous examples) ------------------------------------

struct Card { std::string suit; int value; std::string toString() const; };

// --- Player interface -----------------------------------------------------

// Abstract base class that both HumanPlayer and ComputerPlayer must satisfy
class IPlayer
{
public:
    virtual std::string getName()             const = 0;
    virtual Card        playCard()                  = 0;
    virtual void        receiveCard(const Card& c)  = 0;
    virtual bool        hasCards()            const = 0;
    virtual int         deckSize()            const = 0;
    virtual ~IPlayer() = default;

protected:
    std::vector<Card> hand;   // shared storage — accessible in child classes
};

// --- Concrete player types ------------------------------------------------

// HumanPlayer: waits for the player to press Enter before drawing
class HumanPlayer : public IPlayer
{
public:
    explicit HumanPlayer(std::string n) : name(std::move(n)) {}

    std::string getName()  const override { return name; }
    bool hasCards()        const override { return !hand.empty(); }
    int  deckSize()        const override { return static_cast<int>(hand.size()); }

    Card playCard() override
    {
        std::cout << name << ", press ENTER to draw your card...";
        std::cin.ignore();   // wait for user input before proceeding
        Card top = hand.back();
        hand.pop_back();
        std::cout << name << " draws: " << top.toString() << "\n";
        return top;
    }

    void receiveCard(const Card& c) override { hand.insert(hand.begin(), c); }

private:
    std::string name;
};

// ComputerPlayer: draws automatically with no user interaction
class ComputerPlayer : public IPlayer
{
public:
    explicit ComputerPlayer(std::string n) : name(std::move(n)) {}

    std::string getName()  const override { return name; }
    bool hasCards()        const override { return !hand.empty(); }
    int  deckSize()        const override { return static_cast<int>(hand.size()); }

    Card playCard() override
    {
        Card top = hand.back();
        hand.pop_back();
        std::cout << name << " (CPU) draws: " << top.toString() << "\n";
        return top;
    }

    void receiveCard(const Card& c) override { hand.insert(hand.begin(), c); }

private:
    std::string name;
};

// --- Factory interface ----------------------------------------------------

// Each factory knows how to create one type of player
class IPlayerFactory
{
public:
    virtual std::unique_ptr<IPlayer> createPlayer(const std::string& name) = 0;
    virtual ~IPlayerFactory() = default;
};

// --- Concrete factories ---------------------------------------------------

class HumanPlayerFactory : public IPlayerFactory
{
public:
    std::unique_ptr<IPlayer> createPlayer(const std::string& name) override
    {
        return std::make_unique<HumanPlayer>(name);
    }
};

class ComputerPlayerFactory : public IPlayerFactory
{
public:
    std::unique_ptr<IPlayer> createPlayer(const std::string& name) override
    {
        return std::make_unique<ComputerPlayer>(name);
    }
};

// --- Game -----------------------------------------------------------------

class FactoryWarGame
{
public:
    // Accepts any two factories — caller decides the player types
    void startGame(IPlayerFactory& factory1, IPlayerFactory& factory2)
    {
        // createPlayer returns IPlayer* — the game never needs to know the concrete type
        auto p1 = factory1.createPlayer("Alice");
        auto p2 = factory2.createPlayer("Bob (CPU)");

        // Build and shuffle a fresh deck
        std::vector<Card> deck;
        for (const auto& suit : {"Spades", "Hearts", "Clubs", "Diamonds"})
            for (int v = 2; v <= 14; ++v)
                deck.push_back({suit, v});
        std::mt19937 rng(std::random_device{}());
        std::shuffle(deck.begin(), deck.end(), rng);

        // Deal 26 cards to each player
        for (int i = 0;  i < 26; ++i) p1->receiveCard(deck[i]);
        for (int i = 26; i < 52; ++i) p2->receiveCard(deck[i]);

        int round = 1;
        while (p1->hasCards() && p2->hasCards() && round <= 10)
        {
            std::cout << "\n── Round " << round << " ─────────────────────────\n";
            Card c1 = p1->playCard();
            Card c2 = p2->playCard();

            if (c1.value > c2.value)
            {
                p1->receiveCard(c1); p1->receiveCard(c2);
                std::cout << p1->getName() << " wins!\n";
            }
            else if (c2.value > c1.value)
            {
                p2->receiveCard(c1); p2->receiveCard(c2);
                std::cout << p2->getName() << " wins!\n";
            }
            else
            {
                p1->receiveCard(c1); p2->receiveCard(c2);
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
    // Swap HumanPlayerFactory for ComputerPlayerFactory to change player type
    ComputerPlayerFactory cpuFactory1;
    ComputerPlayerFactory cpuFactory2;

    FactoryWarGame game;
    game.startGame(cpuFactory1, cpuFactory2);

    return 0;
}
```

#### Key terms

| Term                                           | Meaning                                                     |
| ---------------------------------------------- | ----------------------------------------------------------- |
| `IPlayerFactory`                               | Abstract factory interface                                  |
| `HumanPlayerFactory` / `ComputerPlayerFactory` | Concrete factories that return different `IPlayer` subtypes |
| `createPlayer`                                 | Factory method — callers use this instead of `new`          |

📖 Reference: [Factory Method Pattern — Refactoring Guru](https://refactoring.guru/design-patterns/factory-method)

---

### 1.4 Singleton Pattern

The Singleton pattern restricts a class to exactly one instance and provides a global access point to it. The modern C++ approach uses a **local static variable**, which is initialised once and is thread-safe by default since C++11.

**War use case:** a `GameManager` that controls the overall flow of the application, ensuring only one game session runs at a time.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <format>

struct Card { std::string suit; int value; std::string toString() const; };

class GameManager
{
public:
    // getInstance() returns the same object every time it is called
    // The static local is created exactly once, on the first call
    static GameManager& getInstance()
    {
        static GameManager instance;   // constructed once; destroyed at program exit
        return instance;
    }

    // Deleting copy and assignment prevents accidental duplication
    GameManager(const GameManager&)            = delete;
    GameManager& operator=(const GameManager&) = delete;

    void startGame(const std::string& p1Name, const std::string& p2Name)
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
        running = false;    // release the lock so the next game can start
    }

    int getGamesPlayed() const { return gamesPlayed; }

private:
    // Private constructor — external code cannot call `new GameManager()`
    GameManager() = default;

    bool running     = false;
    int  gamesPlayed = 0;

    void runGame(const std::string& p1Name, const std::string& p2Name)
    {
        std::vector<Card> deck;
        for (const auto& suit : {"Spades", "Hearts", "Clubs", "Diamonds"})
            for (int v = 2; v <= 14; ++v)
                deck.push_back({suit, v});
        std::mt19937 rng(std::random_device{}());
        std::shuffle(deck.begin(), deck.end(), rng);

        // Give the first 26 cards to each player
        std::vector<Card> hand1(deck.begin(),        deck.begin() + 26);
        std::vector<Card> hand2(deck.begin() + 26,   deck.end());

        int w1 = 0, w2 = 0;
        // Play a 5-round sample for demonstration
        for (int round = 1; round <= 5; ++round)
        {
            Card c1 = hand1.back(); hand1.pop_back();
            Card c2 = hand2.back(); hand2.pop_back();

            std::cout << std::format("  Round {}: {} [{}] vs {} [{}]  =>  ",
                round, p1Name, c1.toString(), p2Name, c2.toString());

            if      (c1.value > c2.value) { ++w1; std::cout << p1Name << " wins\n"; }
            else if (c2.value > c1.value) { ++w2; std::cout << p2Name << " wins\n"; }
            else                          {       std::cout << "Tie\n"; }
        }

        std::cout << std::format("Result => {} wins: {}  {} wins: {}\n\n",
            p1Name, w1, p2Name, w2);
    }
};

int main()
{
    // Both calls go through the same GameManager instance
    GameManager::getInstance().startGame("Alice", "Bob");
    GameManager::getInstance().startGame("Carol", "Dave");

    std::cout << std::format("Total games played: {}\n",
        GameManager::getInstance().getGamesPlayed());
    return 0;
}
```

#### Key terms

| Term                                               | Meaning                                                            |
| -------------------------------------------------- | ------------------------------------------------------------------ |
| `static GameManager instance`                      | Local static — created once on first call, automatically destroyed |
| `= delete` on copy constructor and copy-assignment | Prevents creating extra instances by accident                      |
| `private` constructor                              | External code cannot call `new GameManager()`                      |

📖 Reference: [Singleton Pattern — Refactoring Guru](https://refactoring.guru/design-patterns/singleton)

---

### 1.5 Builder Pattern

The Builder pattern constructs complex objects step by step. Instead of a constructor with many parameters, you call setter-style methods on a builder object and then call `build()` to get the finished product. Each method returns `*this` so calls can be chained.

**War use case:** configure a game session (player names, round count, shuffle option, house rules) before it starts, without a sprawling constructor.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <stdexcept>
#include <format>

struct Card { std::string suit; int value; std::string toString() const; };

// --- Configuration struct -------------------------------------------------

// Plain data holder — filled in by the builder, consumed by the game
struct GameConfig
{
    std::string player1Name = "Player 1";
    std::string player2Name = "Player 2";
    int  maxRounds   = 26;
    bool shuffleDeck = true;
    bool tieGoesToP1 = false;   // house rule: ties award the round to player 1
    bool verbose     = true;
};

// --- Builder --------------------------------------------------------------

class GameConfigBuilder
{
public:
    // Each setter returns *this so calls can be chained fluently
    GameConfigBuilder& setPlayer1(const std::string& name)
    {
        config.player1Name = name;
        return *this;
    }

    GameConfigBuilder& setPlayer2(const std::string& name)
    {
        config.player2Name = name;
        return *this;
    }

    // Validate the input before storing it — throw on bad values
    GameConfigBuilder& setMaxRounds(int rounds)
    {
        if (rounds < 1 || rounds > 26)
            throw std::invalid_argument("Rounds must be between 1 and 26");
        config.maxRounds = rounds;
        return *this;
    }

    GameConfigBuilder& withShuffle(bool shuffle)
    {
        config.shuffleDeck = shuffle;
        return *this;
    }

    // Fluent, descriptive name — reads like English: .withTieRuleP1()
    GameConfigBuilder& withTieRuleP1()
    {
        config.tieGoesToP1 = true;
        return *this;
    }

    GameConfigBuilder& withVerboseOutput(bool v)
    {
        config.verbose = v;
        return *this;
    }

    // Finalise and return the completed config
    GameConfig build() const { return config; }

private:
    GameConfig config;  // accumulates settings as methods are called
};

// --- Game -----------------------------------------------------------------

class BuilderWarGame
{
public:
    void play(const GameConfig& cfg)
    {
        if (cfg.verbose)
            std::cout << std::format(
                "Starting game: {} vs {}  ({} rounds, shuffle={})\n\n",
                cfg.player1Name, cfg.player2Name, cfg.maxRounds, cfg.shuffleDeck);

        std::vector<Card> deck;
        for (const auto& suit : {"Spades", "Hearts", "Clubs", "Diamonds"})
            for (int v = 2; v <= 14; ++v)
                deck.push_back({suit, v});

        if (cfg.shuffleDeck)
        {
            std::mt19937 rng(std::random_device{}());
            std::shuffle(deck.begin(), deck.end(), rng);
        }

        // Each player takes the first or second half of the deck
        std::vector<Card> hand1(deck.begin(),        deck.begin() + 26);
        std::vector<Card> hand2(deck.begin() + 26,   deck.end());

        int w1 = 0, w2 = 0;
        for (int round = 1; round <= cfg.maxRounds; ++round)
        {
            Card c1 = hand1.back(); hand1.pop_back();
            Card c2 = hand2.back(); hand2.pop_back();

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
                // Apply the house rule if configured
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
    // Method chaining reads like a sentence describing the game setup
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

#### Key terms

| Term                | Meaning                                     |
| ------------------- | ------------------------------------------- |
| `GameConfig`        | Plain data holder — the product being built |
| `GameConfigBuilder` | Accumulates settings step by step           |
| `return *this`      | Enables method chaining (fluent interface)  |
| `.build()`          | Finalises and returns the completed config  |

📖 Reference: [Builder Pattern — Refactoring Guru](https://refactoring.guru/design-patterns/builder)

---

## Exercises

Compile and run each starter file with:

```bash
g++ --std=c++20 -o week-02-design-patterns week-02-design-patterns.cpp
./week-02-design-patterns
```

### AI Usage Guidelines

AI tools are encouraged but use them critically:

- Refine your prompts — vague prompts yield vague responses
- Validate AI output — don't trust it blindly
- Acknowledge AI usage at the top of any AI-assisted file:

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

### Task 1 — Strategy Pattern Extension

Extend the Strategy pattern example by adding a third draw strategy: `LowestCardStrategy`, which always plays the **lowest** card in the player's hand. Wire it into the game alongside `RandomStrategy` and `HighestCardStrategy` and observe how the win rates differ across strategies.

> **Hint:** `LowestCardStrategy` follows the same structure as `HighestCardStrategy` — sort the hand and take the first element instead of the last.

---

### Task 2 — Observer Pattern Extension

Extend the Observer pattern example by adding a `StreakObserver` that tracks the **longest consecutive winning streak** for each player. It should print the result at the end of the game in the format:

```
Alice longest streak: 4
Bob longest streak: 2
```

> **Hint:** keep a `currentStreak` and `longestStreak` counter for each player. Reset `currentStreak` to 0 whenever the other player wins or a tie occurs.

---

### Task 3 — Builder Pattern Extension

Extend the Builder pattern example with two new configuration options:

| Option               | Description                                                                  |
| -------------------- | ---------------------------------------------------------------------------- |
| `setNumDecks(int n)` | Combine `n` standard 52-card decks into one before splitting between players |
| `setAcesHigh(bool)`  | When `false`, treat Aces as value `1` instead of `14`                        |

Update the game logic to respect both settings.

> **Hint:** for `setNumDecks`, repeat the deck-building loop `n` times before shuffling. For `setAcesHigh(false)`, clamp any card with `value == 14` to `value = 1` after dealing.
