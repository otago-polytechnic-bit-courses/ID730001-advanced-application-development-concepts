<img src="../../resources (ignore)/img/logo.jpg" alt="Otago Polytechnic Logo" width="200" height="auto" />

# ID730001: Advanced Application Development Concepts

## Practical

| Level | Credits | Assessment Type | Weighting |
| ----- | ------- | --------------- | --------- |
| 7     | 15      | Individual      | 20%       |

## Assessment Overview

This Practical assessment covers the written and design work that underpins both parts of the Project. It includes the design documentation for the Blackjack application, the independent framework research proposal, and the presentation of your Part 2 prototype. Completing this assessment well will directly support your success in the Project.

## Learning Outcomes

At the successful completion of this course, learners will be able to:

1. Critically evaluate and implement a range of programming paradigms to solve unfamiliar problems.
2. Create efficient full-stack applications using advanced industry techniques, tools and frameworks.

## Assessments

| Assessment | Weighting | Due Date           | Learning Outcome |
| ---------- | --------- | ------------------ | ---------------- |
| Practical  | 20%       | 26 June at 4:59 PM | 1, 2             |
| Project    | 80%       | 26 June at 4:59 PM | 1, 2             |

## Conditions of Assessment

You will complete this assessment mostly during your learner-managed time. However, there will be time during class to discuss the requirements and your progress. This assessment must be completed by 26 June at 4:59 PM.

## Pass Criteria

This assessment is criterion-referenced (CRA) with a cumulative pass mark of 50% across all assessments in ID730001: Advanced Application Development Concepts.

## Submission

All written documents must be committed to the `practical` branch of your GitHub Classroom repository.

- Repository URL: [https://classroom.github.com/a/RgDe5bs0](https://classroom.github.com/a/RgDe5bs0)
- Branch: Switch to the Practical branch using the following command: `git checkout -b practical`
- Due Date: 26 June at 4:59 PM
- Late Penalty: 10% per day, rolling over at 12:00 AM

Place design documents in a clearly named folder, e.g., `design/`. Place the Part 2 proposal and `README.md` in the repository root.

## Authenticity

All parts of your submitted assessment must be completely your work. Do your best to complete this assessment without using AI tools. You need to demonstrate to the course lecturer that you can meet the learning outcomes for this assessment.

### AI Tools

Learning to use AI tools is an important skill. While AI tools are powerful, you must be aware of the following:

- If you provide an AI tool with a prompt that is not refined enough, it may generate a not-so-useful response.
- Do not trust the AI tool's responses blindly. You must still use your judgement and may need to do additional research to determine if the response is correct.
- Acknowledge what AI tool you have used. In the assessment's repository `README.md` file, please include what prompt(s) you provided to the AI tool and how you used the response(s) to help you with your work.

This also applies to code snippets retrieved from StackOverflow and GitHub. Failure to do this may result in a mark of zero for this assessment.

## Policy on Submissions, Extensions, Resubmissions and Resits

The school's process concerning submissions, extensions, resubmissions and resits complies with Otago Polytechnic policies. Learners can view policies on the Otago Polytechnic website at [https://www.op.ac.nz/about-us/governance-and-management/policies](https://www.op.ac.nz/about-us/governance-and-management/policies).

### Extensions

Familiarise yourself with the assessment due date. Extensions will only be granted if you are unable to complete the assessment by the due date because of unforeseen circumstances outside your control. The length of the extension granted will depend on the circumstances and must be negotiated with the course lecturer before the assessment due date. A medical certificate or support letter may be needed. Extensions will not be granted on the due date and for poor time management or pressure of other assessments.

### Resits

Resits and reassessments are not applicable in ID730001: Advanced Application Development Concepts.

---

# Part 1: Blackjack Application — Design Phase

## Learning Outcomes 1 and 2 (10 marks)

Before you start the Design Phase, read through the Development Phase requirements in the Project assessment. This will help you understand what you need to build and ensure your design document is comprehensive.

Once you understand the requirements, create a design document that outlines the structure of your application. This will help you plan your work effectively.

> **Note:** To move onto the Development Phase, the course lecturer must approve your design document.

---

### Class Diagram (5 marks)

Create a UML class diagram using a digital tool of your choice that shows all required classes, their attributes, methods and relationships.

For each class, include:

- Class name
- All attributes with their names and data types
- All methods with their names, parameters and return types
- Visibility modifiers where appropriate, i.e., `+` public, `-` private

For each relationship between classes, include:

- Relationship type, e.g., association, composition, inheritance, etc.
- Multiplicity / cardinality, e.g., one-to-many
- Direction of the relationship

---

### Design Patterns and Concurrency Plan (5 marks)

In a written document, describe how you plan to apply the following to your Blackjack application.

#### Four Design Patterns

- **The Strategy Pattern (compulsory).** Identify which classes are involved, explain why this pattern is appropriate for this part of the application, and provide a brief pseudocode or diagram illustrating the pattern's structure in your design.
- **One chosen from the provided list** — Observer, Factory, or Builder. Identify which classes are involved, explain why this pattern is appropriate, and provide a brief pseudocode or diagram illustrating the pattern's structure in your design.
- **Two additional patterns** researched and selected independently. For each, identify which classes are involved, explain why this pattern is appropriate, and provide a brief pseudocode or diagram illustrating the pattern's structure in your design.

The following patterns are suggested as starting points, but you are not limited to this list:

| Pattern             | Possible Application in Blackjack                                                                                                |
| ------------------- | -------------------------------------------------------------------------------------------------------------------------------- |
| **Command**         | Encapsulate player actions, e.g., hit, stand, split, surrender as command objects, enabling action history or undo functionality |
| **State**           | Model the game's phases, e.g., player turn, dealer turn, round resolution as explicit state objects with defined transitions     |
| **Singleton**       | Ensure only one instance of `GameDatabase` or a configuration manager exists throughout the application                          |
| **Decorator**       | Wrap player objects with additional behaviours such as logging or statistics tracking without modifying the base class           |
| **Template Method** | Define the skeleton of a game round in a base class and let subclasses override specific steps                                   |

Your chosen additional patterns must be different from the Strategy Pattern and the one pattern you selected above. All four patterns must be meaningfully distinct from one another.

#### One Concurrency Mechanism

Describe one concurrency mechanism appropriate to your chosen language, e.g., threads, thread pools, locks, async/await, coroutines. Your description must cover:

- What concurrent task(s) you plan to implement
- Which concurrency tools your chosen language provides and why you selected them
- How you will ensure thread safety where shared state is involved

---

# Part 2: Independent Framework Research — Research and Approval Phase

## Learning Outcomes 1 and 2 (5 marks)

### Overview

In this part, you will independently research a tool or framework that has not been covered in any previous course. You will define your own set of requirements and submit a written proposal to the course lecturer for approval before you begin implementation in the Project assessment.

### Constraints

- The tool or framework must not have been taught in any previous course. If you are unsure, check with the course lecturer before investing time in research.
- You may use the same tool or framework as another learner in the class.
- Both your chosen tool or framework and your 12 requirements must be approved by the course lecturer before you begin implementation.

### Choose a Tool or Framework

Research a tool or framework that genuinely interests you and that you have not studied before. Good candidates include, but are not limited to:

| Category           | Examples                            |
| ------------------ | ----------------------------------- |
| Game Development   | Game Maker, Unreal, Blender         |
| Mobile Development | Flutter, React Native, SwiftUI      |
| Web Development    | Django, Ruby on Rails, Vue.js       |
| Other              | Anything you can justify at Level 7 |

This list is illustrative, not exhaustive. You are encouraged to look beyond it.

### Submit a Proposal

Before writing any code, submit a short written proposal to the course lecturer. Your proposal must include:

- The name and purpose of the tool or framework
- Why you chose it and what you hope to learn
- Evidence that it has not been taught in a previous course, e.g., a brief note confirming this
- A draft list of 12 requirements you plan to implement

> **Note:** The course lecturer must approve both your tool or framework choice and your 12 requirements before you proceed to implementation. Approval will be confirmed in writing, e.g., via a GitHub issue or email.

### Writing Your 12 Requirements

Your requirements must:

- Be specific and verifiable — a marker should be able to read each one and determine clearly whether it has been met
- Collectively demonstrate a meaningful and non-trivial use of the tool or framework
- Range in complexity — include straightforward requirements as well as at least three that push into more advanced features
- Be written in your own words, not copied from documentation

Each requirement should follow this format:

> **REQ-01:** The application must [do something specific and observable].

Example requirements for a web development framework might be:

> **REQ-01:** The application must implement a user registration and login system using the framework's built-in authentication features.

---

# Part 2: Independent Framework Research — Presentation Phase

## Learning Outcomes 1 and 2 (8 marks)

### Overview

Present your research and working prototype to the course lecturer. Your presentation must be either a **live demonstration** or a **recorded video walkthrough** of at least five minutes.

### Content Requirements

Your presentation must cover all of the following:

- **Introduction:** what the tool or framework is, what problem it solves, and why you chose it
- **Critical evaluation:** strengths and limitations you discovered through hands-on use; how it compares to alternatives you considered
- **Live demo or walkthrough:** walk through your prototype and demonstrate each of the 12 requirements working as specified
- **Reflection:** what you found challenging, what you would do differently, and what you would explore next

---

# Documentation

## Learning Outcomes 1 and 2 (1 mark)

In `README.md`, include the following:

- Project description and purpose
- The programming language and version used, and instructions for setting up the environment and installing dependencies
- How to run the game
- A brief description of each design pattern and concurrency option you implemented and why you chose them
- Setup and run instructions specific to Part 2
- A table mapping each Part 2 requirement to the relevant file(s) and a one-sentence description of how it is met
- Any AI tool usage acknowledgement and prompts used

---

_Author: Grayson Orr_
_Course: ID730001: Advanced Application Development Concepts_
