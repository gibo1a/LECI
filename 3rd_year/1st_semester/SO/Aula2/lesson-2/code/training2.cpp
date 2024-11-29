#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "delays.h"
#include "process.h" 

int main(void)
{
  for(int i = 0;i <= 39;i++){
    printf("%s","=");
  }
  printf("\n");
  pid_t ret = pfork();
  if (ret == 0)
  {
    pexecl("/usr/bin/ls","./ls","-l",NULL);
  }
  else
  {
    pwait(NULL);
    for(int i = 0;i <= 39;i++){
        printf("%s","=");
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}