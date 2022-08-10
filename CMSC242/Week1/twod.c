#include <stdio.h>
#include <string.h>

void print_initials (char w[][5], int n) 
{
  for(int i = 0; i < n; ++i)
    printf ("%c", w[i][0]);
  printf("\n");
}

int main()
{
  char words[2][5];

  strncpy(words[0], "foo", 4);
  strncpy(words[1], "blah", 4);

  for (int i = 0; i < 2; ++i)
    printf("%s\n", words[i]);

  print_initials(words, 2);

}
