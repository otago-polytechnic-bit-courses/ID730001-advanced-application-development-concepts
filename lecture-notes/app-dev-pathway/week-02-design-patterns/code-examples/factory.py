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