*This project has been created as part of the 42 curriculum by lclodic, mnicolas.*

# Minishell

## Description

Minishell is a minimalist Unix shell written in C, developed as part of the 42
curriculum. The goal is to build a simplified reimplementation of `bash`,
covering the full pipeline: reading a line from the user, tokenising it,
parsing it into an abstract command tree, expanding environment variables and
quotes, setting up pipes and redirections, forking processes, executing
commands, and finally collecting their exit statuses. It is a deep dive into
processes, file descriptors, signals and the POSIX API.

The project deliberately restricts itself to a small, tightly controlled set
of allowed external functions and enforces the 42 norm on every source file.

## Instructions

### Compilation

```sh
make            # builds the libft, then compiles minishell
make clean      # removes object files
make fclean     # removes object files + the minishell binary
make re         # full rebuild
```

The binary `minishell` is produced at the project root. It is linked against
GNU `readline` (`-lreadline`), which must be available on the system.

### Running

```sh
./minishell
```

An interactive prompt is displayed. Type commands as you would in `bash`. Use
`ctrl-C` to clear the current line, `ctrl-D` to exit, and `ctrl-\` is ignored
in interactive mode.

The shell can also read commands from a pipe for non-interactive use:

```sh
echo "ls -la | grep minishell" | ./minishell
```

### Supported features

- Interactive prompt with working history (`readline` / `add_history`)
- Command search through the `PATH` variable, plus absolute and relative paths
- Built-ins: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Redirections: `<`, `>`, `<<` (heredoc), `>>`
- Pipelines with `|`
- Environment variable expansion (`$VAR`) and last exit status (`$?`)
- Single quotes (no interpretation) and double quotes (interpretation except `$`)
- Signal handling for `ctrl-C`, `ctrl-D`, `ctrl-\` matching `bash`'s interactive
  behaviour

## Resources

### Classic references

- `man bash`, `man readline`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`,
  `man 7 signal`
- POSIX specification for shells:
  https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
- GNU readline documentation:
  https://tiswww.case.edu/php/chet/readline/readline.html
- 42 subject PDF (v10.0)

### Use of AI

AI assistants (Claude, ChatGPT) were used as a complement to classical
documentation and peer review, never as a substitute for understanding. More
precisely:

- **Brainstorming and high-level design.** We discussed the parser / executor
  boundary, data-structure choices for the command list and heredoc handling
  strategies with the AI before writing code ourselves.
- **Rubber-ducking edge cases.** Tricky bash behaviours around quoting,
  environment expansion inside double quotes, `$?` timing and exit-status
  propagation through pipelines were clarified by asking the AI to explain
  bash's reference behaviour, which we then verified against a real `bash`.
- **Norm-driven refactoring.** Once the core logic worked, AI was used to
  suggest clean ways to split oversized functions into 25-line 42-norm
  compliant helpers.
- **Documentation.** This README was drafted with AI assistance and reviewed
  and edited by hand.
