# Minishell

A lightweight Unix shell written in C, inspired by Bash and designed as a 42 project. It implements command parsing, environment management, builtins, pipes, redirection, heredoc support, and interactive signal handling.

## Features

- Shell prompt using GNU Readline
- Parsing and tokenization of user input
- Environment variable expansion
- Quoting and argument handling
- Builtins:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Pipes: `|`
- Redirections:
  - input: `<`
  - output: `>`
  - append: `>>`
  - heredoc: `<<`
- Process execution and exit status management
- Signal handling for interactive shell behavior

## Requirements

- Linux operating system
- `cc` or `gcc`
- `readline` development library
- `ncurses` library

## Build

From the project root, run:

```bash
make
```

This compiles the project into an executable named `minishell`.

## Run

```bash
./minishell
```

You should see a prompt similar to:

```bash
minishell>
```

## Example Usage

```bash
minishell> echo hello
hello

minishell> pwd
/home/user/project

minishell> export TEST=hello

minishell> echo $TEST
hello

minishell> ls -l | grep minishell
-rw-r--r--  1 user user  ... README.md

minishell> cat << EOF
hello from heredoc
EOF
```

## Project Structure

- `Execution/` — command execution, builtins, pipes, redirections, environment utilities
- `Parsing/` — lexer, parser, expansion, heredoc handling, token management, signal logic
- `Makefile` — build rules
- `minishell.h` — project headers and data structures

## Notes

This is a simplified shell implementation, not a full Bash clone. It supports the core features expected for a minishell-style project and is intended to behave like a real interactive shell for common command-line workflows.

## Exit

You can leave the shell using:

```bash
exit
```

or by pressing `Ctrl-D`.
