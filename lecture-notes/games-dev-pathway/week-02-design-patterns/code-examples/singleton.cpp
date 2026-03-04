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
            std::cout << "A game is already in progress\n";
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
    GameManager::getInstance().startGame("Alice", "Bob");

    std::cout << std::format("Total games played: {}\n",
                             GameManager::getInstance().getGamesPlayed());
    return 0;
}