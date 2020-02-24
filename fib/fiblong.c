#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1
long fib(long n)
{
  if (n <= 1)
    return n;
  return fib(n - 1) + fib(n - 2);
}

int main()
{
  FILE *ofp;
  long pfd[2];
  int pid1, pid2;
  int retval;
  char outputFilename[10] = "";
  int n = 1;
  while (1)
  {
    printf("Enter an integer between 1 and 50:");
    scanf("%i", &n);
    if (n < 0 || n > 50)
    {
      printf("Goodbye! \n");
      return 0;
    }
    sprintf(outputFilename, "Fib-%d.txt", n);
    if (pipe(pfd) != 0)
    {
      fprintf(stderr, "Pipe creation failed!");
    }
    pid1 = fork();
    if (pid1 == 0)
    {
      for (int i = 1; i <= n; i++)
      {
        long fib_number = fib(i);
        write(pfd[WRITE_END], &fib_number, sizeof(long));
      }
      exit(0);
    }
    else
    {
      pid2 = fork();
      if (pid2 == 0)
      {
        ofp = fopen(outputFilename, "w");
        if (ofp == NULL)
        {
          fprintf(stderr, "Can't open output file %s!\n", outputFilename);
          exit(1);
        }
        for (int i = 1; i <= n; i++)
        {
          long fibonacci;
          read(pfd[READ_END], &fibonacci, sizeof(long));
          fprintf(ofp, "%d. %ld \n", i, fibonacci);
        }
        fclose(ofp);
        exit(0);
      }
      wait(NULL);
    }
  }
  return 0;
}