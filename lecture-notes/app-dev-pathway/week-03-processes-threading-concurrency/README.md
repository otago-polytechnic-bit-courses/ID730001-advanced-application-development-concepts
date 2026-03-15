# Week 03 - Processes, Threads and Concurrency

## Navigation

|            | Link                                                                                           |
| ---------- | ---------------------------------------------------------------------------------------------- |
| ← Previous | [Week 02 - Design Patterns](./lecture-notes/app-dev-pathway/week-02-design-patterns/README.md) |
| → Next     | [Week 04 - Networking](./lecture-notes/app-dev-pathway/week-04-networking/README.md)           |

---

## 1. Processes vs Threads

Before writing concurrent code, it helps to understand the two fundamental units of execution the operating system provides.

|                     | Process                                                         | Thread                                                              |
| ------------------- | --------------------------------------------------------------- | ------------------------------------------------------------------- |
| **Definition**      | An independent program in execution, with its own memory space  | A unit of execution _within_ a process; shares the process's memory |
| **Memory**          | Isolated - processes cannot read each other's memory by default | Shared - all threads in a process see the same heap and globals     |
| **Creation cost**   | High - the OS must allocate a new address space                 | Low - just a new stack and register set within the existing process |
| **Communication**   | `multiprocessing.Queue`, `Pipe`, shared memory                  | Direct - via shared variables (but requires synchronisation)        |
| **Crash isolation** | A crash in one process does not affect others                   | A crash in one thread can bring down the entire process             |
| **Python API**      | `multiprocessing.Process`                                       | `threading.Thread`                                                  |

**The Python GIL:** Python's Global Interpreter Lock (GIL) means only one thread executes Python bytecode at a time. This limits CPU-bound parallelism with threads. For CPU-bound work, use `multiprocessing` or `concurrent.futures.ProcessPoolExecutor`. For I/O-bound work (network, disk), threads are still effective because the GIL is released during I/O.

| Workload type                           | Best tool                |
| --------------------------------------- | ------------------------ |
| I/O-bound (network, disk, database)     | `threading` or `asyncio` |
| CPU-bound (computation, data crunching) | `multiprocessing`        |

**Rule of thumb:** use multiple processes when isolation matters or work is CPU-bound; use multiple threads when you need low-overhead concurrency for I/O-bound work within a single program (e.g. handling many bank transactions simultaneously).

---

## 2. `threading.Thread`

`threading.Thread` launches a function on a new OS thread. The thread runs concurrently with the caller - both execute at the same time.

```python
import threading

# A plain function - any callable can be passed to Thread
def process_deposit(account: str, amount: float) -> None:
    print(f"Depositing ${amount} into account {account}")

# target= is the callable; args= is the tuple of arguments passed to it
t = threading.Thread(target=process_deposit, args=("ACC-001", 500.0))

# start() launches the thread - it begins running immediately
t.start()

# join() blocks the calling thread until t finishes
# You should always join() threads you start, unless you explicitly detach them
t.join()

print("Deposit complete.")
```

**Launching multiple threads:**

```python
import threading
from typing import NamedTuple

def process_transaction(thread_id: int, tx_type: str, amount: float) -> None:
    print(f"[Thread {thread_id}] {tx_type} ${amount}")

# Spawn one thread per transaction and collect them for joining
workers: list[threading.Thread] = []

workers.append(threading.Thread(target=process_transaction, args=(1, "Deposit",    200.0)))
workers.append(threading.Thread(target=process_transaction, args=(2, "Withdrawal",  50.0)))
workers.append(threading.Thread(target=process_transaction, args=(3, "Transfer",   300.0)))

# Start all threads before joining any - otherwise they run sequentially
for t in workers:
    t.start()

# Wait for every thread to finish before the program exits
for t in workers:
    t.join()

print("All transactions processed.")
```

**`join` vs `daemon` threads:**

| Approach                           | Behaviour                                                                                                             |
| ---------------------------------- | --------------------------------------------------------------------------------------------------------------------- |
| `t.join()`                         | Caller blocks until `t` finishes. Safe - you know when it's done.                                                     |
| `t.daemon = True` then `t.start()` | Thread runs independently; exits when the main program exits. Dangerous if the thread outlives objects it references. |

> Prefer `join()`. Only use daemon threads when the thread truly does not share any data with the rest of the program.

📖 Reference: [Python - threading.Thread](https://docs.python.org/3/library/threading.html#threading.Thread)

---

## 3. Locks

When multiple threads share data, they can interleave in unpredictable ways and corrupt it. A **lock** ensures only one thread accesses a critical section at a time.

### 3.1 The problem - a race condition

```python
import threading

# Shared bank balance - accessed by multiple threads simultaneously
balance = 1000.0

def deposit(amount: float) -> None:
    global balance
    # DANGER: read-modify-write is NOT atomic in Python
    # Thread A reads 1000, Thread B reads 1000, both add 100, both write 1100
    # Net result: 1100 instead of the correct 1200
    balance += amount

threads = [threading.Thread(target=deposit, args=(100.0,)) for _ in range(10)]
for t in threads: t.start()
for t in threads: t.join()

# May print anything from 1100 to 2000 - output is non-deterministic
print(f"Final balance: ${balance}")
```

### 3.2 The solution - `threading.Lock`

```python
import threading

class BankAccount:
    def __init__(self, account_id: str, initial_balance: float) -> None:
        self.account_id = account_id
        self._balance   = initial_balance
        # One lock per account - only one thread can hold it at a time
        self._lock      = threading.Lock()

    def deposit(self, amount: float) -> None:
        # The 'with' statement acquires the lock on entry and releases it on exit,
        # even if an exception is raised - equivalent to C++ lock_guard
        with self._lock:
            self._balance += amount
            print(f"[{self.account_id}] Deposited ${amount}  "
                  f"Balance: ${self._balance}")

    def withdraw(self, amount: float) -> bool:
        with self._lock:   # only one thread in here at a time
            if amount > self._balance:
                print(f"[{self.account_id}] Insufficient funds")
                return False
            self._balance -= amount
            print(f"[{self.account_id}] Withdrew ${amount}  "
                  f"Balance: ${self._balance}")
            return True

    @property
    def balance(self) -> float:
        with self._lock:   # even reads need protection
            return self._balance


account = BankAccount("ACC-001", 1000.0)

# Multiple threads depositing and withdrawing concurrently
threads: list[threading.Thread] = []
for _ in range(5):
    threads.append(threading.Thread(target=account.deposit,  args=(100.0,)))
for _ in range(3):
    threads.append(threading.Thread(target=account.withdraw, args=( 50.0,)))

for t in threads: t.start()
for t in threads: t.join()

print(f"Final balance: ${account.balance}")
```

### 3.3 `threading.RLock` - re-entrant locking

Python also provides `threading.RLock` (re-entrant lock), which allows the **same thread** to acquire the lock multiple times without deadlocking. Use it when a method that holds a lock needs to call another method that also acquires the same lock.

```python
import threading

class BankAccount:
    def __init__(self, account_id: str, balance: float) -> None:
        self.account_id = account_id
        self._balance   = balance
        # RLock: the same thread can acquire this lock multiple times
        self._lock      = threading.RLock()

    def deposit(self, amount: float) -> None:
        with self._lock:
            self._balance += amount

    def deposit_with_bonus(self, amount: float, bonus: float) -> None:
        with self._lock:
            # Calls deposit(), which also acquires _lock - safe with RLock
            # Would deadlock with a plain Lock
            self.deposit(amount)
            self.deposit(bonus)
```

|                            | `threading.Lock`  | `threading.RLock`                 |
| -------------------------- | ----------------- | --------------------------------- |
| Same thread can re-acquire | ✗ (deadlock)      | ✓                                 |
| Overhead                   | Minimal           | Slightly higher                   |
| Use when                   | No nested locking | Methods call other locked methods |

📖 Reference: [Python - threading.Lock](https://docs.python.org/3/library/threading.html#lock-objects)

---

## 4. Deadlocks and Race Conditions

### 4.1 Race conditions

A **race condition** occurs when the correctness of a program depends on the relative timing of threads. The deposit example above is a classic race condition - `balance += amount` is not atomic.

**Symptoms:** non-deterministic results, bugs that only appear under load, results that change between runs.

**Prevention:** protect every shared read _and_ write with the same lock.

### 4.2 Deadlocks

A **deadlock** occurs when two or more threads each hold a lock the other needs, so all of them wait forever.

```
Thread A holds lock1, waits for lock2
Thread B holds lock2, waits for lock1
→ Neither can proceed
```

```python
import threading

lock1 = threading.Lock()
lock2 = threading.Lock()

# DANGER: this transfer function can deadlock
def unsafe_transfer(from_account, to_account, amount):
    with from_account._lock:          # Thread A acquires ACC-001's lock
        with to_account._lock:        # Thread A waits for ACC-002's lock
            pass                      # Meanwhile Thread B holds ACC-002 and
                                      # waits for ACC-001 → deadlock
```

**Prevention - always acquire locks in a consistent order:**

```python
import threading

def safe_transfer(from_account: BankAccount,
                  to_account:   BankAccount,
                  amount:       float) -> bool:
    # Determine a consistent lock ordering using the object's id()
    # id() returns a unique integer for each object - acts like a memory address
    # Always locking lower-id first breaks circular wait
    first, second = (
        (from_account, to_account)
        if id(from_account) < id(to_account)
        else (to_account, from_account)
    )

    with first._lock:
        with second._lock:
            if from_account._balance < amount:
                return False
            from_account._balance -= amount
            to_account._balance   += amount
            return True
```

**Four conditions for deadlock (all must hold):**

| Condition        | Description                                         |
| ---------------- | --------------------------------------------------- |
| Mutual exclusion | Resources cannot be shared                          |
| Hold and wait    | Thread holds one resource while waiting for another |
| No preemption    | Resources cannot be forcibly taken away             |
| Circular wait    | Thread A waits for B, B waits for A                 |

> Break any one condition to prevent deadlock. The consistent ordering above breaks **circular wait**.

📖 Reference: [Python - threading](https://docs.python.org/3/library/threading.html)

---

## 5. Condition Variables

A **condition variable** lets a thread sleep until another thread signals that something has changed. This is the correct way to implement a waiting thread - far better than a busy loop that wastes CPU.

**Bank use case:** a fraud-checker thread waits until a transaction is queued; the transaction processor wakes it up.

```python
import threading
import queue
from dataclasses import dataclass

@dataclass
class Transaction:
    account_id: str
    type:       str    # "deposit" or "withdrawal"
    amount:     float


class TransactionQueue:
    def __init__(self) -> None:
        self._queue = queue.Queue()   # thread-safe by design - no manual locking needed

    def push(self, tx: Transaction) -> None:
        # Queue.put() is thread-safe and wakes any blocked get() calls automatically
        self._queue.put(tx)

    def pop(self) -> Transaction:
        # Queue.get() blocks if the queue is empty - equivalent to condition_variable::wait()
        return self._queue.get()

    def empty(self) -> bool:
        return self._queue.empty()


txq = TransactionQueue()

def producer() -> None:
    txq.push(Transaction("ACC-001", "deposit",    500.0))
    txq.push(Transaction("ACC-002", "withdrawal", 200.0))
    txq.push(Transaction("ACC-003", "deposit",   1000.0))

def consumer() -> None:
    for _ in range(3):
        tx = txq.pop()   # sleeps if nothing is queued yet
        print(f"Processing {tx.type} of ${tx.amount} for {tx.account_id}")

t_producer = threading.Thread(target=producer)
t_consumer = threading.Thread(target=consumer)

t_producer.start()
t_consumer.start()
t_producer.join()
t_consumer.join()
```

**Using `threading.Condition` explicitly** (mirrors C++ `std::condition_variable` more closely):

```python
import threading
from collections import deque
from typing import Optional

class ManualTransactionQueue:
    def __init__(self) -> None:
        self._queue: deque[Transaction] = deque()
        self._lock  = threading.Lock()
        # Condition wraps a lock - wait() releases the lock and sleeps atomically
        self._cv    = threading.Condition(self._lock)

    def push(self, tx: Transaction) -> None:
        with self._cv:
            self._queue.append(tx)
            self._cv.notify()    # wake one waiting consumer

    def pop(self) -> Transaction:
        with self._cv:
            # wait_for() re-checks the condition after each wakeup (handles spurious wakes)
            self._cv.wait_for(lambda: len(self._queue) > 0)
            return self._queue.popleft()
```

**`notify()` vs `notify_all()`:**

| Method            | Behaviour                                                                                 |
| ----------------- | ----------------------------------------------------------------------------------------- |
| `cv.notify()`     | Wakes exactly one waiting thread. Use when any one worker can handle the work.            |
| `cv.notify_all()` | Wakes all waiting threads. Use when all of them need to respond (e.g. a shutdown signal). |

📖 Reference: [Python - threading.Condition](https://docs.python.org/3/library/threading.html#condition-objects)

---

## 6. Thread Pools

Creating and destroying threads is expensive. A **thread pool** pre-allocates a fixed number of worker threads that pick up tasks from a shared queue. Python's `concurrent.futures.ThreadPoolExecutor` provides this out of the box.

```python
from concurrent.futures import ThreadPoolExecutor, as_completed
import threading

def process_transaction(tx_id: int, amount: float) -> str:
    # Each task runs on one of the pool's worker threads
    thread_name = threading.current_thread().name
    return f"Transaction {tx_id} (${amount}) processed on {thread_name}"

# ThreadPoolExecutor manages the worker threads automatically
# max_workers=4 means at most 4 tasks run simultaneously
with ThreadPoolExecutor(max_workers=4) as pool:
    # submit() schedules a task and returns a Future immediately
    futures = [
        pool.submit(process_transaction, i, i * 100.0)
        for i in range(1, 11)
    ]

    # as_completed() yields futures in the order they finish (not submission order)
    for future in as_completed(futures):
        print(future.result())

# The 'with' block waits for all tasks to complete before exiting
```

**Submitting tasks and collecting results in order:**

```python
from concurrent.futures import ThreadPoolExecutor

with ThreadPoolExecutor(max_workers=4) as pool:
    # map() is like the built-in map() but runs each call in the pool
    # Results are returned in submission order (blocks until each is ready)
    results = list(pool.map(
        lambda i: process_transaction(i, i * 50.0),
        range(1, 11)
    ))

for r in results:
    print(r)
```

**Building a manual thread pool** (mirrors the C++ example more closely):

```python
import threading
import queue
from typing import Callable

class ThreadPool:
    def __init__(self, num_threads: int) -> None:
        self._tasks:   queue.Queue[Callable] = queue.Queue()
        self._stop     = False
        self._workers: list[threading.Thread] = []

        # Launch all worker threads immediately
        for _ in range(num_threads):
            t = threading.Thread(target=self._worker_loop, daemon=True)
            t.start()
            self._workers.append(t)

    def _worker_loop(self) -> None:
        while True:
            # get() blocks until a task is available or a sentinel None arrives
            task = self._tasks.get()
            if task is None:
                return       # None is the shutdown signal
            task()
            self._tasks.task_done()   # signal that this task is complete

    def submit(self, task: Callable) -> None:
        self._tasks.put(task)

    def shutdown(self) -> None:
        # Send one None sentinel per worker to unblock them all
        for _ in self._workers:
            self._tasks.put(None)
        for t in self._workers:
            t.join()


pool = ThreadPool(4)

for i in range(1, 11):
    # Capture i by default argument to avoid the closure-over-loop-variable pitfall
    pool.submit(lambda i=i: print(f"Processing transaction {i} "
                                  f"on {threading.current_thread().name}"))

pool.shutdown()
```

> **Python tip:** `concurrent.futures.ThreadPoolExecutor` is preferred in real code. The manual version above is shown to mirror the C++ structure for learning purposes.

**Why use a thread pool over raw threads?**

| Raw threads                               | Thread pool                              |
| ----------------------------------------- | ---------------------------------------- |
| One thread per task                       | Fixed number of threads, unlimited tasks |
| High creation overhead for short tasks    | Creation cost paid once at startup       |
| Unbounded - 10,000 tasks = 10,000 threads | Bounded - 10,000 tasks on N threads      |

📖 Reference: [Python - concurrent.futures.ThreadPoolExecutor](https://docs.python.org/3/library/concurrent.futures.html#threadpoolexecutor)

---

## 7. `concurrent.futures`, Futures and `asyncio`

Python's `concurrent.futures` module provides `Future` objects equivalent to C++ `std::future`. For cooperative concurrency (especially I/O-bound work), Python also offers `asyncio`.

### 7.1 `ThreadPoolExecutor` and `Future`

`executor.submit()` schedules a callable and returns a `Future` - a handle to a value that will be ready at some point.

```python
from concurrent.futures import ThreadPoolExecutor
import time

def check_fraud(account_id: str, amount: float) -> float:
    """Returns a fraud score - imagine this does real ML inference."""
    time.sleep(0.1)   # simulate time-consuming analysis
    return 0.95 if amount > 5000.0 else 0.02

with ThreadPoolExecutor() as pool:
    # submit() returns immediately - check_fraud runs in the background
    fraud_future = pool.submit(check_fraud, "ACC-001", 7500.0)

    # Do other work here while check_fraud runs concurrently
    print("Validating account details...")

    # future.result() blocks until the value is ready, then returns it
    score = fraud_future.result()

if score > 0.8:
    print(f"Transaction flagged for review (score: {score})")
else:
    print(f"Transaction approved (score: {score})")
```

**Running multiple async tasks in parallel:**

```python
from concurrent.futures import ThreadPoolExecutor, as_completed

accounts = ["ACC-001", "ACC-002", "ACC-003"]

with ThreadPoolExecutor() as pool:
    # Launch all checks at the same time - dict maps future → account name
    future_to_account = {
        pool.submit(check_fraud, acc, 1000.0): acc
        for acc in accounts
    }

    # as_completed() yields each future as it finishes (not submission order)
    for future in as_completed(future_to_account):
        acc   = future_to_account[future]
        score = future.result()
        print(f"{acc}: fraud score = {score}")
```

### 7.2 Promises - `concurrent.futures.Future` set externally

Python's equivalent of `std::promise` is manually creating a `Future` and fulfilling it from another thread.

```python
from concurrent.futures import Future
import threading
import time

# Create a Future manually - this is the write end (the "promise")
approval_future: Future[str] = Future()

def worker() -> None:
    """Performs the check and fulfils the promise."""
    time.sleep(0.05)   # simulate compliance check
    # set_result() unblocks anyone waiting on result()
    approval_future.set_result("APPROVED")

t = threading.Thread(target=worker)
t.start()

print("Waiting for compliance check...")

# result() blocks here until the worker calls set_result()
result = approval_future.result()
print(f"Transaction status: {result}")

t.join()
```

### 7.3 `asyncio` - cooperative concurrency

For I/O-bound work, `asyncio` offers a lighter alternative to threads. Instead of OS threads, it uses a single-threaded **event loop** with `async`/`await` syntax.

```python
import asyncio

async def check_fraud_async(account_id: str, amount: float) -> float:
    """Async version - yields control during the sleep instead of blocking."""
    await asyncio.sleep(0.1)   # non-blocking sleep; other tasks run during this
    return 0.95 if amount > 5000.0 else 0.02

async def main() -> None:
    accounts = ["ACC-001", "ACC-002", "ACC-003"]

    # gather() runs all coroutines concurrently in the event loop
    # equivalent to launching multiple threads and joining them
    scores = await asyncio.gather(
        *[check_fraud_async(acc, 1000.0) for acc in accounts]
    )

    for acc, score in zip(accounts, scores):
        print(f"{acc}: fraud score = {score}")

asyncio.run(main())
```

**`threading` vs `asyncio` - when to use which:**

| Scenario                                            | Use                              |
| --------------------------------------------------- | -------------------------------- |
| Run a function and get its return value (I/O-bound) | `ThreadPoolExecutor` + `Future`  |
| Run a function and get its return value (CPU-bound) | `ProcessPoolExecutor` + `Future` |
| Many concurrent I/O operations (network, DB)        | `asyncio`                        |
| Result produced by a callback or event              | `Future.set_result()`            |
| Fire-and-forget (no return value needed)            | `threading.Thread(daemon=True)`  |

📖 Reference: [Python - concurrent.futures](https://docs.python.org/3/library/concurrent.futures.html)

---

## 8. Thread Safety and Atomic Operations

### 8.1 The GIL and thread safety

Python's GIL makes some operations implicitly thread-safe that are not in C++. Simple operations on built-in types (appending to a list, incrementing a small integer) are protected by the GIL at the bytecode level. However, **compound operations** like `balance += amount` are still unsafe because they compile to multiple bytecode instructions.

**Rule:** never rely on GIL protection for correctness. Always use explicit synchronisation (`Lock`, `Queue`, `atomic`) for shared mutable state.

### 8.2 `threading.Event` - simple one-shot signals

`threading.Event` is the simplest synchronisation primitive - one thread sets a flag, others wait for it. Equivalent to `std::atomic<bool>` + `std::condition_variable` used as a one-shot signal.

```python
import threading
import time

# Event starts unset (False)
processing_started = threading.Event()

def worker() -> None:
    print("Worker: starting up...")
    time.sleep(0.1)
    # set() flips the flag to True and wakes all threads blocked in wait()
    processing_started.set()
    print("Worker: processing...")

t = threading.Thread(target=worker)
t.start()

# wait() blocks until set() is called - like condition_variable::wait with a bool flag
processing_started.wait()
print("Main: worker has started, proceeding.")
t.join()
```

### 8.3 `threading.Semaphore` - limiting concurrency

A `Semaphore` allows up to N threads into a section simultaneously - useful for rate-limiting (e.g. at most 3 concurrent API calls).

```python
import threading
import time

# At most 3 threads can process transactions simultaneously
semaphore = threading.Semaphore(3)

def process_transaction(tx_id: int) -> None:
    with semaphore:   # blocks if 3 threads are already inside
        print(f"[TX {tx_id}] Processing...")
        time.sleep(0.1)
        print(f"[TX {tx_id}] Done.")

threads = [threading.Thread(target=process_transaction, args=(i,)) for i in range(10)]
for t in threads: t.start()
for t in threads: t.join()
```

**When to use which synchronisation primitive:**

| Situation                                  | Use                   |
| ------------------------------------------ | --------------------- |
| Single shared variable, protect read/write | `threading.Lock`      |
| Method calls other locked methods          | `threading.RLock`     |
| Wait for a condition to become true        | `threading.Condition` |
| One-shot signal between threads            | `threading.Event`     |
| Limit N concurrent accesses                | `threading.Semaphore` |
| Thread-safe producer/consumer queue        | `queue.Queue`         |

📖 Reference: [Python - threading synchronisation](https://docs.python.org/3/library/threading.html#semaphore-objects)

---

## Exercises

No special compile flags are needed - Python threads are available in the standard library.

```bash
python week-03-concurrency.py
```

### AI Usage Guidelines

AI tools are encouraged but use them critically:

- Refine your prompts - vague prompts yield vague responses
- Validate AI output - don't trust it blindly
- Acknowledge AI usage at the top of any AI-assisted file:

```python
"""
Brief description of what this file does.

AI Assistance: This file was developed with assistance from [AI Tool Name]

Prompts used:
- "Your first prompt here"
- "Your second prompt here"

Usage: Describe how you used the AI responses to help you with your work
"""
```

---

### Task 1 - Thread-Safe Bank

Build a `Bank` class that manages multiple `BankAccount` objects and supports concurrent operations.

**`BankAccount` class:**

| Member / Method          | Description                                                                |
| ------------------------ | -------------------------------------------------------------------------- |
| `id`, `owner`, `balance` | Member variables                                                           |
| `deposit(amount)`        | Adds to balance; thread-safe                                               |
| `withdraw(amount)`       | Subtracts from balance; returns `False` if insufficient funds; thread-safe |
| `get_balance()`          | Returns current balance; thread-safe                                       |

**`Bank` class:**

| Method                             | Description                                                                                                  |
| ---------------------------------- | ------------------------------------------------------------------------------------------------------------ |
| `create_account(owner, initial)`   | Creates a new account and returns its ID                                                                     |
| `transfer(from_id, to_id, amount)` | Atomically moves funds between accounts; returns `False` if source has insufficient funds; must not deadlock |
| `get_total_assets()`               | Sum of all account balances; should be consistent                                                            |
| `print_statement()`                | Prints all accounts and their balances                                                                       |

```python
bank = Bank()
a1 = bank.create_account("Alice", 1000.0)
a2 = bank.create_account("Bob",    500.0)

# Launch 20 concurrent transfers in random directions
threads = (
    [threading.Thread(target=bank.transfer, args=(a1, a2, 50.0)) for _ in range(10)] +
    [threading.Thread(target=bank.transfer, args=(a2, a1, 30.0)) for _ in range(10)]
)
for t in threads: t.start()
for t in threads: t.join()

bank.print_statement()
# Total assets must always equal 1500.00
```

> **Hint:** use the consistent lock-ordering strategy from section 4.2 - order locks by `id()` of each account to avoid deadlock.

---

### Task 2 - Transaction Pipeline

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

Use `queue.Queue` as your thread-safe queue. Use a **sentinel value** (`None`) to signal each stage that no more items are coming so consumers can exit cleanly.

```python
from dataclasses import dataclass
import queue

@dataclass
class Transaction:
    account_id: str
    type:       str
    amount:     float

raw_queue:   queue.Queue = queue.Queue()
valid_queue: queue.Queue = queue.Queue()
account = BankAccount("ACC-001", 0.0)
```

Expected output (order may vary):

```
[Validator] Approved:  deposit    $200.00 for ACC-001
[Validator] Rejected:  deposit    $-50.00 - invalid amount
[Processor] Applied:   deposit    $200.00 - Balance: $200.00
...
```

> **Hint:** put `None` onto the queue after the last real item. In the consumer, check `if item is None: break` to exit the loop.

---

### Task 3 - Async Fraud Detection

Build a `FraudDetector` that runs multiple checks concurrently using `ThreadPoolExecutor` and combines the results.

**Required checks (each runs on its own thread):**

| Check                                | Logic                                                                  | Returns       |
| ------------------------------------ | ---------------------------------------------------------------------- | ------------- |
| `check_amount(amount)`               | Score `0.9` if amount > $10,000, else `0.1`                            | `float` score |
| `check_velocity(account_id, amount)` | Score `0.8` if this is the 3rd+ transaction in the session, else `0.1` | `float` score |
| `check_location(account_id)`         | Score `0.7` if account ends in odd digit, else `0.1`                   | `float` score |

**`FraudDetector` class:**

| Method                               | Description                                                                        |
| ------------------------------------ | ---------------------------------------------------------------------------------- |
| `__init__()`                         | Constructor                                                                        |
| `analyse(transaction) → FraudResult` | Runs all three checks concurrently; waits for all results; returns a `FraudResult` |

**`FraudResult` dataclass:**

```python
@dataclass
class FraudResult:
    combined_score:     float              # weighted average of the three scores
    is_flagged:         bool               # True if combined_score > 0.6
    recommendation:     str               # "APPROVE", "REVIEW", or "BLOCK"
    individual_scores:  dict[str, float]
```

```python
detector = FraudDetector()
tx = Transaction("ACC-007", "withdrawal", 15000.0)
result = detector.analyse(tx)

print(f"Score: {result.combined_score}")
print(f"Flagged: {result.is_flagged}")
print(f"Recommendation: {result.recommendation}")
```

> **Hint:** submit all three checks with `executor.submit()` before calling `.result()` on any of them - this ensures they run in parallel rather than sequentially.
