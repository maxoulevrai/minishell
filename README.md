*This project has been created as part of the 42 curriculum by yzidani and maleca.*

# minishell

## Description
`minishell` is a small Unix shell implementation inspired by Bash.

The goal of the project is to understand how a shell works internally by rebuilding core behaviors from scratch in C:
- prompt loop and user input handling,
- tokenization and parsing,
- environment variable expansion,
- execution of commands and pipelines,
- redirections,
- built-ins (`cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`),
- process management and signals.

This project is primarily focused on low-level programming skills: memory management, file descriptors, `fork`/`execve`, inter-process communication with pipes, and robust error handling.

## Instructions
### Requirements
- Linux (or Unix-compatible environment)
- `cc`
- `make`
- `readline` development library

### Compilation
From the repository root:

```bash
make
```

Useful targets:

```bash
make clean
make fclean
make re
```

### Execution
After compilation:

```bash
./minishell
```

### Notes
- The shell is interactive and displays its own prompt.
- To exit, use `exit` or `Ctrl-D`.
- If needed, a Valgrind suppression file is available: `valgrind_readline_leaks_ignore.supp`.

## Resources
Classic references used for shell-related concepts:

1. POSIX Shell Command Language
https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
2. Bash Reference Manual
https://www.gnu.org/software/bash/manual/bash.html
3. GNU Readline Documentation
https://tiswww.case.edu/php/chet/readline/rltop.html
4. Linux man pages (`man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`, `man 7 signal`)
https://man7.org/linux/man-pages/
5. Advices I wish I had been given before I start minishell
https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b
6. Writing your own Shell
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
7. Minishell: Building a mini-bash
https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

### AI Usage
AI was used as an assistant for:
- drafting and structuring this README,
- providing wording and clarity improvements,
- testing, fixing a few issues and resolving tedious tasks.

AI was not used as an autonomous replacement for project implementation decisions. Final code choices, integration, and validation remained under student control.
