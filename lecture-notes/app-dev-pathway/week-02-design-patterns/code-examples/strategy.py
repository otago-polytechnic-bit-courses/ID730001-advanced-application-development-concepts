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