# simple_shell

A minimalist Unix shell written in C — designed as an educational and compact implementation to understand how `fork`/`exec`/`wait`, command parsing, and basic memory management work in a simple shell.

This project currently implements:

* A REPL (read–eval–print loop) using `getline()`
* Input parsing with `strtok()` and dynamic buffers (`Malloc` / `Realloc` wrappers)
* Extensible builtins through a lookup table (`g_builtin[]`)
* External command execution via `fork()` + `execvp()` and `wait()`
* Clear error handling using standard exit codes (`sysexits.h`)

---

## Motivation

Building a simple shell is a classic systems programming exercise — it helps you deeply understand how Unix handles processes, system calls, memory, and text parsing. This implementation is short, cleanly structured, and easy to extend. It serves both as a learning project and a strong technical portfolio piece.

---

## Project Structure

Main files:

* `shell.c` — REPL loop, parsing, execution, and builtin table.
* `utils.c` — wrappers for `fork`, `execvp`, `wait`, and memory helpers (`Malloc`, `Realloc`, `Getcwd`).
* `builtin.c` — implementations of builtin commands (e.g., `shell_exit`).
* `shell.h` — header file with typedefs, prototypes, and macros.

---

## Implemented Features

* Prompt showing the current working directory (`getcwd`)
* Execution of external programs via `execvp`
* Example builtin: `exit`
* Basic tracking of the last command's exit status (`status`)
* Unified error reporting using standard system exit codes

---

## Compilation

Inside the project directory, run:

```bash
gcc *.c -o simple_shell -Wall -Wextra -g
```

You may rename the output binary as you prefer, e.g., `shelss`.

---

## Usage

```bash
./simple_shell
# Example session
# /home/user/simple_shell  $> ls
# shell.c  utils.c  builtin.c  shell.h
# /home/user/simple_shell  $> exit
```

---

## Memory Management Notes

* `getline()` allocates (or reallocates) the input buffer. The string returned by `shell_read_line()` must be freed by the caller.
* `shell_split_line()` returns a dynamically allocated array (`char **`) of pointers that reference **inside** the `line` buffer (since `strtok()` modifies the original string).

Correct order to free memory:

1. `free(args);` — frees the array returned by `shell_split_line`
2. `free(line);` — frees the input line buffer

Do **not** call `free(args[i])`, since those pointers refer to parts of the same `line` buffer.

---

## Adding a Builtin

1. Declare the function in `shell.h`:

   ```c
   int shell_cd(char **args);
   ```
2. Implement it in `builtin.c`.
3. Register it in the builtin table in `shell.c`:

   ```c
   t_builtin g_builtin[] = {
       { .builtin_name = "exit", .foo = shell_exit },
       { .builtin_name = "cd",   .foo = shell_cd },
       { .builtin_name = NULL }
   };
   ```

`shell_exec()` searches for `args[0]` in the table, calls the corresponding function, and stores its return code in `status`.

---

## Development & Debugging Tips

* Always compile with `-Wall -Wextra -g` for better diagnostics.
* Use `valgrind --leak-check=full ./simple_shell` to check for memory leaks or invalid memory use.
* Test corner cases: empty lines, long inputs, `Ctrl+D` (EOF), repeated spaces, and custom builtins.

---

## Known Limitations

* The parser does **not** handle quotes (`"`), escape sequences, redirections (`>`, `<`), or pipes (`|`).
* No line editing or history (e.g., `readline`).
* No background job control or signal management (`SIGINT`, `SIGTSTP`).

These limitations are intentional to keep the scope small — they’re excellent next steps once the basics are stable.

---

## Future Roadmap

* Implement more builtins: `cd`, `echo`, `status`
* Add redirection and pipes (`dup2`, `pipe`)
* Signal handling so `Ctrl+C` doesn’t kill the main shell
* Basic command history and in-line editing
* Automated tests and CI integration

---
