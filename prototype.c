#include <wjelement.h>
#include <wjreader.h>

int main(int argc, char **argv) {
  FILE *jsonfile, *schemafile;
  WJReader readjson, readschema;
  WJElement doc = NULL, schema = NULL;
  WJElement entity = NULL;
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
  if (!(readjson = WJROpenFILEDocument(jsonfile, NULL, 0)))
  {
    puts("json failed to open");
    return 1;
  }
  if (!(readschema = WJROpenFILEDocument(schemafile, NULL, 0)))
  {
    puts("schema failed to open");
    return 1;
  }
  doc = WJEOpenDocument(readjson, NULL, NULL, NULL);
  schema = WJEOpenDocument(readschema, NULL, NULL, NULL);

  while (entity = _WJEObject(doc, "[]", WJE_GET, &entity))
  {
    printf("puk\n");
    printf("name: %s\n", WJEString(entity, "name", WJE_GET, ""));
  }

  while (entity = _WJEObject(schema, "items.properties[]", WJE_GET, &entity))
  {
    printf("byk\n");
  }


      //doc = WJEObject(NULL, NULL, WJE_NEW);
      //WJEString(doc, "name", WJE_SET, "Serenity");
      //WJEDump(doc);
      //printf("azaza: %s\n", WJEString(doc, "name", WJE_GET, ""));

      WJECloseDocument(doc);
      WJECloseDocument(schema);
}
