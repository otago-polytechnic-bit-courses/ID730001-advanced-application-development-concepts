# Week 01 - Git, Programming Paradigms and C++

## Navigation

|                  | Link                                                      |
| ---------------- | --------------------------------------------------------- |
| GitHub Classroom | [ID730001-S1-26](https://classroom.github.com/a/RgDe5bs0) |
| → Next           | [Week 02]()                                               |

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

## 3. C++

C++ is a general-purpose, compiled programming language known for its performance and control over system resources. It builds on C by adding object-oriented features, generic programming (templates), and a rich standard library. C++ is widely used in game development, operating systems, embedded systems, and high-performance applications. C++ emphasises explicit control over memory and system resources, prioritising performance and expressiveness.

📖 Reference: [cppreference.com](https://en.cppreference.com/w/)

---

### 3.1 C++ Compiler

C++ must be compiled before it can run. The compiler translates C++ source code into an executable binary. We use `g++` with the `--std=c++20` flag throughout this course.

```bash
# Compile a file named my_program.cpp into an executable named my_program
g++ --std=c++20 -o my_program my_program.cpp

# Run the compiled executable
./my_program
```

📖 Reference: [cppreference.com](https://en.cppreference.com/w/)

---

### 3.2 Data Types

C++ has several built-in data types. Some require including a standard library header before they can be used.

| Type         | Example                             | Header required |
| ------------ | ----------------------------------- | --------------- |
| Boolean      | `true`, `false`                     | -               |
| Integer      | `1`, `2`, `-3`                      | -               |
| Double       | `2.5`, `-3.14`                      | -               |
| String       | `"Hello"`, `"World"`                | `<string>`      |
| Null pointer | `nullptr`                           | -               |
| Vector       | `{1, 2, 3}`                         | `<vector>`      |
| Pair / Tuple | `{1, 2}` / `{1, 2, 3}`              | `<tuple>`       |
| Map          | `{{"name", "John"}, {"age", "25"}}` | `<map>`         |

> We will focus on Boolean, Integer, Double, String, nullptr, Vector and Map for now.

📖 Reference: [C++ - Fundamental Types](https://en.cppreference.com/w/cpp/language/types)

---

### 3.3 Variables

A variable is a named container that stores a value. In C++, you must declare the type of a variable when you create it (or use `auto` to let the compiler infer it).

```cpp
#include <iostream>
#include <string>

int main() {
    // Explicitly typed variables
    std::string name = "John";  // type: std::string
    int age = 25;               // type: int

    // auto lets the compiler deduce the type from the assigned value
    auto score = 98.5;  // deduced as double

    std::cout << name << " is " << age << " years old." << std::endl;
    return 0;
}
```

Variables are mutable by default. Use `const` to make a variable immutable - the compiler will prevent you from accidentally changing it later.

```cpp
// const variables cannot be reassigned after initialisation
const double PI = 3.14159;
const int MAX_PLAYERS = 4;
```

📖 Reference: [C++ - Declarations](https://en.cppreference.com/w/cpp/language/declarations)

---

### 3.4 Operators

| Category              | Operators                         | Notes                             |
| --------------------- | --------------------------------- | --------------------------------- |
| Arithmetic            | `+`, `-`, `*`, `/`, `%`           | Use `std::pow` for exponentiation |
| Assignment            | `=`, `+=`, `-=`, `*=`, `/=`, `%=` |                                   |
| Comparison            | `==`, `!=`, `>`, `<`, `>=`, `<=`  |                                   |
| Logical               | `&&`, `\|\|`, `!`                 | `and`, `or`, `not`                |
| Increment / Decrement | `++`, `--`                        |                                   |

📖 Reference: [C++ - Expressions](https://en.cppreference.com/w/cpp/language/expressions)

---

### 3.5 Conditional Statements

```cpp
#include <iostream>

int main() {
    int score = 75;

    // if - runs the block only when the condition is true
    if (score >= 90) {
        std::cout << "Excellent!" << std::endl;
    }

    // if...else - one branch for true, another for false
    if (score >= 50) {
        std::cout << "Pass" << std::endl;
    } else {
        std::cout << "Fail" << std::endl;
    }

    // if...else if...else - check multiple conditions in order
    if (score >= 90) {
        std::cout << "A" << std::endl;
    } else if (score >= 75) {
        std::cout << "B" << std::endl;
    } else {
        std::cout << "C or below" << std::endl;
    }

    // Ternary operator - compact single-expression conditional
    // Syntax: condition ? value_if_true : value_if_false
    std::string result = (score >= 50) ? "Pass" : "Fail";

    return 0;
}
```

📖 Reference: [C++ - if statement](https://en.cppreference.com/w/cpp/language/if)

---

### 3.6 Loops

```cpp
#include <iostream>
#include <vector>

int main() {
    // Classic for loop - useful when you need the index
    for (int i = 0; i < 10; i++) {
        std::cout << i << std::endl;
    }

    // Range-based for loop - cleaner when you just need each element
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    for (const auto& element : numbers) {
        // const auto& avoids copying each element
        std::cout << element << std::endl;
    }

    // while loop - repeat while a condition holds
    int count = 0;
    while (count < 3) {
        std::cout << count << std::endl;
        count++;  // don't forget to update the condition variable
    }

    return 0;
}
```

C++ also supports `break` (exit a loop early) and `continue` (skip to the next iteration).

📖 Reference: [C++ - for statement](https://en.cppreference.com/w/cpp/language/for)

---

### 3.7 Functions

A function is a named, reusable block of code that takes input (parameters), performs some work, and returns output.

**Regular function:**

```cpp
#include <iostream>
#include <string>

// Return type comes first, then the function name, then parameters in parentheses
int add(int a, int b) {
    return a + b;  // the value after return is sent back to the caller
}

std::string greet(const std::string& name) {
    // const std::string& means: accept a string without copying it
    return "Hello, " + name + "!";
}

int main() {
    std::cout << add(1, 2) << std::endl;    // 3
    std::cout << greet("John") << std::endl; // Hello, John!
    return 0;
}
```

**Lambda function (anonymous function):** useful for short, inline logic - especially when passing a function to an algorithm.

```cpp
#include <iostream>

int main() {
    // Syntax: [capture](parameters) { body }
    // The [] is the capture list - leave empty if the lambda doesn't use outer variables
    auto add = [](int a, int b) { return a + b; };
    std::cout << add(1, 2) << std::endl;  // 3

    auto greet = [](const std::string& name) { return "Hello, " + name + "!"; };
    std::cout << greet("John") << std::endl;  // Hello, John!

    return 0;
}
```

**Default parameters:** a parameter with a default value is optional at the call site.

```cpp
// If the caller doesn't pass a name, "World" is used automatically
std::string greet(const std::string& name = "World") {
    return "Hello, " + name + "!";
}

// greet()        => "Hello, World!"
// greet("John")  => "Hello, John!"
```

📖 Reference: [C++ - Functions](https://en.cppreference.com/w/cpp/language/functions)

---

### 3.8 `std::format`

`std::format` (C++20) embeds values directly into a string using `{}` placeholders - similar to Python f-strings.

```cpp
#include <iostream>
#include <format>
#include <string>

int main() {
    std::string name = "John";
    int age = 30;

    // {} is replaced with the corresponding argument in order
    std::string greeting = std::format("Hello, my name is {} and I am {} years old", name, age);
    std::cout << greeting << std::endl;
    // Hello, my name is John and I am 30 years old

    // Expressions can be used directly as arguments
    std::cout << std::format("Next year I will be {} years old", age + 1) << std::endl;
    // Next year I will be 31 years old

    return 0;
}
```

📖 Reference: [C++ - std::format](https://en.cppreference.com/w/cpp/utility/format/format)

---

### 3.9 Classes

A class is a blueprint for creating objects. It bundles data (member variables) and behaviour (methods) together. In C++, members are `private` by default - use `public` to expose them to callers.

```cpp
#include <iostream>
#include <string>
#include <format>

class Person {
private:
    // Private members - only accessible inside the class
    std::string name;
    int age;

public:
    // Constructor - called automatically when you create a Person object.
    // The initialiser list ": name(name), age(age)" sets the members
    // before the constructor body runs (more efficient than assigning inside {})
    Person(const std::string& name, int age) : name(name), age(age) {}

    // const after the method signature means this method won't modify the object
    std::string greet() const {
        return std::format("Hello, my name is {} and I am {} years old", name, age);
    }
};

int main() {
    Person john("John", 30);
    std::cout << john.greet() << std::endl;
    // Hello, my name is John and I am 30 years old

    return 0;
}
```

📖 Reference: [C++ - Classes](https://en.cppreference.com/w/cpp/language/classes)

---

### 3.10 Vectors

A `std::vector` is a resizable, ordered container. Elements are accessed by zero-based index.

```cpp
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<std::string> fruits = {"Apple", "Banana", "Cherry"};

    std::cout << fruits[0] << std::endl;      // Apple  (index from the front)
    std::cout << numbers.back() << std::endl; // 5      (.back() returns the last element)

    return 0;
}
```

**2D vectors** - a vector of vectors, useful for grids or matrices:

```cpp
#include <iostream>
#include <vector>
#include <string>

int main() {
    // Each inner vector is a row
    std::vector<std::vector<int>> grid = {
        {1, 2, 3},
        {4, 5, 6}
    };

    // Access with [row][column]
    std::cout << grid[0][0] << std::endl; // 1  (row 0, column 0)
    std::cout << grid[1][2] << std::endl; // 6  (row 1, column 2)

    // Inner vectors don't have to be the same length
    std::vector<std::vector<int>> jagged = {
        {1, 2, 3},
        {4, 5},
        {6}
    };

    return 0;
}
```

📖 Reference: [C++ - std::vector](https://en.cppreference.com/w/cpp/container/vector)

---

### 3.11 Structured Bindings

Structured bindings (C++17) let you unpack a pair, tuple, or struct into named variables in one line - making iteration over maps much cleaner.

```cpp
#include <iostream>
#include <tuple>
#include <map>

int main() {
    // Unpack a pair into two named variables
    std::pair<std::string, int> person = {"John", 30};
    auto [name, age] = person;  // name = "John", age = 30

    std::cout << name << std::endl; // John
    std::cout << age  << std::endl; // 30

    // Unpack a tuple (works for any number of elements)
    auto coords = std::make_tuple(10, 20, 30);
    auto [x, y, z] = coords;  // x = 10, y = 20, z = 30

    // Structured bindings shine when iterating over a map
    // Each entry is a std::pair<key, value> - binding gives it readable names
    std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 82}};
    for (const auto& [student, score] : scores) {
        std::cout << student << ": " << score << std::endl;
    }
    // Alice: 95
    // Bob: 82

    return 0;
}
```

📖 Reference: [C++ - Structured Bindings](https://en.cppreference.com/w/cpp/language/structured_binding)

---

### 3.12 Copying and Merging Collections

Unlike Python's `*` unpacking operator, C++ uses assignment for copies and `.insert()` for merging.

```cpp
#include <iostream>
#include <vector>
#include <map>

int main() {
    // --- Vectors ---

    std::vector<int> numbers = {1, 2, 3};

    // Copy: assignment creates an independent copy
    std::vector<int> copy_of_numbers = numbers;  // {1, 2, 3}

    // Merge: insert the contents of one vector into another
    std::vector<int> more_numbers = {4, 5, 6};
    std::vector<int> merged = numbers;
    // insert(position, range_begin, range_end)
    merged.insert(merged.end(), more_numbers.begin(), more_numbers.end());
    // merged: {1, 2, 3, 4, 5, 6}

    // --- Maps ---

    std::map<std::string, int> person = {{"age", 30}, {"score", 95}};

    // Copy: same as vectors - assignment copies the whole map
    std::map<std::string, int> copy_of_person = person;

    // Merge: insert all entries from another map
    std::map<std::string, int> extra = {{"level", 5}, {"bonus", 10}};
    std::map<std::string, int> merged_person = person;
    merged_person.insert(extra.begin(), extra.end());
    // merged_person: {age:30, bonus:10, level:5, score:95}

    return 0;
}
```

📖 Reference: [C++ - Parameter pack](https://en.cppreference.com/w/cpp/language/parameter_pack)

---

### 3.13 `std::transform`

`std::transform` applies a function to every element in a container and writes the results to an output container - equivalent to Python's `map()`.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Pre-allocate the output vector to the same size as the input
    std::vector<int> squared(numbers.size());

    // transform(input_begin, input_end, output_begin, function)
    std::transform(numbers.begin(), numbers.end(), squared.begin(),
                   [](int num) { return num * num; });
    // squared: {1, 4, 9, 16, 25}

    // You can also store the lambda separately and pass it by name
    auto cube = [](int num) { return num * num * num; };
    std::vector<int> cubed(numbers.size());
    std::transform(numbers.begin(), numbers.end(), cubed.begin(), cube);
    // cubed: {1, 8, 27, 64, 125}

    return 0;
}
```

Execution model:

```
Input          Callback              Output
1  ──────────▶ [](int n){ n*n } ───▶ 1
2  ──────────▶ [](int n){ n*n } ───▶ 4
3  ──────────▶ [](int n){ n*n } ───▶ 9
4  ──────────▶ [](int n){ n*n } ───▶ 16
5  ──────────▶ [](int n){ n*n } ───▶ 25
```

📖 Reference: [C++ - std::transform](https://en.cppreference.com/w/cpp/algorithm/transform)

---

### 3.14 `std::copy_if`

`std::copy_if` copies only the elements that satisfy a predicate into a new container - equivalent to Python's `filter()`.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::vector<int> evens;

    // copy_if(input_begin, input_end, output_inserter, predicate)
    // std::back_inserter grows the output vector automatically as elements are added
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(evens),
                 [](int num) { return num % 2 == 0; });
    // evens: {2, 4}

    // Named predicate - identical result, just more readable
    auto is_even = [](int num) { return num % 2 == 0; };
    std::vector<int> evens2;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(evens2), is_even);
    // evens2: {2, 4}

    return 0;
}
```

Execution model:

```
Input          Predicate                    Output
1  ──────────▶ [](int n){ n%2==0 } ───────▶ removed
2  ──────────▶ [](int n){ n%2==0 } ───────▶ 2
3  ──────────▶ [](int n){ n%2==0 } ───────▶ removed
4  ──────────▶ [](int n){ n%2==0 } ───────▶ 4
5  ──────────▶ [](int n){ n%2==0 } ───────▶ removed
```

📖 Reference: [C++ - std::copy_if](https://en.cppreference.com/w/cpp/algorithm/copy)

---

### 3.15 `std::accumulate`

`std::accumulate` (from `<numeric>`) reduces a container to a single value by repeatedly applying a function - equivalent to Python's `reduce()`.

```cpp
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // accumulate(begin, end, initial_value, function)
    // Starts with the initial value, then applies the function to each element
    int total = std::accumulate(numbers.begin(), numbers.end(), 0,
                                [](int acc, int num) { return acc + num; });
    std::cout << total << std::endl; // 15  (0+1+2+3+4+5)

    // A different initial value shifts the result
    auto add = [](int acc, int num) { return acc + num; };
    int total2 = std::accumulate(numbers.begin(), numbers.end(), 5, add);
    std::cout << total2 << std::endl; // 20  (5+1+2+3+4+5)

    return 0;
}
```

Execution model (initial value = 5):

```
Input          Callback                          Accumulator
1  ──────────▶ [](int acc, int n){ acc+n } ────▶ 5  + 1  = 6
2  ──────────▶ [](int acc, int n){ acc+n } ────▶ 6  + 2  = 8
3  ──────────▶ [](int acc, int n){ acc+n } ────▶ 8  + 3  = 11
4  ──────────▶ [](int acc, int n){ acc+n } ────▶ 11 + 4  = 15
5  ──────────▶ [](int acc, int n){ acc+n } ────▶ 15 + 5  = 20
```

📖 Reference: [C++ - std::accumulate](https://en.cppreference.com/w/cpp/algorithm/accumulate)

---

### 3.16 Maps

A `std::map` stores key-value pairs sorted by key. Keys must be unique. Access a value by its key using `[]` or `.at()`.

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    // Initialise with brace syntax
    std::map<std::string, int> person = {
        {"age", 25},
        {"score", 95}
    };

    // Access by key - [] inserts a default value if the key doesn't exist
    std::cout << person["age"] << std::endl;    // 25

    // .at() is safer - throws an exception if the key is missing
    std::cout << person.at("score") << std::endl; // 95

    // Add or update an entry
    person["level"] = 3;

    return 0;
}
```

Maps can hold vector values:

```cpp
#include <map>
#include <vector>
#include <string>

int main() {
    // Map where each value is a vector of strings
    std::map<std::string, std::vector<std::string>> person = {
        {"favourite_fruits", {"Apple", "Banana", "Cherry"}}
    };

    std::cout << person["favourite_fruits"][0] << std::endl; // Apple

    return 0;
}
```

A vector of maps is useful for storing collections of records:

```cpp
#include <vector>
#include <map>
#include <string>

int main() {
    std::vector<std::map<std::string, int>> people = {
        {{"age", 25}, {"score", 95}},
        {{"age", 20}, {"score", 82}}
    };

    std::cout << people[0]["age"]   << std::endl; // 25
    std::cout << people[1]["score"] << std::endl; // 82

    return 0;
}
```

> We use the map initialiser list syntax `{}` in this course rather than inserting entries one by one.

📖 Reference: [C++ - std::map](https://en.cppreference.com/w/cpp/container/map)

---

### 3.17 Erase-Remove Idiom

`std::copy_if` produces a **filtered copy**. When you need to remove elements from an existing vector **in-place**, use the erase-remove idiom instead. It works in two steps:

1. `std::remove_if` shifts unwanted elements to the end and returns an iterator to the first unwanted element - the vector's size is unchanged at this point.
2. `.erase()` truncates the vector at that iterator, actually removing the elements.

```cpp
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};

    // Step 1 + 2 combined: remove all odd numbers in-place
    numbers.erase(
        std::remove_if(numbers.begin(), numbers.end(),
                       [](int n) { return n % 2 != 0; }),  // predicate: true = remove
        numbers.end()
    );
    // numbers: {2, 4, 6}

    return 0;
}
```

Visualisation of the two steps:

```
Before:                  {1, 2, 3, 4, 5, 6}
After std::remove_if:    {2, 4, 6, ?, ?, ?}  ← iterator points here
After .erase():          {2, 4, 6}
```

| Approach                    | When to use                                  |
| --------------------------- | -------------------------------------------- |
| `std::copy_if` → new vector | Keep the original; work with a filtered copy |
| Erase-remove idiom          | Modify the existing vector in-place          |

📖 Reference: [C++ - std::remove_if](https://en.cppreference.com/w/cpp/algorithm/remove)

---

### 3.18 STL Search Algorithms

Several tasks require finding elements in a container. These algorithms all return **iterators** - dereference with `*` to get the actual value, or use `->` to access a member.

#### `std::max_element`

Returns an iterator to the largest element. Supply a comparator lambda to compare structs by a specific field.

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2};

    // Without a comparator - finds the largest int
    auto it = std::max_element(numbers.begin(), numbers.end());
    // *it == 9  (dereference to get the value)

    // With a struct and a custom comparator
    struct Employee { std::string name; double salary; };
    std::vector<Employee> team = {{"Alice", 85000}, {"Bob", 92000}};

    // The comparator defines what "less than" means for the comparison
    // std::max_element picks the element for which no other is "greater"
    auto top = std::max_element(team.begin(), team.end(),
        [](const Employee& a, const Employee& b) {
            return a.salary < b.salary;  // a < b → Bob wins (highest salary)
        });

    // top is an iterator; use -> to access struct members
    std::cout << top->name   << std::endl; // Bob
    std::cout << top->salary << std::endl; // 92000

    return 0;
}
```

> Always check the iterator is not `.end()` before dereferencing - `.end()` is returned for an empty range.

#### `std::min_element`

Identical to `std::max_element` but returns the smallest element. The comparator logic is the same.

#### `std::find_if`

Returns an iterator to the **first** element for which a predicate returns true.

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 3, 5, 4, 7};

    auto it = std::find_if(numbers.begin(), numbers.end(),
        [](int n) { return n % 2 == 0; });  // first even number

    if (it != numbers.end()) {
        std::cout << *it << std::endl; // 4
    }

    return 0;
}
```

#### Quick reference

| Algorithm                     | What it returns                          |
| ----------------------------- | ---------------------------------------- |
| `std::max_element(b, e, cmp)` | Iterator to the largest element          |
| `std::min_element(b, e, cmp)` | Iterator to the smallest element         |
| `std::find_if(b, e, pred)`    | Iterator to the first matching element   |
| `std::count_if(b, e, pred)`   | Count of elements matching the predicate |
| `std::any_of(b, e, pred)`     | `true` if at least one element matches   |
| `std::all_of(b, e, pred)`     | `true` if every element matches          |

📖 Reference: [C++ - Algorithm library](https://en.cppreference.com/w/cpp/algorithm)

---

### 3.19 Sorting

`std::sort` rearranges elements in-place. Without a comparator it sorts in ascending order. Provide a lambda to sort by custom criteria or in descending order.

```cpp
#include <algorithm>
#include <vector>
#include <string>

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9};

    // Default: ascending order
    std::sort(numbers.begin(), numbers.end());
    // {1, 2, 5, 8, 9}

    // Descending: the comparator returns true when a should come before b
    // Here a > b means larger values come first
    std::sort(numbers.begin(), numbers.end(),
        [](int a, int b) { return a > b; });
    // {9, 8, 5, 2, 1}

    // Sorting structs by a field
    struct Student { std::string name; double gpa; };
    std::vector<Student> students = {{"Charlie", 3.1}, {"Alice", 3.9}, {"Bob", 3.4}};

    // Sort by GPA descending - highest first
    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.gpa > b.gpa;
        });
    // Alice (3.9), Bob (3.4), Charlie (3.1)

    return 0;
}
```

To get only the top N elements, sort the whole vector and take the first N:

```cpp
std::sort(students.begin(), students.end(),
    [](const Student& a, const Student& b) { return a.gpa > b.gpa; });

int n = 2;
// std::min guards against requesting more elements than exist
std::vector<Student> top_n(students.begin(),
    students.begin() + std::min(n, (int)students.size()));
// top_n: Alice, Bob
```

📖 Reference: [C++ - std::sort](https://en.cppreference.com/w/cpp/algorithm/sort)

---

### 3.20 Inheritance and Virtual Functions

Inheritance lets a child class build on a parent class, reusing its members and overriding methods to provide specialised behaviour.

```cpp
#include <iostream>
#include <string>

// Base class - defines common interface and shared behaviour
class Animal {
protected:
    // protected: accessible inside this class and in child classes,
    // but not from outside
    std::string name;

public:
    Animal(const std::string& name) : name(name) {}

    // virtual - marks this method as overridable by child classes
    virtual std::string speak() const {
        return name + " makes a sound";
    }

    // Always declare the destructor virtual in a base class.
    // This ensures the correct destructor runs when deleting via a base pointer.
    virtual ~Animal() {}
};

// Child class - inherits everything from Animal
class Dog : public Animal {
public:
    // Call the parent constructor via the initialiser list
    Dog(const std::string& name) : Animal(name) {}

    // override - explicitly marks this as replacing the parent's speak()
    // The compiler will error if the signature doesn't match the parent
    std::string speak() const override {
        return name + " barks";
    }
};

int main() {
    Dog d("Rex");
    std::cout << d.speak() << std::endl;  // Rex barks
    return 0;
}
```

#### Pure virtual functions and abstract classes

A pure virtual function (`= 0`) has no implementation in the base class. Any class with at least one pure virtual function is **abstract** - you cannot create objects of it directly. Child classes must override every pure virtual function.

```cpp
// Shape is abstract - it defines an interface that all shapes must follow
class Shape {
public:
    // = 0 means "no implementation here; subclasses must provide one"
    virtual double area() const = 0;
    virtual std::string describe() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}

    // Must implement both pure virtual methods or Circle is also abstract
    double area() const override {
        return 3.14159 * radius * radius;
    }

    std::string describe() const override {
        return "Circle with radius " + std::to_string(radius);
    }
};

int main() {
    // Shape s;     // ERROR - cannot instantiate an abstract class
    Circle c(5.0);
    std::cout << c.area() << std::endl; // 78.54
    return 0;
}
```

#### Calling the parent constructor

Use the initialiser list to call the parent's constructor before your own initialisation runs:

```cpp
class Payment {
protected:
    double amount;
    std::string currency;
public:
    Payment(double amount, std::string currency = "USD")
        : amount(amount), currency(currency) {}
};

class CreditCardPayment : public Payment {
    std::string card_number;
public:
    // Payment(...) in the initialiser list runs the parent constructor first,
    // then card_number(card) initialises the child's own member
    CreditCardPayment(double amount, std::string currency, std::string card)
        : Payment(amount, currency), card_number(card) {}
};
```

#### Key terms

| Term              | Meaning                                                                    |
| ----------------- | -------------------------------------------------------------------------- |
| `virtual`         | Method can be overridden in a child class                                  |
| `= 0`             | Pure virtual - child class must implement this                             |
| `override`        | Explicitly marks a method as overriding a parent method (compiler-checked) |
| Abstract class    | A class with at least one pure virtual method; cannot be instantiated      |
| `protected:`      | Accessible in the class and its children, but not from outside             |
| `virtual ~Base()` | Virtual destructor - always include in base classes                        |

📖 Reference: [C++ - Virtual functions](https://en.cppreference.com/w/cpp/language/virtual)

---

### 3.21 Smart Pointers

Raw pointers (`new` / `delete`) require manual memory management. Smart pointers automate this - they free memory automatically when no longer needed.

#### `std::shared_ptr`

`shared_ptr` uses reference counting: multiple `shared_ptr`s can share ownership of one object. The object is destroyed when the last owner goes out of scope. Always create them with `std::make_shared`.

```cpp
#include <memory>
#include <iostream>

class Dog {
public:
    std::string name;
    Dog(std::string n) : name(n) {}
};

int main() {
    // make_shared allocates the object and wraps it in a shared_ptr
    // Prefer make_shared over "new" - it's safer and more efficient
    auto dog = std::make_shared<Dog>("Rex");

    // Access members with -> just like a raw pointer
    std::cout << dog->name << std::endl;  // Rex

    // Both variables now point to the same Dog - the count is 2
    auto same_dog = dog;

    // When both go out of scope, the count drops to 0 and Dog is automatically destroyed

    return 0;
}
```

#### Polymorphism with `shared_ptr`

Store child-class objects behind a base-class `shared_ptr`. This lets you hold different payment types in one vector and call virtual methods through the base pointer.

```cpp
#include <memory>
#include <vector>

std::vector<std::shared_ptr<Payment>> transactions;

auto cc     = std::make_shared<CreditCardPayment>(100.0, "USD", "1234");
auto crypto = std::make_shared<CryptoPayment>(500.0, "USD", "0xABC", "Bitcoin");

transactions.push_back(cc);
transactions.push_back(crypto);

// Virtual dispatch - calls the correct get_fee() for each concrete type at runtime
for (auto& payment : transactions) {
    std::cout << payment->get_fee() << std::endl;
}
```

#### Getting the type name at runtime

Add a virtual `get_type()` method to the base class. This is cleaner and more portable than `typeid`, whose name format varies between compilers.

```cpp
class Payment {
public:
    // Each child class returns its own type name as a string
    virtual std::string get_type() const = 0;
};

class CreditCardPayment : public Payment {
public:
    std::string get_type() const override { return "CreditCardPayment"; }
};

// Filter a mixed transaction vector to get only credit card payments
std::vector<std::shared_ptr<Payment>> cc_only;
std::copy_if(transactions.begin(), transactions.end(), std::back_inserter(cc_only),
    [](const std::shared_ptr<Payment>& p) {
        return p->get_type() == "CreditCardPayment";
    });
```

📖 Reference: [C++ - std::shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr)

---

### 3.22 Timestamps with `std::chrono`

`std::chrono` is the standard C++ library for time. Use it to capture the current moment when an object is constructed.

```cpp
#include <chrono>
#include <ctime>
#include <string>

int main() {
    // Capture the current time as a time_point
    auto now = std::chrono::system_clock::now();

    // Convert to time_t so we can format it as a human-readable string
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    // std::ctime converts to a string like "Thu Feb  1 14:22:07 2024\n"
    std::string timestamp = std::ctime(&t);

    return 0;
}
```

Storing a timestamp in a class:

```cpp
class Event {
protected:
    // Store the raw time_point - convert to string only when needed
    std::chrono::system_clock::time_point timestamp;

public:
    Event() : timestamp(std::chrono::system_clock::now()) {}
    // timestamp is automatically set to "now" whenever an Event is created
};
```

📖 Reference: [C++ - std::chrono](https://en.cppreference.com/w/cpp/chrono)

---

### 3.23 User Input with `std::cin`

`std::cin` reads values typed at the terminal. It is the input counterpart to `std::cout`.

```cpp
#include <iostream>
#include <string>

int main() {
    // Reading a single value - stops at whitespace
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;
    std::cout << "You entered " << number << std::endl;

    // Reading a full line (including spaces)
    std::string sentence;
    std::cout << "Enter a sentence: ";
    std::getline(std::cin, sentence);
    std::cout << "You entered: " << sentence << std::endl;

    return 0;
}
```

Reading input in a game loop:

```cpp
std::string choice;

while (true) {
    std::cout << "Hit or stand? ";
    std::cin >> choice;

    if (choice == "hit") {
        // deal a card
    } else if (choice == "stand") {
        break;  // exit the loop
    } else {
        // re-prompt for unrecognised input
        std::cout << "Invalid choice, try again." << std::endl;
    }
}
```

**Important: mixing `>>` and `getline`**

`std::cin >>` leaves a newline character in the input buffer. If you call `std::getline` immediately after, it reads that leftover newline as an empty string. Fix this with `std::cin.ignore()`:

```cpp
int age;
std::cout << "Enter your age: ";
std::cin >> age;
std::cin.ignore();  // discard the leftover newline from the buffer

std::string name;
std::cout << "Enter your name: ";
std::getline(std::cin, name);  // now reads the full line correctly
```

📖 Reference: [C++ - std::cin](https://en.cppreference.com/w/cpp/io/cin)

---

### 3.24 Random Shuffling with `std::shuffle`

`std::shuffle` randomises the order of elements in a range. It requires a random number engine - use `std::mt19937` seeded from `std::random_device` for a different result each run.

```cpp
#include <algorithm>  // std::shuffle
#include <random>     // std::mt19937, std::random_device
#include <vector>

int main() {
    std::vector<int> deck = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // std::random_device{} provides a hardware entropy seed (true randomness)
    // std::mt19937 is a fast, high-quality pseudo-random engine
    // Seeding from random_device ensures a different shuffle every run
    std::mt19937 rng(std::random_device{}());

    // Shuffle the entire deck in-place
    std::shuffle(deck.begin(), deck.end(), rng);
    // e.g. {7, 2, 10, 1, 5, 3, 9, 4, 6, 8}

    return 0;
}
```

| Component              | Purpose                                                |
| ---------------------- | ------------------------------------------------------ |
| `std::random_device{}` | Provides hardware entropy for seeding                  |
| `std::mt19937`         | Pseudo-random number engine (fast, high quality)       |
| `std::shuffle`         | Uses the engine to permute a range uniformly at random |

📖 Reference: [C++ - std::shuffle](https://en.cppreference.com/w/cpp/algorithm/random_shuffle)

---

## Exercises

Compile and run the starter file:

```bash
g++ --std=c++20 -o week-01-git-programming-paradigms-c++-1 week-01-git-programming-paradigms-c++-1.cpp
./week-01-git-programming-paradigms-c++-1
```

Expected output:

```
Hello, World!
```

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

### Task 1 - Data Pipeline

Create a function `process_data_pipeline` that takes a `std::vector<User>` and applies a series of transformations using `std::copy_if`, `std::transform`, and `std::accumulate`.

User struct:

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

The function should:

1. Filter out users with `status != "active"`
2. Filter out users under 25
3. Compute `total_spent` for each user (sum of all purchases)
4. Compute `loyalty_years` for each user (`2026 - member_since`)
5. Assign a `tier` based on `total_spent`:

| `total_spent` | Tier       |
| ------------- | ---------- |
| < 500         | `"Bronze"` |
| 500 – 999     | `"Silver"` |
| ≥ 1000        | `"Gold"`   |

6. Use `std::accumulate` to calculate total revenue from qualifying users
7. Return a `PipelineResult` struct with `processed_users`, `total_revenue`, `user_count`, and `average_spending`

```cpp
std::vector<User> users = {
    {1, "Alice",   30, {200, 400, 150}, 2019, "active"},
    {2, "Bob",     22, {100, 50},       2021, "active"},
    {3, "Charlie", 28, {500, 600},      2020, "inactive"},
    {4, "Diana",   35, {300, 200, 100}, 2018, "active"},
};

auto result = process_data_pipeline(users);
```

Expected output:

```
processed_users: Alice (total_spent: 750, loyalty_years: 7, tier: Silver),
                 Diana (total_spent: 600, loyalty_years: 8, tier: Silver)
total_revenue:   1350
user_count:      2
average_spending: 675.00
```

> Bob is excluded (age < 25). Charlie is excluded (status = `"inactive"`).

---

### Task 2 - Organisation Transformer

Create a function `transform_organisation` that enriches a nested organisation struct with computed statistics.

Input structs:

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

Add to each **team**: `total_salary`, `avg_performance` (rounded to 2 dp), `top_performer`.

Add to each **department**: `team_count`, `employee_count`, `utilisation_rate` (total salary / budget as %, rounded to 2 dp).

Add a company-level **`summary`**: `total_departments`, `total_teams`, `total_employees`, `highest_paid_employee`, `departments_over_budget` (names where `utilisation_rate > 80`).

> Use `std::accumulate`, `std::max_element`, and range-based loops where appropriate.

```cpp
Organisation org = {
    "TechCorp",
    {{
        "Engineering", 500000.0,
        {
            {"Backend",  {{"Alice", 85000, 4.5}, {"Bob", 90000, 4.8}}},
            {"Frontend", {{"Charlie", 80000, 4.2}}}
        }
    }}
};

auto result = transform_organisation(org);
```

Expected output:

```
Company: TechCorp

Department: Engineering
Budget: $500000.00, Utilisation: 51.00%, Teams: 2, Employees: 3

  Team: Backend
  Total Salary: $175000.00, Avg Performance: 4.65, Top Performer: Bob (4.80)

  Team: Frontend
  Total Salary: $80000.00, Avg Performance: 4.20, Top Performer: Charlie (4.20)

Summary:
  Total Departments: 1, Total Teams: 2, Total Employees: 3
  Highest Paid: Bob ($90000.00)
  Departments Over Budget: none
```

---

### Task 3 - Payment Processing System

Build a payment processing system using inheritance and smart pointers.

**Base class: `Payment`**

| Member / Method                                        | Description                                                                                                 |
| ------------------------------------------------------ | ----------------------------------------------------------------------------------------------------------- |
| `amount`, `currency`, `timestamp`, `status`            | Member variables (`timestamp` set via `std::chrono::system_clock::now()`, `status` defaults to `"pending"`) |
| `Payment(double amount, std::string currency = "USD")` | Constructor                                                                                                 |
| `virtual double get_fee() const = 0`                   | Pure virtual                                                                                                |
| `virtual bool process() = 0`                           | Pure virtual                                                                                                |
| `bool validate() const`                                | Returns `amount > 0`                                                                                        |
| `double get_total() const`                             | Returns `amount + get_fee()`                                                                                |
| `virtual std::string to_string() const`                | Returns formatted payment info                                                                              |

**Child classes:**

| Class                 | Extra members                                | Fee formula                                           | `process()` behaviour               |
| --------------------- | -------------------------------------------- | ----------------------------------------------------- | ----------------------------------- |
| `CreditCardPayment`   | `card_number` (last 4 digits, `std::string`) | `2.9% of amount + $0.30`                              | validate → set status → return bool |
| `CryptoPayment`       | `wallet_address`, `crypto_type`              | `1% of amount`, min $1.00                             | validate → set status → return bool |
| `BankTransferPayment` | `account_number`, `routing_number`           | `$5.00 flat` if amount < $1000, else `0.5% of amount` | validate → set status → return bool |

**`PaymentProcessor` class:**

| Method                                       | Description                                                                                                                  |
| -------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------- |
| `PaymentProcessor()`                         | Initialises empty `transactions` vector                                                                                      |
| `process_payment(shared_ptr<Payment>)`       | Calls `process()`, appends to `transactions` regardless of outcome                                                           |
| `get_transactions_by_type(string type_name)` | Returns transactions filtered by type name                                                                                   |
| `get_total_processed() const`                | Sum of `amount` for all `"completed"` transactions                                                                           |
| `get_total_fees_collected() const`           | Sum of fees for all `"completed"` transactions                                                                               |
| `generate_report() const`                    | Returns `Report` struct with `count_by_type`, `total_processed_by_type`, `average_transaction_by_type`, `total_fees_by_type` |

Example:

```cpp
PaymentProcessor processor;

auto cc     = std::make_shared<CreditCardPayment>(100.0, "USD", "1234");
auto crypto = std::make_shared<CryptoPayment>(500.0, "USD", "0xABC123", "Bitcoin");
auto bank   = std::make_shared<BankTransferPayment>(2000.0, "USD", "123456789", "987654321");

processor.process_payment(cc);
processor.process_payment(crypto);
processor.process_payment(bank);

std::cout << cc->get_fee()     << std::endl;  // 3.20   (100 * 0.029 + 0.30)
std::cout << crypto->get_fee() << std::endl;  // 5.00   (1% of 500, above $1.00 minimum)
std::cout << bank->get_fee()   << std::endl;  // 10.00  (0.5% of 2000)
```

Expected report:

```
count_by_type:               { CreditCardPayment: 1, CryptoPayment: 1, BankTransferPayment: 1 }
total_processed_by_type:     { CreditCardPayment: 100.00, CryptoPayment: 500.00, BankTransferPayment: 2000.00 }
average_transaction_by_type: { CreditCardPayment: 100.00, CryptoPayment: 500.00, BankTransferPayment: 2000.00 }
total_fees_by_type:          { CreditCardPayment: 3.20, CryptoPayment: 5.00, BankTransferPayment: 10.00 }
```

---

### Task 4 - Student Data Analysis

Build a data analysis system for student records using classes and STL algorithms.

**`Student` class:**

| Method                                                                     | Description                                                            |
| -------------------------------------------------------------------------- | ---------------------------------------------------------------------- |
| `Student(int id, string name, map<string,char> grades, double attendance)` | Constructor                                                            |
| `double get_gpa() const`                                                   | A=4.0, B=3.0, C=2.0, D=1.0, F=0.0; returns average across all subjects |
| `string get_status() const`                                                | `"Honors"` (GPA ≥ 3.5), `"Good Standing"` (GPA ≥ 2.0), `"Probation"`   |
| `bool is_at_risk() const`                                                  | `true` if GPA < 2.0 or attendance < 75                                 |

**`Analyser` class:**

| Method                                   | Description                                                                                               |
| ---------------------------------------- | --------------------------------------------------------------------------------------------------------- |
| `Analyser(vector<Student>)`              | Constructor                                                                                               |
| `get_top_students(int n)`                | Top n students by GPA descending                                                                          |
| `get_subject_statistics(string subject)` | Returns `SubjectStats` with `average_gpa`, `grade_distribution`, `passing_rate` (% scoring C or better)   |
| `identify_struggling_students()`         | Students where `is_at_risk()` is true                                                                     |
| `calculate_correlations()`               | Returns `data_points` (pairs of attendance, GPA) and `interpretation` string                              |
| `generate_comprehensive_report()`        | Returns `Report` with `overall`, `status_distribution`, `subjects`, `at_risk_students`, `recommendations` |

> Use `std::transform`, `std::copy_if`, `std::accumulate`, range-based for loops, and `std::map` where appropriate.

Example setup:

```cpp
std::vector<Student> students = {
    {1, "Alice",   {{"Math",'A'},{"Science",'B'},{"English",'A'}}, 95},
    {2, "Bob",     {{"Math",'C'},{"Science",'D'},{"English",'B'}}, 70},
    {3, "Charlie", {{"Math",'B'},{"Science",'B'},{"English",'B'}}, 88},
    {4, "Diana",   {{"Math",'A'},{"Science",'A'},{"English",'A'}}, 98},
    {5, "Eve",     {{"Math",'F'},{"Science",'D'},{"English",'C'}}, 65},
};

Analyser analyser(students);
```

Expected report:

```
overall: total_students: 5, average_gpa: 2.73, average_attendance: 83.20
status_distribution: Honors: 2, Good Standing: 2, Probation: 1

subjects:
  Math:    average_gpa: 3.00, grade_distribution: [A:2, B:1, C:1, F:1], passing_rate: 80.00%
  Science: average_gpa: 2.40, grade_distribution: [A:1, B:2, D:2],      passing_rate: 60.00%
  English: average_gpa: 3.20, grade_distribution: [A:2, B:2, C:1],      passing_rate: 100.00%

at_risk_students: Bob, Eve

recommendations:
  - Focus on improving attendance for at-risk students
  - Provide additional support in Math and Science for struggling students
  - Recognise and reward high performers to encourage continued success
```

---

### Task 5 - Blackjack Game

Build a complete, playable command-line Blackjack game using OOP.

**Game rules:**

- Goal: get closer to 21 than the dealer without going over
- Face cards (J, Q, K) = 10; Aces = 11 or 1 (whichever avoids a bust); number cards = face value
- Dealer must hit on ≤ 16, stand on ≥ 17
- Players can hit or stand

**Required classes:**

| Class           | Key members                                  | Key methods                                                                                                                                            |
| --------------- | -------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `Card`          | `rank`, `suit`                               | `get_value()`, `to_string()`                                                                                                                           |
| `Deck`          | `std::vector<Card> cards`                    | `shuffle()`, `deal_card()`, `cards_remaining()`, `reset()`                                                                                             |
| `Hand`          | `std::vector<Card> cards`                    | `add_card()`, `get_value()`, `is_blackjack()`, `is_bust()`, `to_string()`                                                                              |
| `Player`        | `name`, `hand`                               | `to_string()`                                                                                                                                          |
| `Dealer`        | `Hand hand`, `name`                          | `show_partial_hand()`, `show_full_hand()`, `should_hit()`, `to_string()`                                                                               |
| `BlackjackGame` | `deck`, `dealer`, `players`, `current_round` | `start_round()`, `deal_initial_cards()`, `player_turn()`, `dealer_turn()`, `determine_winners()`, `display_game_state()`, `play_game()`, `game_over()` |

**`Hand::get_value()` logic:** Count each Ace as 11. If the total exceeds 21, recount Aces as 1 one at a time until the hand is ≤ 21 or no Aces remain.

**Game flow:**

1. Display a welcome message with player names
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

```cpp
BlackjackGame game({"Alice", "Bob"});
game.play_game();
```
