#include <iostream>
#include <thread>
#include <vector>

// Shared bank balance — accessed by multiple threads simultaneously
double balance = 1000.0;

void deposit(double amount)
{
    // DANGER: read-modify-write is NOT atomic
    // Thread A reads 1000, Thread B reads 1000, both add 100, both write 1100
    // Net result: 1100 instead of the correct 1200
    balance += amount;
}

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
        threads.emplace_back(deposit, 100.0);
    for (auto& t : threads) t.join();

    // May print anything from 1100 to 2000 — output is non-deterministic
    std::cout << "Final balance: $" << balance << "\n";
    return 0;
}