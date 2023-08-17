# C - Simple Shell

This is a simple UNIX command line interpreter implemented in C. The project aims to create a basic shell that can execute simple commands entered by the user.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Tasks](#tasks)
- [Contributors](#contributors)
- [License](#license)

## Introduction

The "C - Simple Shell" project is a small-scale implementation of a shell that provides a command-line interface for users to interact with the operating system. The shell interprets user commands and executes them by creating child processes.

## Features

- Displays a prompt and waits for user input.
- Executes simple commands entered by the user.
- Handles "command not found" errors.
- Implements built-in commands:
  - `exit`: Exits the shell.
  - `env`: Prints the current environment.
- Supports command lines with arguments.
- Handles the `PATH` environment variable to find executable programs.
- Manages child processes using the `fork` system call.

## Getting Started

To get started with the simple shell project, follow these steps:

1. Clone the repository: `git clone https://github.com/Mido-Hyuga/simple_shell.git`
2. Navigate to the project directory: `cd simple_shell`
3. Compile the code: `gcc -Wall -Werror -Wextra -pedantic *.c -o shell`
4. Run the shell: `./shell`

## Usage

1. Run the compiled shell executable.
2. Enter commands at the prompt.
3. Press `Enter` to execute a command.
4. The shell will display the output of the executed command.
5. Use the built-in commands `exit` to exit the shell or `env` to display the environment.

## Tasks

The project is broken down into several tasks, each building on the previous one to enhance the shell's functionality. The tasks include:

- **Betty would be proud:** Ensuring code adheres to the coding style guide.
- **Simple shell 0.1:** Creating a basic command-line interpreter.
- **Simple shell 0.2:** Enhancing the shell to handle command lines with arguments.
- **Simple shell 0.3:** Adding PATH handling and improving error handling.
- **Simple shell 0.4:** Implementing the `exit` built-in command.
- **Simple shell 1.0:** Implementing the `env` built-in command.

## Contributors

This project was developed by [Your Name] and [Contributor Name]. Contributions and feedback are welcome.

## License

This project is licensed under the ALX Africa.

---
