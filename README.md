# CS 246 Biquadris

Biquadris is a two-player competitive Tetris-inspired game developed as a final project for CS 246. The game emphasizes object-oriented design principles and demonstrates concepts such as polymorphism, inheritance, and design patterns.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Game Rules](#game-rules)
- [Design Patterns](#design-patterns)
- [Class Structure](#class-structure)
- [Project Documentation](#project-documentation)
- [Installation](#installation)
- [Usage](#usage)
- [Contributors](#contributors)

## Overview

Biquadris is a turn-based variant of Tetris where two players take turns dropping blocks on their respective boards. The game incorporates special actions that can be used to hinder the opponent, adding a strategic element to the gameplay.

## Features

- Turn-based gameplay for two players
- Multiple difficulty levels with different block probabilities
- Special actions: blind, heavy, force
- Command shortcuts and custom key bindings
- Text-based and graphical interface
- Shadow blocks to preview where pieces will land
- Score tracking with high score persistence

## Game Rules

- Players take turns dropping blocks on their respective boards
- When a player completes at least two rows simultaneously, they can apply a special action to their opponent:
  - **Blind**: Obscures part of the opponent's board
  - **Heavy**: Makes blocks harder to maneuver (they drop faster)
  - **Force**: Forces a specific block type on the opponent
- The game ends when a player can no longer place blocks on their board
- The player with the higher score wins

## Design Patterns

This project implements several key design patterns:

- **Factory Pattern**: Used for the Level and Shape classes, allowing for easy addition of new levels and block types
- **Decorator Pattern**: Enables multiple effects to be applied simultaneously to a player
- **Observer Pattern**: Efficiently updates game state and renders the display

## Class Structure

The game is structured around the following key classes:

- **Game**: Manages the overall game state and player turns
- **Player**: Handles player-specific data and actions
- **Studio**: Represents the game board for each player
- **Shape**: Abstract base class for different block types
- **Level**: Defines game behavior for different difficulty levels
- **GameProperties**: Manages key bindings and command shortcuts

For detailed class relationships, see the [UML diagrams](#project-documentation) below.

## Project Documentation

- [Initial UML Diagram](uml_V1.pdf)
- [Final UML Diagram](uml-final.pdf)
- [Design Document](design.pdf)

The design document includes:
- Project schedule and delegation
- Design considerations and patterns
- Implementation details for each class
- Discussion of design challenges and solutions

## Installation

### Prerequisites
- C++ compiler with C++17 support
- X11 libraries for graphical interface

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/eddywang4340/CS246-Biquadris.git
cd biquadris

# Compile the project
make
```

## Usage

```bash
# Run the game with default settings
./biquadris

# Run with command line options
./biquadris -text -seed 123 -startlevel 2

# Command line options:
# -text: Run in text-only mode
# -seed <n>: Set random seed
# -startlevel <n>: Set starting level (0-4)
# -scriptfile1 <file>: Set script file for player 1
# -scriptfile2 <file>: Set script file for player 2
```

### Game Controls

| Command | Description | Shortcuts |
|---------|-------------|-----------|
| left | Move block left | l, lef |
| right | Move block right | r, ri, rig, righ |
| down | Move block down | do, dow |
| drop | Drop block | dr, dro |
| clockwise | Rotate block clockwise | cl, clo, cloc, clock |
| counterclockwise | Rotate block counterclockwise | co, cou, coun, count |
| levelup | Increase difficulty level | levelu |
| leveldown | Decrease difficulty level | leveld |
| restart | Restart game | re, res, rest |
| I, J, L, O, S, Z, T | Change current block | i, j, l, o, s, z, t |

## Contributors

- Daniel Zhao
- Edward Wang
- Yiyan Huang
