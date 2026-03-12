#include <iostream>
#include <thread>
#include <vector>
#include <string>

void process_transaction(int id, const std::string& type, double amount)
{
    std::cout << "[Thread " << id << "] " << type
              << " $" << amount << "\n";
}

int main()
{
    std::vector<std::thread> workers;

    // Spawn one thread per transaction
    workers.emplace_back(process_transaction, 1, "Deposit",    200.0);
    workers.emplace_back(process_transaction, 2, "Withdrawal", 50.0);
    workers.emplace_back(process_transaction, 3, "Transfer",   300.0);

    // Wait for every thread to finish before the program exits
    for (auto& t : workers) t.join();

    std::cout << "All transactions processed.\n";
    return 0;
}