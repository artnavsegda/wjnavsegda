#include <stdio.h>
#include <string.h>
#include <wjelement.h>
#include <wjreader.h>

int main(int argc, char **argv) {
  WJElement input = NULL, output = NULL, inputobj = NULL, iface = NULL;
  WJReader readjson;
  FILE *fp;
  fp = popen("./wrapper.sh", "r");
  if (fp == NULL)
  {
    puts("handle error");
    return 1;
  }
  if (!(readjson = WJROpenFILEDocument(fp, NULL, 0)))
  {
    puts("json failed to open");
    return 1;
  }

  input = WJEOpenDocument(readjson, NULL, NULL, NULL);
  //inputobj = WJEObject(input,"values",WJE_GET);
  while (iface = _WJEObject(input,"values[]", WJE_GET, &iface))
  {
    WJEDump(iface);
  }



  //output = WJEObject(NULL, NULL, WJE_NEW);
  //WJEDump(inputobj);

}
