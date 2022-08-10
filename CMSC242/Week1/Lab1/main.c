#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

int main()
{

  char words1[5][10];
while(1) 
{ 
  for(int i = 0; i < 5; ++i)
  {
   
    scanf("%11s", words1[i]);
    if(strcmp("DONE",words1[i]) == 0) {
      printf("First: %s\n", words1[alphaCheck(words1, i)]);
      printf("Longest: %d\n", maxLength(words1, i));
      exit(0);
      
    }
    if(lowercaseCheck(words1[i]) == 0 || strlen(words1[i]) > 10) {
	printf("Error\n");
	exit(0);
    }

  }
  printf("First: %s\n", words1[alphaCheck(words1, 5)]);
  printf("Longest: %d\n", maxLength(words1, 5));

}
}



