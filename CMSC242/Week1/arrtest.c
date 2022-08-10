#include <stdio.h>

int arrsum (int *vals, int n)
{
  int sum = 0;
  for (int i = 0; i < n; ++i)
    sum += vals[i];
  return sum;
}

int main()
{
  int values[5];
  int n;

  values[0] = 42;
  values[1] = 10;
  values[2] = -2;
  n = 3;

  printf("%d\n", arrsum(values, n));

}

