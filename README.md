# Minishell

## 🐚 Project Overview

Minishell is a custom implementation of a Unix shell, similar to bash but with a simplified feature set. This project demonstrates deep understanding of process creation and control, file descriptor manipulation, signal handling, and parsing techniques.

## ✨ Features

### Command Line Interface
- Interactive prompt with username and current directory
- Command history navigation
- Line editing capabilities (using readline library)

### Core Functionality
- Command execution with absolute or relative paths
- Environment variable management and expansion
- Exit status tracking with `$?` support
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\\)

### Command Processing
- Command parsing with quotes (`'` and `"`) handling
- Support for input/output redirections (`<`, `>`, `<<`, `>>`)
- Pipelines for connecting multiple commands (`|`)

### Built-in Commands
- `echo` with `-n` flag support
- `cd` for directory navigation
- `pwd` to display current working directory
- `env` to display environment variables
- `export` to set environment variables
- `unset` to remove environment variables
- `exit` to terminate the shell

### Bonus Features
- Logical operators (`&&`, `||`) with parentheses for precedence
- Wildcard expansion (`*`) in the current directory

## 🧠 Technical Implementation

### Architecture

The implementation follows a modular design with distinct components:

1. **Lexer/Parser**: Transforms raw input into structured tokens and builds an abstract syntax tree
2. **Executor**: Processes the command tree and handles execution flow
3. **Built-ins**: Custom implementation of shell built-in commands
4. **Environment Manager**: Handles environment variable storage and manipulation
5. **Signal Handler**: Manages signal interception and appropriate responses

### Key Challenges

- **Parsing Complex Commands**: Handling nested quotes, redirections, and pipes
- **Process Management**: Creating, monitoring, and synchronizing child processes
- **File Descriptor Management**: Proper handling of input/output redirections
- **Memory Management**: Preventing leaks in a complex, long-running program
- **Signal Handling**: Implementing bash-like behavior for terminal signals

## 💻 Usage

### Prerequisites

- GCC compiler
- Make
- Readline library

### Installation

```bash
# Clone the repository
git clone https://github.com/Melis-Pablo/minishell.git
cd minishell

# Compile the program
make
```

### Running Minishell

```bash
# Launch the shell
./minishell
```

### Example Commands

```bash
# Basic command execution
$ ls -la

# Redirections
$ ls > file.txt
$ cat < file.txt

# Pipes
$ ls -la | grep .c | wc -l

# Environment variables
$ echo $HOME
$ export MY_VAR=hello
$ echo $MY_VAR

# Here document
$ cat << EOF
> This is a multi-line
> text input
> EOF

# Bonus features
$ ls *.c
$ (ls -la && echo "Success") || echo "Failure"
```

## 🛠️ Development Approach

### Parser Implementation

The command parser was implemented using a recursive descent approach:

1. **Lexical Analysis**: Breaking input into tokens (commands, arguments, operators)
2. **Syntax Analysis**: Building an abstract syntax tree from tokens
3. **Semantic Analysis**: Validating command structure before execution

### Process Management

Commands are executed using a carefully designed process management system:

```
Input: cmd1 | cmd2 | cmd3

Execution Flow:
           ┌─────┐
           │Shell│
           └──┬──┘
              │
     ┌────────┴────────┐
     ▼        ▼        ▼
┌────┐    ┌────┐    ┌────┐
│cmd1│───►│cmd2│───►│cmd3│
└────┘    └────┘    └────┘
```

### Signal Handling

Custom signal handlers ensure the shell responds appropriately to user interrupts:

- **SIGINT (Ctrl+C)**: Interrupts current command, displays a new prompt
- **SIGQUIT (Ctrl+\\)**: Ignored in interactive mode
- **EOF (Ctrl+D)**: Exits the shell gracefully

## 📝 Learning Outcomes

This project provided in-depth experience with:

- **Low-level System Programming**: Working directly with Unix system calls
- **Process Creation and Control**: Managing process execution and communication
- **Parser Design**: Building a robust command interpreter
- **Signal Handling**: Implementing custom signal responses
- **Memory Management**: Ensuring proper allocation and deallocation in a complex program

## 🔍 Testing

The implementation was tested against various scenarios:

- Complex command combinations with pipes and redirections
- Edge cases in quoting and variable expansion
- Signal handling during different execution states
- Memory leak detection using Valgrind
- Comparison with bash behavior for reference

## 📖 Resources

For detailed project requirements, see the [minishell.md](minishell.md) file.

---

*This project is part of the 42 School Common Core curriculum.*