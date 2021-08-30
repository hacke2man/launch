#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char * argv[])
{
  umask(0);
  pid_t process_id = fork();
  // Indication of fork() failure
  if (process_id < 0)
  {
    // Return failure in exit status
    exit(1);
  }
  // PARENT PROCESS. Need to kill it.
  if (process_id > 0)
  {
    // return success in exit status
    exit(0);
  }

  //set new session
  chdir("/");
  pid_t sid = setsid();
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  execvp(argv[1], &argv[1]);
}
