#include <stdio.h>
#include <stdlib.h>

void payload()
{
  printf("You got here. \n");
  exit(0);
}

void vuln_func()
{
  char buffer[2048];
  printf("%p\n", buffer);
  fgets(buffer, 3000, stdin);
}

int main(int argc, char* argv[])
{
  vuln_func();
}
