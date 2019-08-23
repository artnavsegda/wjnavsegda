#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "config.h"

int arrlength(char **array)
{
  int length = 0;
  while (array[length] != NULL)
    length++;
  return length;
}

int parse(char * stringtoparse)
{
  char *tokarr[100]; // maximum argument count
  int i = 0;
  tokarr[i] = stringtoparse;

  while ((tokarr[i] = strtok(tokarr[i], " ")) != NULL)
    tokarr[++i] = NULL;

  printf("number of tokens %d\n", arrlength(tokarr));
}

int main()
{
  rl_bind_key('\t', rl_complete);

  while (1)
  {
    char * input = readline("prompt> ");
    if (!input)
      break;
    add_history(input);
    parse(input);
    free(input);
  }
	return 0;
}
