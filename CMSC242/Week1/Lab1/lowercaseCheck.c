#include "main.h"

int lowercaseCheck(char lower[])
{
  for(int i = 0; lower[i] != '\0'; ++i) {
    if(!(lower[i] >= 'a' && lower[i] <= 'z')) {
      return 0;
    }
  }
  return 1;
}
