/*The resulting times dont add up to the time it took for the program to finish,
because the process is blocked for five seconds after sleep().
*/
#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
int main()
{
  struct utsname data;
  struct rusage usage;
  double usr_time, sys_time;
  struct timeval usr_time_start, usr_time_end;
  struct timeval sys_time_start, sys_time_end;
  int who = RUSAGE_SELF;
  getrusage(who, &usage);
  usr_time_start = usage.ru_utime;
  sys_time_start = usage.ru_stime;
  for (size_t i = 0; i <= 10000; i++)
  {
    printf(" %zu\n", i);
  }
  sleep(5);
  uname(&data);
  printf("Operating System Version: %s \n", data.version);
  printf("Machine Name: %s \n", data.nodename);
  printf("Release Level: %s \n", data.release);
  printf("Version Level: %s \n", data.version);
  printf("Hardware Platform: %s \n", data.machine);
  getrusage(who, &usage);
  usr_time_end = usage.ru_utime;
  sys_time_end = usage.ru_stime;
  usr_time = (double)(usr_time_end.tv_usec - usr_time_start.tv_usec) / (1000000);
  sys_time = (double)(sys_time_end.tv_usec - sys_time_start.tv_usec) / (1000000);
  printf("User time: %f \n", usr_time);
  printf("System time: %f \n", sys_time);
}

