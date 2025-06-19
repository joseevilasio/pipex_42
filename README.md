<p align="center">
	<img src="https://img.shields.io/github/last-commit/joseevilasio/pipex_42?color=%2312bab9&style=flat-square"/>
</p>

# pipex

#### Finished in: 2024-08-04

## About

**Pipex** is a Unix-based project developed in C as part of the 42 School curriculum, focused on mastering file descriptors, process creation, and inter-process communication using pipes.

The program mimics the shell's piping behavior (e.g., `ls | grep txt`) by executing chained commands with input/output redirection. In the **bonus part**, we extended the functionality to support multiple pipes, `here_doc`, and command path resolution with flexible argument parsing.

Throughout the project, we explored:
- `fork()`, `execve()`, and `wait()` system calls
- File descriptor duplication and redirection with `dup2()`
- Handling environment paths (`PATH`) and command resolution
- Creating a shell-like environment with minimal tools

## Build

Clone the repository:
```shell
git clone https://github.com/joseevilasio/pipex_42.git
```
Enter the project directory:
```shell
cd pipex_42
```
Run `make` to build the mandatory version:
```shell
make
```
Run `make bonus` to build the extended version:
```shell
make bonus
```

## Usage

### Mandatory Version:
```shell
./pipex infile "cmd1" "cmd2" outfile
```
Example:
```shell
./pipex input.txt "grep hello" "wc -l" output.txt
```
This will execute: `< input.txt grep hello | wc -l > output.txt`

### Bonus Version:
Supports:
- Multiple commands (`cmd1 | cmd2 | ... | cmdN`)
- `here_doc` functionality for inline input

Example:
```shell
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```

## The Norm

This project follows the 42 School's "The Norm" (_Version 4_). To review the Norm, [click here](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf).

## Contributions

Issues, improvements or suggestions are welcome via pull request or GitHub issue.

### Message to Students

Understanding the flow of file descriptors and how processes interact at the system level is key to this project. Take time to visualize your pipeline and test edge cases. The bonus part is not just harder — it’s where you grow the most.
