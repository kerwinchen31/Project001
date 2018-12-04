# Project 01: Shell
## By: Kerwin Chen and Tahmid Jamal


### Features

 * Forks to execute commands
 * Can handle awkward semicolon usage and spacing
 * Multi-command input
 * Basic redirection

### Attempted

 * Piping 
 * Double Redirection ( < > )

### Bugs

 * It takes multiple exits to quit the shell, correlating with the amount of commands taken.
 * When using redirects, you should not space.
 
### Files & Function Headers

**func.c**
 * char ** parse_args<p>
 *Input*: char * linee<p>
 *Output*: Fully eliminates extra semicolons or unecessary spaces, not in conjunction with operators, and returns pointer every individual command<p>
    
 
 * char** space_args()<p>
 *Input*: char * line<p>
 *Output*: Returns a pointer to every individual word of one command.
 
 
 * void redirect_out<p>
 *Input*: char ** args, int symbol<p>
 *Output*: Void. Redirects standard out to standard in.
 
 
 * void redirect_in()<p>
 *Input*: char ** args, int symbol<p>
 *Output*: Void. Redirects standard in to standard out.
 
 
**main.c**
 * Runs the CShell 
 
 * int run()<p>
 *Input*: char ** args <p>
 *Output*: int 
    Is used by our main function to run individual commands parsed in.
