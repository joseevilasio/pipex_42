# pipex
This project is about handling pipes.

## About
The Pipex project focuses on exploring a fundamental UNIX mechanism—pipes—by implementing them in a C program. The goal is to recreate the behavior of shell piping commands, enabling the redirection of input and output between processes. The program accepts file names and commands as arguments, mimicking the shell operation < file1 cmd1 | cmd2 > file2.

Key Features:

- Handles standard shell commands using pipes.
- Manages memory allocation and deallocation to prevent leaks.
- Adheres to strict coding norms, ensuring robustness and error handling.
  
Bonus Features:

- Supports **multiple pipes**, allowing chaining of several commands like ```< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2 ```.
- Implements **heredoc**, handling the input redirection (<< LIMITER) to read from a given limiter and appending output (>>) to the target file. For example, ```cmd << LIMITER | cmd1 >> file```.
## Build
To compile the library, simply use the makefile targets on the command line within the 'src' folder.
```
./src/make
```

## Usage

