#include <wjelement.h>
#include <wjreader.h>

int main(int argc, char **argv) {
  FILE *jsonfile;
  WJReader readjson;
  WJElement doc = NULL;
  if (jsonfile = fopen(argv[1], "r"))
  {
    if (readjson = WJROpenFILEDocument(jsonfile, NULL, 0))
    {
      doc = WJEOpenDocument(readjson, NULL, NULL, NULL);
      //doc = WJEObject(NULL, NULL, WJE_NEW);
      WJEString(doc, "name", WJE_SET, "Serenity");
      WJEDump(doc);
      printf("azaza: %s\n", WJEString(doc, "name", WJE_GET, ""));
      WJECloseDocument(doc);
    }
    else
    {
      puts("file not found");
    }
  }
  else
  {
    puts("file not found");
  }
}
