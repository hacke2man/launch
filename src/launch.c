#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char * argv[])
{
  char * home = getenv("HOME");
  char path[PATH_MAX];
  sprintf(path, "%s/.local/share/launch/launch-command-pipe", home);
  FILE * fp = fopen(path, "w");

  int sum = 0;
  for (int i = 1; i < argc; i++) {
    sum += strlen(argv[i]) + 1;
  }

  char tmps[sum + 1];
  for (int i = 1; i < argc; i++) {
    strcat(tmps, argv[i]);
    strcat(tmps, " ");
  }
  strcat(tmps, "\n");

  fputs(tmps, fp);
  printf("%s", tmps);
  fclose(fp);
}
