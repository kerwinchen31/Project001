#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

char ** parse_args( char *linee);

char ** space_args( char *line);

void redirect_out(char ** args, int symbol);

void redirect_in(char ** args, int symbol);
