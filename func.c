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


//is given a line from user input to fully parse and remove unnecessary
//semicolons and spacing (keeps spacing for operators)
//arguments: *linee, the line from user
//returns: char**, each pointer points to separate command of user

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

//after being given individual command, parses them into their components
//arguments: char *line, a command
//returns: char **, each pointer points to a component "word" of the command

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

//redirects standard in to standard out
//arguments: char **args, int symbol, we want to know what operator is being used on what commands
//returns: void
void redirect_out(char ** args, int symbol){

  int backup = dup(1);

  int fd = open(args[symbol + 1], O_WRONLY | O_CREAT, 777);

  dup2(fd, 1);

  args[symbol] = NULL;

  execvp(args[0], args);

  dup2(backup, 1);

  close(fd);

}


//redirects standard out to standard in
//arguments: same as previous
//returns: n/a
void redirect_in(char ** args, int symbol){

  int backup = dup(0);

  int fd = open(args[symbol + 1], O_RDONLY, 777);

  dup2(fd, 0);

  args[symbol] = NULL;

  execvp(args[0], args);

  //dup2(backup, 0);

  //close(fd);

}
/*
  void redirect_inout(char ** args, int in, int out){
  
  int backupin = dup(0);
  int backupout = dup(1);
  int fdin = open(args[in + 1], O_RDONLY, 777);
  int fdout = open(args[out + 1], O_WRONLY | O_CREAT, 777);
  dup2(fdin, 0);
  dup2(fdout, 1);
  args[in] = NULL;
  printf("PLEASE WORK\n");
  execvp(args[0], args);

  dup2(backupin, 0);
  dup2(backupout, 1);
  close(fdin);
  close(fdout);
  }
*/

//void execp_pipe(char *arg1, char *arg2) {
//   int fd[2];
//   pipe(fd);
//   int f1 = fork();
 // if (f1) {
//      int f2 = fork();
//      if (f2) {
//              close(fd[0]);
//              close(fd[1]);
//              int statusf1, statusf2;
//              waitpid(f1, &statusf1, 0);
//              waitpid(f2, &statusf2, 0);
//              if (WIFEXITED(statusf1)) {
//                      WEXITSTATUS(statusf1);
//              }
//              if (WIFEXITED(statusf2)) {
//                      WEXITSTATUS(statusf2);
//              }
//      }
//      else {
//              close(fd[WRITE]);
//              dup2(fd[READ], STDIN_FILENO);
//              execvp(arg2[0], arg2);
//              close(fd[READ]);
//              exist(EXIT_SUCCESS);
//      }
//   }
//   else {
//      close(fd[READ]);
//      dup2(fd[WRITE], STDOUT_FILENO);
//      execvp(arg1[0], arg1);
//      close(fd[WRITE]);
//      exist(EXIT_SUCCESS);
//}}
