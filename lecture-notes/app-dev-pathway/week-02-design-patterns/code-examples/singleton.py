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