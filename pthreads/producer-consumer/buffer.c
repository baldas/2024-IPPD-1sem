#include <assert.h>

static int buffer;
static int size = 0;

int buffer_is_empty()
{
  return size == 0;
}

int buffer_is_full()
{
  return size == 1;
}

void buffer_put (int value)
{
  assert(size == 0);
  size = 1;
  buffer = value;
}

int buffer_get()
{
  assert(size == 1);
  size = 0;
  return buffer;
}
