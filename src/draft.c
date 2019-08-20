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
char interface[100] = "";
char option[100] = "";

int level = 0;

WJElement getelementbynameprop(WJElement container, char * text)
{
  WJElement entity = NULL;
  while (entity = _WJEObject(container, "[]", WJE_GET, &entity)) {
    if (strcmp(WJEString(entity, "name", WJE_GET, ""), text) == 0) {
      return entity;
    }
  }
}

int setparameter(char * setiface, char * setparam, char * setvalue)
{
  printf("setting %s %s %s\n",setiface,setparam,setvalue);
}

int execute(char * line)
{
  if (strcmp(line,"..")==0){
    level--;
    return 0;
  }
    switch (level)
    {
      case 0:
        strcpy(interface,line);
      break;
      case 1:
        strcpy(option,line);
      break;
      case 2:
        setparameter(interface,option,line);
        return 0;
      break;
    }
      level++;
    //sprintf(greet,"%s >",line);
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

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    switch (level)
    {
      case 0:
        while (entity = _WJEObject(doc, "[]", WJE_GET, &entity)) {
          if (strncmp(WJEString(entity, "name", WJE_GET, ""), text, len) == 0) {
            //printf("\ndebug state %d len %d index %d result %s\n",state, len, list_index, WJEString(entity, "name", WJE_GET, ""));
            return strdup(WJEString(entity, "name", WJE_GET, ""));
          }
        }
      break;
      case 1:
        while (parameter = _WJEObject(schema, "items.properties[]", WJE_GET, &parameter)) {
          if (strncmp(parameter->name, text, len) == 0) {
            //printf("\ndebug state %d len %d index %d result %s\n",state, len, list_index, parameter->name);
            return strdup(parameter->name);
          }
        }
      break;
      case 2:
        if (!state)
        {
          entity = getelementbynameprop(doc,interface);
          char temp[100];
          sprintf(temp,"items.properties.%s",option);
          parameter = WJEObject(schema, temp, WJE_GET);
          //puts(WJEString(entity, parameter->name, WJE_GET, ""));
          return strdup(WJEString(entity, parameter->name, WJE_GET, ""));
        }
      break;
    }

    return NULL;
}
