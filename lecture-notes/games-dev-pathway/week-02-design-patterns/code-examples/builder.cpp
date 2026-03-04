#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <stdexcept>
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