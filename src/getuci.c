#include <string.h>
#include <wjelement.h>
#include <wjreader.h>

char * linefy(char * marker)
{
  char * pch = strpbrk(marker,"\n\t");
  while (pch != NULL)
  {
    *pch = ' ';
    pch = strpbrk(pch,"\n\t");
  }
}

int main(int argc, char **argv) {
  WJElement arg = NULL;
  arg = WJEObject(NULL, NULL, WJE_NEW);
  WJEString(arg, "config", WJE_SET, "network");
  WJEString(arg, "type", WJE_SET, "interface");

  char * something = WJEToString(arg, TRUE);
  linefy(something);
  puts(something);
}
