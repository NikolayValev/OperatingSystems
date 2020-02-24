#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int myfib(int n)
{
  if (n <= 1)
    return 1;
  return myfib(n - 1) + myfib(n - 2);
}
void *print_to_file(void *n)
{
  int temp_number;
  char outputFilename[10] = "";
  int *userInput = (int *)n;
  sprintf(outputFilename, "Fib-%d.txt", *userInput);
  FILE *ofp = fopen(outputFilename, "w");
  if (ofp == NULL)
  {
    fprintf(stderr, "Can't open output file %s!\n", outputFilename);
    exit(1);
  }
  for (int i = 0; i < *userInput; i++)
  {
    fprintf(ofp, "%d. %d \n", i + 1, myfib(i));
  }
  fclose(ofp);
  pthread_exit(NULL);
}
int main()
{
  int n = 0;
  int i = 0;
  pthread_t worker[20];
  pthread_attr_t attr[20];
  while (1)
  {
    printf("Enter an integer between 1 and 50:");
    scanf("%i", &n);
    if (n < 0)
    {
      printf("Goodbye! \n");
      for (int j = 0; j < i; j++)
      {
        pthread_join(worker[i], NULL);
      }
      return 0;
    }
    pthread_attr_init(&attr[i]);
    pthread_create(&worker[i], &attr[i], print_to_file, &n);
    i++;
  }
  return 0;
}