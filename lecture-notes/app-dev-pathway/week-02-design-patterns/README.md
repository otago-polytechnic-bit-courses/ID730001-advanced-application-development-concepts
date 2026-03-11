# Week 02 — Design Patterns

## Navigation

|            | Link                                                                                                                              |
| ---------- | --------------------------------------------------------------------------------------------------------------------------------- |
| ← Previous | [Week 01 - Git, Programming Paradigms & Python](lecture-notes/app-dev-pathway/week-01-git-programming-paradigms-python/README.md) |
| → Next     | [Week 03 - Processes, Threads & Concurrency](lecture-notes/app-dev-pathway/week-03-processes-threading-concurrency/README.md)     |

---

## Design Patterns

**Design patterns** are reusable solutions to common software design problems. They provide a way to structure code that is flexible, maintainable, and scalable.

There are three broad categories:

| Category        | Focus                                                  | Examples                      |
| --------------- | ------------------------------------------------------ | ----------------------------- |
| **Behavioural** | Communication and interaction between objects          | Observer, Strategy, Command   |
| **Creational**  | Object creation                                        | Singleton, Factory, Builder   |
| **Structural**  | How classes and objects compose into larger structures | Adapter, Decorator, Composite |

We use the card game **War** as a running example throughout. In War, two players each have a deck of cards. Each player draws a card — the player with the higher card wins the round. The game continues until one player holds all the cards.

---

## 1. Behavioural Patterns

### 1.1 Strategy Pattern

The **Strategy** pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable. The algorithm can vary independently from the clients that use it.

**In War:** Different strategies for how a player chooses which card to play — always random, or always the highest card available.

```python
import random


class Card:
    def __init__(self, suit, value):
        self.suit = suit
        self.value = value

    def __str__(self):
        names = {11: "Jack", 12: "Queen", 13: "King", 14: "Ace"}
        name = names.get(self.value, str(self.value))
        return f"{name} of {self.suit}"


class Deck:
    def __init__(self):
        suits = ["Spades", "Hearts", "Clubs", "Diamonds"]
        self.cards = [Card(suit, value) for suit in suits for value in range(2, 15)]
        self.shuffle()

    def shuffle(self):
        random.shuffle(self.cards)

    def draw(self):
        if not self.cards:
            raise RuntimeError("Deck is empty")
        return self.cards.pop()

    def add_card(self, card):
        self.cards.insert(0, card)

    def is_empty(self):
        return len(self.cards) == 0

    def size(self):
        return len(self.cards)


class IDrawStrategy:
    def choose_card(self, deck):
        raise NotImplementedError


class RandomStrategy(IDrawStrategy):
    def choose_card(self, deck):
        return deck.draw()


class HighestCardStrategy(IDrawStrategy):
    def choose_card(self, deck):
        hand = []
        while not deck.is_empty():
            hand.append(deck.draw())

        hand.sort(key=lambda c: c.value)
        best = hand.pop()

        for card in hand:
            deck.add_card(card)

        return best


class Player:
    def __init__(self, name, strategy):
        self.name = name
        self.strategy = strategy
        self.deck = Deck.__new__(Deck)
        self.deck.cards = []

    def play_card(self):
        return self.strategy.choose_card(self.deck)

    def receive_card(self, card):
        self.deck.add_card(card)

    def deal_half(self, source, count):
        for _ in range(count):
            self.deck.add_card(source.draw())

    def has_cards(self):
        return not self.deck.is_empty()

    def deck_size(self):
        return self.deck.size()


class WarGame:
    def play(self):
        source = Deck()

        alice = Player("Alice (Random)", RandomStrategy())
        bob = Player("Bob (Highest)", HighestCardStrategy())

        alice.deal_half(source, 26)
        bob.deal_half(source, 26)

        round_num = 1
        while alice.has_cards() and bob.has_cards() and round_num <= 50:
            c1 = alice.play_card()
            c2 = bob.play_card()

            print(f"Round {round_num}: {alice.name} plays {c1}  vs  {bob.name} plays {c2}")

            if c1.value > c2.value:
                alice.receive_card(c1)
                alice.receive_card(c2)
                print(f"  => {alice.name} wins the round!")
            elif c2.value > c1.value:
                bob.receive_card(c1)
                bob.receive_card(c2)
                print(f"  => {bob.name} wins the round!")
            else:
                alice.receive_card(c1)
                bob.receive_card(c2)
                print("  => Tie! Each player keeps their card.")

            print(f"  Cards: {alice.name}={alice.deck_size()}  {bob.name}={bob.deck_size()}\n")
            round_num += 1

        if alice.deck_size() > bob.deck_size():
            print(f"{alice.name} wins the game!")
        elif bob.deck_size() > alice.deck_size():
            print(f"{bob.name} wins the game!")
        else:
            print("The game is a draw!")


game = WarGame()
game.play()
```

---

### 1.2 Observer Pattern

The **Observer** pattern defines a one-to-many dependency between objects so that when one object changes state, all its dependents are notified automatically.

**In War:** Notify interested parties whenever a round ends — a scoreboard that tracks wins, and a logger that records what happened.

```python
import random
from dataclasses import dataclass


class Card:
    def __init__(self, suit, value):
        self.suit = suit
        self.value = value

    def __str__(self):
        names = {11: "Jack", 12: "Queen", 13: "King", 14: "Ace"}
        name = names.get(self.value, str(self.value))
        return f"{name} of {self.suit}"


class Deck:
    def __init__(self):
        suits = ["Spades", "Hearts", "Clubs", "Diamonds"]
        self.cards = [Card(suit, value) for suit in suits for value in range(2, 15)]
        random.shuffle(self.cards)

    def draw(self):
        return self.cards.pop()

    def add_card(self, card):
        self.cards.insert(0, card)

    def is_empty(self):
        return len(self.cards) == 0

    def size(self):
        return len(self.cards)


@dataclass
class RoundResult:
    round: int
    card1: object
    card2: object
    player1_name: str
    player2_name: str
    winner: str


class IGameObserver:
    def on_round_end(self, result):
        raise NotImplementedError


class Scoreboard(IGameObserver):
    def __init__(self):
        self.wins1 = 0
        self.wins2 = 0
        self.ties = 0

    def on_round_end(self, result):
        if result.winner == result.player1_name:
            self.wins1 += 1
        elif result.winner == result.player2_name:
            self.wins2 += 1
        else:
            self.ties += 1

    def print_summary(self, p1, p2):
        print("\n── Scoreboard ──────────────────────")
        print(f"{p1}: {self.wins1} wins")
        print(f"{p2}: {self.wins2} wins")
        print(f"Ties: {self.ties}")


class RoundLogger(IGameObserver):
    def on_round_end(self, result):
        print(f"[Round {result.round:2}]  {result.player1_name} ({result.card1}) "
              f"vs {result.player2_name} ({result.card2})  =>  {result.winner}")


class ObserverWarGame:
    def __init__(self):
        self.observers = []

    def add_observer(self, observer):
        self.observers.append(observer)

    def play(self):
        source = Deck()
        deck1 = Deck.__new__(Deck)
        deck1.cards = []
        deck2 = Deck.__new__(Deck)
        deck2.cards = []

        for _ in range(26):
            deck1.add_card(source.draw())
        for _ in range(26):
            deck2.add_card(source.draw())

        p1 = "Alice"
        p2 = "Bob"
        round_num = 1

        while not deck1.is_empty() and not deck2.is_empty() and round_num <= 30:
            c1 = deck1.draw()
            c2 = deck2.draw()

            result = RoundResult(round_num, c1, c2, p1, p2, "")

            if c1.value > c2.value:
                result.winner = p1
                deck1.add_card(c1)
                deck1.add_card(c2)
            elif c2.value > c1.value:
                result.winner = p2
                deck2.add_card(c1)
                deck2.add_card(c2)
            else:
                result.winner = "Tie"
                deck1.add_card(c1)
                deck2.add_card(c2)

            self._notify(result)
            round_num += 1

        for obs in self.observers:
            if isinstance(obs, Scoreboard):
                obs.print_summary(p1, p2)

    def _notify(self, result):
        for obs in self.observers:
            obs.on_round_end(result)


logger = RoundLogger()
board = Scoreboard()

game = ObserverWarGame()
game.add_observer(logger)
game.add_observer(board)
game.play()
```

---

## 2. Creational Patterns

### 2.1 Factory Pattern

The **Factory** pattern provides an interface for creating objects, allowing subclasses to decide which concrete class to instantiate.

**In War:** Create different types of players — a human player who is prompted for input, and a computer player who plays automatically.

```python
import random


class Card:
    def __init__(self, suit, value):
        self.suit = suit
        self.value = value

    def __str__(self):
        names = {11: "Jack", 12: "Queen", 13: "King", 14: "Ace"}
        name = names.get(self.value, str(self.value))
        return f"{name} of {self.suit}"


class IPlayer:
    def get_name(self):
        raise NotImplementedError

    def play_card(self):
        raise NotImplementedError

    def receive_card(self, card):
        raise NotImplementedError

    def has_cards(self):
        raise NotImplementedError

    def deck_size(self):
        raise NotImplementedError


class HumanPlayer(IPlayer):
    def __init__(self, name):
        self.name = name
        self.hand = []

    def get_name(self):
        return self.name

    def has_cards(self):
        return len(self.hand) > 0

    def deck_size(self):
        return len(self.hand)

    def play_card(self):
        input(f"{self.name}, press ENTER to draw your card...")
        card = self.hand.pop()
        print(f"{self.name} draws: {card}")
        return card

    def receive_card(self, card):
        self.hand.insert(0, card)


class ComputerPlayer(IPlayer):
    def __init__(self, name):
        self.name = name
        self.hand = []

    def get_name(self):
        return self.name

    def has_cards(self):
        return len(self.hand) > 0

    def deck_size(self):
        return len(self.hand)

    def play_card(self):
        card = self.hand.pop()
        print(f"{self.name} (CPU) draws: {card}")
        return card

    def receive_card(self, card):
        self.hand.insert(0, card)


class IPlayerFactory:
    def create_player(self, name):
        raise NotImplementedError


class HumanPlayerFactory(IPlayerFactory):
    def create_player(self, name):
        return HumanPlayer(name)


class ComputerPlayerFactory(IPlayerFactory):
    def create_player(self, name):
        return ComputerPlayer(name)


class FactoryWarGame:
    def start_game(self, factory1, factory2):
        p1 = factory1.create_player("Alice")
        p2 = factory2.create_player("Bob (CPU)")

        suits = ["Spades", "Hearts", "Clubs", "Diamonds"]
        deck = [Card(suit, value) for suit in suits for value in range(2, 15)]
        random.shuffle(deck)

        for card in deck[:26]:
            p1.receive_card(card)
        for card in deck[26:]:
            p2.receive_card(card)

        round_num = 1
        while p1.has_cards() and p2.has_cards() and round_num <= 10:
            print(f"\n── Round {round_num} ─────────────────────────")
            c1 = p1.play_card()
            c2 = p2.play_card()

            if c1.value > c2.value:
                p1.receive_card(c1)
                p1.receive_card(c2)
                print(f"{p1.get_name()} wins!")
            elif c2.value > c1.value:
                p2.receive_card(c1)
                p2.receive_card(c2)
                print(f"{p2.get_name()} wins!")
            else:
                p1.receive_card(c1)
                p2.receive_card(c2)
                print("Tie!")

            print(f"Cards: {p1.get_name()}={p1.deck_size()} {p2.get_name()}={p2.deck_size()}")
            round_num += 1


cpu_factory1 = ComputerPlayerFactory()
cpu_factory2 = ComputerPlayerFactory()

game = FactoryWarGame()
game.start_game(cpu_factory1, cpu_factory2)
```

---

### 2.2 Singleton Pattern

The **Singleton** pattern restricts the instantiation of a class to a single instance and provides a global point of access to that instance.

**In War:** A `GameManager` that controls the overall application flow, ensuring only one game session is active at a time.

```python
import random


class Card:
    def __init__(self, suit, value):
        self.suit = suit
        self.value = value

    def __str__(self):
        names = {11: "Jack", 12: "Queen", 13: "King", 14: "Ace"}
        name = names.get(self.value, str(self.value))
        return f"{name} of {self.suit}"


class GameManager:
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance.running = False
            cls._instance.games_played = 0
        return cls._instance

    @classmethod
    def get_instance(cls):
        return cls()

    def start_game(self, p1_name, p2_name):
        if self.running:
            print("A game is already in progress!")
            return

        self.running = True
        self.games_played += 1
        print(f"── Game {self.games_played} starting: {p1_name} vs {p2_name} ──")
        self._run_game(p1_name, p2_name)
        self.running = False

    def get_games_played(self):
        return self.games_played

    def _run_game(self, p1_name, p2_name):
        suits = ["Spades", "Hearts", "Clubs", "Diamonds"]
        deck = [Card(suit, value) for suit in suits for value in range(2, 15)]
        random.shuffle(deck)

        hand1 = deck[:26]
        hand2 = deck[26:]

        w1 = 0
        w2 = 0

        for round_num in range(1, 6):
            c1 = hand1.pop()
            c2 = hand2.pop()

            print(f"  Round {round_num}: {p1_name} [{c1}] vs {p2_name} [{c2}]  =>  ", end="")

            if c1.value > c2.value:
                w1 += 1
                print(f"{p1_name} wins")
            elif c2.value > c1.value:
                w2 += 1
                print(f"{p2_name} wins")
            else:
                print("Tie")

        print(f"Result => {p1_name} wins: {w1}  {p2_name} wins: {w2}\n")


GameManager.get_instance().start_game("Alice", "Bob")
GameManager.get_instance().start_game("Carol", "Dave")

print(f"Total games played: {GameManager.get_instance().get_games_played()}")
```

---

### 2.3 Builder Pattern

The **Builder** pattern constructs complex objects step by step. The same construction process can create different representations, avoiding large constructor parameter lists.

**In War:** Configure a game session — number of rounds, shuffle behaviour, house rules — before the game starts.

```python
import random


class Card:
    def __init__(self, suit, value):
        self.suit = suit
        self.value = value

    def __str__(self):
        names = {11: "Jack", 12: "Queen", 13: "King", 14: "Ace"}
        name = names.get(self.value, str(self.value))
        return f"{name} of {self.suit}"


class GameConfig:
    def __init__(self):
        self.player1_name = "Player 1"
        self.player2_name = "Player 2"
        self.max_rounds = 26
        self.shuffle_deck = True
        self.tie_goes_to_p1 = False
        self.verbose = True


class GameConfigBuilder:
    def __init__(self):
        self.config = GameConfig()

    def set_player1(self, name):
        self.config.player1_name = name
        return self

    def set_player2(self, name):
        self.config.player2_name = name
        return self

    def set_max_rounds(self, rounds):
        if rounds < 1 or rounds > 26:
            raise ValueError("Rounds must be between 1 and 26")
        self.config.max_rounds = rounds
        return self

    def with_shuffle(self, shuffle):
        self.config.shuffle_deck = shuffle
        return self

    def with_tie_rule_p1(self):
        self.config.tie_goes_to_p1 = True
        return self

    def with_verbose_output(self, verbose):
        self.config.verbose = verbose
        return self

    def build(self):
        return self.config


class BuilderWarGame:
    def play(self, cfg):
        if cfg.verbose:
            print(f"Starting game: {cfg.player1_name} vs {cfg.player2_name}  "
                  f"({cfg.max_rounds} rounds, shuffle={cfg.shuffle_deck})\n")

        suits = ["Spades", "Hearts", "Clubs", "Diamonds"]
        deck = [Card(suit, value) for suit in suits for value in range(2, 15)]

        if cfg.shuffle_deck:
            random.shuffle(deck)

        hand1 = deck[:26]
        hand2 = deck[26:]

        w1 = 0
        w2 = 0

        for round_num in range(1, cfg.max_rounds + 1):
            c1 = hand1.pop()
            c2 = hand2.pop()

            if c1.value > c2.value:
                w1 += 1
                outcome = f"{cfg.player1_name} wins"
            elif c2.value > c1.value:
                w2 += 1
                outcome = f"{cfg.player2_name} wins"
            else:
                if cfg.tie_goes_to_p1:
                    w1 += 1
                    outcome = f"Tie => {cfg.player1_name} (house rule)"
                else:
                    outcome = "Tie"

            if cfg.verbose:
                print(f"Round {round_num:2}: {c1} vs {c2}  =>  {outcome}")

        print(f"\nFinal: {cfg.player1_name} = {w1}  {cfg.player2_name} = {w2}")


cfg = (GameConfigBuilder()
       .set_player1("Alice")
       .set_player2("Bob")
       .set_max_rounds(10)
       .with_shuffle(True)
       .with_tie_rule_p1()
       .with_verbose_output(True)
       .build())

game = BuilderWarGame()
game.play(cfg)
```

---

## Exercises

### AI Usage Guidelines

AI tools are encouraged but use them critically:

- Refine your prompts — vague prompts yield vague responses
- Validate AI output — don't trust it blindly
- Acknowledge AI usage at the top of any AI-assisted file:

```python
"""
Brief description of what this file does

AI Assistance: This file was developed with assistance from [AI Tool Name]

Prompts used:
- "Your first prompt here"
- "Your second prompt here"

Usage: Describe how you used the AI responses to help you with your work
"""
```

---

### Task 1 — Third Draw Strategy

Extend the Strategy pattern example by adding a `LowestCardStrategy` that always plays the lowest card in the player's hand. Wire it into the game alongside `RandomStrategy` and `HighestCardStrategy`, and observe how the win rates differ across the three strategies.

---

### Task 2 — Streak Observer

Extend the Observer pattern example by adding a `StreakObserver` that tracks the longest consecutive winning streak for each player. It should print the result at the end of the game in the following format:

```
Alice longest streak: 4
Bob longest streak: 2
```

---

### Task 3 — Extended Builder Options

Extend the Builder pattern example with two new configuration options:

- `set_num_decks(n)` — combines `n` standard 52-card decks into one before splitting between players
- `set_aces_high(value)` — when `False`, treats Aces as value `1` instead of `14`

Update the game logic to respect both settings.
