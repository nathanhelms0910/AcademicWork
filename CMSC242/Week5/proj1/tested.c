#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
int main()
{
    int num;
    bool boolVal = true;
    
    while(boolVal) {
      fscanf(stdin, "%d", &num);
      if(num == 0) {
	printf("End of Testing\n");
	boolVal = false;
      }
      else if(num < 0) {
	printf("Error\n");
	boolVal = false;
      }
      else {
	num = num / 2;
	sleep(1);
	printf("Num halved is: %d\n", num);
      }
    }
  }
  
