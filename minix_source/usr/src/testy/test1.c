#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char** argv)
{
  printf("Get oppid of process with pid 123 - does not exist\n");
  assert(getoppid(123) == -1);
  assert(errno = EINVAL);
  printf("OK\n");
}
