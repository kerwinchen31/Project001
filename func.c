#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <errno.h>

#include <sys/wait.h>

#include <signal.h>

#include <sys/stat.h>

#include <fcntl.h>

#include "func.h"

char ** parse_args(char * linee) {

  char * line = malloc(strlen(linee) * sizeof(char));

  strncpy(line, linee, strlen(linee) - 1);

  line[strlen(linee)] = '\0';

  //printf("made line%sx\n", line);

  char * copy = malloc(strlen(line) * sizeof(char));

  int i, j = 0;

  while (i < strlen(line)) {

    if (line[i] == ' ') {

      if (i == 0) {

        while (line[i] == ' ') {

          i++;

        }

      }

      while (line[i + 1] == ' ') {

        i++;

      }

      while (line[i + 1] == ';') {

        i++;

      }

      if (line[i +1] == '\0') {

	j++;

	break;

      }

    }

    copy[j] = line[i];

    if (line[i] == ';') {

      while (line[i + 1] == ';') {

 i++;

      }

      while (line[i + 1] == ' ') {

        i++;

      }

      if (line[i + 1] == '\0') {

        j++;

        break;

      }

    }

    if (line[i + 1] == '\0') {

      j++;

      break;

    }

    i++;

    j++;

  }

  copy[j] = '\0';

  i = 0;

  j = 0;

  //printf("%sx\n", copy);

  //printf("bb%c\n", copy[strlen(copy) - 1]);

  if (copy[strlen(copy) - 1] == ';') {

    copy[strlen(copy) - 1] = '\0';

  }

  char ** separated = calloc(6, sizeof(char * ));

  while (copy) {

    separated[i] = strsep( & copy, ";");

    i++;

  }

  separated[i] = NULL;

  //while (separated[j]) {

  //  printf("%s|", separated[j]);

  //  j++;

  //}

  //printf("\n");

  return separated;

}

char ** space_args( char *line) {

  // I don't want to modify line.

  char *dummy = malloc(strlen(line) * sizeof(char));

  strcpy(dummy, line);

  // At most 5 arguments of strings (array of chars / char pointers) 

  char **separated = calloc( 6 , sizeof(char*) );

  

  for (int i = 0; dummy; i++) { 

    // i is the current arg of separated, dummy keeps getting split until you hit the NULL at the end

    separated[i] = strsep(&dummy, " "); 

    //printf("%s \n", separated[i]);

  }

  return separated; 

}

void redirect_out(char ** args, int symbol){

  int backup = dup(1);

  int fd = open(args[symbol + 1], O_WRONLY | O_CREAT, 777);

  dup2(fd, 1);

  args[symbol] = NULL;

  execvp(args[0], args);

  dup2(backup, 1);

  close(fd);

}



void redirect_in(char ** args, int symbol){

  int backup = dup(0);

  int fd = open(args[symbol + 1], O_RDONLY, 777);

  dup2(fd, 0);

  args[symbol] = NULL;

  execvp(args[0], args);

  dup2(backup, 0);

  close(fd);

}
