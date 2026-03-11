# Week 01 — Git, Programming Paradigms & Python

## Navigation

|                  | Link                                                                                         |
| ---------------- | -------------------------------------------------------------------------------------------- |
| GitHub Classroom | [ID730001-S1-26](https://classroom.github.com/a/RgDe5bs0)                                    |
| → Next           | [Week 02 - Design Patterns](lecture-notes/app-dev-pathway/week-02-design-patterns/README.md) |

---

## 1. Git

### 1.1 Useful Git Commands

| Command                      | Description                                        |
| ---------------------------- | -------------------------------------------------- |
| `git clone <repository-url>` | Clone a repository to your local machine           |
| `git status`                 | Check the status of your local repository          |
| `git add <file>`             | Stage changes for the next commit                  |
| `git commit -m "message"`    | Commit staged changes with a descriptive message   |
| `git push`                   | Push committed changes to the remote repository    |
| `git pull`                   | Pull the latest changes from the remote repository |
| `git branch`                 | List all branches in the repository                |
| `git switch <branch>`        | Switch to a different branch                       |
| `git restore <file>`         | Discard working directory changes for a file       |
| `git checkout <branch>`      | Switch to a different branch (older command)       |
| `git fetch`                  | Fetch changes from the remote repository           |
| `git merge <branch>`         | Merge a branch into the current branch             |
| `git log`                    | View the commit history                            |

**`git switch` vs `git checkout`:** `git switch` is newer and designed specifically for branch switching. `git checkout` is older and has additional uses (e.g. restoring files). Prefer `git switch` for clarity.

📖 Reference: [GitHub Git Handbook](https://guides.github.com/introduction/git-handbook/)

---

## 2. Programming Paradigms

A **paradigm** is a fundamental style of programming that provides a way to structure and organise code.

| Paradigm            | Focus                                                      | Common Languages |
| ------------------- | ---------------------------------------------------------- | ---------------- |
| **Procedural**      | Writing procedures/routines that operate on data           | C                |
| **Object-Oriented** | Organising code around objects with properties and methods | Java, Python     |
| **Functional**      | Pure functions, avoiding mutable state                     | Haskell, Lisp    |
| **Declarative**     | Describing _what_ to accomplish rather than _how_          | SQL, HTML        |
| **Event-Driven**    | Organising code around events and handlers                 | JavaScript       |
| **Logic**           | Defining rules and facts; the program infers conclusions   | Prolog           |

---

## 3. Python

Python is a high-level, interpreted programming language known for its simplicity and readability. It is used for web development, data science, automation, AI, scientific computing, and more. Python prioritises code readability through significant indentation and a philosophy of simplicity and explicitness.

📖 Reference: [Python docs](https://docs.python.org/3/)

---

### 3.1 Python Interpreter

Python's interpreter executes code line by line. You can run code in two ways — interactively via the Python REPL, or by executing a `.py` file. We will primarily use files so we can see results in the terminal.

📖 Reference: [python.org](https://www.python.org/)

---

### 3.2 Data Types

Python has several built-in data types:

| Type       | Example                       | Notes                             |
| ---------- | ----------------------------- | --------------------------------- |
| Boolean    | `True`, `False`               |                                   |
| Integer    | `1`, `2`, `-3`                |                                   |
| Float      | `2.5`, `-3.14`                |                                   |
| String     | `"Hello"`, `"World"`          |                                   |
| None       | `None`                        |                                   |
| List       | `[1, 2, 3]`                   | Mutable, ordered                  |
| Tuple      | `(1, 2, 3)`                   | Immutable, ordered                |
| Dictionary | `{"name": "John", "age": 25}` | Mutable, key-value pairs          |
| Set        | `{1, 2, 3}`                   | Mutable, unordered, unique values |

> We will focus on Boolean, Integer, Float, String, None, List, and Dictionary for now.

📖 Reference: [Python — Built-in Types](https://docs.python.org/3/library/stdtypes.html)

---

### 3.3 Variables

A variable is a named container that stores a value.

```python
name = "John"  # String variable
age = 25       # Integer variable

print(type(name))  # <class 'str'>
print(type(age))   # <class 'int'>
```

In Python, all variables are mutable by default — their values can be reassigned. However, some data types (strings, numbers, tuples) are **immutable** — once created, their values cannot be modified in place (you can only reassign the variable).

📖 Reference: [Python — Variables](https://docs.python.org/3/tutorial/introduction.html#using-python-as-a-calculator)

---

### 3.4 Operators

| Category   | Operators                                |
| ---------- | ---------------------------------------- |
| Arithmetic | `+`, `-`, `*`, `/`, `//`, `%`, `**`      |
| Assignment | `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `**=` |
| Comparison | `==`, `!=`, `>`, `<`, `>=`, `<=`         |
| Logical    | `and`, `or`, `not`                       |
| Membership | `in`, `not in`                           |
| Identity   | `is`, `is not`                           |

📖 Reference: [Python — Operators](https://docs.python.org/3/library/operator.html)

---

### 3.5 Conditional Statements

```python
# if statement
if condition:
    pass

# if...else statement
if condition:
    pass
else:
    pass

# if...elif...else statement
if condition1:
    pass
elif condition2:
    pass
else:
    pass

# Ternary (conditional expression)
x = value_if_true if condition else value_if_false
```

📖 Reference: [Python — if Statements](https://docs.python.org/3/tutorial/controlflow.html#if-statements)

---

### 3.6 Loops

```python
# for loop with range
for i in range(10):
    pass

# for loop over an iterable
for element in iterable:
    pass

# while loop
while condition:
    pass

# List comprehension
new_list = [expression for item in iterable if condition]
```

Python also supports `break` (exit a loop early) and `continue` (skip to the next iteration).

📖 Reference: [Python — for Statements](https://docs.python.org/3/tutorial/controlflow.html#for-statements)

---

### 3.7 Functions

A function is a reusable block of code that performs a specific task.

**Regular function:**

```python
def add(num1, num2):
    return num1 + num2

print(add(1, 2))        # 3
print(type(add))        # <class 'function'>
print(type(add(1, 2)))  # <class 'int'>
```

**Lambda function (anonymous):**

```python
add = lambda num1, num2: num1 + num2
print(add(1, 2))  # 3

greet = lambda name: "Hello, " + name + "!"
print(greet("John"))  # Hello, John!
```

**Default parameters:**

```python
def greet(name="World"):
    return f"Hello, {name}!"

print(greet())        # Hello, World!
print(greet("John"))  # Hello, John!
```

📖 Reference: [Python — Defining Functions](https://docs.python.org/3/tutorial/controlflow.html#defining-functions)

---

### 3.8 F-Strings

F-strings (prefixed with `f`) embed expressions directly inside string literals using `{}`.

```python
name = "John"
age = 30

greeting = f"Hello, my name is {name} and I am {age} years old"
print(greeting)  # Hello, my name is John and I am 30 years old

# Expressions are supported too
print(f"Next year I will be {age + 1} years old")  # Next year I will be 31 years old
```

📖 Reference: [Python — Formatted String Literals](https://docs.python.org/3/tutorial/inputoutput.html#formatted-string-literals)

---

### 3.9 Classes

A class is a blueprint for creating objects, defining their properties and methods.

```python
class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def greet(self):
        return f"Hello, my name is {self.name} and I am {self.age} years old"


john = Person("John", 30)
print(john.greet())  # Hello, my name is John and I am 30 years old
```

📖 Reference: [Python — Classes](https://docs.python.org/3/tutorial/classes.html)

---

### 3.10 Lists

A list stores an ordered, mutable collection of values, each accessible by a zero-based index.

```python
numbers = [1, 2, 3, 4, 5]
fruits = ["Apple", "Banana", "Cherry"]
mixed = [1, "Hello", True, None, 3.14]  # Mixed types allowed

print(fruits[0])   # Apple
print(numbers[-1]) # 5  (negative indexing counts from the end)
```

**2D Lists:**

```python
grid = [
    [1, 2, 3],
    [4, 5, 6],
]

print(grid[0][0])  # 1
print(grid[1][2])  # 6
```

📖 Reference: [Python — Lists](https://docs.python.org/3/tutorial/introduction.html#lists)

---

### 3.11 Unpacking

Unpacking extracts values from lists or tuples into individual variables.

```python
# List unpacking
numbers = [1, 2, 3]
a, b, c = numbers
print(a, b, c)  # 1 2 3

# Dictionary — unpacking keys by default
person = {"name": "John", "age": 30}
name, age = person  # unpacks keys: "name", "age"

# Unpacking values
name, age = person.values()  # "John", 30
```

📖 Reference: [Python — Unpacking Argument Lists](https://docs.python.org/3/tutorial/controlflow.html#unpacking-argument-lists)

---

### 3.12 Unpacking Operator

The `*` operator unpacks lists; `**` unpacks dictionaries. Useful for copying, merging, and passing arguments.

```python
# Copy a list
numbers = [1, 2, 3]
copy = [*numbers]

# Merge lists
merged = [*numbers, *[4, 5, 6]]  # [1, 2, 3, 4, 5, 6]

# Copy a dictionary
person = {"name": "John", "age": 30}
copy_person = {**person}

# Merge dictionaries
details = {"is_male": True, "country": "USA"}
full = {**person, **details}  # {'name': 'John', 'age': 30, 'is_male': True, 'country': 'USA'}
```

📖 Reference: [Python — Unpacking Argument Lists](https://docs.python.org/3/tutorial/controlflow.html#unpacking-argument-lists)

---

### 3.13 `map()`

`map()` applies a function to every element in an iterable and returns a map object (convert to a list with `list()`).

```python
numbers = [1, 2, 3, 4, 5]
squared = list(map(lambda num: num * num, numbers))
print(squared)  # [1, 4, 9, 16, 25]
```

Execution model:

```
Input          Callback                      Output
1  ──────────▶ lambda num: num * num ───────▶ 1
2  ──────────▶ lambda num: num * num ───────▶ 4
3  ──────────▶ lambda num: num * num ───────▶ 9
4  ──────────▶ lambda num: num * num ───────▶ 16
5  ──────────▶ lambda num: num * num ───────▶ 25
```

📖 Reference: [Python — map()](https://docs.python.org/3/library/functions.html#map)

---

### 3.14 `filter()`

`filter()` returns only elements that satisfy a condition, as a filter object (convert with `list()`).

```python
numbers = [1, 2, 3, 4, 5]
evens = list(filter(lambda num: num % 2 == 0, numbers))
print(evens)  # [2, 4]
```

Execution model:

```
Input          Callback                           Output
1  ──────────▶ lambda num: num % 2 == 0 ─────────▶ removed
2  ──────────▶ lambda num: num % 2 == 0 ─────────▶ 2
3  ──────────▶ lambda num: num % 2 == 0 ─────────▶ removed
4  ──────────▶ lambda num: num % 2 == 0 ─────────▶ 4
5  ──────────▶ lambda num: num % 2 == 0 ─────────▶ removed
```

📖 Reference: [Python — filter()](https://docs.python.org/3/library/functions.html#filter)

---

### 3.15 `reduce()`

`reduce()` from `functools` reduces an iterable to a single value by accumulating a result across all elements.

```python
from functools import reduce

numbers = [1, 2, 3, 4, 5]

# Initial value 0 → sum = 15
total = reduce(lambda acc, num: acc + num, numbers, 0)
print(total)  # 15

# Initial value 5 → sum = 20
total = reduce(lambda acc, num: acc + num, numbers, 5)
print(total)  # 20
```

Execution model (initial value = 5):

```
Input          Callback                             Accumulator
1  ──────────▶ lambda acc, num: acc + num ─────────▶ 5 + 1  = 6
2  ──────────▶ lambda acc, num: acc + num ─────────▶ 6 + 2  = 8
3  ──────────▶ lambda acc, num: acc + num ─────────▶ 8 + 3  = 11
4  ──────────▶ lambda acc, num: acc + num ─────────▶ 11 + 4 = 15
5  ──────────▶ lambda acc, num: acc + num ─────────▶ 15 + 5 = 20
```

📖 Reference: [Python — functools.reduce()](https://docs.python.org/3/library/functools.html#functools.reduce)

---

### 3.16 Dictionaries

A dictionary stores an unordered collection of key-value pairs. Dictionaries are mutable.

```python
person = {
    "name": "John",
    "age": 25,
    "is_male": True,
}

print(person["name"])       # John
print(person.get("name"))   # John  (safer — returns None if key missing)
```

Dictionaries can hold mixed types, including lists and functions:

```python
person = {
    "name": "John",
    "favourite_fruits": ["Apple", "Banana"],
    "greet": lambda: f"Hello, {person['name']}!",
}

print(person["favourite_fruits"][0])  # Apple
print(person["greet"]())              # Hello, John!
```

Lists of dictionaries are common:

```python
people = [
    {"name": "John", "age": 25},
    {"name": "Jane", "age": 20},
]

print(people[0]["name"])  # John
print(people[1]["age"])   # 20
```

> We use dictionary literal syntax `{}` in this course rather than the `dict()` constructor.

📖 Reference: [Python — Dictionaries](https://docs.python.org/3/tutorial/datastructures.html#dictionaries)

---

## Exercises

Copy `week-01-git-programming-paradigms-python-1.py` into your `id730001-s1-26` repository and run it:

```bash
python3 week-01-git-programming-paradigms-python-1.py
```

Expected output:

```
Hello, World!
```

### AI Usage Guidelines

AI tools are encouraged but use them critically:

- Refine your prompts — vague prompts yield vague responses
- Validate AI output — don't trust it blindly
- Acknowledge AI usage at the top of any AI-assisted file:

```python
"""
Brief description of what this file does

AI Assistance: This file was developed with assistance from [AI Tool Name]

Prompts used:
- "Your first prompt here"
- "Your second prompt here"

Usage: Describe how you used the AI responses to help you with your work
"""
```

---

### Task 1 — Data Pipeline

Create a function `process_data_pipeline` that takes a list of user dictionaries and applies a series of transformations using `map`, `filter`, and `reduce`.

Each user dictionary has this structure:

```python
{
    "id": 1,
    "name": "John Doe",
    "age": 28,
    "purchases": [150, 200, 75, 300],
    "member_since": 2020,
    "status": "active"
}
```

The function should:

1. Filter out users with `status != "active"`
2. Filter out users under 25
3. Map each user to add `total_spent` (sum of all purchases)
4. Map each user to add `loyalty_years` (`2026 - member_since`)
5. Map each user to add `tier` based on `total_spent`:

| `total_spent` | Tier       |
| ------------- | ---------- |
| < 500         | `"Bronze"` |
| 500 – 999     | `"Silver"` |
| ≥ 1000        | `"Gold"`   |

6. Use `reduce` to calculate total revenue from qualifying users
7. Return a dictionary with `processed_users`, `total_revenue`, `user_count`, and `average_spending`

```python
users = [
    {"id": 1, "name": "Alice", "age": 30, "purchases": [200, 400, 150], "member_since": 2019, "status": "active"},
    {"id": 2, "name": "Bob",   "age": 22, "purchases": [100, 50],       "member_since": 2021, "status": "active"},
    {"id": 3, "name": "Charlie","age": 28, "purchases": [500, 600],      "member_since": 2020, "status": "inactive"},
    {"id": 4, "name": "Diana", "age": 35, "purchases": [300, 200, 100], "member_since": 2018, "status": "active"},
]

result = process_data_pipeline(users)
```

Expected output:

```python
{
    "processed_users": [
        {"id": 1, "name": "Alice", ..., "total_spent": 750,  "loyalty_years": 7, "tier": "Silver"},
        {"id": 4, "name": "Diana", ..., "total_spent": 600,  "loyalty_years": 8, "tier": "Silver"},
    ],
    "total_revenue": 1350,
    "user_count": 2,
    "average_spending": 675.0
}
```

> Bob is excluded (age < 25). Charlie is excluded (status = "inactive").

---

### Task 2 — Organisation Transformer

Create a function `transform_organisation` that takes a nested dictionary representing a company structure and enriches it with computed statistics.

Input structure:

```python
{
    "company": "TechCorp",
    "departments": [
        {
            "name": "Engineering",
            "budget": 500000,
            "teams": [
                {
                    "name": "Backend",
                    "employees": [
                        {"name": "Alice",   "salary": 85000, "performance": 4.5},
                        {"name": "Bob",     "salary": 90000, "performance": 4.8},
                    ]
                },
                {
                    "name": "Frontend",
                    "employees": [
                        {"name": "Charlie", "salary": 80000, "performance": 4.2},
                    ]
                }
            ]
        }
    ]
}
```

Add the following to each **team**:

| Key               | Value                                            |
| ----------------- | ------------------------------------------------ |
| `total_salary`    | Sum of all employee salaries                     |
| `avg_performance` | Average performance score (rounded to 2 dp)      |
| `top_performer`   | Employee dict with the highest performance score |

Add the following to each **department**:

| Key                | Value                                                               |
| ------------------ | ------------------------------------------------------------------- |
| `team_count`       | Number of teams                                                     |
| `employee_count`   | Total employees across all teams                                    |
| `utilisation_rate` | `total_salary_all_teams / budget` as a percentage (rounded to 2 dp) |

Add a company-level **`summary`** dictionary:

| Key                       | Value                                                  |
| ------------------------- | ------------------------------------------------------ |
| `total_departments`       | Count of departments                                   |
| `total_teams`             | Count of all teams                                     |
| `total_employees`         | Count of all employees                                 |
| `highest_paid_employee`   | Employee dict with the highest salary company-wide     |
| `departments_over_budget` | List of department names where `utilisation_rate > 80` |

> Use list comprehensions, `map`/`filter`/`reduce`, and dictionary unpacking where appropriate.

For the example above: Backend has `total_salary = 175000`, `avg_performance = 4.65`. Frontend has `total_salary = 80000`, `avg_performance = 4.2`. Engineering has `utilisation_rate = 51.0` (not over budget).

---

### Task 3 — Payment Processing System

Build a payment processing system using inheritance.

**Base class: `Payment`**

| Property / Method                           | Description                                                                         |
| ------------------------------------------- | ----------------------------------------------------------------------------------- |
| `amount`, `currency`, `timestamp`, `status` | Properties (`timestamp` set via `datetime.now()`, `status` defaults to `"pending"`) |
| `__init__(self, amount, currency="USD")`    | Constructor                                                                         |
| `process(self)`                             | Abstract — raise `NotImplementedError`                                              |
| `validate(self)`                            | Returns `True` if `amount > 0`                                                      |
| `get_fee(self)`                             | Abstract — raise `NotImplementedError`                                              |
| `get_total(self)`                           | Returns `amount + fee`                                                              |
| `__str__(self)`                             | Returns formatted payment info                                                      |

**Child classes:**

| Class                 | Extra Properties                        | Fee Formula                                           | `process()` behaviour               |
| --------------------- | --------------------------------------- | ----------------------------------------------------- | ----------------------------------- |
| `CreditCardPayment`   | `card_number` (last 4 digits as string) | `2.9% of amount + $0.30`                              | validate → set status → return bool |
| `CryptoPayment`       | `wallet_address`, `crypto_type`         | `1% of amount`, min $1.00                             | validate → set status → return bool |
| `BankTransferPayment` | `account_number`, `routing_number`      | `$5.00 flat` if amount < $1000, else `0.5% of amount` | validate → set status → return bool |

**`PaymentProcessor` class:**

| Method                                   | Description                                                                                                       |
| ---------------------------------------- | ----------------------------------------------------------------------------------------------------------------- |
| `__init__`                               | Initialises empty `transactions` list                                                                             |
| `process_payment(payment)`               | Calls `payment.process()`, appends to `transactions` regardless of outcome                                        |
| `get_transactions_by_type(payment_type)` | Returns transactions filtered by class type                                                                       |
| `get_total_processed()`                  | Sum of `amount` for all `"completed"` transactions                                                                |
| `get_total_fees_collected()`             | Sum of fees for all `"completed"` transactions                                                                    |
| `generate_report()`                      | Returns dict with `count_by_type`, `total_processed_by_type`, `average_transaction_by_type`, `total_fees_by_type` |

Example:

```python
processor = PaymentProcessor()

cc      = CreditCardPayment(100, "USD", "1234")
crypto  = CryptoPayment(500, "USD", "0xABC123", "Bitcoin")
bank    = BankTransferPayment(2000, "USD", "123456789", "987654321")

processor.process_payment(cc)
processor.process_payment(crypto)
processor.process_payment(bank)

print(cc.get_fee())     # 3.20   (100 * 0.029 + 0.30)
print(crypto.get_fee()) # 5.00   (1% of 500, above $1.00 minimum)
print(bank.get_fee())   # 10.00  (0.5% of 2000)
```

Expected report:

```python
{
    "count_by_type":              {"CreditCardPayment": 1, "CryptoPayment": 1, "BankTransferPayment": 1},
    "total_processed_by_type":    {"CreditCardPayment": 100, "CryptoPayment": 500, "BankTransferPayment": 2000},
    "average_transaction_by_type":{"CreditCardPayment": 100.0, "CryptoPayment": 500.0, "BankTransferPayment": 2000.0},
    "total_fees_by_type":         {"CreditCardPayment": 3.20, "CryptoPayment": 5.00, "BankTransferPayment": 10.00},
}
```

---

### Task 4 — Student Data Analysis

Build a data analysis system for student records using classes and functional programming.

**`Student` class:**

| Method                                                 | Description                                                                                 |
| ------------------------------------------------------ | ------------------------------------------------------------------------------------------- |
| `__init__(self, student_id, name, grades, attendance)` | Constructor                                                                                 |
| `get_gpa(self)`                                        | Calculates GPA using A=4.0, B=3.0, C=2.0, D=1.0, F=0.0; returns average across all subjects |
| `get_status(self)`                                     | Returns `"Honors"` (GPA ≥ 3.5), `"Good Standing"` (GPA ≥ 2.0), or `"Probation"`             |
| `is_at_risk(self)`                                     | Returns `True` if GPA < 2.0 or attendance < 75                                              |

**`Analyser` class:**

| Method                                  | Description                                                                                                      |
| --------------------------------------- | ---------------------------------------------------------------------------------------------------------------- |
| `__init__(self, students)`              | Accepts list of `Student` objects                                                                                |
| `get_top_students(self, n)`             | Returns top `n` students sorted by GPA descending                                                                |
| `get_subject_statistics(self, subject)` | Returns `average_gpa`, `grade_distribution`, and `passing_rate` (% who received C or better) for a given subject |
| `identify_struggling_students(self)`    | Returns students where `is_at_risk()` is `True`                                                                  |
| `calculate_correlations(self)`          | Returns `data_points` (list of `(attendance, gpa)` tuples) and an `interpretation` string                        |
| `generate_comprehensive_report(self)`   | Returns nested dict with `overall`, `status_distribution`, `subjects`, `at_risk_students`, and `recommendations` |

> Use `map`, `filter`, `reduce`, list comprehensions, and dictionary comprehensions where appropriate.

Example setup:

```python
students_data = [
    {"student_id": 1, "name": "Alice",   "grades": {"Math": "A", "Science": "B", "English": "A"}, "attendance": 95},
    {"student_id": 2, "name": "Bob",     "grades": {"Math": "C", "Science": "D", "English": "B"}, "attendance": 70},
    {"student_id": 3, "name": "Charlie", "grades": {"Math": "B", "Science": "B", "English": "B"}, "attendance": 88},
    {"student_id": 4, "name": "Diana",   "grades": {"Math": "A", "Science": "A", "English": "A"}, "attendance": 98},
    {"student_id": 5, "name": "Eve",     "grades": {"Math": "F", "Science": "D", "English": "C"}, "attendance": 65},
]

students = [Student(**data) for data in students_data]
analyser = Analyser(students)
```

Expected report output:

```python
{
    "overall": {"total_students": 5, "average_gpa": 3.13, "average_attendance": 83.2},
    "status_distribution": {"Honors": 2, "Good Standing": 2, "Probation": 1},
    "subjects": {
        "Math":    {"average_gpa": 3.0, "grade_distribution": {"A": 2, "B": 1, "C": 1, "F": 1}, "passing_rate": 80.0},
        "Science": {"average_gpa": 2.6, "grade_distribution": {"A": 1, "B": 2, "D": 2},          "passing_rate": 60.0},
        "English": {"average_gpa": 3.0, "grade_distribution": {"A": 2, "B": 2, "C": 1},          "passing_rate": 100.0},
    },
    "at_risk_students": ["Bob", "Eve"],
    "recommendations": [
        "Focus on improving attendance for at-risk students",
        "Provide additional support in Math and Science for struggling students",
        "Recognise and reward high performers to encourage continued success",
    ]
}
```

---

### Task 5 — Blackjack Game

Build a complete, playable command-line Blackjack game using OOP.

**Game rules:**

- Goal: get closer to 21 than the dealer without going over
- Face cards (J, Q, K) = 10; Aces = 11 or 1 (whichever avoids a bust); number cards = face value
- Dealer must hit on ≤ 16, stand on ≥ 17
- Players can hit or stand

**Required classes:**

| Class           | Key Properties                               | Key Methods                                                                                                                                            |
| --------------- | -------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `Card`          | `rank`, `suit`                               | `get_value()`, `__str__()`                                                                                                                             |
| `Deck`          | `cards`                                      | `shuffle()`, `deal_card()`, `cards_remaining()`, `reset()`                                                                                             |
| `Hand`          | `cards`                                      | `add_card()`, `get_value()`, `is_blackjack()`, `is_bust()`, `__str__()`                                                                                |
| `Player`        | `name`, `hand`                               | `__str__()`                                                                                                                                            |
| `Dealer`        | `hand`, `name`                               | `show_partial_hand()`, `show_full_hand()`, `should_hit()`, `__str__()`                                                                                 |
| `BlackjackGame` | `deck`, `dealer`, `players`, `current_round` | `start_round()`, `deal_initial_cards()`, `player_turn()`, `dealer_turn()`, `determine_winners()`, `display_game_state()`, `play_game()`, `game_over()` |

**`Hand.get_value()` logic:** Count each Ace as 11; if the total exceeds 21, recount each Ace as 1 until the hand is ≤ 21 or no Aces remain.

**Game flow:**

1. Display a welcome message with the player names
2. Each round: deal 2 cards to each player and the dealer (dealer's second card hidden) → check for blackjack → player turns (hit or stand) → dealer reveals and plays → determine and announce winners → ask to play again
3. End when all players choose to quit

Example session:

```
Welcome to Blackjack!
Players: Alice, Bob

----- Round 1 -----

Alice's hand: 10 of Hearts, Ace of Spades (Total: 21) - Blackjack!
Bob's hand: 7 of Diamonds, 8 of Clubs (Total: 15)
Dealer's hand: 9 of Hearts, [Hidden Card]

Bob, do you want to hit or stand? hit
Bob's hand: 7 of Diamonds, 8 of Clubs, 5 of Spades (Total: 20)
Bob, do you want to hit or stand? stand

Dealer's hand: 9 of Hearts, 6 of Diamonds (Total: 15)
Dealer hits and gets 10 of Clubs (Total: 25) - Dealer busts!

Alice wins! (Blackjack)
Bob wins!

Do you want to play another round? yes
```

To start the game:

```python
game = BlackjackGame(["Alice", "Bob"])
game.play_game()
```
