#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "delays.h"
#include "process.h" 

int main(void)
{
  pid_t ret = pfork();
  if (ret == 0)
  {
    for(int i = 1;i <= 10;i++){
        printf("%u %s \n",i,"child");
    }
  }
  else
  {
    pwait(NULL);
    for(int i = 11;i <= 20;i++){
        printf("%u %s \n",i,"parent");
    }
  }

  return EXIT_SUCCESS;
}