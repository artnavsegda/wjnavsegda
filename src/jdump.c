#include <string.h>
#include <wjelement.h>
#include <wjreader.h>

WJElement getelementbynameprop(WJElement container, char * text)
{
  WJElement entity = NULL;
  while (entity = _WJEObject(container, "[]", WJE_GET, &entity)) {
    if (strcmp(WJEString(entity, "name", WJE_GET, ""), text) == 0) {
      return entity;
    }
  }
}

int main(int argc, char **argv) {
  FILE *jsonfile, *schemafile;
  WJReader readjson, readschema;
  WJElement doc = NULL, schema = NULL;
  WJElement entity = NULL, parameter = NULL, enumoption = NULL;
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
    //printf("%s.", WJEString(entity, "name", WJE_GET, ""));

    while (parameter = _WJEObject(schema, "items.properties[]", WJE_GET, &parameter))
    {
      printf("%s.", WJEString(entity, "name", WJE_GET, ""));
      printf("%s = ", parameter->name);
      //printf("%s = ", WJEString(parameter, "type", WJE_GET, ""));
      printf("%s\n", WJEString(entity, parameter->name, WJE_GET, "None"));
    }
  }

      if (WJEArrayF(schema, WJE_GET, NULL, "items.properties.mode.enum"))
      {
        while (enumoption = WJEGetF(schema, enumoption, "items.properties.mode.enum"))
        {
          puts(WJEString(enumoption, NULL, WJE_GET, ""));
        }
      }

      WJEDump(doc);

      WJECloseDocument(doc);
      WJECloseDocument(schema);
}

