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
char temp[100];

int level = 0;

WJElement getelementbynameprop(WJElement container, char * text)
{
  WJElement entity = NULL;
  while (entity = _WJEObject(container, "[]", WJE_GET, &entity)) {
    if (strcmp(WJEString(entity, "name", WJE_GET, ""), text) == 0) {
      return entity;
    }
  }
  return NULL;
}

int setparameter(char * setiface, char * setparam, char * setvalue)
{
  printf("setting %s %s %s\n",setiface,setparam,setvalue);
  entity = getelementbynameprop(doc,setiface);
  sprintf(temp,"items.properties.%s",option);
  parameter = WJEObject(schema, temp, WJE_GET);
  WJEString(entity, parameter->name, WJE_SET, setvalue);
}

int arrlength(char **array)
{
  int length = 0;
  while (array[length] != NULL)
    length++;
  return length;
}

int parse(char * stringtoparse, char **tokarr)
{
  int i = 0;
  tokarr[i] = stringtoparse;
  while ((tokarr[i] = strtok(tokarr[i], " ")) != NULL)
    tokarr[++i] = NULL;
}

void entitylist(void)
{
    while (entity = _WJEObject(doc, "[]", WJE_GET, &entity)) {
      puts(WJEString(entity, "name", WJE_GET, ""));
    }
}

void parameterlist()
{
  while (parameter = _WJEObject(schema, "items.properties[]", WJE_GET, &parameter)) {
    puts(parameter->name);
  }
}

int execute(int argc, char *argv[])
{
  if (strcmp(argv[0],"..")==0){
    if (level > 0)
      level--;
    else
      printf("Already at the command root\n",argv[0]);
    return 0;
  }
    switch (level)
    {
      case 0:
        if (argv[0][0]=='?')
        {
          //printf("Help is on the way\n",argv[0]);
          entitylist();
          return 0;
        }
        if (getelementbynameprop(doc,argv[0]) != NULL)
          strcpy(interface,argv[0]);
        else
        {
          printf("No interface %s found\n",argv[0]);
          return 0;
        }
      break;
      case 1:
        if (argv[0][0]=='?')
        {
          //printf("Help is on the way\n",argv[0]);
          parameterlist();
          return 0;
        }
        if (argc == 1)
        {
          sprintf(temp,"items.properties.%s",argv[0]);
          parameter = WJEObject(schema, temp, WJE_GET);
          if (parameter)
          {
            entity = getelementbynameprop(doc,interface);
            printf("Value: %s\n", WJEString(entity, parameter->name, WJE_GET, ""));
            strcpy(option,argv[0]);
          }
          else
          {
            printf("No property %s defined\n",argv[0]);
            return 0;
          }
        }
        else
        {
          setparameter(interface,argv[0],argv[1]);
        }
      break;
      case 2:
        setparameter(interface,option,argv[0]);
        return 0;
      break;
    }
    if (level < 1)
      level++;
    //sprintf(greet,"%s >",line);
}

int interpret(char * stringtointerpret)
{
  char *tokarr[100]; // maximum argument count
  parse(stringtointerpret, tokarr);
  int numberoftokens = arrlength(tokarr);
  //printf("number of tokens %d\n", numberoftokens);
  if (numberoftokens > 0)
    execute(numberoftokens,tokarr);
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
      interpret(input);
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
