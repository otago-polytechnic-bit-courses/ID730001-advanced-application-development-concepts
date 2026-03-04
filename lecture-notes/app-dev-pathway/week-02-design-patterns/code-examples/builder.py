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