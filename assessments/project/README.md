# Project

<img src="../../resources (ignore)/img/logo.jpg" alt="Otago Polytechnic Logo" width="200" height="auto" />

# ID730001: Advanced Application Development Concepts

## Assessment Information

| Level | Credits | Assessment Type | Weighting |
| ----- | ------- | --------------- | --------- |
| 7     | 15      | Individual      | 80%       |

## Assessment Overview

In this individual assessment, you will design and develop a Blackjack application in Python. The project is divided into two parts:

- **Part 1 (this document):** A fully playable command-line Blackjack game that demonstrates object-oriented programming, design patterns, concurrency, and persistent data storage using SQLite.
- **Part 2:** TBC.

## Learning Outcomes

At the successful completion of this course, learners will be able to:

1. Critically evaluate and implement a range of programming paradigms to solve unfamiliar problems.
2. Create efficient full-stack applications using advanced industry techniques, tools and frameworks.

## Assessments

| Assessment | Weighting | Due Date           | Learning Outcome |
| ---------- | --------- | ------------------ | ---------------- |
| Practical  | 20%       | 22 May at 4.59 PM  | 1                |
| Project    | 80%       | 26 June at 4.59 PM | 1, 2             |

## Conditions of Assessment

You will complete this assessment mostly during your learner-managed time. However, there will be time during class to discuss the requirements and your progress on this assessment. This assessment will need to be completed by 26 June at 4.59 PM.

## Pass Criteria

This assessment is criterion-referenced (CRA) with a cumulative pass mark of 50% across all assessments in ID730001: Advanced Application Development Concepts.

## Submission

You must submit all application files via GitHub Classroom.

- Repository URL: [https://classroom.github.com/a/RgDe5bs0](https://classroom.github.com/a/RgDe5bs0)
- Branch: Switch to the Project branch using the following command: `git checkout -b project`
- Due Date: 26 June at 4.59 PM
- Late Penalty: 10% per day, rolling over at 12.00 AM

The latest application files in the Project branch will be used to mark against the marking rubric. Please test your application before you submit. Partial marks may be given for incomplete functionality.

## Authenticity

All parts of your submitted assessment must be completely your work. Do your best to complete this assessment without using AI tools. You need to demonstrate to the course lecturer that you can meet the learning outcomes for this assessment.

### AI Tools

Learning to use AI tools is an important skill. While AI tools are powerful, you must be aware of the following:

- If you provide an AI tool with a prompt that is not refined enough, it may generate a not-so-useful response
- Do not trust the AI tool's responses blindly. You must still use your judgement and may need to do additional research to determine if the response is correct
- Acknowledge what AI tool you have used. In the assessment's repository `README.md` file, please include what prompt(s) you provided to the AI tool and how you used the response(s) to help you with your work

This also applies to code snippets retrieved from StackOverflow and GitHub.

Failure to do this may result in a mark of zero for this assessment.

## Policy on Submissions, Extensions, Resubmissions and Resits

The school's process concerning submissions, extensions, resubmissions and resits complies with Otago Polytechnic policies. Learners can view policies on the Otago Polytechnic website located at [https://www.op.ac.nz/about-us/governance-and-management/policies](https://www.op.ac.nz/about-us/governance-and-management/policies).

### Extensions

Familiarise yourself with the assessment due date. Extensions will only be granted if you are unable to complete the assessment by the due date because of unforeseen circumstances outside your control. The length of the extension granted will depend on the circumstances and must be negotiated with the course lecturer before the assessment due date. A medical certificate or support letter may be needed. Extensions will not be granted on the due date and for poor time management or pressure of other assessments.

### Resits

Resits and reassessments are not applicable in ID730001: Advanced Application Development Concepts.

---

## Assessment Requirements - Part 1: Blackjack Application

The Part 1 marking rubric is available [here]().

---

### Design Phase - Learning Outcome 1 (10 marks)

Before you start the Design Phase, read through the Development Phase requirements below. This will help you understand what you need to build and ensure your design document is comprehensive.

Once you understand the requirements, create a design document that outlines the structure of your application. This will help you plan your work effectively.

To move onto the Development Phase, the course lecturer must approve your design document.

---

#### Class Diagram (5 marks)

- Create a UML class diagram using a digital tool of your choice that shows all required classes, their attributes, methods and relationships.
- For each class, include:
  - Class name
  - All attributes with their names and data types
  - All methods with their names, parameters and return types
  - Visibility modifiers where appropriate (`+` public, `-` private)
- For each relationship between classes, include:
  - Relationship type (association, composition, inheritance, etc.)
  - Multiplicity/cardinality (e.g., one-to-many)
  - Direction of the relationship

---

#### Design Patterns and Concurrency Plan (5 marks)

In a written document, describe how you plan to apply the following to your Blackjack application:

- **Two design patterns** from the course (Strategy, Observer, Factory, Singleton, or Builder). For each pattern:
  - Identify which classes are involved
  - Explain why this pattern is appropriate for this part of the application
  - Provide a brief pseudocode or diagram illustrating the pattern's structure in your design
- **One concurrency mechanism** from the course (e.g., threading, thread pool, locks, asyncio). Describe:
  - What concurrent task(s) you plan to implement
  - Which Python concurrency tools you will use and why
  - How you will ensure thread safety where shared state is involved

---

### Development Phase - Learning Outcome 1 (28 marks)

Once the course lecturer has approved your design document, you can start developing your application. You should follow the requirements in your design document, but you can make changes as needed. If you make significant changes to your design document, please update it accordingly.

---

#### Project Management (2 marks)

In this phase, you will use the Agile software development methodology.

- You will decide the duration of your sprints and how to break down your work into sprints and tasks.
- Create a GitHub Project to manage your work. The project must include columns for Backlog, In Progress and Done.
- Create issues for each task and move them across the columns as you work on them.

Here is an example of how to break down your work into sprints and tasks:

| Sprint | Tasks                                                                                                                 |
| ------ | --------------------------------------------------------------------------------------------------------------------- |
| 1      | Set up project structure, implement `Card`, `Deck`, and `Hand` classes, implement basic `Player` and `Dealer` classes |
| 2      | Implement `BlackjackGame` class and core game loop, implement design pattern 1                                        |
| 3      | Implement design pattern 2, implement concurrency feature, implement SQLite database layer                            |
| 4      | Implement functional programming tasks, write unit tests, finalise documentation                                      |

---

#### Core Game (8 marks)

Implement a fully playable command-line Blackjack game using object-oriented programming. The game must include the following classes:

| Class           | Required Attributes                          | Required Methods                                                                                                                                             |
| --------------- | -------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `Card`          | `rank`, `suit`                               | `get_value()` — returns the card's numeric value; `__str__()` — returns a human-readable representation such as `"Ace of Spades"`                            |
| `Deck`          | `cards`                                      | `shuffle()`, `deal_card()`, `cards_remaining()`, `reset()`                                                                                                   |
| `Hand`          | `cards`                                      | `add_card(card)`, `get_value()` — correctly handles Ace as 11 or 1; `is_blackjack()`, `is_bust()`, `__str__()`                                               |
| `Player`        | `name`, `hand`, `chips`                      | `place_bet(amount)` — deducts from chips; `receive_winnings(amount)` — adds to chips; `__str__()`                                                            |
| `Dealer`        | `hand`, `name`                               | `show_partial_hand()` — reveals only the first card; `show_full_hand()`, `should_hit()` — returns `True` if hand value ≤ 16; `__str__()`                     |
| `BlackjackGame` | `deck`, `dealer`, `players`, `current_round` | `start_round()`, `deal_initial_cards()`, `player_turn(player)`, `dealer_turn()`, `determine_winners()`, `display_game_state()`, `play_game()`, `game_over()` |

**Game rules:**

- Goal: get closer to 21 than the dealer without going over ("busting")
- Face cards (J, Q, K) = 10; Aces = 11 or 1 (whichever avoids a bust); number cards = face value
- Dealer must hit on ≤ 16 and stand on ≥ 17
- Players may hit or stand on their turn
- A Blackjack (Ace + 10-value card on the initial deal) beats any non-Blackjack 21
- Players start with 1000 chips; they place a bet before each round
- A player who wins a round receives double their bet back; a Blackjack pays 1.5×; a loss forfeits the bet; a tie returns the bet unchanged
- A player with 0 chips is out of the game
- The game ends when all players have no chips, or all players choose to quit

**Game flow:**

1. Display a welcome message with player names and starting chips
2. Each round:
   a. Players place their bets
   b. Deal two cards to each player and the dealer (dealer's second card is hidden)
   c. Check for Blackjack (announce immediately if found)
   d. Each player takes their turn (hit or stand), skip if they have Blackjack
   e. Dealer reveals hidden card and plays their turn
   f. Determine and announce winners; update chip counts
   g. Remove players with 0 chips
   h. Ask remaining players whether to play another round
3. Display a final summary when the game ends

Example game session:

```
Welcome to Blackjack!
Players: Alice (1000 chips), Bob (1000 chips)

----- Round 1 -----

Alice, place your bet: 100
Bob, place your bet: 200

Alice's hand: 10 of Hearts, Ace of Spades (Total: 21) - Blackjack!
Bob's hand: 7 of Diamonds, 8 of Clubs (Total: 15)
Dealer's hand: 9 of Hearts, [Hidden]

Bob, do you want to hit or stand? hit
Bob's hand: 7 of Diamonds, 8 of Clubs, 5 of Spades (Total: 20)
Bob, do you want to hit or stand? stand

Dealer reveals: 9 of Hearts, 6 of Diamonds (Total: 15)
Dealer hits and receives 10 of Clubs (Total: 25) - Dealer busts!

Alice wins! (Blackjack) — receives 250 chips. Total: 1150 chips.
Bob wins! — receives 400 chips. Total: 1200 chips.

Do you want to play another round? (Alice: yes / Bob: yes)
```

To start the game:

```python
game = BlackjackGame(["Alice", "Bob"])
game.play_game()
```

---

#### Design Patterns (6 marks)

Implement **two** of the following design patterns within your Blackjack application. The patterns must be meaningfully integrated — they should add clear value to the design, not be bolted on artificially.

---

##### Option A — Strategy Pattern (3 marks)

Implement a `DrawStrategy` interface with at least **three** concrete strategies that control how a player decides whether to hit or stand:

| Strategy               | Behaviour                                                            |
| ---------------------- | -------------------------------------------------------------------- |
| `HumanStrategy`        | Prompts the player for input (`hit` or `stand`) via the command line |
| `ConservativeStrategy` | Stands if the hand value is ≥ 15; otherwise hits                     |
| `AggressiveStrategy`   | Stands only if the hand value is ≥ 18; otherwise hits                |

Players must be configurable with any strategy at construction time. The game loop must not need to know which strategy a player is using.

---

##### Option B — Observer Pattern (3 marks)

Implement an `IGameObserver` interface and attach at least **two** concrete observers to the game:

| Observer     | Behaviour                                                                                                      |
| ------------ | -------------------------------------------------------------------------------------------------------------- |
| `Scoreboard` | Tracks wins, losses and ties per player and prints a summary at the end of each round                          |
| `GameLogger` | Logs every significant game event (bet placed, card dealt, winner declared, etc.) to a timestamped `.log` file |

The `BlackjackGame` class must maintain a list of observers and notify all of them at appropriate points during the game (e.g., after each round ends).

---

##### Option C — Factory Pattern (3 marks)

Implement a `PlayerFactory` interface with at least **two** concrete factories:

| Factory              | Creates                                                                         |
| -------------------- | ------------------------------------------------------------------------------- |
| `HumanPlayerFactory` | A `HumanPlayer` whose actions are driven by keyboard input                      |
| `BotPlayerFactory`   | A `BotPlayer` whose actions are determined automatically (e.g., basic strategy) |

The `BlackjackGame` class must accept factories rather than constructing players directly, so that human and bot players can be mixed freely without changing the game logic.

---

##### Option D — Builder Pattern (3 marks)

Implement a `GameConfigBuilder` that constructs a `GameConfig` object step-by-step before the game starts. The builder must support at least the following options:

| Method                      | Effect                                                                                    |
| --------------------------- | ----------------------------------------------------------------------------------------- |
| `set_num_players(n)`        | Sets the number of players (1–6)                                                          |
| `set_starting_chips(n)`     | Sets the starting chip count for all players                                              |
| `set_num_decks(n)`          | Combines `n` standard 52-card decks into one shoe                                         |
| `set_min_bet(amount)`       | Sets the minimum bet allowed per round                                                    |
| `with_verbose_output(bool)` | Enables or disables detailed play-by-play output                                          |
| `build()`                   | Returns the validated `GameConfig` object; raises `ValueError` for invalid configurations |

The `BlackjackGame` class must accept a `GameConfig` object and respect all configured options during play.

---

#### Concurrency (4 marks)

Add a concurrent feature to your Blackjack application using the threading tools covered in the course. You must implement **one** of the following:

---

##### Option A — Concurrent Fraud / Cheat Detection (4 marks)

While the game is running, a background `CheatDetector` thread monitors player activity for suspicious patterns. The detector must:

- Run as a separate `threading.Thread` (or via `ThreadPoolExecutor`) so it does not block the main game loop
- Use a thread-safe `queue.Queue` to receive game events from the main thread (e.g., a player hitting 5+ times in a single round, or placing a bet that equals their entire chip stack)
- Use a `threading.Lock` or `threading.Event` to safely communicate a detection result back to the main thread
- Print a warning message during normal output if a suspicious pattern is detected (e.g., `[CheatDetector] Warning: Alice has hit 6 times this round`)
- Not cause any race conditions or deadlocks

---

##### Option B — Timed Player Turns (4 marks)

Each human player has a limited time to make their hit/stand decision. The timer must:

- Use `threading.Thread` to run a countdown concurrently with waiting for player input
- Use `threading.Event` to signal between the input thread and the timer thread
- Automatically stand the player (i.e., default to `stand`) if the time limit expires before input is received
- Display a live countdown to the terminal while waiting for input (e.g., `Bob, hit or stand? [8s remaining]`)
- Be configurable — the time limit must be set via the `GameConfig` (default: 30 seconds)
- Not cause any race conditions or deadlocks

---

##### Option C — Async Statistics Engine (4 marks)

After each round, a statistics engine computes and displays updated player analytics concurrently so computation does not block the game loop. The engine must:

- Use `ThreadPoolExecutor` with `submit()` to run at least **three** computations in parallel after each round ends:
  - Win/loss/tie ratio per player
  - Average bet size per player across all rounds played
  - A "hot streak" flag: `True` if the player has won the last three consecutive rounds
- Collect results using `Future.result()` and display a formatted stats panel before the next round begins
- Use a `threading.Lock` to protect the shared statistics store that persists across rounds
- Not cause any race conditions or deadlocks

---

#### Persistent Statistics with SQLite (6 marks)

Implement a `GameDatabase` class that records game history persistently to a SQLite database (`blackjack.db`). The database must use the following schema:

```sql
players      (id, name, created_at)
game_sessions(id, started_at, ended_at, num_rounds)
rounds       (id, session_id, round_number, played_at)
round_results(id, round_id, player_id, bet, outcome, chips_before, chips_after)
```

**`GameDatabase` class:**

| Method                                                                        | Description                                                                                                     |
| ----------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------- |
| `__init__(path: str)`                                                         | Opens or creates the database, creates the schema if it does not exist, enables foreign key enforcement         |
| `get_or_create_player(name: str) -> int`                                      | Returns the existing player ID if the name is found, otherwise inserts a new player and returns the new ID      |
| `start_session() -> int`                                                      | Inserts a new game session record with the current timestamp and returns the session ID                         |
| `end_session(session_id: int, num_rounds: int)`                               | Updates the session record with the end timestamp and total rounds played                                       |
| `record_round(session_id: int, round_number: int) -> int`                     | Inserts a round record and returns its ID                                                                       |
| `record_result(round_id, player_id, bet, outcome, chips_before, chips_after)` | Inserts a `round_results` row for one player's outcome in a round                                               |
| `get_player_summary(name: str)`                                               | Prints a formatted summary for the named player — see expected output below                                     |
| `get_leaderboard()`                                                           | Prints the top five players ranked by total chips won (chips_after minus chips_before summed across all rounds) |

The `BlackjackGame` class must use `GameDatabase` to record every session, round, and result as the game is played.

Expected output for `get_player_summary("Alice")`:

```
Player: Alice
Total rounds played: 42
Wins: 20  Losses: 18  Ties: 4
Win rate: 47.6%
Average bet: $85.50
Best round: +$300 (Session 3, Round 7)
```

> **Hint:** use `with conn:` inside all write operations to manage transactions automatically. Always enable foreign keys with `PRAGMA foreign_keys = ON`.

---

#### Functional Programming (2 marks)

Implement a standalone module `blackjack_analysis.py` that analyses a completed game session using functional programming techniques. The module must:

- Accept a list of `round_results` dictionaries (as would be returned from a database query) with the structure:
  ```python
  {"player": "Alice", "bet": 100, "outcome": "win", "chips_before": 1000, "chips_after": 1100}
  ```
- Use `map`, `filter`, and `reduce` (imported from `functools`) to compute the following — no explicit `for` loops or list comprehensions are permitted within these computations:
  - Total chips won across all winning rounds for each player (using `filter` then `reduce`)
  - A list of rounds where the bet exceeded the player's average bet for that session (using `map` then `filter`)
  - The overall chip change per player as a dictionary (using `map` and `reduce`)
- Return all results in a single dictionary from a function named `analyse_session(results)`

---

### Code Quality and Best Practices - Learning Outcome 1 (12 marks)

When developing your application, you must follow best practices for code quality.

---

#### Code Organisation (3 marks)

- Organise your code into a clear module structure. At minimum, separate concerns into distinct files:

| File / Module           | Contents                                             |
| ----------------------- | ---------------------------------------------------- |
| `card.py`               | `Card`, `Deck`, `Hand`                               |
| `players.py`            | `Player`, `Dealer`, and any strategy/factory classes |
| `game.py`               | `BlackjackGame`, observer or builder classes         |
| `database.py`           | `GameDatabase`                                       |
| `blackjack_analysis.py` | Functional programming analysis module               |
| `main.py`               | Entry point — constructs and starts the game         |

- Each module must have a single, clearly defined responsibility.
- Functions and methods must be focused — no function should exceed 30 lines.
- Avoid global state; pass dependencies explicitly.

---

#### Code Style and Formatting (2 marks)

- All code must pass `pylint` with a score of 7.0 or above.
- All code must be formatted with `black`.
- Follow Python naming conventions: `snake_case` for variables and functions, `PascalCase` for classes.
- Use meaningful, descriptive names for all variables, functions, parameters and classes.
- Include type hints on all function signatures.

---

#### Use of OOP Principles (2 marks)

- Demonstrate correct use of **encapsulation**: use private attributes (prefix with `_`) for internal state and expose it only through methods or properties where appropriate.
- Demonstrate correct use of **inheritance**: at minimum, `Dealer` should inherit from a base class or share an interface with `Player`.
- Demonstrate correct use of **polymorphism**: the game loop must be able to call methods such as `take_turn()` or `choose_action()` on different player types without branching on type.
- Avoid code duplication — extract shared logic into base classes or utility functions.

---

#### Error Handling (2 marks)

- Wrap all database operations in `try/except` blocks and handle `sqlite3.Error` gracefully.
- Validate all user input from the command line (e.g., ensure bets are positive integers within the player's chip range; ensure hit/stand input is one of the accepted values).
- Raise appropriate built-in exceptions (`ValueError`, `RuntimeError`) with descriptive messages for invalid internal states (e.g., dealing from an empty deck).
- Never expose raw stack traces to the player during normal gameplay.

---

#### Version Control (2 marks)

- Maintain a clean Git history with descriptive commit messages.
- Use conventional commit messages (`feat:`, `fix:`, `refactor:`, `docs:`, `test:`, etc.).
- Commit regularly with small, focused changes rather than large, monolithic commits.

---

#### Documentation (1 mark)

In `README.md`, include the following:

- Project description and purpose
- Instructions for setting up the Python environment (e.g., `pip install -r requirements.txt`)
- How to run the game
- How to run the unit tests
- A brief description of each design pattern and concurrency option you implemented and why you chose them
- Any AI tool usage acknowledgement and prompts used

---

## Assessment Requirements - Part 2

**TBC**

---

_Author: Grayson Orr_  
_Course: ID730001: Advanced Application Development Concepts_
