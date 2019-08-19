#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <wjelement.h>
#include <wjreader.h>

char **character_name_completion(const char *, int, int);
char *character_name_generator(const char *, int);

WJElement doc = NULL, schema = NULL;
WJElement entity = NULL, parameter = NULL;

char greet[100] = ">";

int level = 0;

int execute(char * line)
{
    sprintf(greet,"%s >",line);
    level = 1;
}

int main(int argc, char *argv[])
{
    rl_attempted_completion_function = character_name_completion;

    FILE *jsonfile, *schemafile;
    WJReader readjson, readschema;
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

    while (1)
    {
      char * input = readline(greet);
      if (!input)
        break;
      add_history(input);
      execute(input);
      free(input);
    }

    return 0;
}

char **
character_name_completion(const char *text, int start, int end)
{
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, character_name_generator);
}

char *
character_name_generator(const char *text, int state)
{
    static int list_index, len;
    char *name;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    switch (level)
    {
      case 0:
        while (entity = _WJEObject(doc, "[]", WJE_GET, &entity)) {
          if (strncmp(WJEString(entity, "name", WJE_GET, ""), text, len) == 0) {
            return strdup(WJEString(entity, "name", WJE_GET, ""));
          }
        }
      break;
      case 1:
        while (parameter = _WJEObject(schema, "items.properties[]", WJE_GET, &parameter)) {
          if (strncmp(parameter->name, text, len) == 0) {
            return strdup(parameter->name);
          }
        }
      break;
    }

    return NULL;
}
