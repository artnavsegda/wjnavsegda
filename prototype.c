#include <wjelement.h>
#include <wjreader.h>

int main(int argc, char **argv) {
  FILE *jsonfile, *schemafile;
  WJReader readjson, readschema;
  WJElement doc = NULL, json = NULL;
  if (!(jsonfile = fopen(argv[1], "r")))
  {
    puts("json not found");
    return 1;
  }
  if (!(schemafile = fopen(argv[2], "r")))
  {
    puts("schema not found");
    return 1;
  }

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
