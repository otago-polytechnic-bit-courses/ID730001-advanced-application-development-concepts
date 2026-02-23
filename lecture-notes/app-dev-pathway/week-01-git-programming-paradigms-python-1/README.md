# Week 01

---

## Important Links

| Section    | Link                                  |
| ---------- | ------------------------------------- |
| GitHub     | [GitHub Classroom - ID730001-S1-26](https://classroom.github.com/a/RgDe5bs0) |
| Next Class | [Week 02]()                           |

---

## Useful Git Commands

| Command                          | Description                                         |
| -------------------------------- | --------------------------------------------------- |
| `git clone <repository-url>`     | Clone a repository to your local machine            |
| `git status`                     | Check the status of your local repository           |
| `git add <file>`                 | Stage changes for the next commit                   |
| `git commit -m "commit message"` | Commit staged changes with a descriptive message    |
| `git push`                       | Push committed changes to the remote repository     |
| `git pull`                       | Pull the latest changes from the remote repository  |
| `git branch`                     | List all branches in the repository                 |
| `git switch <branch>`            | Switch to a different branch                        |
| `git restore <file>`             | Discard changes in the working directory for a file |
| `git checkout <branch>`          | Switch to a different branch (older command)        |
| `git fetch`                      | Fetch changes from the remote repository            |
| `git merge <branch>`             | Merge a branch into the current branch              |
| `git log`                        | View the commit history                             |

What is the difference between `git switch` and `git checkout`?

`git switch` is a newer command introduced to simplify branch switching, while `git checkout` is an older command that can also be used for switching branches but has additional functionalities like restoring files. For branch switching, it is recommended to use `git switch` for clarity.

> Resource: <https://guides.github.com/introduction/git-handbook/>

---

## Programming Paradigms

In programming, a paradigm is a fundamental style of programming that provides a way to structure and organise code. Different paradigms offer different approaches to solving problems and writing code. Some common programming paradigms include:

- Procedural Programming: Focuses on writing procedures or routines that operate on data. It is based on the concept of procedure calls and is often used in languages like C.
- Object-Oriented Programming: Organises code around objects that have properties and methods. It is based on the concepts of classes and objects and is often used in languages like Java and Python.
- Functional Programming: Emphasises the use of pure functions and avoids mutable state. It is based on the concept of mathematical functions and is often used in languages like Haskell and Lisp.
- Declarative Programming: Focuses on describing what the program should accomplish rather than how to accomplish it. It is often used in languages like SQL and HTML.
- Event-Driven Programming: Organises code around events and their handlers. It is often used in languages like JavaScript for web development.
- Logic Programming: Based on formal logic, where you define rules and facts and the program infers conclusions. It is often used in languages like Prolog.

---

## Python

Python is a high-level, interpreted programming language known for its simplicity and readability. It is a versatile language used for web development, data science, automation, artificial intelligence, scientific computing and much more. Python emphasises code readability with its use of significant indentation and follows a philosophy that prioritises simplicity and explicitness.

> Resource: <https://docs.python.org/3/>

---

### Python Interpreter

Python comes with an interpreter that allows you to execute Python code. The interpreter reads and executes Python code line by line. You can run Python code in two ways: interactive mode (Python REPL) or by executing a Python file. We will primarily use Python files to write and test our code, allowing us to see the results in the terminal.

> Resource: <https://www.python.org/>

---

### Data Types

Data types are the different values that can be stored and manipulated in a program. Python has several built-in data types:

- Boolean: `True` or `False`
- Integer: `1`, `2`, `-3`
- Float: `2.5`, `-3.14`
- String: `"Hello"`, `"World"`
- None: `None`
- List: `[1, 2, 3]`
- Tuple: `(1, 2, 3)`
- Dictionary: `{"name": "John", "age": 25}`
- Set: `{1, 2, 3}`

We will primarily focus on Boolean, Integer, Float, String, None, List and Dictionary for now.

> Resource: <https://docs.python.org/3/library/stdtypes.html>

---

### Variables

A variable is a named container that stores a value. It is like a box that holds a value and the variable's name is like a label on the box. You can use the variable's name to access its value.

```python
# A variable named "name" with value "John"
name = "John"

# A variable named "age" with the value 25
age = 25

# Get a variable's data type
print(type(name)) # <class 'str'>
print(type(age)) # <class 'int'>
```

In Python, all variables are mutable by default, meaning their values can be changed. However, some data types like strings, numbers and tuples are immutable, meaning once created, their values cannot be modified (you can only reassign the variable).

> Resource: <https://docs.python.org/3/tutorial/introduction.html#using-python-as-a-calculator>

---

### Operators

Operators are symbols that perform operations on values. There are several types of operators in Python:

- Arithmetic operators: `+`, `-`, `*`, `/`, `//`, `%`, `**`
- Assignment operators: `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `**=`
- Comparison operators: `==`, `!=`, `>`, `<`, `>=`, `<=`
- Logical operators: `and`, `or`, `not`
- Membership operators: `in`, `not in`
- Identity operators: `is`, `is not`

There are many other operators in Python, but we will only be concerned with these for now.

> Resource: <https://docs.python.org/3/library/operator.html>

---

### Conditional Statements

Conditional statements allow you to execute different blocks of code depending on whether a condition is `True` or `False`. There are several types of conditionals in Python:

- if statement
- if...else statement
- if...elif...else statement
- ternary operator (conditional expression)

```python
# if statement
if condition:
 # Code to execute if condition is True
    pass

# if...else statement
if condition:
 # Code to execute if condition is True
    pass
else:
 # Code to execute if condition is False
    pass

# if...elif...else statement
if condition1:
 # Code to execute if condition1 is True
    pass
elif condition2:
 # Code to execute if condition2 is True
    pass
else:
 # Code to execute if all conditions are False
    pass

# Ternary operator
x = value_if_true if condition else value_if_false
```

> Resource: <https://docs.python.org/3/tutorial/controlflow.html#if-statements>

---

### Loops

Loops are statements that allow you to execute a block of code repeatedly. There are several types of loops in Python:

- for loop
- while loop
- List comprehension (advanced for loop)

```python
# for loop with range
for i in range(10):
 # Code to execute repeatedly
    pass

# for loop with iterable
for element in iterable:
 # Code to execute repeatedly
    pass

# while loop
while condition:
 # Code to execute repeatedly
    pass

# List comprehension
new_list = [expression for item in iterable if condition]
```

Python also has `break` to exit a loop early and `continue` to skip to the next iteration.

> Resource: <https://docs.python.org/3/tutorial/controlflow.html#for-statements>

---

### Functions

A function is a block of code that performs a specific task. It is like a machine that takes in some input, performs some operations and returns some output. A function is a reusable piece of code you can use in your program.

```python
# A function named "add" that takes in two numbers and returns their sum
def add(num1, num2):
    return num1 + num2

print(add(1, 2)) # 3

# A function named "greet" that takes in a name and returns a greeting
def greet(name):
    return "Hello, " + name + "!"

print(greet("John")) # Hello, John!

# Get a function's data type
print(type(add)) # <class 'function'>

# Get a function's return type
print(type(add(1, 2))) # <class 'int'>
```

Python also supports lambda functions (anonymous functions) for simple operations:

```python
# A lambda function that takes in two numbers and returns their sum
add = lambda num1, num2: num1 + num2

print(add(1, 2)) # 3

# A lambda function that takes in a name and returns a greeting
greet = lambda name: "Hello, " + name + "!"

print(greet("John")) # Hello, John!
```

Functions can have default parameter values:

```python
# A function with a default parameter
def greet(name="World"):
    return f"Hello, {name}!"

print(greet()) # Hello, World!
print(greet("John")) # Hello, John!
```

> Resource: <https://docs.python.org/3/tutorial/controlflow.html#defining-functions>

---

### F-Strings (Formatted String Literals)

F-strings allow you to embed expressions inside string literals using curly braces `{}`. F-strings are prefixed with `f` or `F` and provide a concise and readable way to format strings.

```python
name = "John"
age = 30

# Using f-strings
greeting = f"Hello, my name is {name} and I am {age} years old"

print(greeting) # Hello, my name is John and I am 30 years old

# F-strings can include expressions
print(f"Next year I will be {age + 1} years old") # Next year I will be 31 years old
```

> Resource: <https://docs.python.org/3/tutorial/inputoutput.html#formatted-string-literals>

---

### Classes

A class is a blueprint for creating objects. It defines a set of properties and methods that the created objects will have. In Python, you can define a class using the `class` keyword.

```python
# Defining a class named Person
class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

 # A method to greet the person
    def greet(self):
        return f"Hello, my name is {self.name} and I am {self.age} years old"

# Creating an instance of the Person class
john = Person("John", 30)

print(john.greet()) # Hello, my name is John and I am 30 years old
```

> Resource: <https://docs.python.org/3/tutorial/classes.html>

---

### Lists

A list is a data structure that stores an ordered collection of values. It is like a box that can hold multiple values and each value is assigned an index starting from 0. You can use a value's index to access its value. Lists are mutable, meaning you can change their contents.

```python
# A list of numbers
numbers = [1, 2, 3, 4, 5]

# A list of strings
fruits = ["Apple", "Banana", "Cherry", "Durian", "Elderberry"]

# A list of Person objects
people = [
    Person("John", 30),
    Person("Jane", 25),
    Person("Jack", 35)
]

# Accessing elements
print(fruits[0]) # Apple
print(numbers[-1]) # 5 (negative indexing)
```

Here is an example of a list with values of different data types.

```python
# A list of different data types
mixed = [1, "Hello", True, None, 3.14]
```

A 2D list (nested list) is a data structure that represents a matrix or a grid-like structure with rows and columns.

```python
# A 2D list of numbers
numbers = [
    [1, 2, 3],
    [4, 5, 6]
]

# A 2D list of strings
fruits = [
    ["Apple", "Banana", "Cherry"],
    ["Durian", "Elderberry", "Fig"]
]

print(numbers[0][0]) # 1
print(fruits[1][2]) # Fig
```

Here is an example of a 2D list with lists of different lengths.

```python
# A 2D list of different lengths
mixed = [
    [1, 2, 3],
    ["Hello", "World"],
    [True, False]
]
```

> Resource: <https://docs.python.org/3/tutorial/introduction.html#lists>

---

### Unpacking

Unpacking is a convenient way to extract values from lists or tuples into distinct variables. It can make your code cleaner and more readable. Here are some examples of using unpacking.

```python
# List unpacking
numbers = [1, 2, 3]
a, b, c = numbers

print(a) # 1
print(b) # 2
print(c) # 3

# Dictionary unpacking (getting keys by default)
person = {"name": "John", "age": 30}
name, age = person # This unpacks keys

# To unpack values
name = person["name"]
age = person["age"]

# Or using dictionary methods
name, age = person.values()
```

> Resource: <https://docs.python.org/3/tutorial/controlflow.html#unpacking-argument-lists>

---

### Unpacking Operator

The unpacking operator (`*` for lists, `**` for dictionaries) allows you to expand an iterable into individual elements. It is useful for copying lists or dictionaries, merging lists or dictionaries and passing multiple arguments to functions. Here are some examples of using the unpacking operator.

```python
# Copying a list
numbers = [1, 2, 3]
copy_of_numbers = [*numbers]
print(copy_of_numbers) # [1, 2, 3]

# Merging lists
more_numbers = [4, 5, 6]
merged_numbers = [*numbers, *more_numbers]
print(merged_numbers) # [1, 2, 3, 4, 5, 6]

# Copying a dictionary
person = {"name": "John", "age": 30}
copy_of_person = {**person}
print(copy_of_person) # {'name': 'John', 'age': 30}

# Merging dictionaries
more_details = {"is_male": True, "country": "USA"}
merged_person = {**person, **more_details}
print(merged_person) # {'name': 'John', 'age': 30, 'is_male': True, 'country': 'USA'}
```

> Resource: <https://docs.python.org/3/tutorial/controlflow.html#unpacking-argument-lists>

---

### Map

Map is a built-in function that transforms an iterable by applying a function to each element and returning a map object (which can be converted to a list). Here is an example of using the `map` function.

```python
# A list of numbers
numbers = [1, 2, 3, 4, 5]

# Map
numbers_squared = list(map(lambda num: num * num, numbers))

print(numbers_squared) # [1, 4, 9, 16, 25]

# Passing a named function to map
def square(num):
    return num * num

numbers_squared = list(map(square, numbers))

print(numbers_squared) # [1, 4, 9, 16, 25]
```

Here is before and after execution model of the `map` function:

```bash
Input list         Callback                Output list

index 0: 1  ─────▶ lambda num: num * num ─────▶ index 0: 1
index 1: 2  ─────▶ lambda num: num * num ─────▶ index 1: 4
index 2: 3  ─────▶ lambda num: num * num ─────▶ index 2: 9
index 3: 4  ─────▶ lambda num: num * num ─────▶ index 3: 16
index 4: 5  ─────▶ lambda num: num * num ─────▶ index 4: 25
```

> Resource: <https://docs.python.org/3/library/functions.html#map>

---

### Filter

Filter is a built-in function that filters an iterable by removing elements not satisfying a condition and returning a filter object (which can be converted to a list). Here is an example of using the `filter` function.

```python
# A list of numbers
numbers = [1, 2, 3, 4, 5]

# Filter
even_numbers = list(filter(lambda num: num % 2 == 0, numbers))

print(even_numbers) # [2, 4]

# Passing a named function to filter
def is_even(num):
    return num % 2 == 0

even_numbers = list(filter(is_even, numbers))

print(even_numbers) # [2, 4]
```

Here is before and after execution model of the `filter` function:

```bash
Input list         Callback                     Output list

index 0: 1  ─────▶ lambda num: num % 2 == 0 ─────▶ removed
index 1: 2  ─────▶ lambda num: num % 2 == 0 ─────▶ index 0: 2
index 2: 3  ─────▶ lambda num: num % 2 == 0 ─────▶ removed
index 3: 4  ─────▶ lambda num: num % 2 == 0 ─────▶ index 1: 4
index 4: 5  ─────▶ lambda num: num % 2 == 0 ─────▶ removed
```

> Resource: <https://docs.python.org/3/library/functions.html#filter>

---

### Reduce

Reduce is a function from the `functools` module that reduces an iterable to a single value by applying a function to each element and returning a single value. Here is an example of using the `reduce` function.

```python
from functools import reduce

# A list of numbers
numbers = [1, 2, 3, 4, 5]

# Reduce with initial value of 0
total = reduce(lambda acc, num: acc + num, numbers, 0)

print(total) # 15

# Passing a named function to reduce with initial value of 5
def add(acc, num):
    return acc + num

total = reduce(add, numbers, 5)

print(total) # 20
```

Here is before and after execution model of the `reduce` function (with initial value 5):

```bash
Input list         Callback                            Accumulator value
index 0: 1  ─────▶ lambda acc, num: acc + num ─────▶ 5 + 1 = 6
index 1: 2  ─────▶ lambda acc, num: acc + num ─────▶ 6 + 2 = 8
index 2: 3  ─────▶ lambda acc, num: acc + num ─────▶ 8 + 3 = 11
index 3: 4  ─────▶ lambda acc, num: acc + num ─────▶ 11 + 4 = 15
index 4: 5  ─────▶ lambda acc, num: acc + num ─────▶ 15 + 5 = 20
```

> Resource: <https://docs.python.org/3/library/functools.html#functools.reduce>

---

### Dictionaries

A dictionary is a data structure that stores a collection of key-value pairs. It is like a box that can hold multiple key-value pairs, assigning each key a value. You can use the key of a key-value pair to access its value. Dictionaries are mutable.

```python
# A dictionary with key-value pairs
person = {
    "name": "John",
    "age": 25,
    "is_male": True
}

print(person["name"]) # John
print(person["age"]) # 25
print(person["is_male"]) # True

# Alternative access method
print(person.get("name")) # John
```

Here is another example of creating a dictionary with variables.

```python
name = "John"
age = 25
is_male = True

# Using dictionary literal
person = {
    "name": name,
    "age": age,
    "is_male": is_male
}
```

Here is another example of a dictionary with key-value pairs of different data types.

```python
# A dictionary with key-value pairs of different data types
person = {
    "name": "John",
    "age": 25,
    "is_male": True,
    "favourite_fruits": ["Apple", "Banana", "Cherry"],
    "greet": lambda: f"Hello, {person['name']}!"
}

print(person["favourite_fruits"][0]) # Apple
print(person["greet"]()) # Hello, John!
```

You can have a list of dictionaries or a dictionary with lists. Here is an example of a list of dictionaries.

```python
# A list of dictionaries
people = [
    {
        "name": "John",
        "age": 25,
        "is_male": True
    },
    {
        "name": "Jane",
        "age": 20,
        "is_male": False
    }
]

print(people[0]["name"]) # John
print(people[1]["age"]) # 20
```

There is an alternative way to create a dictionary using the `dict()` constructor.

```python
# A dictionary using the dict() constructor
person = dict()
person["name"] = "John"
person["age"] = 25
person["is_male"] = True

print(person["name"]) # John
print(person["age"]) # 25
```

In this course, we will use the dictionary literal syntax to create dictionaries.

> Resource: <https://docs.python.org/3/tutorial/datastructures.html#dictionaries>

---

## Exercises

Copy the file `week-01-git-programming-paradigms-python-1` into your id730001-s1-26 repository. Open your id730001-s1-26 repository in Visual Studio Code. Open the terminal and run the command `python week-01-git-programming-paradigms-python-1.py` to run the file. You should see the following output.

```bash
$ python3 week-01-git-programming-paradigms-python-1.py
Hello, World!
```

Learning to use AI tools is an important skill. While AI tools are powerful, you must be aware of the following:

- If you provide an AI tool with a prompt that is not refined enough, it may generate a not-so-useful response
- Do not trust the AI tool's responses blindly. You must still use your judgement and may need to do additional research to determine if the response is correct
- Acknowledge what AI tool you have used. If you use AI to help you with a file, include a docstring comment at the top of the file

Here is an example docstring comment:

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

### Task 1

Create a function called `process_data_pipeline` that takes a list of dictionaries representing user data and applies a series of transformations using map, filter and reduce. Each user dictionary has the following structure:

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

Your function should:

1. Filter out users who are inactive (status != "active")
2. Filter out users under 25 years old
3. Map each user to add a new key `total_spent` (sum of all purchases)
4. Map each user to add a new key `loyalty_years` (2026 - member_since)
5. Map each user to add a new key `tier` based on total_spent:
   - "Bronze" if total_spent < 500
   - "Silver" if 500 <= total_spent < 1000
   - "Gold" if total_spent >= 1000
6. Use reduce to calculate the total revenue from all qualifying users
7. Return a dictionary containing:
   - `processed_users`: list of processed user dictionaries
   - `total_revenue`: total revenue from reduce
   - `user_count`: number of qualifying users
   - `average_spending`: total revenue / user count

Here is an example of how to use the `process_data_pipeline` function:

```python
users = [
    {"id": 1, "name": "Alice", "age": 30, "purchases": [200, 400, 150], "member_since": 2019, "status": "active"},
    {"id": 2, "name": "Bob", "age": 22, "purchases": [100, 50], "member_since": 2021, "status": "active"},
    {"id": 3, "name": "Charlie", "age": 28, "purchases": [500, 600], "member_since": 2020, "status": "inactive"},
    {"id": 4, "name": "Diana", "age": 35, "purchases": [300, 200, 100], "member_since": 2018, "status": "active"}
]

result = process_data_pipeline(users)
print(result)

"""
Expected Output:

{
    "processed_users": [
        {"id": 1, "name": "Alice", "age": 30, "purchases": [200, 400, 150], "member_since": 2019, "status": "active", "total_spent": 750, "loyalty_years": 7, "tier": "Silver"},
        {"id": 4, "name": "Diana", "age": 35, "purchases": [300, 200, 100], "member_since": 2018, "status": "active", "total_spent": 600, "loyalty_years": 8, "tier": "Silver"}
    ],
    "total_revenue": 1350,
    "user_count": 2,
    "average_spending": 675.0
}
"""
```

Bob is excluded because he is under 25. Charlie is excluded because his status is "inactive". Alice's total_spent is 200 + 400 + 150 = 750 (Silver tier). Diana's total_spent is 300 + 200 + 100 = 600 (Silver tier). Total revenue is 750 + 600 = 1350. Average spending is 1350 / 2 = 675.0.

---

### Task 2

Create a function called `transform_organisation` that takes a complex nested dictionary representing an organisation structure and performs deep transformations. The function should:

1. Accept a dictionary with this structure:

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
                        {"name": "Alice", "salary": 85000, "performance": 4.5},
                        {"name": "Bob", "salary": 90000, "performance": 4.8}
                    ]
                },
                {
                    "name": "Frontend",
                    "employees": [
                        {"name": "Charlie", "salary": 80000, "performance": 4.2}
                    ]
                }
            ]
        }
    ]
}
```

2. Transform the structure to:
   - Add a `total_salary` key to each team (sum of all employee salaries)
   - Add an `avg_performance` key to each team (average of all performance scores, rounded to 2 decimal places)
   - Add a `top_performer` key to each team (employee with highest performance score)
   - Add a `team_count` key to each department (number of teams)
   - Add an `employee_count` key to each department (total employees across all teams)
   - Add a `utilisation_rate` key to each department (total salary across all teams / budget, expressed as a percentage rounded to 2 decimal places)
   - Add a company-level `summary` dictionary with:
     - `total_departments`: count of departments
     - `total_teams`: count of all teams across all departments
     - `total_employees`: count of all employees across the entire company
     - `highest_paid_employee`: the employee dictionary with the highest salary across the whole company
     - `departments_over_budget`: list of department names where utilisation_rate > 80

3. Use list comprehensions, map/filter/reduce and dictionary unpacking where appropriate

For the example above, the Backend team has `total_salary` = 175000 and `avg_performance` = 4.65. The Frontend team has `total_salary` = 80000 and `avg_performance` = 4.2. The Engineering department has `team_count` = 2, `employee_count` = 3 and `utilisation_rate` = 51.0. Since 51.0 is not over 80, `departments_over_budget` would be an empty list.

```python
transformed_organisation = transform_organisation({
    "company": "TechCorp",
    "departments": [
        {
            "name": "Engineering",
            "budget": 500000,
            "teams": [
                {
                    "name": "Backend",
                    "employees": [
                        {"name": "Alice", "salary": 85000, "performance": 4.5},
                        {"name": "Bob", "salary": 90000, "performance": 4.8}
                    ]
                },
                {
                    "name": "Frontend",
                    "employees": [
                        {"name": "Charlie", "salary": 80000, "performance": 4.2}
                    ]
                }
            ]
        }
    ]
})

print(transformed_organisation)

"""
Expected Output:
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
                        {"name": "Alice", "salary": 85000, "performance": 4.5},
                        {"name": "Bob", "salary": 90000, "performance": 4.8}
                    ],
                    "total_salary": 175000,
                    "avg_performance": 4.65,
                    "top_performer": {"name": "Bob", "salary": 90000, "performance": 4.8}
                },
                {
                    "name": "Frontend",
                    "employees": [
                        {"name": "Charlie", "salary": 80000, "performance": 4.2}
                    ],
                    "total_salary": 80000,
                    "avg_performance": 4.2,
                    "top_performer": {"name": "Charlie", "salary": 80000, "performance": 4.2}
                }
            ],
            "team_count": 2,
            "employee_count": 3,
            "utilisation_rate": 51.0
        }
    ],
    "summary": {
        "total_departments": 1,
        "total_teams": 2,
        "total_employees": 3,
        "highest_paid_employee": {"name": "Bob", "salary": 90000, "performance": 4.8},
        "departments_over_budget": []
    }
}
"""
```

---

### Task 3

Create a payment processing system with the following requirements:

1. Base Class: `Payment`
   - Properties: `amount`, `currency`, `timestamp` (set automatically on init using `datetime.now()`), `status` (default "pending")
   - Methods:
     - `__init__(self, amount, currency="USD")`
     - `process(self)` - abstract method (should raise NotImplementedError)
     - `validate(self)` - checks if amount > 0, returns boolean
     - `get_fee(self)` - abstract method (should raise NotImplementedError)
     - `get_total(self)` - returns amount + fee
     - `__str__(self)` - returns formatted payment info

2. Child Classes:
   - `CreditCardPayment(Payment)`:
     - Additional property: `card_number` (last 4 digits only, stored as a string)
     - Additional init parameter: `card_number`
     - Fee: 2.9% of amount + $0.30
     - `process()`: calls validate(), calculates total, sets status to "completed" and returns True; if validation fails, sets status to "failed" and returns False
   - `CryptoPayment(Payment)`:
     - Additional properties: `wallet_address`, `crypto_type`
     - Additional init parameters: `wallet_address`, `crypto_type`
     - Fee: 1% of amount, with a minimum fee of $1.00
     - `process()`: calls validate(), sets status to "completed" and returns True; if validation fails, sets status to "failed" and returns False
   - `BankTransferPayment(Payment)`:
     - Additional properties: `account_number`, `routing_number`
     - Additional init parameters: `account_number`, `routing_number`
     - Fee: flat $5.00 for amounts under $1000, otherwise 0.5% of amount
     - `process()`: calls validate(), sets status to "completed" and returns True; if validation fails, sets status to "failed" and returns False

3. `PaymentProcessor` Class:
   - `__init__(self)` - initialises an empty transactions list
   - `process_payment(self, payment)` - calls payment.process() and appends the payment to transactions regardless of outcome
   - `get_transactions_by_type(self, payment_type)` - returns a list of transactions filtered by class type (e.g., passing CreditCardPayment returns only credit card payments)
   - `get_total_processed(self)` - returns the sum of amounts for all transactions with status "completed"
   - `get_total_fees_collected(self)` - returns the sum of fees for all transactions with status "completed"
   - `generate_report(self)` - returns a dictionary with:
     - `count_by_type`: dictionary of payment type name to count of transactions
     - `total_processed_by_type`: dictionary of payment type name to total amount processed (completed only)
     - `average_transaction_by_type`: dictionary of payment type name to average transaction amount (completed only)
     - `total_fees_by_type`: dictionary of payment type name to total fees collected (completed only)

Here is an example of how to use the `PaymentProcessor` class:

```python
from datetime import datetime

processor = PaymentProcessor()

cc_payment = CreditCardPayment(100, "USD", "1234")
crypto_payment = CryptoPayment(500, "USD", "0xABC123", "Bitcoin")
bank_payment = BankTransferPayment(2000, "USD", "123456789", "987654321")

processor.process_payment(cc_payment)
processor.process_payment(crypto_payment)
processor.process_payment(bank_payment)

print(cc_payment.get_fee()) # 3.20  (100 * 0.029 + 0.30)
print(cc_payment.get_total()) # 103.20

print(crypto_payment.get_fee()) # 5.00  (1% of 500 = 5.00, above the $1.00 minimum)
print(crypto_payment.get_total()) # 505.00

print(bank_payment.get_fee()) # 10.00  (0.5% of 2000, since amount >= $1000)
print(bank_payment.get_total()) # 2010.00

report = processor.generate_report()
print(report)

"""
Expected Output:
{
    'count_by_type': {'CreditCardPayment': 1, 'CryptoPayment': 1, 'BankTransferPayment': 1},
    'total_processed_by_type': {'CreditCardPayment': 100, 'CryptoPayment': 500, 'BankTransferPayment': 2000},
    'average_transaction_by_type': {'CreditCardPayment': 100.0, 'CryptoPayment': 500.0, 'BankTransferPayment': 2000.0},
    'total_fees_by_type': {'CreditCardPayment': 3.20, 'CryptoPayment': 5.00, 'BankTransferPayment': 10.00}
}
"""
```

---

### Task 4

Create a comprehensive data analysis system that processes a dataset of student records. The system should use classes, functional programming and complex data structures.

1. Create a `Student` class:
   - Properties: `student_id`, `name`, `grades`, `attendance`
   - Methods:
     - `__init__(self, student_id, name, grades, attendance)`
     - `get_gpa(self)` - calculates GPA from grades using: A=4.0, B=3.0, C=2.0, D=1.0, F=0.0. Returns the average across all subjects.
     - `get_status(self)` - returns "Honors" if GPA >= 3.5, "Good Standing" if GPA >= 2.0, or "Probation" otherwise
     - `is_at_risk(self)` - returns True if GPA < 2.0 or attendance < 75

2. Create an `Analyser` class:
   - `__init__(self, students)` - accepts list of Student objects
   - `get_top_students(self, n)` - returns the top n Student objects sorted by GPA descending
   - `get_subject_statistics(self, subject)` - returns a dict with:
     - `average_gpa`: the mean GPA value for that subject across all students who have that subject
     - `grade_distribution`: dict mapping each letter grade to the count of students who received it
     - `passing_rate`: percentage of students who received a C or better, i.e., not D or F in that subject
   - `identify_struggling_students(self)` - returns list of Student objects where is_at_risk() is True
   - `calculate_correlations(self)` - compares attendance to GPA across all students and returns a dict with:
     - `data_points`: list of (attendance, gpa) tuples for each student
     - `interpretation`: a string describing whether higher attendance tends to correspond with higher GPA based on the data
   - `generate_comprehensive_report(self)` - returns a nested dictionary with:
     - `overall`: dict with `total_students`, `average_gpa`, `average_attendance`
     - `status_distribution`: dict mapping each status string to the count of students with that status
     - `subjects`: dict mapping each subject name to its statistics from get_subject_statistics
     - `at_risk_students`: list of names of at-risk students
     - `recommendations`: list of recommendation strings based on the data

3. Data processing requirements:
   - Use map to transform student data where appropriate
   - Use filter to find specific student groups
   - Use reduce for aggregate calculations
   - Use list comprehensions for complex filtering
   - Use dictionary comprehensions for creating summary structures

Here is an example of how to use the `Analyser` class:

```python
students_data = [
    {"student_id": 1, "name": "Alice", "grades": {"Math": "A", "Science": "B", "English": "A"}, "attendance": 95},
    {"student_id": 2, "name": "Bob", "grades": {"Math": "C", "Science": "D", "English": "B"}, "attendance": 70},
    {"student_id": 3, "name": "Charlie", "grades": {"Math": "B", "Science": "B", "English": "B"}, "attendance": 88},
    {"student_id": 4, "name": "Diana", "grades": {"Math": "A", "Science": "A", "English": "A"}, "attendance": 98},
    {"student_id": 5, "name": "Eve", "grades": {"Math": "F", "Science": "D", "English": "C"}, "attendance": 65}
]

# Create Student objects
students = [Student(**data) for data in students_data]

# Analyse
analyser = Analyser(students)
report = analyser.generate_comprehensive_report()
top_3 = analyser.get_top_students(3) # [Diana (4.0), Alice (3.67), Charlie (3.0)]
math_stats = analyser.get_subject_statistics("Math")
at_risk = analyser.identify_struggling_students() # Bob and Eve

print(report)
"""
{
    'overall': {'total_students': 5, 'average_gpa': 3.13, 'average_attendance': 83.2},
    'status_distribution': {'Honors': 2, 'Good Standing': 2, 'Probation': 1},
    'subjects': {
        'Math': {'average_gpa': 3.0, 'grade_distribution': {'A': 2, 'B': 1, 'C': 1, 'F': 1}, 'passing_rate': 80.0},
        'Science': {'average_gpa': 2.6, 'grade_distribution': {'A': 1, 'B': 2, 'D': 2}, 'passing_rate': 60.0},
        'English': {'average_gpa': 3.0, 'grade_distribution': {'A': 2, 'B': 2, 'C': 1}, 'passing_rate': 100.0}
    },
    'at_risk_students': ['Bob', 'Eve'],
    'recommendations': [
        "Focus on improving attendance for at-risk students",
        "Provide additional support in Math and Science for struggling students",
        "Recognise and reward high performers to encourage continued success"
    ]
}
"""
```

---

### Task 5

Create a complete, playable Blackjack game using object-oriented programming. The game should support multiple players, follow standard Blackjack rules and provide an interactive command-line experience.

Game Rules:

- Goal: Get closer to 21 than the dealer without going over
- Face cards, e.g., J, Q, K are worth 10
- Aces are worth 11 or 1, whichever keeps the hand at or below 21
- Dealer must hit on 16 or less and stand on 17 or more
- Blackjack (Ace + 10-value card as the initial two cards) pays 3:2
- Regular win pays 1:1
- Players can hit, stand, or double down on first two cards only

Required Classes:

1. Card Class:
   - Properties: `rank` (2-10, J, Q, K, A), `suit` (Hearts, Diamonds, Clubs, Spades)
   - Methods:
     - `__init__(self, rank, suit)`
     - `get_value(self)` - returns numeric value, e.g., face cards = 10, Ace = 11, number cards = their number
     - `__str__(self)` - returns formatted card string, e.g., "Ace of Spades", "7 of Hearts"

2. Deck Class:
   - Properties: `cards` (list of Card objects)
   - Methods:
     - `__init__(self)` - creates a standard 52-card deck
     - `shuffle(self)` - randomises card order using `random.shuffle`
     - `deal_card(self)` - removes and returns the top card from the deck
     - `cards_remaining(self)` - returns the number of cards remaining
     - `reset(self)` - rebuilds and shuffles a fresh 52-card deck

3. Hand Class:
   - Properties: `cards` (list), `bet` (amount wagered)
   - Methods:
     - `__init__(self, bet=0)`
     - `add_card(self, card)` - adds a card to the hand
     - `get_value(self)` - calculates hand total, treating each Ace as 11 unless doing so would cause a bust, in which case it is counted as 1
     - `is_blackjack(self)` - returns True if the hand has exactly 2 cards and a value of 21
     - `is_bust(self)` - returns True if hand value exceeds 21
     - `can_double_down(self)` - returns True if the hand has exactly 2 cards
     - `__str__(self)` - returns a readable display of all cards and the current total

4. Player Class:
   - Properties: `name`, `chips`, `hands` (list of Hand objects, supports multiple hands if you want to extend for splitting)
   - Methods:
     - `__init__(self, name, chips=1000)`
     - `place_bet(self, amount)` - deducts amount from chips and returns a new Hand with that bet
     - `has_chips(self, amount)` - returns True if the player has at least that many chips
     - `win(self, amount)` - adds amount to chips
     - `lose(self, amount)` - deducts amount from chips
     - `can_continue(self)` - returns True if chips > 0
     - `__str__(self)` - returns a string showing name and chip count

5. Dealer Class:
   - Properties: `hand`, `name`
   - Methods:
     - `__init__(self)`
     - `show_partial_hand(self)` - displays the first card only, hiding the second card
     - `show_full_hand(self)` - displays all cards and the total
     - `should_hit(self)` - returns True if hand value is 16 or less
     - `__str__(self)` - returns the dealer's full hand display

6. BlackjackGame Class:
   - Properties: `deck`, `dealer`, `players` (list), `current_round`
   - Methods:
     - `__init__(self, player_names)` - initialises the game with a list of player names, creates a shuffled deck
     - `start_round(self)` - begins a new round, collects bets, deals initial cards
     - `deal_initial_cards(self)` - deals 2 cards to each player and 2 to the dealer
     - `player_turn(self, player)` - handles a player's choices, e.g., hit, stand, double down in a loop until they stand or bust
     - `dealer_turn(self)` - dealer reveals hidden card and hits until reaching 17 or more
     - `determine_winners(self)` - compares each player's hand to the dealer's and pays out or deducts chips accordingly
     - `display_game_state(self, hide_dealer_card=True)` - prints all hands; if hide_dealer_card is True, shows the dealer's first card only
     - `play_game(self)` - main game loop that continues until all players are out of chips or choose to quit
     - `check_for_bankruptcies(self)` - removes any players who have 0 chips
     - `game_over(self)` - returns True if the players list is empty

Game Flow:

1. Display a welcome message and show all players and their starting chips
2. Each round:
   - Players place their bets
   - Deal 2 cards to each player and the dealer. The dealer's second card is hidden
   - Check each player for an immediate blackjack
   - Run each player's turn, i.e., hit, stand, or double down
   - Dealer reveals hidden card and plays by house rules
   - Determine winners and update chip counts
   - Display updated chip counts
   - Ask if players want to continue
3. Game ends when all players are out of chips or all choose to quit

Here is an example of how to start the game:

```python
game = BlackjackGame(["Alice", "Bob"])
game.play_game()

"""
Welcome to Blackjack!
Players: Alice ($1000), Bob ($1000)

 ----- Round 1 -----

Alice, place your bet: 100
Bob, place your bet: 150

Alice's hand: 10 of Hearts, Ace of Spades (Total: 21) - Blackjack!
Bob's hand: 7 of Diamonds, 8 of Clubs (Total: 15)
Dealer's hand: 9 of Hearts, [Hidden Card]

Bob, do you want to hit, stand or double down? hit
Bob's hand: 7 of Diamonds, 8 of Clubs, 5 of Spades (Total: 20)

Bob, do you want to hit, stand or double down? stand
Dealer's hand: 9 of Hearts, 6 of Diamonds (Total: 15)
Dealer hits and gets 10 of Clubs (Total: 25) - Dealer busts!

Alice wins 150 chips! (Blackjack pays 3:2)
Bob wins 150 chips!
Updated Chips: Alice ($1150), Bob ($1200)

Do you want to play another round? yes
"""
```
