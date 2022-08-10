#include "main.h"
#include <string.h>


int alphaCheck(char alpha[][10], int n)
{
  int a = 0;
  for(int i = 0; i < n; ++i)
  {
    if(strcmp(alpha[i],alpha[a]) < 0) {
      a = i;
    }
  }
  return a;
}
