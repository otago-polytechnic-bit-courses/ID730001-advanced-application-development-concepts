# ID730001: Advanced Application Development Concepts

---

## Part 1: Blackjack Application - Development Phase - Learning Outcomes 1 and 2

### Project Management (2 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                    |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 1.6-2   | GitHub Project set up with Backlog, In Progress and Done columns. Issues created for each task and moved across columns as work progresses. Sprint breakdown is clear and consistent use is demonstrable across the full assessment period. |
| B    | 1.3-1.5 | GitHub Project set up with required columns. Most tasks tracked as issues. Sprint planning present. Some gaps in consistent use.                                                                                                            |
| C    | 1-1.2   | GitHub Project exists but use is inconsistent. Some tasks tracked as issues but columns not used systematically.                                                                                                                            |
| D/E  | 0-0.9   | GitHub Project not set up or rarely used. Tasks not tracked as issues. No clear sprint breakdown.                                                                                                                                           |

### Core Game (8 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                                                                  |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 6.4-8   | All six required classes implemented with the correct attributes and methods. Hand value correctly handles Aces as 11 or 1. Scoring system implemented as specified. Split and surrender actions work correctly. Dealer follows the hit/stand rules. Game flow matches the specification including welcome message, round structure, leaderboard, and player elimination. |
| B    | 5.1-6.3 | All six classes present and mostly functional. Most game rules and flow implemented correctly. Minor issues with edge cases such as Ace handling, split, or surrender.                                                                                                                                                                                                    |
| C    | 4-5     | Most classes present but some are incomplete or have functional issues. Core game loop works but some rules or actions are missing or incorrect.                                                                                                                                                                                                                          |
| D/E  | 0-3.9   | Several classes missing or non-functional. Game loop does not work correctly. Major rules or actions absent.                                                                                                                                                                                                                                                              |

### Design Patterns

#### Strategy Pattern - Compulsory (3 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                           |
| ---- | ------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 2.4-3   | `DrawStrategy` interface implemented with all four required concrete strategies - `HumanStrategy`, `BasicStrategy`, `ConservativeStrategy`, and `AggressiveStrategy`. Bot strategies follow the basic strategy tables. Players are configurable with any strategy at construction. The game loop does not branch on strategy type. |
| B    | 1.9-2.3 | All four strategies present and mostly correct. Minor issues with basic strategy table accuracy or strategy configuration. Game loop mostly decoupled from strategy type.                                                                                                                                                          |
| C    | 1.5-1.8 | Strategy interface implemented but one or more strategies are missing or incorrect. Some coupling between the game loop and strategy type.                                                                                                                                                                                         |
| D/E  | 0-1.4   | Strategy pattern absent or not meaningfully implemented. Strategies missing or game loop branches on player type.                                                                                                                                                                                                                  |

#### Chosen Pattern - Observer, Factory, or Builder (3 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                          |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 2.4-3   | The chosen pattern is fully and correctly implemented. Both required concrete implementations are present and functional. The pattern is meaningfully integrated - it adds clear value to the design and matches the approved Practical document. |
| B    | 1.9-2.3 | Pattern implemented and mostly correct. Both concrete implementations present with minor issues. Integration is reasonable.                                                                                                                       |
| C    | 1.5-1.8 | Pattern partially implemented. One concrete implementation may be missing or incorrect. Integration feels superficial.                                                                                                                            |
| D/E  | 0-1.4   | Pattern absent, incorrect, or does not match the approved design.                                                                                                                                                                                 |

#### Two Additional Patterns (6 marks)

| Band | Marks   | Criteria                                                                                                                                                                                   |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| A    | 4.8-6   | Both additional patterns fully implemented, meaningfully integrated, and distinct from each other and from the two patterns above. Implementation matches the approved Practical document. |
| B    | 3.8-4.7 | Both patterns present and mostly correct. Integration is reasonable. Minor issues with one pattern.                                                                                        |
| C    | 3-3.7   | One pattern well implemented; the other is incomplete or poorly integrated.                                                                                                                |
| D/E  | 0-2.9   | One or both patterns absent, non-functional, or artificially bolted on.                                                                                                                    |

### Concurrency (4 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                      |
| ---- | ------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 3.2-4   | The chosen concurrency option fully implemented and matches the approved Practical document. Runs concurrently without blocking the main game loop. Thread safety handled correctly using appropriate synchronisation primitives. No race conditions or deadlocks. Behaviour matches the specification for the chosen option. |
| B    | 2.6-3.1 | Concurrency implemented and mostly functional. Runs concurrently. Minor issues with synchronisation or edge case behaviour.                                                                                                                                                                                                   |
| C    | 2-2.5   | Concurrency partially implemented. May block the game loop or have synchronisation issues. Core behaviour present but incomplete.                                                                                                                                                                                             |
| D/E  | 0-1.9   | Concurrency absent or non-functional. Causes blocking, race conditions, or deadlocks.                                                                                                                                                                                                                                         |

### Persistent Statistics with a Relational Database (6 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                                                                        |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 4.8-6   | `GameDatabase` class implemented with all required methods. Schema matches the specification with all four tables and correct relationships. Foreign key enforcement enabled. All write operations use transactions. `getPlayerSummary` and `getLeaderboard` produce correctly formatted output. `BlackjackGame` records every session, round and result as the game is played. |
| B    | 3.8-4.7 | All required methods present and mostly functional. Schema correct with minor issues. Transactions used for most writes. Output mostly matches the specification.                                                                                                                                                                                                               |
| C    | 3-3.7   | Most methods implemented but some missing or incorrect. Schema partially correct. Transactions inconsistently used. Output present but not fully matching the specification.                                                                                                                                                                                                    |
| D/E  | 0-2.9   | Database integration largely absent or non-functional. Schema incorrect or missing tables. No transaction use.                                                                                                                                                                                                                                                                  |

### Functional Programming (2 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                |
| ---- | ------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 1.6-2   | Standalone module implemented with an `analyseSession` function (or idiomatic equivalent). All three computations performed using `map`, `filter`, and `reduce` equivalents with no explicit loops or list comprehensions. Results returned in a single data structure. |
| B    | 1.3-1.5 | Module present and most computations correct. Minor use of loops or list comprehensions in one computation.                                                                                                                                                             |
| C    | 1-1.2   | Module present but some computations missing or using loops instead of functional constructs.                                                                                                                                                                           |
| D/E  | 0-0.9   | Module absent or does not use functional constructs. Computations use loops throughout.                                                                                                                                                                                 |

---

## Code Quality and Best Practices - Learning Outcomes 1 and 2 (11 marks)

### Code Organisation (3 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                           |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| A    | 2.4-3   | Code split across clearly named modules matching the required structure. Each module has a single, clearly defined responsibility. No function exceeds 30 lines. No global state - dependencies passed explicitly. |
| B    | 1.9-2.3 | Modules mostly match the required structure. Responsibilities mostly clear. Most functions within 30 lines. Minimal global state.                                                                                  |
| C    | 1.5-1.8 | Module structure partially follows the requirements. Some responsibilities mixed. Some functions exceed 30 lines. Some global state.                                                                               |
| D/E  | 0-1.4   | Little to no module structure. Responsibilities not separated. Functions frequently exceed 30 lines. Global state used throughout.                                                                                 |

### Code Style and Formatting (2 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                               |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| A    | 1.6-2   | Code passes a linting tool with no errors or significant warnings. Consistent formatting throughout. Naming conventions of the chosen language followed consistently. All names are meaningful and descriptive. Type annotations or hints on all function signatures where the language supports them. |
| B    | 1.3-1.5 | Code mostly passes linting with minor warnings. Formatting mostly consistent. Naming conventions generally followed. Most names descriptive. Type annotations mostly present.                                                                                                                          |
| C    | 1-1.2   | Linting errors present. Formatting inconsistent. Naming conventions not always followed. Some names unclear. Type annotations missing in several places.                                                                                                                                               |
| D/E  | 0-0.9   | Code does not pass linting. No consistent formatting. Poor naming throughout. Type annotations largely absent.                                                                                                                                                                                         |

### Use of OOP Principles (2 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                  |
| ---- | ------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 1.6-2   | Encapsulation applied consistently - internal state accessed through methods or properties. `Dealer` inherits from a base class or shared interface with `Player`. Polymorphism used so the game loop can call player methods without branching on type. No unnecessary code duplication. |
| B    | 1.3-1.5 | OOP principles mostly applied. Inheritance and polymorphism present with minor issues. Some minor code duplication.                                                                                                                                                                       |
| C    | 1-1.2   | Some OOP principles applied but inconsistently. Inheritance or polymorphism may be missing or poorly used. Some code duplication.                                                                                                                                                         |
| D/E  | 0-0.9   | OOP principles largely absent. No meaningful inheritance or polymorphism. Significant code duplication.                                                                                                                                                                                   |

### Error Handling (2 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                    |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 1.6-2   | All database operations wrapped in appropriate error handling. All command-line input validated with clear feedback for invalid options. Appropriate exceptions with descriptive messages thrown for invalid internal states. No raw stack traces or internal errors exposed to the player. |
| B    | 1.3-1.5 | Most database operations and input validated. Exceptions used in most cases. Minor gaps where errors could surface to the player.                                                                                                                                                           |
| C    | 1-1.2   | Basic error handling present but some database operations or inputs unhandled. Some stack traces or internal errors may appear during play.                                                                                                                                                 |
| D/E  | 0-0.9   | Little or no error handling. Unhandled errors crash the application. Stack traces exposed to the player.                                                                                                                                                                                    |

### Version Control (2 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                      |
| ---- | ------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 1.6-2   | Commit messages follow a conventional commit format consistently (e.g., `feat:`, `fix:`, `refactor:`). Messages are descriptive and reflect the context of each change. Commits are small and focused throughout development. |
| B    | 1.3-1.5 | Most commits follow the convention and are descriptive. Mostly focused commits with minor lapses.                                                                                                                             |
| C    | 1-1.2   | Commit messages vary in quality and convention adherence. Some large or vague commits.                                                                                                                                        |
| D/E  | 0-0.9   | Commits do not follow a convention. Messages unclear or non-descriptive. Very large or infrequent commits.                                                                                                                    |

---

## Part 2: Independent Framework Research - Implementation Phase - Learning Outcomes 1 and 2

### Requirements Implementation (25 marks)

Each of the 12 requirements is marked according to the complexity band confirmed at approval:

| Band         | Marks each |
| ------------ | ---------- |
| Standard     | 1          |
| Intermediate | 2          |
| Advanced     | 3          |

| Band | Marks   | Criteria                                                                                                                                                                                                                                                         |
| ---- | ------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 20-25   | Requirements are fully implemented and clearly meet their specification. Advanced requirements demonstrate critical evaluation and non-trivial use of the framework. All implementation files committed to the `project` branch in a clearly named subdirectory. |
| B    | 16-19   | Most requirements implemented and meeting their specification. Advanced requirements mostly met with minor gaps.                                                                                                                                                 |
| C    | 12.5-15 | Several requirements implemented but some incomplete or not meeting their specification. Advanced requirements partially met.                                                                                                                                    |
| D/E  | 0-12.4  | Fewer than half the requirements implemented or meeting their specification. Little evidence of meaningful framework use.                                                                                                                                        |
