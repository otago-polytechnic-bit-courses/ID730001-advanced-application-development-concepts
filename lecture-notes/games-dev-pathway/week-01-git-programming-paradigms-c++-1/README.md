# Week 01

---

## Important Links

| Section    | Link                                  |
| ---------- | ------------------------------------- |
| GitHub     | [GitHub Classroom - id730001-S1-26]() |
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

## C++

C++ is a general-purpose, compiled programming language known for its performance and control over system resources. It builds on C by adding object-oriented features, generic programming (templates), and a rich standard library. C++ is widely used in game development, operating systems, embedded systems, and high-performance applications. C++ emphasises explicit control over memory and system resources and follows a philosophy that prioritises performance and expressiveness.

> Resource: <https://en.cppreference.com/w/>

---

### C++ Compiler

C++ must be compiled before it can be run. The compiler reads and translates C++ code into an executable program. You can compile and run C++ code using `g++` with the `--std=c++20` flag. We will primarily use C++ files to write and test our code, allowing us to see the results in the terminal.

```bash
g++ --std=c++20 -o my_program my_program.cpp
./my_program
```

> Resource: <https://en.cppreference.com/w/>

---

### Data Types

Data types are the different values that can be stored and manipulated in a program. C++ has several built-in data types:

- Boolean: `true` or `false`
- Integer: `1`, `2`, `-3`
- Double: `2.5`, `-3.14`
- String: `"Hello"`, `"World"` (requires `#include <string>`)
- Null pointer: `nullptr`
- Vector: `{1, 2, 3}` (requires `#include <vector>`)
- Pair/Tuple: `{1, 2, 3}` (requires `#include <tuple>`)
- Map: `{{"name", "John"}, {"age", 25}}` (requires `#include <map>`)

We will primarily focus on Boolean, Integer, Double, String, nullptr, Vector and Map for now.

> Resource: <https://en.cppreference.com/w/cpp/language/types>

---

### Variables

A variable is a named container that stores a value. It is like a box that holds a value and the variable's name is like a label on the box. You can use the variable's name to access its value.

```cpp
#include <iostream>
#include <string>

int main() {
    // A variable named "name" with value "John"
    std::string name = "John";

    // A variable named "age" with the value 25
    int age = 25;

    // Use auto to let the compiler infer the type
    auto score = 98.5;  // Deduced as double

    std::cout << name << " is " << age << " years old." << std::endl;
    return 0;
}
```

In C++, variables are mutable by default, meaning their values can be changed. However, you can declare a variable as `const` to make it immutable, meaning once created, its value cannot be modified.

```cpp
const double PI = 3.14159;
const int MAX_PLAYERS = 4;
```

> Resource: <https://en.cppreference.com/w/cpp/language/declarations>

---

### Operators

Operators are symbols that perform operations on values. There are several types of operators in C++:

- Arithmetic operators: `+`, `-`, `*`, `/`, `%` (use `std::pow` for exponentiation)
- Assignment operators: `=`, `+=`, `-=`, `*=`, `/=`, `%=`
- Comparison operators: `==`, `!=`, `>`, `<`, `>=`, `<=`
- Logical operators: `&&` (and), `||` (or), `!` (not)
- Increment/decrement operators: `++`, `--`

There are many other operators in C++, but we will only be concerned with these for now.

> Resource: <https://en.cppreference.com/w/cpp/language/expressions>

---

### Conditional Statements

Conditional statements allow you to execute different blocks of code depending on whether a condition is `true` or `false`. There are several types of conditionals in C++:

- if statement
- if...else statement
- if...else if...else statement
- ternary operator (conditional expression)

```cpp
#include <iostream>

int main() {
    int score = 75;

    // if statement
    if (score >= 90) {
        // Code to execute if condition is true
    }

    // if...else statement
    if (score >= 50) {
        // Code to execute if condition is true
    } else {
        // Code to execute if condition is false
    }

    // if...else if...else statement
    if (score >= 90) {
        // Code to execute if condition1 is true
    } else if (score >= 75) {
        // Code to execute if condition2 is true
    } else {
        // Code to execute if all conditions are false
    }

    // Ternary operator
    std::string result = (score >= 50) ? "Pass" : "Fail";

    return 0;
}
```

> Resource: <https://en.cppreference.com/w/cpp/language/if>

---

### Loops

Loops are statements that allow you to execute a block of code repeatedly. There are several types of loops in C++:

- for loop
- while loop
- range-based for loop (similar to Python's `for x in iterable`)

```cpp
#include <iostream>
#include <vector>

int main() {
    // for loop with index
    for (int i = 0; i < 10; i++) {
        // Code to execute repeatedly
    }

    // range-based for loop with iterable
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    for (const auto& element : numbers) {
        // Code to execute repeatedly
    }

    // while loop
    int count = 0;
    while (count < 3) {
        // Code to execute repeatedly
        count++;
    }

    return 0;
}
```

C++ also has `break` to exit a loop early and `continue` to skip to the next iteration.

> Resource: <https://en.cppreference.com/w/cpp/language/for>

---

### Functions

A function is a block of code that performs a specific task. It is like a machine that takes in some input, performs some operations and returns some output. A function is a reusable piece of code you can use in your program.

```cpp
#include <iostream>
#include <string>

// A function named "add" that takes in two numbers and returns their sum
int add(int a, int b) {
    return a + b;
}

std::cout << add(1, 2) << std::endl; // 3

// A function named "greet" that takes in a name and returns a greeting
std::string greet(const std::string& name) {
    return "Hello, " + name + "!";
}

std::cout << greet("John") << std::endl; // Hello, John!
```

C++ also supports lambda functions (anonymous functions) for simple operations:

```cpp
#include <iostream>

int main() {
    // A lambda function that takes in two numbers and returns their sum
    auto add = [](int a, int b) { return a + b; };

    std::cout << add(1, 2) << std::endl; // 3

    // A lambda function that takes in a name and returns a greeting
    auto greet = [](const std::string& name) { return "Hello, " + name + "!"; };

    std::cout << greet("John") << std::endl; // Hello, John!
}
```

Functions can have default parameter values:

```cpp
// A function with a default parameter
std::string greet(const std::string& name = "World") {
    return "Hello, " + name + "!";
}

// greet()        → "Hello, World!"
// greet("John")  → "Hello, John!"
```

> Resource: <https://en.cppreference.com/w/cpp/language/functions>

---

### std::format (Formatted String Literals)

`std::format` allows you to embed expressions inside string literals using curly braces `{}`. It is available in C++20 and provides a concise and readable way to format strings.

```cpp
#include <iostream>
#include <format>

int main() {
    std::string name = "John";
    int age = 30;

    // Using std::format
    std::string greeting = std::format("Hello, my name is {} and I am {} years old", name, age);

    std::cout << greeting << std::endl;
    // Hello, my name is John and I am 30 years old

    // std::format can include expressions
    std::cout << std::format("Next year I will be {} years old", age + 1) << std::endl;
    // Next year I will be 31 years old
}
```

> Resource: <https://en.cppreference.com/w/cpp/utility/format/format>

---

### Classes

A class is a blueprint for creating objects. It defines a set of properties and methods that the created objects will have. In C++, you can define a class using the `class` keyword.

```cpp
#include <iostream>
#include <string>
#include <format>

// Defining a class named Person
class Person {
private:
    std::string name;
    int age;

public:
    // Constructor
    Person(const std::string& name, int age) : name(name), age(age) {}

    // A method to greet the person
    std::string greet() const {
        return std::format("Hello, my name is {} and I am {} years old", name, age);
    }
};

int main() {
    // Creating an instance of the Person class
    Person john("John", 30);

    std::cout << john.greet() << std::endl;
    // Hello, my name is John and I am 30 years old
}
```

> Resource: <https://en.cppreference.com/w/cpp/language/classes>

---

### Vectors

A vector is a data structure that stores an ordered collection of values. It is like a box that can hold multiple values and each value is assigned an index starting from 0. You can use a value's index to access its value. Vectors are mutable, meaning you can change their contents.

```cpp
#include <iostream>
#include <vector>
#include <string>

int main() {
    // A vector of numbers
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // A vector of strings
    std::vector<std::string> fruits = {"Apple", "Banana", "Cherry", "Durian", "Elderberry"};

    // Accessing elements
    std::cout << fruits[0] << std::endl;    // Apple
    std::cout << numbers.back() << std::endl; // 5 (last element)
}
```

A 2D vector (nested vector) is a data structure that represents a matrix or a grid-like structure with rows and columns.

```cpp
#include <iostream>
#include <vector>
#include <string>

int main() {
    // A 2D vector of numbers
    std::vector<std::vector<int>> numbers = {
        {1, 2, 3},
        {4, 5, 6}
    };

    // A 2D vector of strings
    std::vector<std::vector<std::string>> fruits = {
        {"Apple", "Banana", "Cherry"},
        {"Durian", "Elderberry", "Fig"}
    };

    std::cout << numbers[0][0] << std::endl; // 1
    std::cout << fruits[1][2] << std::endl;  // Fig
}
```

Here is an example of a 2D vector with vectors of different lengths.

```cpp
// A 2D vector of different lengths
std::vector<std::vector<int>> mixed = {
    {1, 2, 3},
    {4, 5},
    {6}
};
```

> Resource: <https://en.cppreference.com/w/cpp/container/vector>

---

### Structured Bindings

Structured bindings are a convenient way to extract values from pairs, tuples, or structs into distinct variables. They can make your code cleaner and more readable. Here are some examples of using structured bindings.

```cpp
#include <iostream>
#include <tuple>
#include <map>

int main() {
    // Pair unpacking
    std::pair<std::string, int> person = {"John", 30};
    auto [name, age] = person;

    std::cout << name << std::endl; // John
    std::cout << age << std::endl;  // 30

    // Tuple unpacking
    auto coords = std::make_tuple(10, 20, 30);
    auto [x, y, z] = coords;

    // Iterating over a map with structured bindings
    std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 82}};
    for (const auto& [student, score] : scores) {
        std::cout << student << ": " << score << std::endl;
    }
}
```

> Resource: <https://en.cppreference.com/w/cpp/language/structured_binding>

---

### Unpacking Operator

The unpacking operators (`...` for parameter packs, initialiser lists for containers) allow you to expand collections into individual elements. They are useful for copying vectors or maps, merging collections, and passing multiple arguments to functions. Here are some examples.

```cpp
#include <iostream>
#include <vector>
#include <map>

int main() {
    // Copying a vector
    std::vector<int> numbers = {1, 2, 3};
    std::vector<int> copy_of_numbers = numbers;
    // copy_of_numbers: {1, 2, 3}

    // Merging vectors
    std::vector<int> more_numbers = {4, 5, 6};
    std::vector<int> merged_numbers = numbers;
    merged_numbers.insert(merged_numbers.end(), more_numbers.begin(), more_numbers.end());
    // merged_numbers: {1, 2, 3, 4, 5, 6}

    // Copying a map
    std::map<std::string, int> person = {{"name_id", 1}, {"age", 30}};
    std::map<std::string, int> copy_of_person = person;

    // Merging maps
    std::map<std::string, int> more_details = {{"is_active", 1}, {"score", 95}};
    std::map<std::string, int> merged_person = person;
    merged_person.insert(more_details.begin(), more_details.end());
}
```

> Resource: <https://en.cppreference.com/w/cpp/language/parameter_pack>

---

### Transform

`std::transform` is a standard algorithm that transforms a container by applying a function to each element and writing the result to an output container. Here is an example of using `std::transform`.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // A vector of numbers
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Transform
    std::vector<int> numbers_squared(numbers.size());
    std::transform(numbers.begin(), numbers.end(), numbers_squared.begin(),
                   [](int num) { return num * num; });

    // numbers_squared: {1, 4, 9, 16, 25}

    // Passing a named function to transform
    auto square = [](int num) { return num * num; };
    std::transform(numbers.begin(), numbers.end(), numbers_squared.begin(), square);

    // numbers_squared: {1, 4, 9, 16, 25}
}
```

Here is before and after execution model of `std::transform`:

```bash
Input vector       Callback                Output vector

index 0: 1  ─────▶ [](int n){ n*n } ─────▶ index 0: 1
index 1: 2  ─────▶ [](int n){ n*n } ─────▶ index 1: 4
index 2: 3  ─────▶ [](int n){ n*n } ─────▶ index 2: 9
index 3: 4  ─────▶ [](int n){ n*n } ─────▶ index 3: 16
index 4: 5  ─────▶ [](int n){ n*n } ─────▶ index 4: 25
```

> Resource: <https://en.cppreference.com/w/cpp/algorithm/transform>

---

### Filter

`std::copy_if` is a standard algorithm that filters a container by copying only elements satisfying a condition into an output container. Here is an example of using `std::copy_if`.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // A vector of numbers
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Filter
    std::vector<int> even_numbers;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(even_numbers),
                 [](int num) { return num % 2 == 0; });

    // even_numbers: {2, 4}

    // Passing a named function to copy_if
    auto is_even = [](int num) { return num % 2 == 0; };
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(even_numbers), is_even);

    // even_numbers: {2, 4}
}
```

Here is before and after execution model of `std::copy_if`:

```bash
Input vector       Callback                        Output vector

index 0: 1  ─────▶ [](int n){ n % 2 == 0 } ─────▶ removed
index 1: 2  ─────▶ [](int n){ n % 2 == 0 } ─────▶ index 0: 2
index 2: 3  ─────▶ [](int n){ n % 2 == 0 } ─────▶ removed
index 3: 4  ─────▶ [](int n){ n % 2 == 0 } ─────▶ index 1: 4
index 4: 5  ─────▶ [](int n){ n % 2 == 0 } ─────▶ removed
```

> Resource: <https://en.cppreference.com/w/cpp/algorithm/copy>

---

### Reduce

`std::accumulate` is a function from `<numeric>` that reduces a container to a single value by applying a function to each element and returning a single value. Here is an example of using `std::accumulate`.

```cpp
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    // A vector of numbers
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Accumulate with initial value of 0
    int total = std::accumulate(numbers.begin(), numbers.end(), 0,
                                [](int acc, int num) { return acc + num; });

    std::cout << total << std::endl; // 15

    // Passing a named function to accumulate with initial value of 5
    auto add = [](int acc, int num) { return acc + num; };
    int total2 = std::accumulate(numbers.begin(), numbers.end(), 5, add);

    std::cout << total2 << std::endl; // 20
}
```

Here is before and after execution model of `std::accumulate` (with initial value 5):

```bash
Input vector       Callback                                 Accumulator value
index 0: 1  ─────▶ [](int acc, int n){ acc + n } ─────▶ 5 + 1 = 6
index 1: 2  ─────▶ [](int acc, int n){ acc + n } ─────▶ 6 + 2 = 8
index 2: 3  ─────▶ [](int acc, int n){ acc + n } ─────▶ 8 + 3 = 11
index 3: 4  ─────▶ [](int acc, int n){ acc + n } ─────▶ 11 + 4 = 15
index 4: 5  ─────▶ [](int acc, int n){ acc + n } ─────▶ 15 + 5 = 20
```

> Resource: <https://en.cppreference.com/w/cpp/algorithm/accumulate>

---

### Maps

A map is a data structure that stores a collection of key-value pairs. It is like a box that can hold multiple key-value pairs, assigning each key a value. You can use the key of a key-value pair to access its value. Maps are mutable.

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    // A map with key-value pairs
    std::map<std::string, int> person = {
        {"age", 25},
        {"score", 95}
    };

    std::cout << person["age"] << std::endl;   // 25
    std::cout << person["score"] << std::endl; // 95

    // Alternative access method
    std::cout << person.at("age") << std::endl; // 25
}
```

Here is another example of creating a map with variables.

```cpp
#include <map>
#include <string>

int main() {
    std::string name = "John";
    int age = 25;
    bool is_male = true;

    // Using map with string keys
    std::map<std::string, std::string> person_str = {
        {"name", name},
        {"status", "active"}
    };
}
```

Here is another example of a map with key-value pairs of different value types using `std::variant` or separate maps.

```cpp
#include <iostream>
#include <map>
#include <vector>
#include <string>

int main() {
    // A map with a vector value
    std::map<std::string, std::vector<std::string>> person = {
        {"favourite_fruits", {"Apple", "Banana", "Cherry"}}
    };

    std::cout << person["favourite_fruits"][0] << std::endl; // Apple
}
```

You can have a vector of maps or a map with vectors. Here is an example of a vector of maps.

```cpp
#include <iostream>
#include <vector>
#include <map>
#include <string>

int main() {
    // A vector of maps
    std::vector<std::map<std::string, int>> people = {
        {{"age", 25}, {"score", 95}},
        {{"age", 20}, {"score", 82}}
    };

    std::cout << people[0]["age"] << std::endl;   // 25
    std::cout << people[1]["score"] << std::endl; // 82
}
```

There is an alternative way to create a map by inserting elements one by one.

```cpp
#include <map>
#include <string>

int main() {
    // A map using insert
    std::map<std::string, int> person;
    person["age"] = 25;
    person["score"] = 95;
    person["is_active"] = 1;
}
```

In this course, we will use the map initialiser list syntax to create maps.

> Resource: <https://en.cppreference.com/w/cpp/container/map>

---

## Exercises

Copy the file `week-01-git-programming-paradigms-c++-1` into your id730001-s1-26 repository. Open your id730001-s1-26 repository in Visual Studio Code. Open the terminal and compile and run the file:

```bash
g++ --std=c++20 -o week-01-git-programming-paradigms-c++-1 week-01-git-programming-paradigms-c++-1.cpp
./week-01-git-programming-paradigms-c++-1
```

You should see the following output.

```bash
Hello, World!
```

Learning to use AI tools is an important skill. While AI tools are powerful, you must be aware of the following:

- If you provide an AI tool with a prompt that is not refined enough, it may generate a not-so-useful response
- Do not trust the AI tool's responses blindly. You must still use your judgement and may need to do additional research to determine if the response is correct
- Acknowledge what AI tool you have used. If you use AI to help you with a file, include a comment block at the top of the file

Here is an example comment block:

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

### Task 1

Create a function called `process_data_pipeline` that takes a `std::vector` of structs representing user data and applies a series of transformations using `std::copy_if`, `std::transform` and `std::accumulate`. Each user should be represented using a struct with the following fields:

```cpp
struct User {
    int id;
    std::string name;
    int age;
    std::vector<int> purchases;
    int member_since;
    std::string status;
};
```

Your function should:

1. Filter out users who are inactive (`status != "active"`)
2. Filter out users under 25 years old
3. Transform each user to compute `total_spent` (sum of all purchases)
4. Transform each user to compute `loyalty_years` (2026 - `member_since`)
5. Transform each user to assign a `tier` based on `total_spent`:
   - `"Bronze"` if `total_spent < 500`
   - `"Silver"` if `500 <= total_spent < 1000`
   - `"Gold"` if `total_spent >= 1000`
6. Use `std::accumulate` to calculate the total revenue from all qualifying users
7. Return a `PipelineResult` struct containing:
   - `processed_users`: vector of processed user data
   - `total_revenue`: total revenue from `std::accumulate`
   - `user_count`: number of qualifying users
   - `average_spending`: total revenue / user count

Here is an example of how to use the `process_data_pipeline` function:

```cpp
std::vector<User> users = {
    {1, "Alice",   30, {200, 400, 150}, 2019, "active"},
    {2, "Bob",     22, {100, 50},       2021, "active"},
    {3, "Charlie", 28, {500, 600},      2020, "inactive"},
    {4, "Diana",   35, {300, 200, 100}, 2018, "active"}
};

auto result = process_data_pipeline(users);

/*
Expected Output:

processed_users:
  Alice  | total_spent: 750  | loyalty_years: 7 | tier: Silver
  Diana  | total_spent: 600  | loyalty_years: 8 | tier: Silver

total_revenue:    1350
user_count:       2
average_spending: 675.00
*/
```

Bob is excluded because he is under 25. Charlie is excluded because his status is `"inactive"`. Alice's `total_spent` is 200 + 400 + 150 = 750 (Silver tier). Diana's `total_spent` is 300 + 200 + 100 = 600 (Silver tier). Total revenue is 750 + 600 = 1350. Average spending is 1350 / 2 = 675.0.

---

### Task 2

Create a function called `transform_organisation` that takes a complex nested struct representing an organisation structure and performs deep transformations. The function should:

1. Accept a struct with this structure:

```cpp
struct Employee {
    std::string name;
    double salary;
    double performance;
};

struct Team {
    std::string name;
    std::vector<Employee> employees;
    // Added by transform:
    double total_salary;
    double avg_performance;
    Employee top_performer;
};

struct Department {
    std::string name;
    double budget;
    std::vector<Team> teams;
    // Added by transform:
    int team_count;
    int employee_count;
    double utilisation_rate;
};

struct Organisation {
    std::string company;
    std::vector<Department> departments;
    // Added by transform:
    struct Summary {
        int total_departments;
        int total_teams;
        int total_employees;
        Employee highest_paid_employee;
        std::vector<std::string> departments_over_budget;
    } summary;
};
```

2. Transform the structure to:
   - Add a `total_salary` field to each team (sum of all employee salaries)
   - Add an `avg_performance` field to each team (average of all performance scores, rounded to 2 decimal places)
   - Add a `top_performer` field to each team (employee with highest performance score)
   - Add a `team_count` field to each department (number of teams)
   - Add an `employee_count` field to each department (total employees across all teams)
   - Add a `utilisation_rate` field to each department (total salary across all teams / budget, expressed as a percentage rounded to 2 decimal places)
   - Add a company-level `summary` struct with:
     - `total_departments`: count of departments
     - `total_teams`: count of all teams across all departments
     - `total_employees`: count of all employees across the entire company
     - `highest_paid_employee`: the employee struct with the highest salary across the whole company
     - `departments_over_budget`: list of department names where `utilisation_rate > 80`

3. Use `std::accumulate`, `std::max_element` and range-based loops where appropriate

For the example above, the Backend team has `total_salary` = 175000 and `avg_performance` = 4.65. The Frontend team has `total_salary` = 80000 and `avg_performance` = 4.2. The Engineering department has `team_count` = 2, `employee_count` = 3 and `utilisation_rate` = 51.0. Since 51.0 is not over 80, `departments_over_budget` would be an empty list.

```cpp
Organisation org = {
    "TechCorp",
    {
        {
            "Engineering", 500000.0,
            {
                {"Backend", {{"Alice", 85000, 4.5}, {"Bob", 90000, 4.8}}},
                {"Frontend", {{"Charlie", 80000, 4.2}}}
            }
        }
    }
};

auto result = transform_organisation(org);

/*
Expected Output:
Company: TechCorp

  Department: Engineering
    Budget: $500000.00 | Utilisation: 51.00% | Teams: 2 | Employees: 3

    Team: Backend
      Total Salary: $175000.00 | Avg Performance: 4.65
      Top Performer: Bob (4.80)

    Team: Frontend
      Total Salary: $80000.00 | Avg Performance: 4.20
      Top Performer: Charlie (4.20)

Summary:
  Total Departments: 1
  Total Teams: 2
  Total Employees: 3
  Highest Paid: Bob ($90000.00)
  Departments Over Budget: none
*/
```

---

### Task 3

Create a payment processing system with the following requirements:

1. Base Class: `Payment`
   - Member variables: `amount`, `currency`, `timestamp` (set automatically on construction using `std::chrono::system_clock::now()`), `status` (default `"pending"`)
   - Methods:
     - `Payment(double amount, std::string currency = "USD")`
     - `virtual double get_fee() const = 0` — pure virtual (must be overridden)
     - `virtual bool process() = 0` — pure virtual
     - `bool validate() const` — returns `amount > 0`
     - `double get_total() const` — returns `amount + get_fee()`
     - `virtual std::string to_string() const` — returns formatted payment info

2. Child Classes:
   - `CreditCardPayment(Payment)`:
     - Additional member: `card_number` (last 4 digits only, stored as `std::string`)
     - Additional constructor parameter: `card_number`
     - Fee: 2.9% of amount + $0.30
     - `process()`: calls `validate()`, calculates total, sets status to `"completed"` and returns true; if validation fails, sets status to `"failed"` and returns false
   - `CryptoPayment(Payment)`:
     - Additional members: `wallet_address`, `crypto_type`
     - Additional constructor parameters: `wallet_address`, `crypto_type`
     - Fee: 1% of amount, with a minimum fee of $1.00
     - `process()`: calls `validate()`, sets status to `"completed"` and returns true; if validation fails, sets status to `"failed"` and returns false
   - `BankTransferPayment(Payment)`:
     - Additional members: `account_number`, `routing_number`
     - Additional constructor parameters: `account_number`, `routing_number`
     - Fee: flat $5.00 for amounts under $1000, otherwise 0.5% of amount
     - `process()`: calls `validate()`, sets status to `"completed"` and returns true; if validation fails, sets status to `"failed"` and returns false

3. `PaymentProcessor` Class:
   - `PaymentProcessor()` — initialises an empty transactions list
   - `process_payment(std::shared_ptr<Payment> payment)` — calls `payment->process()` and appends the payment to transactions regardless of outcome
   - `get_transactions_by_type(const std::string& type_name)` — returns a list of transactions filtered by class type name
   - `get_total_processed() const` — returns the sum of amounts for all transactions with status `"completed"`
   - `get_total_fees_collected() const` — returns the sum of fees for all transactions with status `"completed"`
   - `generate_report() const` — returns a `Report` struct with:
     - `count_by_type`: map of payment type name to count of transactions
     - `total_processed_by_type`: map of payment type name to total amount processed (completed only)
     - `average_transaction_by_type`: map of payment type name to average transaction amount (completed only)
     - `total_fees_by_type`: map of payment type name to total fees collected (completed only)

Here is an example of how to use the `PaymentProcessor` class:

```cpp
PaymentProcessor processor;

auto cc_payment     = std::make_shared<CreditCardPayment>(100.0, "USD", "1234");
auto crypto_payment = std::make_shared<CryptoPayment>(500.0, "USD", "0xABC123", "Bitcoin");
auto bank_payment   = std::make_shared<BankTransferPayment>(2000.0, "USD", "123456789", "987654321");

processor.process_payment(cc_payment);
processor.process_payment(crypto_payment);
processor.process_payment(bank_payment);

std::cout << cc_payment->get_fee()    << std::endl;  // 3.20  (100 * 0.029 + 0.30)
std::cout << cc_payment->get_total()  << std::endl;  // 103.20

std::cout << crypto_payment->get_fee()   << std::endl;  // 5.00  (1% of 500 = 5.00, above the $1.00 minimum)
std::cout << crypto_payment->get_total() << std::endl;  // 505.00

std::cout << bank_payment->get_fee()   << std::endl;  // 10.00  (0.5% of 2000, since amount >= $1000)
std::cout << bank_payment->get_total() << std::endl;  // 2010.00

auto report = processor.generate_report();

/*
Expected Output:
{
  count_by_type:               { CreditCardPayment: 1, CryptoPayment: 1, BankTransferPayment: 1 },
  total_processed_by_type:     { CreditCardPayment: 100.00, CryptoPayment: 500.00, BankTransferPayment: 2000.00 },
  average_transaction_by_type: { CreditCardPayment: 100.00, CryptoPayment: 500.00, BankTransferPayment: 2000.00 },
  total_fees_by_type:          { CreditCardPayment: 3.20, CryptoPayment: 5.00, BankTransferPayment: 10.00 }
}
*/
```

---

### Task 4

Create a comprehensive data analysis system that processes a dataset of student records. The system should use classes, STL algorithms and lambdas.

1. Create a `Student` class:
   - Member variables: `student_id`, `name`, `grades` (`std::map<std::string, char>` mapping subject to letter grade), `attendance` (double, percentage)
   - Methods:
     - `Student(int student_id, std::string name, std::map<std::string, char> grades, double attendance)`
     - `double get_gpa() const` — calculates GPA from grades using: A=4.0, B=3.0, C=2.0, D=1.0, F=0.0. Returns the average across all subjects.
     - `std::string get_status() const` — returns `"Honors"` if GPA >= 3.5, `"Good Standing"` if GPA >= 2.0, or `"Probation"` otherwise
     - `bool is_at_risk() const` — returns true if GPA < 2.0 or attendance < 75

2. Create an `Analyser` class:
   - `Analyser(std::vector<Student> students)` — accepts a vector of `Student` objects
   - `std::vector<Student> get_top_students(int n) const` — returns the top n `Student` objects sorted by GPA descending
   - `SubjectStats get_subject_statistics(const std::string& subject) const` — returns a `SubjectStats` struct with:
     - `average_gpa`: the mean GPA value for that subject across all students who have that subject
     - `grade_distribution`: `std::map<char, int>` mapping each letter grade to the count of students who received it
     - `passing_rate`: percentage of students who received a C or better, i.e., not D or F in that subject
   - `std::vector<Student> identify_struggling_students() const` — returns a vector of `Student` objects where `is_at_risk()` is true
   - `calculate_correlations() const` — compares attendance to GPA across all students and returns a struct with:
     - `data_points`: vector of `std::pair<double, double>` of (attendance, gpa) for each student
     - `interpretation`: a string describing whether higher attendance tends to correspond with higher GPA based on the data
   - `Report generate_comprehensive_report() const` — returns a `Report` struct with:
     - `overall`: struct with `total_students`, `average_gpa`, `average_attendance`
     - `status_distribution`: `std::map<std::string, int>` mapping each status string to the count of students with that status
     - `subjects`: map of subject name to its `SubjectStats`
     - `at_risk_students`: vector of names of at-risk students
     - `recommendations`: vector of recommendation strings based on the data

3. Data processing requirements:
   - Use `std::transform` to transform student data where appropriate
   - Use `std::copy_if` to find specific student groups
   - Use `std::accumulate` for aggregate calculations
   - Use range-based for loops for complex filtering
   - Use `std::map` for creating summary structures

Here is an example of how to use the `Analyser` class:

```cpp
std::vector<Student> students = {
    {1, "Alice",   {{"Math",'A'},{"Science",'B'},{"English",'A'}}, 95},
    {2, "Bob",     {{"Math",'C'},{"Science",'D'},{"English",'B'}}, 70},
    {3, "Charlie", {{"Math",'B'},{"Science",'B'},{"English",'B'}}, 88},
    {4, "Diana",   {{"Math",'A'},{"Science",'A'},{"English",'A'}}, 98},
    {5, "Eve",     {{"Math",'F'},{"Science",'D'},{"English",'C'}}, 65}
};

Analyser analyser(students);
auto report     = analyser.generate_comprehensive_report();
auto top_3      = analyser.get_top_students(3);                 // Diana (4.0), Alice (3.67), Charlie (3.0)
auto math_stats = analyser.get_subject_statistics("Math");
auto at_risk    = analyser.identify_struggling_students();      // Bob and Eve

/*
Expected Output:
overall:
  total_students:     5
  average_gpa:        2.73
  average_attendance: 83.20

status_distribution:
  Honors:        2
  Good Standing: 2
  Probation:     1

subjects:
  Math:
    average_gpa:        3.00
    grade_distribution: A:2  B:1  C:1  F:1
    passing_rate:       80.00%

  Science:
    average_gpa:        2.40
    grade_distribution: A:1  B:2  D:2
    passing_rate:       60.00%

  English:
    average_gpa:        3.20
    grade_distribution: A:2  B:2  C:1
    passing_rate:       100.00%

at_risk_students: Bob, Eve

recommendations:
  - Focus on improving attendance for at-risk students
  - Provide additional support in Math and Science for struggling students
  - Recognise and reward high performers to encourage continued success
*/
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

1. `Card` Class:
   - Members: `rank` (e.g., `"2"`, `"J"`, `"A"`), `suit` (e.g., `"Hearts"`, `"Diamonds"`, `"Clubs"`, `"Spades"`)
   - Methods:
     - `Card(std::string rank, std::string suit)`
     - `int get_value() const` — returns numeric value, e.g., face cards = 10, Ace = 11, number cards = their number
     - `std::string to_string() const` — returns formatted card string, e.g., `"Ace of Spades"`, `"7 of Hearts"`

2. `Deck` Class:
   - Member: `std::vector<Card> cards`
   - Methods:
     - `Deck()` — creates a standard 52-card deck
     - `void shuffle()` — randomises card order using `std::shuffle` and `std::mt19937`
     - `Card deal_card()` — removes and returns the top card from the deck
     - `int cards_remaining() const` — returns the number of cards remaining
     - `void reset()` — rebuilds and shuffles a fresh 52-card deck

3. `Hand` Class:
   - Members: `std::vector<Card> cards`, `int bet` (amount wagered)
   - Methods:
     - `Hand(int bet = 0)`
     - `void add_card(const Card& card)` — adds a card to the hand
     - `int get_value() const` — calculates hand total, treating each Ace as 11 unless doing so would cause a bust, in which case it is counted as 1
     - `bool is_blackjack() const` — returns true if the hand has exactly 2 cards and a value of 21
     - `bool is_bust() const` — returns true if hand value exceeds 21
     - `bool can_double_down() const` — returns true if the hand has exactly 2 cards
     - `std::string to_string() const` — returns a readable display of all cards and the current total

4. `Player` Class:
   - Members: `name`, `chips`, `hands` (`std::vector<Hand>`, supports multiple hands if you want to extend for splitting)
   - Methods:
     - `Player(std::string name, int chips = 1000)`
     - `Hand place_bet(int amount)` — deducts amount from chips and returns a new `Hand` with that bet
     - `bool has_chips(int amount) const` — returns true if the player has at least that many chips
     - `void win(int amount)` — adds amount to chips
     - `void lose(int amount)` — deducts amount from chips
     - `bool can_continue() const` — returns true if chips > 0
     - `std::string to_string() const` — returns a string showing name and chip count

5. `Dealer` Class:
   - Members: `Hand hand`, `std::string name`
   - Methods:
     - `Dealer()`
     - `void show_partial_hand() const` — displays the first card only, hiding the second card
     - `void show_full_hand() const` — displays all cards and the total
     - `bool should_hit() const` — returns true if hand value is 16 or less
     - `std::string to_string() const` — returns the dealer's full hand display

6. `BlackjackGame` Class:
   - Members: `Deck deck`, `Dealer dealer`, `std::vector<Player> players`, `int current_round`
   - Methods:
     - `BlackjackGame(std::vector<std::string> player_names)` — initialises the game with a list of player names, creates a shuffled deck
     - `void start_round()` — begins a new round, collects bets, deals initial cards
     - `void deal_initial_cards()` — deals 2 cards to each player and 2 to the dealer
     - `void player_turn(Player& player)` — handles a player's choices, e.g., hit, stand, double down in a loop until they stand or bust
     - `void dealer_turn()` — dealer reveals hidden card and hits until reaching 17 or more
     - `void determine_winners()` — compares each player's hand to the dealer's and pays out or deducts chips accordingly
     - `void display_game_state(bool hide_dealer_card = true)` — prints all hands; if `hide_dealer_card` is true, shows the dealer's first card only
     - `void play_game()` — main game loop that continues until all players are out of chips or choose to quit
     - `void check_for_bankruptcies()` — removes any players who have 0 chips
     - `bool game_over() const` — returns true if the players vector is empty

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

```cpp
BlackjackGame game({"Alice", "Bob"});
game.play_game();

/*
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
*/
```
