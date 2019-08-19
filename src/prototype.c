#include <wjelement.h>
#include <wjreader.h>

int main(int argc, char **argv) {
  FILE *jsonfile, *schemafile;
  WJReader readjson, readschema;
  WJElement doc = NULL, schema = NULL;
  WJElement entity = NULL, parameter = NULL;
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
    printf("entity : %s\n", WJEString(entity, "name", WJE_GET, ""));

    while (parameter = _WJEObject(schema, "items.properties[]", WJE_GET, &parameter))
    {
      printf("parameter name: %s\n", parameter->name);
      printf("parameter type: %s\n", WJEString(parameter, "type", WJE_GET, ""));
      printf("parameter value: %s\n", WJEString(entity, parameter->name, WJE_GET, ""));
    }
  }

      //doc = WJEObject(NULL, NULL, WJE_NEW);
      //WJEString(doc, "name", WJE_SET, "Serenity");
      //WJEDump(doc);
      //printf("azaza: %s\n", WJEString(doc, "name", WJE_GET, ""));

      WJECloseDocument(doc);
      WJECloseDocument(schema);
}

