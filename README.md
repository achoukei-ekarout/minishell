_This project has been created as part of the 42 curriculum by achoukei, ekarout_

---
<div align="center">

```
         _       _     _          _ _
  /\/\  (_)_ __ (_)___| |__   ___| | |
 /    \ | | '_ \| / __| '_ \ / _ \ | |
/ /\/\ \| | | | | \__ \ | | |  __/ | |
\/    \/_|_|_| |_|_|___/_| |_|\___|_|_|
```
</div>

<div align="center">

![Language](https://img.shields.io/badge/language-C-blue?style=flat-square)
![School](https://img.shields.io/badge/school-42-purple?style=flat-square)
![Status](https://img.shields.io/badge/status-finished-brightgreen?style=flat-square)

</div>

---

## Description

**Minishell** is a project from the 42 curriculum that challenges students to build a functional Unix shell from scratch in C, using `bash` as a reference.

The goal is to deeply understand how a shell works under the hood — from tokenizing raw user input to forking child processes, managing file descriptors, and handling signals. Every layer of the shell is implemented manually: the lexer, parser, expander, executor, and built-in commands.

### Features

| Feature | Details |
|---|---|
| **Interactive prompt** | Persistent prompt loop using `readline`, with command history |
| **Command execution** | Resolves binaries via `PATH`, forks with `execve` |
| **Pipes** | Chains commands with `\|`, connecting stdout → stdin |
| **Redirections** | Supports `>`, `>>`, `<`, and `<<` (heredoc) |
| **Environment variables** | Expansion of `$VAR` and `$?` (last exit status) |
| **Quoting** | Handles single quotes (literal) and double quotes (with expansion) |
| **Signals** | `ctrl-C`, `ctrl-D`, `ctrl-\` behave as in bash |
| **Built-ins** | `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` |

---

## Code Details

The shell is structured as a classic pipeline: **tokenize → parse → execute**. Each stage is isolated, making the codebase modular and easier to debug.

### Tokenisation

Raw input is scanned character by character and split into meaningful elements — commands, arguments, pipes (`|`), and redirections (`<`, `>`, `<<`, `>>`). Special care is taken to handle:

- Quoting rules (single and double quotes)
- Environment variable expansion
- Whitespace separation and edge cases (nested quotes, ambiguous redirections)

The result is a clean token stream that closely mirrors Bash's lexing behavior, and serves as input to the parser.

### Abstract Syntax Tree

The token stream is organized into a tree that reflects the logical execution of the command. Key properties:

- **Pipe nodes** are binary — left and right children map to each side of the pipe, encoding data flow naturally
- **Command nodes** are leaves — they hold the command and its arguments, as well as redirections
- The tree structure encodes operator precedence and chaining without extra bookkeeping

This separation between syntax analysis and execution keeps the codebase clean and makes complex pipelines easy to reason about.

### Execution

The AST is traversed recursively, with each node type handling its own logic:

| Node | Behavior |
|---|---|
| **Pipe** | Forks two processes, connects stdout → stdin via `pipe` + `dup2` |
| **Command** | Executes the binary via `execve`, with full `PATH` resolution |
| **Redirection** | Opens the target file and wires the appropriate file descriptor |

Exit status propagates back up the tree, and all file descriptors are properly cleaned up after each branch resolves.

---

## Instructions

### Requirements

- GCC
- GNU Make
- `readline` library — install with:
  ```bash
  sudo apt install libreadline-dev   # Debian/Ubuntu
  brew install readline              # macOS
  ```

### Compilation

```bash
# Clone the repository
git clone https://github.com/achoukei-ekarout/minishell.git
cd minishell

# Compile
make
```

### Execution

```bash
./minishell
```

### Makefile targets

```bash
make          # compile the project
make clean    # remove object files
make fclean   # remove object files and binary
make re       # full recompile from scratch
```

---

## Resources

### Documentation & references

- [**GNU Bash Reference Manual**](https://www.gnu.org/software/bash/manual/bash.html) — the primary behavioral reference for quoting, expansions, and built-ins
- [**POSIX Shell Command Language**](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — specification for standard shell syntax and semantics
- `man` pages for: `execve`, `fork`, `pipe`, `dup2`, `waitpid`, `readline`, `signal`, `sigaction`

### Tutorials & articles

- [Write a Shell in C — Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/) — accessible walkthrough of shell fundamentals
- [Bash manual: Shell Operation](https://www.gnu.org/software/bash/manual/bash.html#Shell-Operation) — step-by-step breakdown of how bash processes each line

### AI usage

AI tools (ChatGPT / Claude) were used in this project to:

- Clarify edge cases in signal handling and POSIX parsing rules
- Help interpret Valgrind output and track down memory leaks
- Explain syscall behavior (e.g. `dup2`, `waitpid` edge cases) when documentation was ambiguous

AI was **not** used to generate or write submitted source code. All logic was implemented and understood by the authors.