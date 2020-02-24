#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define N_WORKERS 50
#define SIZE_NAME 11
int myfib(int n)
{if (n <= 1)
        return 1;
return myfib(n - 1) + myfib(n - 2);
}
DWORD WINAPI writefib(LPVOID n)
{
    FILE* ofp;
    char outputFilename[SIZE_NAME];
    int* input = (int*)n;
    sprintf_s(outputFilename, SIZE_NAME, "Fib-%i.txt", *input);
    fopen_s(&ofp, outputFilename, "w");
    if (ofp == NULL)
    {
        fprintf(stderr, "Can't open output file %s!\n", outputFilename);
        exit(1);
    }
    for (int i = 0; i < *input; i++)
    {
        fprintf(ofp, "%u. %u \n", i + 1, myfib(i));
    }
    fclose(ofp);
    return 0;
}
int main()
{
    HANDLE worker[N_WORKERS];
    char buffer[SIZE_NAME];
    int input = 0;
    int i = 0;
    while (1)
    {
        printf("Enter an integer between 1 and 50:\nEnter -1 to exit!\n");
        scanf_s("%i", &input);
        if (input == -1)
        {
            WaitForMultipleObjects(i, worker, TRUE, INFINITE);
            for (int j = 0; j < i; j++)
            {
                CloseHandle(worker[j]);
            }
        }
        if (input < 0) { continue;}
        worker[i] = CreateThread(NULL, 0, writefib, &input, 0, NULL);
        i++;
    }
}