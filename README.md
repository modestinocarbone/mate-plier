# MATE-PLIER - A Simple Expression Evaluator

MATE-PLIER is a command-line calculator program that supports basic nested arithmetic operations calculations using parenthesis `(`, `)`. The program can process expressions with the following operators: `+`, `-`, `*`, `/`, and `^` (for exponentiation).


## Available Commands

- `:q` - Quit the program.
- `:h` - Show help instructions.
- `:c` - Clear the screen (works in UNIX-like systems).
  
### Interactive Mode
```bash
MATE_PLIER:>3+2+32*2
69
MATE_PLIER:>cos(3.14)
-0.999999
MATE_PLIER:>sin(22)^2+cos(22)^2
1
MATE_PLIER:>3+2/7
3.285714
MATE_PLIER:>:q
```
## Available functions

|eval func| Explaination |
| -------- | ------- |
|exp(x)	| Exponential function (e^x) | 
|sin(x)	| Sine of angle x (in radians) |
|cos(x)	| Cosine of angle x (in radians)|
|tan(x) |	Tangent of angle x (in radians)|
|log(x) |	Base-10 logarithm of x	|
|ln(x)	| Natural logarithm (base e) of x|

## Dependencies

Make sure the libedit development library is installed. On Ubuntu/Debian, use the following command:

```bash
sudo apt-get update
sudo apt-get install libedit-dev
```

### Compilation and Installation

Clone this repository or download the source code and execute the makefile,
have fun.


