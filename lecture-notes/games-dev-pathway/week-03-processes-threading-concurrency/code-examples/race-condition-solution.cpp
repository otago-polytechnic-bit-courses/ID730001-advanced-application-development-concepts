
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

class BankAccount
{
public:
    BankAccount(const std::string& id, double initial)
        : account_id(id), balance(initial) {}

    void deposit(double amount)
    {
        // lock_guard locks the mutex on construction and unlocks on destruction
        // This guarantees the mutex is always released, even if an exception is thrown
        std::lock_guard<std::mutex> lock(mtx);
        balance += amount;
        std::cout << "[" << account_id << "] Deposited $" << amount
                  << "  Balance: $" << balance << "\n";
    }

    void withdraw(double amount)
    {
        std::lock_guard<std::mutex> lock(mtx);   // only one thread in here at a time
        if (amount > balance)
        {
            std::cout << "[" << account_id << "] Insufficient funds\n";
            return;
        }
        balance -= amount;
        std::cout << "[" << account_id << "] Withdrew $" << amount
                  << "  Balance: $" << balance << "\n";
    }

    double get_balance() const
    {
        std::lock_guard<std::mutex> lock(mtx);   // even reads need protection
        return balance;
    }

private:
    std::string  account_id;
    double       balance;
    mutable std::mutex mtx;   // mutable: allows locking even in const methods
};

int main()
{
    BankAccount account("ACC-001", 1000.0);

    // Multiple threads depositing and withdrawing concurrently
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
        threads.emplace_back([&account]() { account.deposit(100.0); });
    for (int i = 0; i < 3; ++i)
        threads.emplace_back([&account]() { account.withdraw(50.0); });

    for (auto& t : threads) t.join();

    std::cout << "Final balance: $" << account.get_balance() << "\n";
    return 0;
}