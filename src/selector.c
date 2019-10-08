#include <string.h>
#include <wjelement.h>
#include <wjreader.h>

int main(int argc, char **argv) {
  *schemafile;
  WJReader readschema;
  WJElement schema = NULL;
  if (!(schemafile = fopen(argv[1], "r")))
  {
    puts("schema not found");
    return 1;
  }
  if (!(readschema = WJROpenFILEDocument(schemafile, NULL, 0)))
  {
    puts("schema failed to open");
    return 1;
  }
  schema = WJEOpenDocument(readschema, NULL, NULL, NULL);

  WJEDump(schema);

  WJECloseDocument(schema);
}

