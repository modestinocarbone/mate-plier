# MATE-PLIER - A Simple Calculator with Constants

MATE-PLIER is a command-line calculator program that supports basic arithmetic operations, constant values (`pi`, `e`), and nested calculations using braces `{}`. The program can process expressions with the following operators: `+`, `-`, `*`, `/`, and `^` (for exponentiation).

## Features

- Supports constants: `pi` and `e` (with values 3.14159265 and 2.71828182).
- Handles basic arithmetic operations: addition, subtraction, multiplication, division, and exponentiation.
- Allows nested expressions using curly braces `{}`.
- Interactive mode with real-time input or can accept expressions as command-line arguments.
- Built-in help command to guide users.

## Available Commands

- `:q` - Quit the program.
- `:h` - Show help instructions.
- `:c` - Clear the screen (works in UNIX-like systems).
  
## Example Usage

### Interactive Mode
```bash
MATE_PLIER:> 3+2
5.000000
MATE_PLIER:> pi*2
6.283185
MATE_PLIER:> {pi+e}/2
2.929888
MATE_PLIER:> :h
```

### Command line mode
```bash
$ mate "3+2"
5.000000
$ mate "{pi+e}/2"
2.929888
```

### Compilation and Installation

Clone this repository or download the source code and execute the makefile,
have fun.


