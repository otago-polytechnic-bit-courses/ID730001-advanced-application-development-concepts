# Part 1: Blackjack Application - Marking Rubric (50 marks)

---

## Design Phase (10 marks)

### Class Diagram (5 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                                                                                                                |
| ---- | ------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 4–5     | Class diagram is professionally designed and covers all required classes. Every class includes accurate attribute names and data types, complete method signatures with parameters and return types, and correct visibility modifiers. All relationships (association, composition, inheritance) are correctly identified and labelled with appropriate multiplicity. Uses proper UML notation consistently throughout. |
| B    | 3.2–3.9 | Diagram shows all required classes with most attributes, methods and relationships present. Minor omissions in method signatures or relationship labels. Multiplicity is mostly correct. Generally follows UML conventions with minor inconsistencies.                                                                                                                                                                  |
| C    | 2.5–3.1 | Diagram includes all required classes but some attributes or methods are missing or incorrectly typed. Relationships are present but may have cardinality errors or missing labels. Some notation inconsistencies.                                                                                                                                                                                                      |
| D/E  | 0–2.4   | Diagram is incomplete or poorly constructed. Significant classes, attributes or methods are missing. Relationships are absent or incorrect. Does not follow UML conventions. Difficult to use as a basis for implementation.                                                                                                                                                                                            |

---

### Design Patterns and Concurrency Plan (5 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                                                                                                    |
| ---- | ------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 4–5     | Both design patterns are clearly identified with all involved classes named and roles explained. A compelling justification is given for why each pattern is appropriate to this specific context. Pseudocode or diagrams clearly illustrate the pattern's structure. The concurrency plan identifies a concrete task, selects appropriate Python tools, and explains how thread safety will be maintained. |
| B    | 3.2–3.9 | Both patterns are described with classes and justifications present. Minor gaps in pseudocode or diagrams. Concurrency plan is present and identifies the task and tools, though thread safety discussion may lack depth.                                                                                                                                                                                   |
| C    | 2.5–3.1 | Patterns are named and classes are listed, but justifications are superficial or generic. Pseudocode or diagrams incomplete. Concurrency plan identifies a task but does not clearly address tooling or thread safety.                                                                                                                                                                                      |
| D/E  | 0–2.4   | One or both patterns are missing, incorrectly identified, or described in a way that shows little understanding. Concurrency plan is absent or shows fundamental misunderstanding of concurrent programming concepts.                                                                                                                                                                                       |

---

## Development Phase (28 marks)

### Project Management (2 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                          |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 1.6–2   | Excellent use of GitHub Project with clear sprint planning and task breakdown. Issues are well-defined with appropriate labels. Tasks move systematically through Backlog, In Progress and Done columns throughout the project. Demonstrates strong, consistent agile methodology implementation. |
| B    | 1.3–1.5 | Good project management with GitHub Project set up correctly. Most tasks are defined as issues and tracked through columns. Sprint planning is present but may lack some detail. Generally follows agile methodology.                                                                             |
| C    | 1–1.2   | Basic GitHub Project implementation. Some tasks tracked as issues but columns used inconsistently. Sprint planning minimal or unclear. Shows some understanding of agile methodology.                                                                                                             |
| D/E  | 0–0.9   | Poor project management. GitHub Project not set up or not used consistently. Tasks not tracked as issues or sprints not defined. Little or no evidence of agile methodology.                                                                                                                      |

---

### Core Game (8 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| ---- | ------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 6.4–8   | All required classes are fully and correctly implemented. `Hand.get_value()` handles Aces correctly in all edge cases. Betting and chip management work correctly across all outcomes (win, loss, tie, Blackjack). The full game loop runs without errors for multiple rounds and multiple players. Blackjack is detected and pays 1.5×. Players with 0 chips are removed. End-of-game summary is displayed. All edge cases (empty deck, all players bust, dealer bust) are handled gracefully. |
| B    | 5.2–6.3 | All required classes are implemented and the game is playable. Minor bugs in edge cases (e.g., Ace handling in rare scenarios, chip rounding). Betting and chip management mostly correct. Game loop handles multiple rounds. Most edge cases handled.                                                                                                                                                                                                                                          |
| C    | 4–5.1   | Core classes are present and the game can be played but has noticeable bugs. Ace handling may be incorrect in some scenarios. Betting logic has errors. Some game states may cause crashes or incorrect outcomes. Limited edge case handling.                                                                                                                                                                                                                                                   |
| D/E  | 0–3.9   | Core classes are incomplete or significantly broken. Game cannot be played through a full round without errors. Major logic errors in card values, hand evaluation, or game flow. Little or no working functionality.                                                                                                                                                                                                                                                                           |

---

### Design Patterns (6 marks)

_Assessed across both chosen patterns — 3 marks each._

#### Pattern 1 (3 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                                                                 |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| A    | 2.4–3   | Pattern is correctly and fully implemented. The implementation demonstrates a clear understanding of the pattern's intent. The pattern is meaningfully integrated — it adds genuine value to the design. The game loop does not need to know about concrete implementations. All required classes/strategies/observers/factories/options are implemented and functional. |
| B    | 2–2.3   | Pattern is implemented correctly with minor omissions. Integration is mostly complete. The intent of the pattern is clear. Most required classes or options are present and functional, with minor issues.                                                                                                                                                               |
| C    | 1.5–1.9 | Pattern is present but partially implemented or misapplied. The integration is superficial. Some required classes or options are missing. Shows a basic understanding of the pattern with notable gaps.                                                                                                                                                                  |
| D/E  | 0–1.4   | Pattern is missing, unrecognisable, or fundamentally incorrect. The implementation shows little or no understanding of the chosen pattern.                                                                                                                                                                                                                               |

#### Pattern 2 (3 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                                                                 |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| A    | 2.4–3   | Pattern is correctly and fully implemented. The implementation demonstrates a clear understanding of the pattern's intent. The pattern is meaningfully integrated — it adds genuine value to the design. The game loop does not need to know about concrete implementations. All required classes/strategies/observers/factories/options are implemented and functional. |
| B    | 2–2.3   | Pattern is implemented correctly with minor omissions. Integration is mostly complete. The intent of the pattern is clear. Most required classes or options are present and functional, with minor issues.                                                                                                                                                               |
| C    | 1.5–1.9 | Pattern is present but partially implemented or misapplied. The integration is superficial. Some required classes or options are missing. Shows a basic understanding of the pattern with notable gaps.                                                                                                                                                                  |
| D/E  | 0–1.4   | Pattern is missing, unrecognisable, or fundamentally incorrect. The implementation shows little or no understanding of the chosen pattern.                                                                                                                                                                                                                               |

---

### Concurrency (4 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                                                                 |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| A    | 3.2–4   | Chosen concurrency option is fully and correctly implemented. Threads are properly started and joined. Thread-safe communication (queue, lock, event, or future) is used correctly throughout. The concurrent feature runs alongside the game loop without blocking it. No race conditions or deadlocks present. All required behaviours are implemented and functional. |
| B    | 2.6–3.1 | Concurrency option is implemented and mostly functional. Thread management is mostly correct. Thread-safe communication is used but may have minor issues. The feature largely does not block the game loop. No obvious deadlocks, though minor thread safety gaps may be present.                                                                                       |
| C    | 2–2.5   | Concurrency option is partially implemented. Threads are used but not managed correctly (e.g., no join, no proper shutdown). Thread-safe communication is absent or used incorrectly. The feature may block the game loop. Potential for race conditions.                                                                                                                |
| D/E  | 0–1.9   | Concurrency option is missing or fundamentally broken. No meaningful use of Python concurrency tools. Race conditions or deadlocks present. Little or no understanding of concurrent programming demonstrated.                                                                                                                                                           |

---

### Persistent Statistics with SQLite (6 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
| ---- | ------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 4.8–6   | `GameDatabase` is fully implemented with all required methods functioning correctly. Schema matches specification with appropriate data types and foreign key constraints. Foreign keys are enabled. All write operations use transactions correctly. `get_player_summary()` and `get_leaderboard()` produce accurate, well-formatted output. The game correctly records every session, round and result. Database persists data correctly across multiple game runs. |
| B    | 3.9–4.7 | `GameDatabase` is implemented with most methods functional. Schema is mostly correct. Transactions are used in most write operations. Summary and leaderboard output is mostly correct. Game records data with minor omissions. Data persists between runs.                                                                                                                                                                                                           |
| C    | 3–3.8   | `GameDatabase` is partially implemented. Some methods are missing or incorrect. Schema has errors or missing constraints. Transactions may not be used. Summary or leaderboard has errors. Data may not persist reliably.                                                                                                                                                                                                                                             |
| D/E  | 0–2.9   | `GameDatabase` is largely missing or broken. Schema has significant errors. No meaningful use of transactions. Summary and leaderboard not functional. Game does not record data persistently.                                                                                                                                                                                                                                                                        |

---

### Functional Programming (2 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                      |
| ---- | ------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 1.6–2   | `analyse_session()` is fully implemented. All three required computations are correct. `map`, `filter`, and `reduce` are used exclusively and appropriately — no `for` loops or list comprehensions are used within these computations. Results are returned in a well-structured dictionary. |
| B    | 1.3–1.5 | `analyse_session()` is mostly implemented. Two of the three computations are correct. `map`, `filter`, and `reduce` are used for most computations with minor deviations.                                                                                                                     |
| C    | 1–1.2   | `analyse_session()` is partially implemented. Only one computation is correct, or `for` loops are used where functional tools are required. Shows basic understanding of functional programming techniques.                                                                                   |
| D/E  | 0–0.9   | Module is missing or does not demonstrate functional programming. `map`, `filter`, and `reduce` are absent or used incorrectly. Computations produce incorrect results.                                                                                                                       |

---

## Code Quality and Best Practices (12 marks)

### Code Organisation (3 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                               |
| ---- | ------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 2.4–3   | Excellent module structure with a clear, logical separation of concerns matching the required file layout. Every module has a single, well-defined responsibility. Functions and methods are focused and do not exceed 30 lines. No global state. Dependencies are passed explicitly. Easy to navigate and understand. |
| B    | 2–2.3   | Good module structure with separation of concerns mostly implemented. Most modules have clear responsibilities. Some functions are slightly long or have minor responsibility overlap. Little global state.                                                                                                            |
| C    | 1.5–1.9 | Basic module structure present but separation of concerns is inconsistent. Some classes or functions handle too many responsibilities. Functions may exceed the line limit. Global state may be present.                                                                                                               |
| D/E  | 0–1.4   | Poor or no module structure. Code is largely in a single file or modules do not separate concerns meaningfully. Functions are long and unfocused. Difficult to navigate or maintain.                                                                                                                                   |

---

### Code Style and Formatting (2 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                               |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| A    | 1.6–2   | Code passes `pylint` with a score of 7.0 or above and is consistently formatted with `black`. All naming conventions are followed throughout (`snake_case`, `PascalCase`). All function signatures include type hints. All names are meaningful, descriptive and unambiguous. Code is highly readable. |
| B    | 1.3–1.5 | Code largely passes `pylint` (minor warnings acceptable). Mostly formatted with `black`. Naming conventions followed with minor inconsistencies. Most function signatures have type hints. Names are generally meaningful. Code is readable.                                                           |
| C    | 1–1.2   | `pylint` score is below 7.0 or `black` formatting is inconsistent. Naming conventions not consistently followed. Type hints are sparse or missing. Some names are unclear. Readability could be improved.                                                                                              |
| D/E  | 0–0.9   | No evidence of linting or formatting. Naming conventions not followed. Type hints absent. Many names are unclear or meaningless. Code is difficult to read.                                                                                                                                            |

---

### Use of OOP Principles (2 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                                                               |
| ---- | ------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 1.6–2   | Encapsulation is correctly applied — internal state uses private attributes and is exposed only through appropriate methods or properties. Inheritance is used correctly with a meaningful base class or shared interface. Polymorphism allows the game loop to call shared methods on different player types without type branching. No unnecessary code duplication. |
| B    | 1.3–1.5 | OOP principles are applied with minor gaps. Encapsulation mostly correct. Inheritance and polymorphism present and mostly correct. Minor duplication.                                                                                                                                                                                                                  |
| C    | 1–1.2   | OOP principles partially applied. Some private attributes used but encapsulation inconsistent. Inheritance used but may not be meaningful. Polymorphism limited or absent. Some duplication present.                                                                                                                                                                   |
| D/E  | 0–0.9   | Little evidence of OOP principles. Attributes not encapsulated. No meaningful inheritance or polymorphism. Significant code duplication.                                                                                                                                                                                                                               |

---

### Error Handling (2 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                          |
| ---- | ------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 1.6–2   | All database operations are wrapped in `try/except` with `sqlite3.Error` handled gracefully. All user input is validated with clear, specific feedback given on invalid input. Appropriate built-in exceptions are raised with descriptive messages for invalid internal states. No raw stack traces are exposed during gameplay. |
| B    | 1.3–1.5 | Database operations mostly wrapped in error handling. User input validation present but may not cover all cases. Exceptions raised for most invalid states. Stack traces rarely if ever exposed.                                                                                                                                  |
| C    | 1–1.2   | Basic error handling present but incomplete. Some database errors not caught. User input validation partial. Some exceptions raised but messages may not be descriptive. Stack traces may occasionally be exposed.                                                                                                                |
| D/E  | 0–0.9   | Little or no error handling. Unhandled exceptions cause crashes. No user input validation. Stack traces exposed to the player. Application is fragile.                                                                                                                                                                            |

---

### Version Control (2 marks)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                     |
| ---- | ------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 1.6–2   | Excellent Git history. All commits use conventional commit format correctly and consistently (`feat:`, `fix:`, `refactor:`, `docs:`, `test:`, etc.). Commit messages are clear, descriptive and meaningful. Regular commits with small, focused changes. No large, monolithic commits. Clean history that is easy to follow. |
| B    | 1.3–1.5 | Good Git history. Most commits follow conventional format. Messages are generally clear and descriptive. Regular commits that are mostly focused. Few large commits. History is understandable.                                                                                                                              |
| C    | 1–1.2   | Basic Git usage. Some commits follow conventional format. Message quality varies. Some large or unfocused commits. History could be clearer.                                                                                                                                                                                 |
| D/E  | 0–0.9   | Poor or no Git history. Few or no commits follow conventional format. Messages are unclear or non-descriptive. Very large commits or very sparse commit history. Difficult to follow.                                                                                                                                        |

---

### Documentation (1 mark)

| Band | Marks   | Criteria                                                                                                                                                                                                                                                                                                                                                                  |
| ---- | ------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| A    | 0.8–1   | `README.md` is comprehensive and well-written. Includes a clear project description, complete environment setup instructions, clear instructions for running the game and the tests, a meaningful description of each chosen design pattern and concurrency option with justification, and any AI tool acknowledgements. Professional, well-formatted and easy to follow. |
| B    | 0.7     | `README.md` covers all required sections. Instructions are clear and mostly complete. Design pattern and concurrency descriptions present. Some details may be missing but documentation is usable.                                                                                                                                                                       |
| C    | 0.5–0.6 | `README.md` is present but incomplete. Some required sections missing or unclear. Instructions may be difficult to follow. Design pattern or concurrency descriptions superficial.                                                                                                                                                                                        |
| D/E  | 0–0.4   | `README.md` is missing or does not cover the required sections. Instructions are absent or unusable. Little or no evidence of reflective documentation.    

---                                                                                                                                                                                                               |
# Part 2: Own Project - Marking Rubric (50 marks)

---

**TBC**