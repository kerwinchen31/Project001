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

//is given a pointer which points to components of one command
//and attempts to execute the commands
//arguments: char **args, which is taken from space_args()
//returns: int
int run(char **args){
  int a;
  if (!strcmp(args[0], "cd")){
    char *dir = args[1];
    int new = chdir(dir);
  }
  a = fork();
  if (!a){
    int i = 0;
    for (; args[i]; i++){}
    if (i >= 5){
      if(!strcmp(args[i - 2], ">") && !strcmp(args[i - 4], "<")){
	//args[i - 2] = NULL;
	//redirect_out(redirect_in(args, i - 4), i - 2);
	//redirect_inout(args, i - 4, i - 2);
      }
    }
    if (i >= 3){
      if (!strcmp(args[i - 2], "<")){
	redirect_in(args, i-2);
      }else if(!strcmp(args[i - 2], ">")){
	redirect_out(args, i-2);
      }else{
	return execvp(args[0], args);
      }
    }else{
      return execvp(args[0], args);
    }
  }else{
    int status;
    wait(&status);
    return WEXITSTATUS(status);
  }
}
      
//prints directory path, and is always waiting for new functions
//arguments: n/a
//returns: n/a
int main(){
  int keepRunning = 1;
  while(keepRunning){
    //signal(SIGTERM, sighandler);
    printf("%s Shell~$ ", getcwd(0,0));
    char line[128];
    fgets(line, 128, stdin);
    //for (int j = 0; line[j]; j++) {
    //  printf("%d| %c->", j, line[j]);
    //}
    char ** args = parse_args( line );
    for (int i = 0; args[i]; i++) {
      if (!strcmp(args[i], "exit")){
	//keepRunning = 0;
	//printf("GOTCHA\n");
	exit(0);
      }
      char ** input = space_args(args[i]);
      run(input);
      // printf("%s", line);
    }
  }
  
  return 0;
}
