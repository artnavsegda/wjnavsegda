#include <string.h>
#include <wjelement.h>
#include <wjreader.h>

int main(int argc, char **argv) {
  FILE * schemafile;
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

  //WJEDump(schema);

  if (WJEGet(schema,"patternProperties",NULL))
  {
    puts("type1");
    WJEDump(WJEGet(schema,"patternProperties[0]",NULL));
  }
  else if (WJEGet(schema,"properties",NULL))
  {
    puts("type2");
  }

  WJECloseDocument(schema);
}

