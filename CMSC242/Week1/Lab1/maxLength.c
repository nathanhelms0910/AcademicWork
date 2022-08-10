#include "main.h"
#include <string.h>


int maxLength(char max[][10], int n)
{
  int maxLength = 0;
  for(int i = 0; i < n; i++)
  {
    if(strlen(max[i]) > maxLength) {
      maxLength = strlen(max[i]);
    }
  }
  return maxLength;
}
