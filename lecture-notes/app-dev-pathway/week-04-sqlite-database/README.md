# Week 04 - SQLite and Databases

## Navigation

|            | Link                                                                                                            |
| ---------- | --------------------------------------------------------------------------------------------------------------- |
| ← Previous | [Week 03 - Processes, Threads and Concurrency](./lecture-notes/games-dev-pathway/week-03-concurrency/README.md) |

---

## 1. Relational Databases and SQLite

A **relational database** organises data into tables of rows and columns. Relationships between tables are expressed via keys. SQL (Structured Query Language) is the standard language for querying and manipulating that data.

**SQLite** is a serverless, file-based relational database engine. Unlike PostgreSQL or MySQL, it runs entirely within your application process - there is no separate server to start or connect to. The entire database is a single `.db` file on disk.

| Feature           | SQLite                                   | PostgreSQL / MySQL                         |
| ----------------- | ---------------------------------------- | ------------------------------------------ |
| **Architecture**  | Embedded - runs inside your process      | Client/server - separate daemon required   |
| **Setup**         | Zero configuration - open a file and go  | Requires installation, users, permissions  |
| **Concurrency**   | Limited - one writer at a time           | Full concurrent reads and writes           |
| **Data storage**  | Single `.db` file                        | Managed by the server                      |
| **Best for**      | Local apps, prototypes, embedded systems | Multi-user web apps, high write throughput |
| **Python module** | `sqlite3` (standard library, no install) | `psycopg2`, `mysql-connector-python`, etc. |

**Rule of thumb:** use SQLite when your application owns its data and concurrency demands are moderate (e.g. a game save system, a desktop app, a test harness). Use a client/server database when multiple machines or processes need to write simultaneously.

> Python ships with SQLite support built in via the `sqlite3` module - no `pip install` required.

📖 Reference: [SQLite Documentation](https://www.sqlite.org/docs.html) | [Python sqlite3 docs](https://docs.python.org/3/library/sqlite3.html)

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

> SQLite uses **dynamic typing** - the declared type is a hint, not a strict constraint. A column declared `TEXT` can store an integer. Python's `sqlite3` module maps SQL types to Python types automatically (`INTEGER` → `int`, `REAL` → `float`, `TEXT` → `str`).

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

## 3. Using SQLite from Python

Python's `sqlite3` module follows the [DB-API 2.0 specification (PEP 249)](https://peps.python.org/pep-0249/), a standard interface shared by most Python database drivers. The core objects are a **Connection** (the database) and a **Cursor** (used to execute statements and fetch results).

### 3.1 Opening and closing a database

```python
import sqlite3

# sqlite3.connect creates the file if it does not exist
# Returns a Connection object
conn = sqlite3.connect("bank.db")

print("Database opened successfully.")

# Always close - flushes writes and releases the file lock
conn.close()
```

Use a **context manager** to ensure the connection is closed even if an exception occurs:

```python
import sqlite3

with sqlite3.connect("bank.db") as conn:
    # conn is closed automatically when the block exits
    print("Database opened successfully.")
```

> `sqlite3.connect(":memory:")` creates a temporary in-memory database - useful for tests.

### 3.2 Executing DDL with `cursor.executescript`

```python
import sqlite3

SCHEMA = """
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
"""

with sqlite3.connect("bank.db") as conn:
    # executescript runs multiple semicolon-separated statements at once
    # It also issues an implicit COMMIT before running
    conn.executescript(SCHEMA)
```

For single statements, use `conn.execute(sql)` directly on the connection (a shortcut that creates a temporary cursor):

```python
conn.execute("PRAGMA foreign_keys = ON")
```

### 3.3 Prepared statements and parameter binding

Never build SQL strings by concatenating user input - this causes **SQL injection**. Use **parameter placeholders** instead: the SQL is compiled once, then executed with parameters safely bound.

Python's `sqlite3` supports two placeholder styles:

```python
import sqlite3

def create_account(conn: sqlite3.Connection, owner: str, balance: float) -> int:
    # ? is the positional placeholder (qmark style)
    sql = "INSERT INTO accounts (owner, balance) VALUES (?, ?)"

    # execute returns a Cursor; lastrowid gives the auto-generated primary key
    cursor = conn.execute(sql, (owner, balance))
    conn.commit()
    return cursor.lastrowid

with sqlite3.connect("bank.db") as conn:
    conn.execute("PRAGMA foreign_keys = ON")
    alice_id = create_account(conn, "Alice", 1000.0)
    bob_id   = create_account(conn, "Bob",   500.0)
    print(f"Created accounts: Alice={alice_id}, Bob={bob_id}")
```

**Named placeholders** (`:name` style) improve readability for many parameters:

```python
sql = "INSERT INTO accounts (owner, balance) VALUES (:owner, :balance)"
conn.execute(sql, {"owner": "Alice", "balance": 1000.0})
```

**Type mapping between Python and SQLite:**

| Python type | SQLite type |
| ----------- | ----------- |
| `None`      | `NULL`      |
| `int`       | `INTEGER`   |
| `float`     | `REAL`      |
| `str`       | `TEXT`      |
| `bytes`     | `BLOB`      |

### 3.4 Reading rows with a cursor

```python
import sqlite3

def print_accounts(conn: sqlite3.Connection) -> None:
    # conn.row_factory makes rows behave like dicts (access by column name)
    conn.row_factory = sqlite3.Row

    cursor = conn.execute("SELECT id, owner, balance FROM accounts ORDER BY id")

    # fetchall() returns all rows at once as a list
    for row in cursor.fetchall():
        print(f"[{row['id']}] {row['owner']}  ${row['balance']:.2f}")

with sqlite3.connect("bank.db") as conn:
    print_accounts(conn)
```

For large result sets, iterate the cursor directly to avoid loading everything into memory:

```python
cursor = conn.execute("SELECT * FROM transactions")
for row in cursor:          # fetches one row at a time
    process(row)
```

**Fetch methods:**

| Method           | Returns                              |
| ---------------- | ------------------------------------ |
| `fetchone()`     | Next row as a tuple, or `None`       |
| `fetchmany(n)`   | Up to `n` rows as a list of tuples   |
| `fetchall()`     | All remaining rows as a list         |
| Iterating cursor | One row at a time (memory efficient) |

📖 Reference: [Python sqlite3 module](https://docs.python.org/3/library/sqlite3.html)

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

### 4.2 Transactions in Python

Python's `sqlite3` module operates in **autocommit-off** mode by default. This means every `INSERT`, `UPDATE`, or `DELETE` is automatically wrapped in an implicit `BEGIN`, but you must call `conn.commit()` to persist changes, or `conn.rollback()` to undo them.

The cleanest approach is to use the connection as a **context manager**:

```python
import sqlite3

def transfer(conn: sqlite3.Connection, from_id: int, to_id: int, amount: float) -> bool:
    try:
        with conn:  # begins a transaction; commits on success, rolls back on exception
            # Check source has sufficient funds
            row = conn.execute(
                "SELECT balance FROM accounts WHERE id = ?", (from_id,)
            ).fetchone()

            if row is None:
                raise ValueError(f"Account {from_id} not found")

            if row[0] < amount:
                raise ValueError("Insufficient funds")

            # Debit source
            conn.execute(
                "UPDATE accounts SET balance = balance - ? WHERE id = ?",
                (amount, from_id)
            )

            # Credit destination
            conn.execute(
                "UPDATE accounts SET balance = balance + ? WHERE id = ?",
                (amount, to_id)
            )

            # Record the transfer in the transactions table
            conn.execute(
                "INSERT INTO transactions (account_id, type, amount) VALUES (?, 'transfer', ?)",
                (from_id, amount)
            )

        return True   # with block exited cleanly → committed

    except ValueError as e:
        print(f"Transfer failed: {e}")
        return False  # with block raised → rolled back automatically
```

> **`with conn:`** does **not** close the connection - it only manages the transaction boundary. Use `conn.close()` (or a separate outer `with sqlite3.connect(...) as conn:`) to close it.

### 4.3 Explicit commit and rollback

For more control, manage transactions manually:

```python
conn.execute("BEGIN")
try:
    conn.execute("UPDATE accounts SET balance = balance - ? WHERE id = ?", (200.0, 1))
    conn.execute("UPDATE accounts SET balance = balance + ? WHERE id = ?", (200.0, 2))
    conn.commit()
except Exception:
    conn.rollback()
    raise
```

> **Bulk inserts:** wrapping thousands of inserts in a single transaction is dramatically faster than the default one-commit-per-statement behaviour - SQLite only flushes to disk once per `COMMIT`.

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

### Explaining a query plan from Python

```python
cursor = conn.execute(
    "EXPLAIN QUERY PLAN SELECT * FROM transactions WHERE account_id = 42"
)
for row in cursor.fetchall():
    print(row)
# Without index: (..., 'SCAN TABLE transactions')
# With index:    (..., 'SEARCH TABLE transactions USING INDEX idx_...')
```

📖 Reference: [SQLite Query Planner](https://www.sqlite.org/queryplanner.html)

---

## 6. A Clean Database Wrapper Class

Working directly with a raw connection is fine for small scripts, but for larger projects a thin wrapper class improves organisation and enforces good habits (foreign keys always on, consistent error handling).

```python
import sqlite3
from typing import Any

class Database:
    """Thin wrapper around sqlite3.Connection."""

    SCHEMA = """
        CREATE TABLE IF NOT EXISTS accounts (
            id         INTEGER PRIMARY KEY AUTOINCREMENT,
            owner      TEXT    NOT NULL,
            balance    REAL    NOT NULL DEFAULT 0.0,
            created_at TEXT    NOT NULL DEFAULT (datetime('now'))
        );
        CREATE TABLE IF NOT EXISTS transactions (
            id         INTEGER PRIMARY KEY AUTOINCREMENT,
            account_id INTEGER NOT NULL REFERENCES accounts(id),
            type       TEXT    NOT NULL CHECK (type IN ('deposit', 'withdrawal', 'transfer')),
            amount     REAL    NOT NULL CHECK (amount > 0),
            timestamp  TEXT    NOT NULL DEFAULT (datetime('now'))
        );
    """

    def __init__(self, path: str) -> None:
        self._conn = sqlite3.connect(path)
        self._conn.row_factory = sqlite3.Row          # rows accessible by column name
        self._conn.execute("PRAGMA foreign_keys = ON") # enforce FK constraints
        self._conn.executescript(self.SCHEMA)

    def close(self) -> None:
        self._conn.close()

    # Support use as a context manager: `with Database("bank.db") as db:`
    def __enter__(self) -> "Database":
        return self

    def __exit__(self, *_: Any) -> None:
        self.close()

    def execute(self, sql: str, params: tuple = ()) -> sqlite3.Cursor:
        return self._conn.execute(sql, params)

    def commit(self) -> None:
        self._conn.commit()

    def rollback(self) -> None:
        self._conn.rollback()

    @property
    def conn(self) -> sqlite3.Connection:
        return self._conn


# Usage
if __name__ == "__main__":
    with Database("bank.db") as db:
        # Insert
        with db.conn:
            cur = db.execute(
                "INSERT INTO accounts (owner, balance) VALUES (?, ?)", ("Alice", 1000.0)
            )
            alice_id = cur.lastrowid

        # Query
        rows = db.execute("SELECT id, owner, balance FROM accounts").fetchall()
        for row in rows:
            print(f"[{row['id']}] {row['owner']}  ${row['balance']:.2f}")
```

---

## 7. Common Pitfalls

### 7.1 SQL injection

Never concatenate user input into a SQL string. Parameter placeholders (`?` or `:name`) prevent injection entirely.

```python
# DANGER - a malicious owner value can drop your entire database
owner = "Alice'; DROP TABLE accounts; --"
conn.execute(f"INSERT INTO accounts (owner) VALUES ('{owner}')")  # BAD

# SAFE - the ? placeholder is never interpreted as SQL
conn.execute("INSERT INTO accounts (owner) VALUES (?)", (owner,))  # GOOD
```

### 7.2 Forgetting `conn.commit()`

Without `commit()`, changes exist only in memory and are lost when the connection closes. Use `with conn:` to commit automatically, or call `conn.commit()` explicitly.

```python
conn.execute("INSERT INTO accounts (owner) VALUES (?)", ("Alice",))
# ← if you close here without commit(), the row is never written

conn.commit()  # persist the change
```

### 7.3 Not enabling foreign keys

SQLite does **not** enforce foreign key constraints by default. Enable them at the start of every connection.

```python
conn.execute("PRAGMA foreign_keys = ON")
```

Without this, inserting a transaction that references a non-existent account silently succeeds.

### 7.4 Passing a single value as a bare string instead of a tuple

A common mistake when using `?` placeholders with a single parameter:

```python
# WRONG - iterates over the characters of the string
conn.execute("SELECT * FROM accounts WHERE owner = ?", "Alice")

# CORRECT - always pass a tuple (note the trailing comma)
conn.execute("SELECT * FROM accounts WHERE owner = ?", ("Alice",))
```

### 7.5 Using `executescript` inside a transaction

`executescript` issues an implicit `COMMIT` before running, which can unexpectedly commit an open transaction. Use it only for schema setup, not within transaction blocks.

---

## Exercises

Run your script directly with Python - no build step required:

```bash
python week_04_sqlite.py
```

### AI Usage Guidelines

AI tools are encouraged but use them critically:

- Refine your prompts - vague prompts yield vague responses
- Validate AI output - don't trust it blindly
- Acknowledge AI usage at the top of any AI-assisted file:

```python
"""
Brief description of what this module does.

AI Assistance: This file was developed with assistance from [AI Tool Name]

Prompts used:
- "Your first prompt here"
- "Your second prompt here"

Usage: Describe how you used the AI responses to help you with your work
"""
```

---

### Task 1 - Account Database

Build a `BankDatabase` class that wraps `sqlite3` and manages accounts and transactions persistently.

**Schema:**

```sql
accounts     (id, owner, balance, created_at)
transactions (id, account_id, type, amount, timestamp)
```

**`BankDatabase` class:**

| Method                                                      | Description                                                                              |
| ----------------------------------------------------------- | ---------------------------------------------------------------------------------------- |
| `__init__(path: str)`                                       | Opens (or creates) the database, creates the schema if needed, enables foreign keys      |
| `create_account(owner: str, initial: float) -> int`         | Inserts an account and returns its generated ID                                          |
| `deposit(account_id: int, amount: float) -> bool`           | Adds funds and records a transaction; returns `False` if account does not exist          |
| `withdraw(account_id: int, amount: float) -> bool`          | Deducts funds in a transaction; returns `False` if insufficient funds or missing account |
| `transfer(from_id: int, to_id: int, amount: float) -> bool` | Atomically moves funds between accounts using a single SQL transaction                   |
| `get_balance(account_id: int) -> float`                     | Returns current balance                                                                  |
| `print_statement(account_id: int)`                          | Prints all transactions for that account in chronological order                          |

```python
db = BankDatabase("bank.db")

alice = db.create_account("Alice", 1000.0)
bob   = db.create_account("Bob",   500.0)

db.deposit(alice, 200.0)
db.transfer(alice, bob, 300.0)
db.withdraw(bob, 100.0)

db.print_statement(alice)
db.print_statement(bob)
# Balances must be consistent across runs - data is persisted in bank.db
```

> **Hint:** use `with conn:` inside `deposit`, `withdraw`, and `transfer` to manage transactions. The `with` block rolls back automatically if an exception is raised.

---

### Task 2 - Query and Report

Extend `BankDatabase` with reporting methods that aggregate data using SQL.

**Required methods:**

| Method                                      | SQL concept                  | Expected output                                  |
| ------------------------------------------- | ---------------------------- | ------------------------------------------------ |
| `total_assets() -> float`                   | `SUM` aggregate              | Sum of all account balances                      |
| `richest_accounts(n: int)`                  | `ORDER BY ... DESC LIMIT n`  | Top n accounts by balance, printed to stdout     |
| `transaction_summary(account_id: int)`      | `GROUP BY` + `SUM` + `COUNT` | Deposits made, withdrawals made, net change      |
| `suspicious_transactions(threshold: float)` | `WHERE amount > ?` + `JOIN`  | Transactions above the threshold with owner name |

```python
db.total_assets()                   # e.g. 1500.00
db.richest_accounts(3)
db.transaction_summary(alice)
db.suspicious_transactions(500.0)
```

Expected output for `transaction_summary`:

```
Account: Alice (id=1)
Deposits: 3 total $700.00
Withdrawals: 1 total $300.00
Net change: +$400.00
```

> **Hint:** use `GROUP BY type` to separate deposits from withdrawals in a single query, then pivot the results in Python using a dictionary keyed on the `type` column.
