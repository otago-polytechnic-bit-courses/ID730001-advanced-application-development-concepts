#include <iostream>
#include <thread>
#include <string>

// A plain function — any callable can be passed to std::thread
void process_deposit(const std::string& account, double amount)
{
    std::cout << "Depositing $" << amount
              << " into account " << account << "\n";
}

int main()
{
    // Launch process_deposit on a new thread
    // Arguments after the callable are forwarded to the function
    std::thread t(process_deposit, "ACC-001", 500.0);

    // join() blocks the calling thread until t finishes
    // You MUST call either join() or detach() before the thread object is destroyed
    t.join();

    std::cout << "Deposit complete.\n";
    return 0;
}