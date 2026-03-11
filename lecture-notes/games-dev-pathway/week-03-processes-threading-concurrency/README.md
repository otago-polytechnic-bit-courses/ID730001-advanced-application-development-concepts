# Week 03 — Processes, Threads & Concurrency

## Navigation

|            | Link                                                                                           |
| ---------- | ---------------------------------------------------------------------------------------------- |
| ← Previous | [Week 02 - Design Patterns](lecture-notes/games-dev-pathway/week-02-design-patterns/README.md) |
| → Next     | [Week 04 - Networking](lecture-notes/games-dev-pathway/week-04-networking/README.md)           |

---

## 1. Processes vs Threads

Before writing concurrent code, it helps to understand the two fundamental units of execution the operating system provides.

|                     | Process                                                         | Thread                                                              |
| ------------------- | --------------------------------------------------------------- | ------------------------------------------------------------------- |
| **Definition**      | An independent program in execution, with its own memory space  | A unit of execution _within_ a process; shares the process's memory |
| **Memory**          | Isolated — processes cannot read each other's memory by default | Shared — all threads in a process see the same heap and globals     |
| **Creation cost**   | High — the OS must allocate a new address space                 | Low — just a new stack and register set within the existing process |
| **Communication**   | Inter-process communication (pipes, sockets, shared memory)     | Direct — via shared variables (but requires synchronisation)        |
| **Crash isolation** | A crash in one process does not affect others                   | A crash in one thread can bring down the entire process             |
| **C++ API**         | OS-specific (`fork` on Linux, `CreateProcess` on Windows)       | `std::thread` (cross-platform, C++11)                               |

**Rule of thumb:** use multiple processes when isolation matters (e.g. a web browser sandboxing tabs); use multiple threads when you need low-overhead parallelism within a single program (e.g. handling many bank transactions simultaneously).

---

## 2. `std::thread`

`std::thread` (from `<thread>`) launches a function on a new OS thread. The thread runs concurrently with the caller — both execute at the same time.

```cpp
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
```

**Launching multiple threads:**

```cpp
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
```

**`join` vs `detach`:**

| Method       | Behaviour                                                                                                |
| ------------ | -------------------------------------------------------------------------------------------------------- |
| `t.join()`   | Caller blocks until `t` finishes. Safe — you know when it's done.                                        |
| `t.detach()` | Thread runs independently; caller does not wait. Dangerous if the thread outlives objects it references. |

> Prefer `join`. Only `detach` when the thread truly does not share any data with the rest of the program.

📖 Reference: [C++ — std::thread](https://en.cppreference.com/w/cpp/thread/thread)

---

## 3. Mutexes & Locks

When multiple threads share data, they can interleave in unpredictable ways and corrupt it. A **mutex** (mutual exclusion lock) ensures only one thread accesses a critical section at a time.

### 3.1 The problem — a race condition

```cpp
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
```

### 3.2 The solution — `std::mutex` and `std::lock_guard`

```cpp
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
```

### 3.3 `std::unique_lock` — more flexible locking

`std::lock_guard` is simple but inflexible. Use `std::unique_lock` when you need to unlock early, defer locking, or use condition variables.

```cpp
#include <mutex>

std::mutex mtx;

void transfer(BankAccount& from, BankAccount& to, double amount)
{
    // unique_lock can be unlocked and re-locked manually
    std::unique_lock<std::mutex> lock(mtx);

    from.withdraw(amount);   // protected by the lock
    lock.unlock();           // release early — to.deposit doesn't need this mutex

    to.deposit(amount);
}
```

|                                | `lock_guard` | `unique_lock`   |
| ------------------------------ | ------------ | --------------- |
| Overhead                       | Minimal      | Slightly higher |
| Manual unlock                  | ✗            | ✓               |
| Deferred locking               | ✗            | ✓               |
| Works with condition variables | ✗            | ✓               |

📖 Reference: [C++ — std::mutex](https://en.cppreference.com/w/cpp/thread/mutex)

---

## 4. Deadlocks & Race Conditions

### 4.1 Race conditions

A **race condition** occurs when the correctness of a program depends on the relative timing of threads. The deposit example above is a classic race condition — the `+=` operation is not atomic.

**Symptoms:** non-deterministic results, bugs that only appear under load, results that change between runs.

**Prevention:** protect every shared read _and_ write with the same mutex.

### 4.2 Deadlocks

A **deadlock** occurs when two or more threads each hold a lock the other needs, so all of them wait forever.

```
Thread A holds mtx1, waits for mtx2
Thread B holds mtx2, waits for mtx1
→ Neither can proceed
```

```cpp
// DANGER: this transfer function can deadlock
void unsafe_transfer(BankAccount& from, BankAccount& to, double amount)
{
    std::lock_guard<std::mutex> lock_from(from.mtx);  // Thread A locks ACC-001
    std::lock_guard<std::mutex> lock_to(to.mtx);      // Thread A waits for ACC-002
    // Meanwhile, Thread B has locked ACC-002 and is waiting for ACC-001 → deadlock
}
```

**Prevention strategies:**

```cpp
#include <mutex>

// Strategy 1: always lock mutexes in the same global order
// (e.g. always lock the account with the lower ID first)

// Strategy 2: use std::lock() to acquire multiple mutexes atomically
void safe_transfer(BankAccount& from, BankAccount& to, double amount)
{
    // std::lock acquires both mutexes simultaneously — no deadlock possible
    std::lock(from.mtx, to.mtx);

    // adopt_lock tells unique_lock the mutex is already locked — just manage its release
    std::unique_lock<std::mutex> lock_from(from.mtx, std::adopt_lock);
    std::unique_lock<std::mutex> lock_to(to.mtx,   std::adopt_lock);

    from.balance -= amount;
    to.balance   += amount;
}   // both locks released here automatically
```

**Four conditions for deadlock (all must hold):**

| Condition        | Description                                         |
| ---------------- | --------------------------------------------------- |
| Mutual exclusion | Resources cannot be shared                          |
| Hold and wait    | Thread holds one resource while waiting for another |
| No preemption    | Resources cannot be forcibly taken away             |
| Circular wait    | Thread A waits for B, B waits for A                 |

> Break any one condition to prevent deadlock. `std::lock` breaks **hold and wait** by acquiring all locks at once.

📖 Reference: [C++ — std::lock](https://en.cppreference.com/w/cpp/thread/lock)

---

## 5. Condition Variables

A **condition variable** lets a thread sleep until another thread signals that something has changed. This is the correct way to implement a waiting thread — far better than a busy loop that wastes CPU.

**Bank use case:** a fraud-checker thread waits until a transaction is queued; the transaction processor wakes it up.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>

struct Transaction
{
    std::string account_id;
    std::string type;    // "deposit" or "withdrawal"
    double      amount;
};

class TransactionQueue
{
public:
    // Called by the producer thread to add a new transaction
    void push(const Transaction& tx)
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            queue.push(tx);
        }
        // Wake up one waiting consumer — called OUTSIDE the lock to avoid
        // immediately blocking the consumer on the mutex we still hold
        cv.notify_one();
    }

    // Called by the consumer thread to take the next transaction
    // Blocks if the queue is empty
    Transaction pop()
    {
        // unique_lock required — condition_variable::wait() needs to unlock temporarily
        std::unique_lock<std::mutex> lock(mtx);

        // wait() atomically: (1) unlocks mtx, (2) sleeps, (3) re-locks when notified
        // The lambda is the wake-up condition — spurious wakeups are re-checked automatically
        cv.wait(lock, [this]() { return !queue.empty(); });

        Transaction tx = queue.front();
        queue.pop();
        return tx;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }

private:
    std::queue<Transaction> queue;
    mutable std::mutex      mtx;
    std::condition_variable cv;
};

int main()
{
    TransactionQueue txq;

    // Producer: pushes three transactions then signals done
    std::thread producer([&txq]()
    {
        txq.push({"ACC-001", "deposit",    500.0});
        txq.push({"ACC-002", "withdrawal", 200.0});
        txq.push({"ACC-003", "deposit",   1000.0});
    });

    // Consumer: processes each transaction as it arrives
    std::thread consumer([&txq]()
    {
        for (int i = 0; i < 3; ++i)
        {
            Transaction tx = txq.pop();   // sleeps if nothing is queued yet
            std::cout << "Processing " << tx.type
                      << " of $"       << tx.amount
                      << " for "       << tx.account_id << "\n";
        }
    });

    producer.join();
    consumer.join();
    return 0;
}
```

**`notify_one` vs `notify_all`:**

| Method            | Behaviour                                                                                 |
| ----------------- | ----------------------------------------------------------------------------------------- |
| `cv.notify_one()` | Wakes exactly one waiting thread. Use when any one worker can handle the work.            |
| `cv.notify_all()` | Wakes all waiting threads. Use when all of them need to respond (e.g. a shutdown signal). |

📖 Reference: [C++ — std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable)

---

## 6. Thread Pools

Creating and destroying threads is expensive. A **thread pool** pre-allocates a fixed number of worker threads that pick up tasks from a shared queue. This amortises the creation cost and puts a cap on total concurrency.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>

class ThreadPool
{
public:
    // Create the pool and launch `num_threads` worker threads immediately
    explicit ThreadPool(size_t num_threads)
    {
        for (size_t i = 0; i < num_threads; ++i)
        {
            // Each worker runs the same loop: wait for a task, execute it, repeat
            workers.emplace_back([this]()
            {
                while (true)
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx);

                        // Sleep until there is a task OR the pool is being shut down
                        cv.wait(lock, [this]()
                            { return !tasks.empty() || stop; });

                        // stop + empty queue means it's time to exit
                        if (stop && tasks.empty()) return;

                        // Take ownership of the next task and release the lock
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();   // execute outside the lock so other threads can grab tasks
                }
            });
        }
    }

    // Submit any callable (lambda, function, functor) as a new task
    void submit(std::function<void()> task)
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            tasks.push(std::move(task));
        }
        cv.notify_one();   // wake one idle worker
    }

    // Destructor: signal all workers to stop and wait for them to finish
    ~ThreadPool()
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();   // wake every worker so they can see stop == true
        for (auto& t : workers) t.join();
    }

private:
    std::vector<std::thread>          workers;
    std::queue<std::function<void()>> tasks;
    std::mutex                        mtx;
    std::condition_variable           cv;
    bool                              stop = false;
};

int main()
{
    // 4 threads handle all incoming transactions — no more thread-per-transaction
    ThreadPool pool(4);

    for (int i = 1; i <= 10; ++i)
    {
        pool.submit([i]()
        {
            std::cout << "Processing transaction " << i
                      << " on thread " << std::this_thread::get_id() << "\n";
        });
    }

    // pool destructor is called here — waits for all 10 tasks to complete
    return 0;
}
```

**Why use a thread pool over raw threads?**

| Raw threads                               | Thread pool                              |
| ----------------------------------------- | ---------------------------------------- |
| One thread per task                       | Fixed number of threads, unlimited tasks |
| High creation overhead for short tasks    | Creation cost paid once at startup       |
| Unbounded — 10,000 tasks = 10,000 threads | Bounded — 10,000 tasks on N threads      |

📖 Reference: [C++ — std::function](https://en.cppreference.com/w/cpp/utility/functional/function)

---

## 7. `std::async`, Futures & Promises

`std::thread` gives you raw control but you have to manage results manually. The higher-level `std::async` / `std::future` / `std::promise` trio lets you launch work and retrieve its return value cleanly.

### 7.1 `std::async` and `std::future`

`std::async` launches a callable asynchronously and returns a `std::future` — a handle to a value that will be ready at some point in the future.

```cpp
#include <iostream>
#include <future>
#include <string>

// Returns a fraud score — imagine this does real ML inference
double check_fraud(const std::string& account_id, double amount)
{
    // Simulate time-consuming analysis
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return (amount > 5000.0) ? 0.95 : 0.02;   // high score = suspicious
}

int main()
{
    // std::launch::async forces immediate execution on a new thread
    // Without the policy, the runtime may defer execution (lazy evaluation)
    std::future<double> fraud_score =
        std::async(std::launch::async, check_fraud, "ACC-001", 7500.0);

    // Do other work here while check_fraud runs in the background...
    std::cout << "Validating account details...\n";

    // future::get() blocks until the result is ready, then returns it
    // Can only be called ONCE — the value is moved out of the future
    double score = fraud_score.get();

    if (score > 0.8)
        std::cout << "Transaction flagged for review (score: " << score << ")\n";
    else
        std::cout << "Transaction approved (score: " << score << ")\n";

    return 0;
}
```

**Running multiple async tasks in parallel:**

```cpp
#include <future>
#include <vector>
#include <string>

int main()
{
    std::vector<std::string> accounts = {"ACC-001", "ACC-002", "ACC-003"};

    // Launch all checks at the same time
    std::vector<std::future<double>> futures;
    for (const auto& acc : accounts)
        futures.push_back(
            std::async(std::launch::async, check_fraud, acc, 1000.0));

    // Collect results — get() blocks on each future in turn
    for (size_t i = 0; i < futures.size(); ++i)
    {
        double score = futures[i].get();
        std::cout << accounts[i] << ": fraud score = " << score << "\n";
    }

    return 0;
}
```

### 7.2 `std::promise` and `std::future`

A `std::promise` is the _write_ end of a future/promise pair. One thread sets the value via the promise; another retrieves it via the future. This is useful when the result is produced by a callback or event rather than a direct return value.

```cpp
#include <iostream>
#include <thread>
#include <future>
#include <string>

int main()
{
    // promise and future are two ends of the same channel
    std::promise<std::string> approval_promise;
    std::future<std::string>  approval_future = approval_promise.get_future();

    // Worker thread: performs the check and fulfils the promise
    std::thread worker([&approval_promise]()
    {
        // Simulate a compliance check
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        // set_value() unblocks anyone waiting on the corresponding future
        approval_promise.set_value("APPROVED");
    });

    std::cout << "Waiting for compliance check...\n";

    // Main thread blocks here until the worker calls set_value()
    std::string result = approval_future.get();
    std::cout << "Transaction status: " << result << "\n";

    worker.join();
    return 0;
}
```

**`std::async` vs `std::promise` — when to use which:**

| Scenario                                  | Use                            |
| ----------------------------------------- | ------------------------------ |
| Run a function and get its return value   | `std::async` + `std::future`   |
| Result is produced by a callback or event | `std::promise` + `std::future` |
| Fire-and-forget (no return value needed)  | `std::thread` + `detach`       |

📖 Reference: [C++ — std::future](https://en.cppreference.com/w/cpp/thread/future)

---

## 8. Memory Model & Atomics

### 8.1 The C++ memory model

Modern CPUs and compilers reorder instructions for performance. Without explicit synchronisation, one thread may observe another thread's writes in a different order than they were made. The C++ memory model defines the rules for when writes become visible across threads.

**Key rule:** any access to a variable from more than one thread — where at least one access is a write — is a **data race** and is **undefined behaviour** unless the accesses are synchronised (via mutex, atomic, or other mechanism).

### 8.2 `std::atomic`

`std::atomic<T>` wraps a type so that reads and writes to it are indivisible — no other thread can observe a half-completed operation. For simple counters and flags, this is cheaper than a mutex.

```cpp
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

// atomic<int> guarantees that += is a single indivisible operation
// No mutex needed for simple increment/decrement
std::atomic<int>    transaction_count{0};
std::atomic<double> total_deposited{0.0};   // note: floating-point atomics have limited ops

void process_deposit(double amount)
{
    // fetch_add atomically adds and returns the old value
    transaction_count.fetch_add(1);

    // operator+= is also atomic for integral types
    // For double, use a compare-exchange loop (see below)
    transaction_count++;
}

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 100; ++i)
        threads.emplace_back(process_deposit, 50.0);
    for (auto& t : threads) t.join();

    // Always exactly 100 — no race condition
    std::cout << "Transactions processed: " << transaction_count << "\n";
    return 0;
}
```

**Atomic flag — the simplest atomic:**

```cpp
#include <atomic>
#include <thread>

// atomic_flag is guaranteed lock-free on all platforms
// Used for simple on/off signals between threads
std::atomic_flag processing = ATOMIC_FLAG_INIT;

void start_processing()
{
    // test_and_set() returns true if the flag was already set
    // Use it to implement a simple spinlock or one-shot signal
    if (!processing.test_and_set())
        std::cout << "Processing started\n";
    else
        std::cout << "Already processing\n";
}
```

**When to use atomics vs mutexes:**

| Situation                                        | Use           |
| ------------------------------------------------ | ------------- |
| Single variable, simple ops (`++`, `+=`, swap)   | `std::atomic` |
| Multiple variables that must be updated together | `std::mutex`  |
| Complex logic inside the critical section        | `std::mutex`  |
| Lowest possible overhead for a counter or flag   | `std::atomic` |

📖 Reference: [C++ — std::atomic](https://en.cppreference.com/w/cpp/atomic/atomic)

---

## Exercises

Compile with threading support:

```bash
g++ --std=c++20 -pthread -o week-03-concurrency week-03-concurrency.cpp
./week-03-concurrency
```

> The `-pthread` flag links the POSIX thread library on Linux/macOS. On Windows with MSVC it is not needed.

### AI Usage Guidelines

AI tools are encouraged but use them critically:

- Refine your prompts — vague prompts yield vague responses
- Validate AI output — don't trust it blindly
- Acknowledge AI usage at the top of any AI-assisted file:

```cpp
/*
 * Brief description of what this file does
 *
 * AI Assistance: This file was developed with assistance from [AI Tool Name]
 *
 * Prompts used:
 * - "Your first prompt here"
 * - "Your second prompt here"
 *
 * Usage: Describe how you used the AI responses to help you with your work
 */
```

---

### Task 1 — Thread-Safe Bank

Build a `Bank` class that manages multiple `BankAccount` objects and supports concurrent operations.

**`BankAccount` class:**

| Member / Method          | Description                                                                |
| ------------------------ | -------------------------------------------------------------------------- |
| `id`, `owner`, `balance` | Member variables                                                           |
| `deposit(double)`        | Adds to balance; thread-safe                                               |
| `withdraw(double)`       | Subtracts from balance; returns `false` if insufficient funds; thread-safe |
| `get_balance() const`    | Returns current balance; thread-safe                                       |

**`Bank` class:**

| Method                                                  | Description                                                                                                  |
| ------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------ |
| `create_account(string owner, double initial)`          | Creates a new account and returns its ID                                                                     |
| `transfer(string from_id, string to_id, double amount)` | Atomically moves funds between accounts; returns `false` if source has insufficient funds; must not deadlock |
| `get_total_assets() const`                              | Sum of all account balances; should be consistent                                                            |
| `print_statement() const`                               | Prints all accounts and their balances                                                                       |

```cpp
Bank bank;
std::string a1 = bank.create_account("Alice", 1000.0);
std::string a2 = bank.create_account("Bob",    500.0);

// Launch 20 concurrent transfers in random directions
std::vector<std::thread> threads;
for (int i = 0; i < 10; ++i)
{
    threads.emplace_back([&]() { bank.transfer(a1, a2, 50.0); });
    threads.emplace_back([&]() { bank.transfer(a2, a1, 30.0); });
}
for (auto& t : threads) t.join();

bank.print_statement();
// Total assets must always equal 1500.00
```

> **Hint:** use `std::lock` with `std::adopt_lock` in `transfer` to acquire both account mutexes simultaneously and avoid deadlock.

---

### Task 2 — Transaction Pipeline

Build a producer-consumer pipeline that simulates incoming transactions being validated and then processed.

**Three-stage pipeline:**

```
[Generator thread] → raw_queue → [Validator thread] → valid_queue → [Processor thread]
```

| Stage     | Responsibility                                                                                                                        |
| --------- | ------------------------------------------------------------------------------------------------------------------------------------- |
| Generator | Produces 20 `Transaction` objects and pushes them onto `raw_queue`                                                                    |
| Validator | Pops from `raw_queue`; approves if `amount > 0` and `account_id` is non-empty; pushes approved ones to `valid_queue`, logs rejections |
| Processor | Pops from `valid_queue`; applies the transaction to a `BankAccount`; prints a confirmation                                            |

Use a `ThreadSafeQueue<T>` template class backed by `std::queue`, `std::mutex`, and `std::condition_variable`. Add a `close()` method that signals no more items will be pushed, allowing consumers to drain the queue and exit cleanly.

```cpp
struct Transaction { std::string account_id; std::string type; double amount; };

ThreadSafeQueue<Transaction> raw_queue;
ThreadSafeQueue<Transaction> valid_queue;
BankAccount account("ACC-001", 0.0);
```

Expected output (order may vary):

```
[Validator] Approved:  deposit    $200.00 for ACC-001
[Validator] Rejected:  deposit    $-50.00 — invalid amount
[Processor] Applied:   deposit    $200.00 — Balance: $200.00
...
```

> **Hint:** `close()` can set an `atomic<bool> done` flag. The `pop()` method should return `std::optional<T>` — returning `std::nullopt` when the queue is both closed and empty.

---

### Task 3 — Async Fraud Detection

Build a `FraudDetector` that runs multiple checks concurrently using `std::async` and combines the results.

**Required checks (each runs on its own thread):**

| Check                                | Logic                                                                  | Returns        |
| ------------------------------------ | ---------------------------------------------------------------------- | -------------- |
| `check_amount(amount)`               | Score `0.9` if amount > $10,000, else `0.1`                            | `double` score |
| `check_velocity(account_id, amount)` | Score `0.8` if this is the 3rd+ transaction in the session, else `0.1` | `double` score |
| `check_location(account_id)`         | Score `0.7` if account ends in odd digit, else `0.1`                   | `double` score |

**`FraudDetector` class:**

| Method                               | Description                                                                        |
| ------------------------------------ | ---------------------------------------------------------------------------------- |
| `FraudDetector()`                    | Constructor                                                                        |
| `analyse(Transaction) → FraudResult` | Runs all three checks concurrently; waits for all results; returns a `FraudResult` |

**`FraudResult` struct:**

```cpp
struct FraudResult {
    double      combined_score;      // weighted average of the three scores
    bool        is_flagged;          // true if combined_score > 0.6
    std::string recommendation;      // "APPROVE", "REVIEW", or "BLOCK"
    std::map<std::string, double> individual_scores;
};
```

```cpp
FraudDetector detector;

Transaction tx{"ACC-007", "withdrawal", 15000.0};
FraudResult result = detector.analyse(tx);

std::cout << "Score: "          << result.combined_score   << "\n";
std::cout << "Flagged: "        << result.is_flagged        << "\n";
std::cout << "Recommendation: " << result.recommendation    << "\n";
```

> **Hint:** launch all three checks with `std::async(std::launch::async, ...)` before calling `.get()` on any of them — this ensures they run in parallel rather than sequentially.
