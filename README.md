# Red-Black Tree in C++ with OOP Racing Simulation

This repository contains my implementation of a **Red-Black Tree** (a self-balancing binary search tree) in C++, along with a small **racing simulation** that demonstrates object-oriented programming concepts such as **inheritance** and **dynamic binding**.

The tree is used to manage and simulate a “race” between three different types of racers, all derived from a common base class.

---

## 🔍 Project Overview

**Core ideas demonstrated:**

- **Red/Black balanced tree**
  - Self-balancing binary search tree
  - Uses colors and rotations to keep tree height logarithmic
- **Inheritance**
  - Base class: `Racer`
  - Derived classes: `Child`, `Bear`, `Monster`
- **Dynamic binding (polymorphism)**
  - Virtual functions in the base class
  - Behavior that depends on the actual racer type at runtime
  - Shows use of Run-Time Type Identification (RTTI)
- **Dynamic memory**
  - Nodes are allocated and managed dynamically in the tree

This is an authentic data structures project implemented from scratch in C++.

---

## 📁 Files in This Repository

```text
red-black-tree-cplusplus/
├── Makefile        # Build rules for the project
├── game.cpp        # Game / simulation logic using racers and the tree
├── main.cpp        # Entry point (sets up and runs the simulation)
├── race.cpp        # Implementation of Racer classes and race behavior
├── race.h          # Declarations for Racer base class and derived racers
├── race2.cpp       # Additional race/simulation logic
├── tree.cpp        # Red-Black Tree implementation
└── tree.h          # Red-Black Tree interface (node + tree declarations)
```

---

## 🌳 Red-Black Tree

The **Red-Black Tree** in `tree.cpp` / `tree.h`:

- Stores keys and maintains **binary search tree order**
- Colors each node **red** or **black**
- Uses **rotations** and **recoloring** on insert to maintain Red-Black properties
- Keeps operations such as **search** and **insertion** at **O(log n)** time

Key Red-Black properties enforced:

- Every node is either red or black
- The root is black
- No red node has a red child (no “red-red” violations)
- Every path from a node to a leaf has the same number of black nodes

This implementation focuses on correctly handling dynamic memory and balancing logic.

---

## 🏁 OOP Racing Simulation (Inheritance & Dynamic Binding)

The racing simulation code in `race.h`, `race.cpp`, `race2.cpp`, and `game.cpp` models a race between different types of racers.

### Class Hierarchy

```text
Racer      (base class)
├── Child  (derived)
├── Bear   (derived)
└── Monster (derived)
```

- All racers inherit from a common base class `Racer`.
- The base class exposes a common interface (e.g., functions related to racing behavior).
- Each derived class (`Child`, `Bear`, `Monster`) provides its own implementation.

### Dynamic Binding

- The project uses **virtual functions** in `Racer` to enable **dynamic binding**.
- At runtime, calls through a `Racer*` (or reference) invoke the correct derived behavior.
- This demonstrates **polymorphism** and how a Red-Black Tree can store and manage base-class pointers while still using derived behavior.

The Red-Black Tree can be used to store racers and organize them (for example, by race results, speed, or other attributes).

---

## 🧪 What This Project Demonstrates (for Employers)

This repository showcases:

- Implementation of a **Red-Black balanced tree** from scratch
- Understanding of:
  - rotations
  - recoloring
  - maintaining tree invariants
- **Dynamic memory management** with node allocation and cleanup
- Solid **object-oriented design**:
  - inheritance
  - base and derived class relationships
  - dynamic binding via virtual functions
- Integration of a non-trivial data structure with an applied **simulation** (the race)

---

## 🛠 Build & Run

Make sure you have a C++ compiler installed (e.g., `g++` or `clang++`).

Clone the repository:

```bash
git clone https://github.com/busschau/red-black-tree-cplusplus.git
cd red-black-tree-cplusplus
```

Build using the provided `Makefile`:

```bash
make
```

This will produce an executable (for example `./a.out` or a named binary depending on your Makefile configuration).

Run the program:

```bash
./a.out
```

(or the executable name produced on your system)

You should see the racing logic execute and/or tree operations demonstrated, depending on how `main.cpp` and the game logic are configured.

---

## 🚀 Possible Future Improvements

- Add one deletion operations to the Red-Black Tree
- Add more racer types and stats (speed, stamina, etc.)
- Display race results more interactively
- Add unit tests for tree operations and racer behavior

---

## 👤 About Me

I’m a Computer Science student at Portland State University with interests in data structures, systems programming, and cybersecurity.  
This project demonstrates my ability to implement complex balanced trees and combine them with object-oriented design in C++.

