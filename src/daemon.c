#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>


char ** getargs(char * str)
{
  int numargs = *str != ' ' ? 1: 0;
  int remaining;
  int stringLength = strlen(str);
  for(int i = 0; i < stringLength; i++)
  {
    remaining = stringLength - (i + 1);

    if(str[i] == ' ' && remaining > 2 && str[i + 1] != ' ')
      numargs++;
  }

  char ** args = malloc(sizeof(char *) * numargs + 1);
  args[numargs] = NULL;
  char * argstart = str;
  char * argend;
  for(int i = 0; i < numargs; i++)
  {
    while(*argstart == ' ')
      argstart = &argstart[1];

    argend = argstart;
    while(*argend != ' ')
      argend = &argend[1];

    *argend = '\0';
    args[i] = malloc(sizeof(char) * strlen(argstart) + 1);
    strcpy(args[i], argstart);

    *argend = ' ';
    argstart = argend;
  }
  return args;
}

void checkpipe()
{
  char * home = getenv("HOME");
  char path[PATH_MAX];
  sprintf(path, "%s/.local/share/launch/launch-command-pipe", home);
  FILE* pipe = fopen(path, "r");
  if(pipe == NULL)
  {
    printf("Command pipe not found\n");
    exit(1);
  }

  char c;
  char str[1000] = {'\0'};
  char tmp[2] = {' ', '\0'};
  while(fread(&c, sizeof(char), 1, pipe))
  {
    *tmp = c;
    strcat(str, tmp);
  }
  fclose(pipe);

  *strchr(str, '\n') = '\0';

  char ** args = getargs(&str[1]);
  if(!fork())
  {
    printf("%d", execvp(args[0], args));
    exit(0);
  }
}

int main(){
  while(1)
    checkpipe();
}
