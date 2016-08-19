#include <stdio.h>

#include "debug.h"

#if defined DEBUG3
#define DEBUG2
#endif

#if defined DEBUG2
#ifndef DEBUG1
#define DEBUG1
#endif
#endif

void myprintf3(const char *s)
{
#if defined DEBUG3
      fprintf(stderr, "%s", s);
#endif
}

void myprintf2(const char *s)
{
#if defined DEBUG2
      fprintf(stderr, "%s", s);
#endif
}

void myprintf1(const char *s)
{
#if defined DEBUG1
      fprintf(stderr, "%s", s);
#endif
}


