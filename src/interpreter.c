#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "config.h"

char *character_names[][6] = {
    {"file", NULL},
    {"eat", "breakfast", "dinner", "lunch", "snack", NULL},
    {"play", "cards", "chess", "go", NULL},
    {"walk", "left", "right", "straight", NULL},
    {NULL, NULL}
};

char *strmbtok ( char *input, char *delimit, char *openblock, char *closeblock) {
    static char *token = NULL;
    char *lead = NULL;
    char *block = NULL;
    int iBlock = 0;
    int iBlockIndex = 0;

    if ( input != NULL) {
        token = input;
        lead = input;
    }
    else {
        lead = token;
        if ( *token == '\0') {
            lead = NULL;
        }
    }

    while ( *token != '\0') {
        if ( iBlock) {
            if ( closeblock[iBlockIndex] == *token) {
                iBlock = 0;
            }
            token++;
            continue;
        }
        if ( ( block = strchr ( openblock, *token)) != NULL) {
            iBlock = 1;
            iBlockIndex = block - openblock;
            token++;
            continue;
        }
        if ( strchr ( delimit, *token) != NULL) {
            *token = '\0';
            token++;
            break;
        }
        token++;
    }
    return lead;
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
  char acOpen[]  = {"\"[<{"};
  char acClose[] = {"\"]>}"};
  int i = 0;
  tokarr[i] = stringtoparse;
  while ((tokarr[i] = strmbtok(tokarr[i], " ", acOpen, acClose)) != NULL)
    tokarr[++i] = NULL;
}

char * find_command(char **tokarr, int start)
{
  int numberoftokens = arrlength(tokarr);
  if (numberoftokens > 0)
  {
    if (start > 0)
      return tokarr[0];
  }
  return NULL;
}

char *command; // luche nikak chem tak

char *
character_name_generator(const char *text, int state)
{
    static int list_index, len;
    char *name;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    if (command == NULL)
    {
      while ((name = character_names[list_index++][0])) {
        if (strncmp(name, text, len) == 0) {
          return strdup(name);
        }
      }
    }
    else
    {
      for (int cmd_index = 0; name = character_names[cmd_index][0]; cmd_index++)
        if (strcmp(name, command) == 0) {
          while ((name = character_names[cmd_index][++list_index])) {
            if (strncmp(name, text, len) == 0) {
              return strdup(name);
          }
        }
      }
    }

    return NULL;
}

char **
character_name_completion(const char *text, int start, int end)
{
    char *tokarr[100];
    char *inputline = strdup(rl_line_buffer);
    parse(inputline, tokarr);
    command = find_command(tokarr, start);

    rl_attempted_completion_over = 1;

    return rl_completion_matches(text, character_name_generator);
}

int main()
{
  rl_bind_key('\t', rl_complete);
  rl_attempted_completion_function = character_name_completion;

  while (1)
  {
    char * input = readline("prompt> ");
    if (!input)
      break;
    add_history(input);
    //interpret(input);
    free(input);
  }
	return 0;
}
