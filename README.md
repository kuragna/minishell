# Minishell - Recreating a partial shell (BASH)

This program attempts to recreate a shell following BASH. It allows the user to write multiples prompts to the program and outputs the desired results from those prompts. Similarly to Bash, our Minishell project should never crash; it should always give the prompt back to the user. It doesn't handle AND (&&), OR (||) nor does it handle priority with parentheses and ';'. It also doesn't consider the execution of background jobs in bash.

Our program allows for the execution of multiple tokens separated by pipes and has a working history. We also implemented redirections to i/o files, handled environment variables, signals (CTRL-c || CTRL-d || CTRL-\\) and quotes. Lastly, we recreated the following builtins for our project, always following bash as a reference: 
 * echo with option -n
 * cd with only a relative or absolute path
 * pwd with no options
 * export with no options
 * unset with no options
 * env with no options or arguments
 * exit with no options

 The readline library that we used for this project does contain leaks so apart from those, our program should be plague-free.

## Installation

```bash
git clone https://github.com/kuragna/minishell
cd minishell && make
./minishell
```

## The Neet and Greedy: How did we do it

### Basics of a shell

A shell is a program which takes a prompt from the user (strings of characters), interprets them as individual tokens (tokenizer) and categorizes them based on their respectives lexical order (lexer). It proceeds to execute these tokens to output the desired result back to the user. To understand any shell, it is important to understand the lexer side of the shell, the parsing side and its executing side.

### The lexer side
The lexer side takes a user's prompt and converts it into an ordered list of tokens, with each token having a lexical value. Our program's lexing grammar is consisted of words, redirections, pipes and newline. We defined a token as a character or string of characters that were delimited by a space or a newline (aka the end of the prompt) or by a delimitor (which could be a redirection or pipe). 

### The parser side

The parser takes tokens, categorizes them following our grammar and stores them in an abstract syntax tree. By using of a top-down approach:
* for each iteration, we would check if the position was bigger than our prompt len -> if yes that means that we are at the end of the prompt -> so the type is NEWLINE
1. is the current token a PIPE -> if yes then the type is PIPE; if no, we go to "2"
2. is the current token a REDIR -> if yes, the type is REDIR and the next token type is a WORD; if no, we go to "3"
3. the current token type is WORD

In order to store our tokens, we made use of the Abstract Syntax Tree (AST) structure. We chose the AST as it makes the execution part of this program much more efficient and easy to code. 

### The execution side

The execution side is pretty self-explanatory; it takes our categorized tokens from our AST and executes them returning the result as an output to the user. The first thing to be done is to make a copy of the current environment to our program so that we are able to manipulate it in later stages (i.e. with export, unset, built-in). Depending on the token type passed to our exeutor, the program will one of two functions:
`ms_exec_pipe` to execute a PIPE node or `ms_exec_cmd` to execute a CMD node.

> [!NOTE]
> CMD nodes contain the base command, the options associated to that command and the redirections (if provided) linked to that command.

If `ms_exec_pipe` is called, the function will change the I/O to the corresponding file descriptors allowing the output of a command to become the input of the next command if both commands were delimited by a pipe. It would then execute the left nodes of the AST, change the I/O to prepare the execution of the right nodes of the AST and execute the right nodes. Its last action is to close all the file descriptors it opened.

If `ms_exec_cmd` is called, it will go through the following conditions:
1. does the current cmd have the REDIR type -> if yes: it calls the `ms_io_handle` function to redirect input and output to their corresponding locations; go to "2"
2. is the current cmd a builtin -> if yes: it calls the `ms_exec_in` function to execute them as builtins and returns 0; else go to "3"
3. it will fork the current process and execute the external commands.
That's it.

## References

* [Shell Grammar](https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html)
* [The parser and AST](https://ruslanspivak.com/lsbasi-part1/)
* [Bash Reference](https://www.gnu.org/software/bash/manual/bash.html)
