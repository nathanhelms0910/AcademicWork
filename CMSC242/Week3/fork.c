#include <stdio.h>
#include <unistd.h>

int main() {

  printf ("Hi\n");

  int pid = fork();

  printf ("Hi again\n", pid);



  if(pid != 0) {
    printf("Parent\n");
  }
  else {
    printf("Child\n");

  }
}
