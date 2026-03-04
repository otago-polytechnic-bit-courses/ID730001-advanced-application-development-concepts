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