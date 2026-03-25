# Week 04 - SQLite and Databases

## Navigation

|            | Link                                                                                                            |
| ---------- | --------------------------------------------------------------------------------------------------------------- |
| ← Previous | [Week 03 - Processes, Threads and Concurrency](./lecture-notes/games-dev-pathway/week-03-concurrency/README.md) |

---

## 1. Relational Databases and SQLite

A **relational database** organises data into tables of rows and columns. Relationships between tables are expressed via keys. SQL (Structured Query Language) is the standard language for querying and manipulating that data.

**SQLite** is a serverless, file-based relational database engine. Unlike PostgreSQL or MySQL, it runs entirely within your application process - there is no separate server to start or connect to. The entire database is a single `.db` file on disk.

| Feature          | SQLite                                   | PostgreSQL / MySQL                         |
| ---------------- | ---------------------------------------- | ------------------------------------------ |
| **Architecture** | Embedded - runs inside your process      | Client/server - separate daemon required   |
| **Setup**        | Zero configuration - open a file and go  | Requires installation, users, permissions  |
| **Concurrency**  | Limited - one writer at a time           | Full concurrent reads and writes           |
| **Data storage** | Single `.db` file                        | Managed by the server                      |
| **Best for**     | Local apps, prototypes, embedded systems | Multi-user web apps, high write throughput |
| **C++ library**  | `sqlite3.h` (single-header, no deps)     | `libpq`, `mysqlclient`, etc.               |

**Rule of thumb:** use SQLite when your application owns its data and concurrency demands are moderate (e.g. a game save system, a desktop app, a test harness). Use a client/server database when multiple machines or processes need to write simultaneously.

📖 Reference: [SQLite Documentation](https://www.sqlite.org/docs.html)

---

## 2. Core SQL - DDL and DML

SQL statements fall into two broad categories:

| Category | Full Name                  | Purpose                      | Key statements                         |
| -------- | -------------------------- | ---------------------------- | -------------------------------------- |
| **DDL**  | Data Definition Language   | Define and modify the schema | `CREATE`, `ALTER`, `DROP`              |
| **DML**  | Data Manipulation Language | Read and write rows          | `SELECT`, `INSERT`, `UPDATE`, `DELETE` |

### 2.1 Creating tables

```sql
-- DDL: define the schema
CREATE TABLE IF NOT EXISTS accounts (
    id        INTEGER PRIMARY KEY AUTOINCREMENT,  -- SQLite generates this value automatically
    owner     TEXT    NOT NULL,
    balance   REAL    NOT NULL DEFAULT 0.0,
    created_at TEXT   NOT NULL DEFAULT (datetime('now'))
);

CREATE TABLE IF NOT EXISTS transactions (
    id         INTEGER PRIMARY KEY AUTOINCREMENT,
    account_id INTEGER NOT NULL REFERENCES accounts(id),  -- foreign key
    type       TEXT    NOT NULL CHECK (type IN ('deposit', 'withdrawal', 'transfer')),
    amount     REAL    NOT NULL CHECK (amount > 0),
    timestamp  TEXT    NOT NULL DEFAULT (datetime('now'))
);
```

**SQLite data types:**

| Type      | Description                | Example values         |
| --------- | -------------------------- | ---------------------- |
| `INTEGER` | Signed integer, 1–8 bytes  | `42`, `-7`, `0`        |
| `REAL`    | 64-bit IEEE floating-point | `3.14`, `1000.0`       |
| `TEXT`    | UTF-8/UTF-16 string        | `'Alice'`, `'deposit'` |
| `BLOB`    | Raw binary data            | Image bytes, checksums |
| `NULL`    | Missing/unknown value      | `NULL`                 |

> SQLite uses **dynamic typing** - the declared type is a hint, not a strict constraint. A column declared `TEXT` can store an integer. This is unusual; most databases enforce types strictly.

### 2.2 Inserting, updating, and deleting rows

```sql
-- DML: write data
INSERT INTO accounts (owner, balance) VALUES ('Alice', 1000.0);
INSERT INTO accounts (owner, balance) VALUES ('Bob', 500.0);

-- Update a specific row - always use WHERE or you update every row
UPDATE accounts SET balance = balance - 200.0 WHERE id = 1;

-- Delete rows matching a condition
DELETE FROM transactions WHERE amount < 0;
```

### 2.3 Querying data

```sql
-- Basic SELECT
SELECT id, owner, balance FROM accounts;

-- Filter with WHERE
SELECT * FROM accounts WHERE balance > 500.0;

-- Sort and limit
SELECT * FROM transactions ORDER BY timestamp DESC LIMIT 10;

-- Aggregate functions
SELECT COUNT(*) AS total_transactions, SUM(amount) AS total_deposited
FROM transactions
WHERE type = 'deposit';

-- JOIN: combine rows from two tables
SELECT a.owner, t.type, t.amount, t.timestamp
FROM transactions t
JOIN accounts a ON t.account_id = a.id
WHERE a.owner = 'Alice'
ORDER BY t.timestamp DESC;
```

📖 Reference: [SQLite SQL Syntax](https://www.sqlite.org/lang.html)

---

## 3. Using SQLite from C++

The SQLite C API is low-level but straightforward. Every operation follows the same pattern: open a database, prepare a statement, bind parameters, step through results, finalise.

### 3.1 Opening and closing a database

```cpp
#include <sqlite3.h>
#include <iostream>
#include <stdexcept>

int main()
{
    sqlite3* db = nullptr;

    // sqlite3_open returns SQLITE_OK (0) on success
    // Creates the file if it does not exist
    int rc = sqlite3_open("bank.db", &db);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return 1;
    }

    std::cout << "Database opened successfully.\n";

    // Always close - flushes writes and releases the file lock
    sqlite3_close(db);
    return 0;
}
```

### 3.2 Executing DDL with `sqlite3_exec`

`sqlite3_exec` is a convenience wrapper for statements that do not return rows (DDL, `INSERT`, `UPDATE`, `DELETE`).

```cpp
#include <sqlite3.h>
#include <iostream>

void check(int rc, sqlite3* db, const char* context)
{
    if (rc != SQLITE_OK)
        throw std::runtime_error(std::string(context) + ": " + sqlite3_errmsg(db));
}

int main()
{
    sqlite3* db = nullptr;
    check(sqlite3_open("bank.db", &db), db, "open");

    const char* schema = R"(
        CREATE TABLE IF NOT EXISTS accounts (
            id      INTEGER PRIMARY KEY AUTOINCREMENT,
            owner   TEXT    NOT NULL,
            balance REAL    NOT NULL DEFAULT 0.0
        );
        CREATE TABLE IF NOT EXISTS transactions (
            id         INTEGER PRIMARY KEY AUTOINCREMENT,
            account_id INTEGER NOT NULL REFERENCES accounts(id),
            type       TEXT    NOT NULL,
            amount     REAL    NOT NULL
        );
    )";

    // Third argument: optional row callback (NULL for DDL)
    // Fourth argument: callback user data
    // Fifth argument: receives error message string
    char* err_msg = nullptr;
    rc = sqlite3_exec(db, schema, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Schema error: " << err_msg << "\n";
        sqlite3_free(err_msg);   // must free the error string
    }

    sqlite3_close(db);
    return 0;
}
```

### 3.3 Prepared statements and parameter binding

Never build SQL strings by concatenating user input - this causes **SQL injection**. Use prepared statements instead: the SQL is compiled once, then executed many times with different parameters safely bound.

```cpp
#include <sqlite3.h>
#include <string>
#include <iostream>

// Insert an account and return the auto-generated ID
int64_t create_account(sqlite3* db, const std::string& owner, double balance)
{
    // ? is a positional parameter placeholder
    const char* sql = "INSERT INTO accounts (owner, balance) VALUES (?, ?)";

    sqlite3_stmt* stmt = nullptr;

    // sqlite3_prepare_v2 compiles the SQL into bytecode
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
        throw std::runtime_error(sqlite3_errmsg(db));

    // Bind parameters - indices are 1-based
    sqlite3_bind_text(stmt, 1, owner.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 2, balance);

    // sqlite3_step executes the statement
    // For INSERT/UPDATE/DELETE, SQLITE_DONE means success
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    int64_t new_id = sqlite3_last_insert_rowid(db);

    // Always finalise - releases the compiled statement
    sqlite3_finalize(stmt);
    return new_id;
}
```

**Bind functions for common types:**

| Function                                              | C++ type                      |
| ----------------------------------------------------- | ----------------------------- |
| `sqlite3_bind_int(stmt, i, v)`                        | `int`                         |
| `sqlite3_bind_int64(stmt, i, v)`                      | `int64_t`                     |
| `sqlite3_bind_double(stmt, i, v)`                     | `double`                      |
| `sqlite3_bind_text(stmt, i, v, -1, SQLITE_TRANSIENT)` | `const char*` / `std::string` |
| `sqlite3_bind_null(stmt, i)`                          | NULL value                    |

### 3.4 Reading rows with `sqlite3_step`

```cpp
#include <sqlite3.h>
#include <iostream>

void print_accounts(sqlite3* db)
{
    const char* sql = "SELECT id, owner, balance FROM accounts ORDER BY id";
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    // sqlite3_step returns SQLITE_ROW while rows remain, then SQLITE_DONE
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        // Column indices are 0-based (opposite of bind which is 1-based)
        int64_t     id      = sqlite3_column_int64(stmt, 0);
        const char* owner   = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double      balance = sqlite3_column_double(stmt, 2);

        std::cout << "[" << id << "] " << owner
                  << "  $" << balance << "\n";
    }

    sqlite3_finalize(stmt);
}
```

📖 Reference: [SQLite C API](https://www.sqlite.org/capi3ref.html)

---

## 4. Transactions

A **database transaction** groups multiple SQL statements into a single all-or-nothing unit. Either every statement succeeds and the changes are committed, or the entire group is rolled back and the database is left unchanged.

Transactions are defined by four properties - **ACID**:

| Property        | Meaning                                                                             |
| --------------- | ----------------------------------------------------------------------------------- |
| **Atomicity**   | All statements in the transaction succeed or none do                                |
| **Consistency** | The database moves from one valid state to another - constraints are never violated |
| **Isolation**   | Concurrent transactions do not see each other's uncommitted changes                 |
| **Durability**  | Once committed, changes survive a crash or power loss                               |

### 4.1 Why transactions matter - a bank transfer

```sql
-- WITHOUT a transaction: if the program crashes here, Alice loses $200 but Bob gains nothing
UPDATE accounts SET balance = balance - 200.0 WHERE id = 1;
-- ← crash here leaves the database in an inconsistent state
UPDATE accounts SET balance = balance + 200.0 WHERE id = 2;

-- WITH a transaction: both updates happen or neither does
BEGIN;
    UPDATE accounts SET balance = balance - 200.0 WHERE id = 1;
    UPDATE accounts SET balance = balance + 200.0 WHERE id = 2;
COMMIT;
```

### 4.2 Transactions in C++

```cpp
#include <sqlite3.h>
#include <stdexcept>
#include <iostream>

bool transfer(sqlite3* db, int64_t from_id, int64_t to_id, double amount)
{
    sqlite3_exec(db, "BEGIN", nullptr, nullptr, nullptr);

    // Check source has sufficient funds
    const char* check_sql = "SELECT balance FROM accounts WHERE id = ?";
    sqlite3_stmt* stmt = nullptr;
    sqlite3_prepare_v2(db, check_sql, -1, &stmt, nullptr);
    sqlite3_bind_int64(stmt, 1, from_id);

    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        sqlite3_exec(db, "ROLLBACK", nullptr, nullptr, nullptr);
        return false;
    }

    double current_balance = sqlite3_column_double(stmt, 0);
    sqlite3_finalize(stmt);

    if (current_balance < amount)
    {
        std::cout << "Insufficient funds\n";
        sqlite3_exec(db, "ROLLBACK", nullptr, nullptr, nullptr);
        return false;
    }

    // Debit source
    const char* debit_sql = "UPDATE accounts SET balance = balance - ? WHERE id = ?";
    sqlite3_prepare_v2(db, debit_sql, -1, &stmt, nullptr);
    sqlite3_bind_double(stmt, 1, amount);
    sqlite3_bind_int64(stmt, 2, from_id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Credit destination
    const char* credit_sql = "UPDATE accounts SET balance = balance + ? WHERE id = ?";
    sqlite3_prepare_v2(db, credit_sql, -1, &stmt, nullptr);
    sqlite3_bind_double(stmt, 1, amount);
    sqlite3_bind_int64(stmt, 2, to_id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr);
    return true;
}
```

> **Without `BEGIN` / `COMMIT`**, SQLite wraps every statement in its own implicit transaction - each statement is committed immediately. This is slow for bulk inserts (each write flushes to disk) and unsafe for multi-step operations. Always use explicit transactions for related statements.

📖 Reference: [SQLite Transactions](https://www.sqlite.org/lang_transaction.html)

---

## 5. Indexes and Query Performance

An **index** is a separate data structure (usually a B-tree) that SQLite maintains alongside a table. It allows rows to be located without scanning every row in the table - equivalent to a book's index rather than reading every page.

```sql
-- Without an index: SQLite reads every row to find matches (full table scan)
SELECT * FROM transactions WHERE account_id = 42;

-- Create an index on the column you query or JOIN on most often
CREATE INDEX IF NOT EXISTS idx_transactions_account_id
    ON transactions (account_id);

-- Now the same query uses the index - much faster for large tables
SELECT * FROM transactions WHERE account_id = 42;

-- Composite index: useful when you filter on two columns together
CREATE INDEX IF NOT EXISTS idx_transactions_account_type
    ON transactions (account_id, type);
```

**When to add an index:**

| Situation                                           | Add index?                                  |
| --------------------------------------------------- | ------------------------------------------- |
| Column used in `WHERE`, `JOIN`, `ORDER BY`          | ✓ Yes                                       |
| Primary key column                                  | ✓ Automatic - SQLite creates one implicitly |
| Column with very few distinct values (e.g. boolean) | ✗ Rarely helpful                            |
| Table with fewer than ~1,000 rows                   | ✗ Full scan is fast enough                  |
| Column written to very frequently                   | ✗ Indexes slow down writes                  |

### Explaining a query plan

```sql
-- EXPLAIN QUERY PLAN shows whether SQLite uses a scan or an index
EXPLAIN QUERY PLAN
SELECT * FROM transactions WHERE account_id = 42;

-- Output without index: SCAN TABLE transactions
-- Output with index:    SEARCH TABLE transactions USING INDEX idx_...
```

📖 Reference: [SQLite Query Planner](https://www.sqlite.org/queryplanner.html)

---

## 6. RAII Wrapper for SQLite

Working with raw SQLite handles is verbose and error-prone - it is easy to forget `sqlite3_finalize` and leak memory. A thin RAII wrapper fixes this.

```cpp
#include <sqlite3.h>
#include <string>
#include <stdexcept>
#include <functional>

// Wraps sqlite3* - closes automatically when it goes out of scope
class Database
{
public:
    explicit Database(const std::string& path)
    {
        if (sqlite3_open(path.c_str(), &db) != SQLITE_OK)
        {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Cannot open database: " + err);
        }
        // Enable foreign key enforcement - OFF by default in SQLite
        exec("PRAGMA foreign_keys = ON");
    }

    ~Database() { if (db) sqlite3_close(db); }

    // Non-copyable - only one owner of the handle
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    void exec(const std::string& sql)
    {
        char* err = nullptr;
        if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err) != SQLITE_OK)
        {
            std::string msg = err;
            sqlite3_free(err);
            throw std::runtime_error("SQL error: " + msg);
        }
    }

    sqlite3* handle() { return db; }

private:
    sqlite3* db = nullptr;
};

// Wraps sqlite3_stmt* - finalises automatically when it goes out of scope
class Statement
{
public:
    Statement(Database& db, const std::string& sql)
    {
        if (sqlite3_prepare_v2(db.handle(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
            throw std::runtime_error("Prepare failed: " + std::string(sqlite3_errmsg(db.handle())));
    }

    ~Statement() { if (stmt) sqlite3_finalize(stmt); }

    // Non-copyable
    Statement(const Statement&) = delete;
    Statement& operator=(const Statement&) = delete;

    void bind(int i, int64_t v)          { sqlite3_bind_int64(stmt, i, v); }
    void bind(int i, double v)           { sqlite3_bind_double(stmt, i, v); }
    void bind(int i, const std::string& v)
    {
        sqlite3_bind_text(stmt, i, v.c_str(), -1, SQLITE_TRANSIENT);
    }

    // Returns true while rows remain
    bool step() { return sqlite3_step(stmt) == SQLITE_ROW; }

    int64_t     col_int   (int i) { return sqlite3_column_int64(stmt, i); }
    double      col_double(int i) { return sqlite3_column_double(stmt, i); }
    std::string col_text  (int i)
    {
        return reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
    }

private:
    sqlite3_stmt* stmt = nullptr;
};

// Usage
int main()
{
    Database db("bank.db");

    db.exec(R"(
        CREATE TABLE IF NOT EXISTS accounts (
            id      INTEGER PRIMARY KEY AUTOINCREMENT,
            owner   TEXT    NOT NULL,
            balance REAL    NOT NULL DEFAULT 0.0
        )
    )");

    {
        Statement insert(db, "INSERT INTO accounts (owner, balance) VALUES (?, ?)");
        insert.bind(1, std::string("Alice"));
        insert.bind(2, 1000.0);
        insert.step();
    }   // stmt finalised here

    {
        Statement select(db, "SELECT id, owner, balance FROM accounts");
        while (select.step())
        {
            std::cout << select.col_int(0) << "  "
                      << select.col_text(1) << "  $"
                      << select.col_double(2) << "\n";
        }
    }   // stmt finalised here

    return 0;   // db closed here
}
```

---

## 7. Common Pitfalls

### 7.1 SQL injection

Never concatenate user input into a SQL string. Prepared statement placeholders (`?`) prevent injection entirely.

```cpp
// DANGER - a malicious owner value can drop your entire database
std::string owner = "Alice'; DROP TABLE accounts; --";
std::string sql = "INSERT INTO accounts (owner) VALUES ('" + owner + "')";
sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);  // BAD

// SAFE - the ? placeholder is never interpreted as SQL
Statement stmt(db, "INSERT INTO accounts (owner) VALUES (?)");
stmt.bind(1, owner);   // inserted as literal text, not SQL
stmt.step();
```

### 7.2 Forgetting to finalise statements

An unfinalised `sqlite3_stmt*` holds a read lock on the database. On SQLite this can block writes and cause `SQLITE_BUSY` errors. The RAII `Statement` class above handles this automatically.

### 7.3 Ignoring return codes

Every SQLite C API call returns an integer status code. Ignoring them hides bugs.

```cpp
// BAD - silently ignores errors
sqlite3_step(stmt);

// GOOD - check the result
int rc = sqlite3_step(stmt);
if (rc != SQLITE_ROW && rc != SQLITE_DONE)
    throw std::runtime_error(sqlite3_errmsg(db));
```

### 7.4 Missing `PRAGMA foreign_keys = ON`

SQLite does **not** enforce foreign key constraints by default for backwards compatibility. Enable them at the start of every connection.

```cpp
db.exec("PRAGMA foreign_keys = ON");
```

---

## Exercises

Compile with the SQLite library:

```bash
g++ --std=c++20 -o week-04-sqlite week-04-sqlite.cpp -lsqlite3
./week-04-sqlite
```

> On Windows with MSVC, link against `sqlite3.lib`. Alternatively, drop the single-file `sqlite3.c` and `sqlite3.h` from the SQLite website into your project and compile them directly.

### AI Usage Guidelines

AI tools are encouraged but use them critically:

- Refine your prompts - vague prompts yield vague responses
- Validate AI output - don't trust it blindly
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

### Task 1 - Account Database

Build a `BankDatabase` class that wraps SQLite and manages accounts and transactions persistently.

**Schema:**

```sql
accounts     (id, owner, balance, created_at)
transactions (id, account_id, type, amount, timestamp)
```

**`BankDatabase` class:**

| Method                                                     | Description                                                                              |
| ---------------------------------------------------------- | ---------------------------------------------------------------------------------------- |
| `BankDatabase(string path)`                                | Opens (or creates) the database, creates the schema if needed, enables foreign keys      |
| `create_account(string owner, double initial) → int64_t`   | Inserts an account and returns its generated ID                                          |
| `deposit(int64_t account_id, double amount) → bool`        | Adds funds and records a transaction; returns `false` if account does not exist          |
| `withdraw(int64_t account_id, double amount) → bool`       | Deducts funds in a transaction; returns `false` if insufficient funds or missing account |
| `transfer(int64_t from, int64_t to, double amount) → bool` | Atomically moves funds between accounts using a single SQL transaction                   |
| `get_balance(int64_t account_id) → double`                 | Returns current balance                                                                  |
| `print_statement(int64_t account_id)`                      | Prints all transactions for that account in chronological order                          |

```cpp
BankDatabase db("bank.db");

int64_t alice = db.create_account("Alice", 1000.0);
int64_t bob   = db.create_account("Bob",   500.0);

db.deposit(alice, 200.0);
db.transfer(alice, bob, 300.0);
db.withdraw(bob, 100.0);

db.print_statement(alice);
db.print_statement(bob);
// Balances must be consistent across runs - data is persisted in bank.db
```

> **Hint:** wrap `deposit`, `withdraw`, and `transfer` in `BEGIN` / `COMMIT` blocks. Use `ROLLBACK` in the error path to leave the database unchanged.

---

### Task 2 - Query and Report

Extend `BankDatabase` with reporting methods that aggregate data using SQL.

**Required methods:**

| Method                                      | SQL concept                  | Expected output                                  |
| ------------------------------------------- | ---------------------------- | ------------------------------------------------ |
| `total_assets() → double`                   | `SUM` aggregate              | Sum of all account balances                      |
| `richest_accounts(int n)`                   | `ORDER BY ... DESC LIMIT n`  | Top n accounts by balance, printed to stdout     |
| `transaction_summary(int64_t account_id)`   | `GROUP BY` + `SUM` + `COUNT` | Deposits made, withdrawals made, net change      |
| `suspicious_transactions(double threshold)` | `WHERE amount > ?` + `JOIN`  | Transactions above the threshold with owner name |

```cpp
db.total_assets();                  // e.g. 1500.00
db.richest_accounts(3);
db.transaction_summary(alice_id);
db.suspicious_transactions(500.0);
```

Expected output for `transaction_summary`:

```
Account: Alice (id=1)
Deposits: 3 total $700.00
Withdrawals: 1 total $300.00
Net change: +$400.00
```

> **Hint:** use `GROUP BY type` to separate deposits from withdrawals in a single query, then pivot the results in C++.
