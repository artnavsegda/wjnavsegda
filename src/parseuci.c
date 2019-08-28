#include <stdio.h>
#include <string.h>
#include <wjelement.h>
#include <wjreader.h>

int main(int argc, char **argv) {
  WJElement input = NULL, output = NULL, ifaceinput = NULL, ifaceoutput = NULL;
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
  output = WJEArray(NULL, NULL, WJE_NEW);
  while (ifaceinput = _WJEObject(input,"values[]", WJE_GET, &ifaceinput))
  {
    //puts(ifaceinput->name);
    //WJEDump(ifaceinput);
    ifaceoutput = WJEObject(output, "interface", WJE_NEW);
    WJEString(ifaceoutput,"name",WJE_NEW,ifaceinput->name);
  }

  WJEDump(output);

}
