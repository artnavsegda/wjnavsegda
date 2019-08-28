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
    ifaceoutput = WJEObject(output, "interface", WJE_NEW);
    puts(ifaceinput->name);
    WJEString(ifaceoutput,"name",WJE_NEW,ifaceinput->name);

    char * macaddr = WJEString(ifaceinput,"macaddr",WJE_GET,"");
    if (macaddr[0])
    {
      WJEString(ifaceoutput,"macaddr",WJE_NEW,macaddr);
    }

    int defaultroute = WJEInt32(ifaceinput,"defaultroute",WJE_GET,-1);
    if (defaultroute != -1)
    {
      WJEBool(ifaceoutput,"defaultroute",WJE_NEW,(XplBool)defaultroute);
    }

    int metric = WJEInt32(ifaceinput,"metric",WJE_GET,-1);
    if (metric != -1)
    {
      WJEInt32(ifaceoutput,"metric",WJE_NEW,metric);
    }

    WJEDump(ifaceinput);
  }

  WJEDump(output);

}
