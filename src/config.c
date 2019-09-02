#include <stdio.h>
#include <wjelement.h>
#include <wjreader.h>
#include <string.h>

#define CONFIGPATH "/etc/zenith.json"
#define MAXPATH 255
#define DEFAULTSCHEMEPATH "/var/lib/zenith/scheme"

struct configstruct_t
{
  char schemepath[MAXPATH];
};

struct configstruct_t config;

void parseconfig(WJElement configjson)
{
  strcpy(config.schemepath, WJEString(configjson, "name", WJE_GET, DEFAULTSCHEMEPATH));
}

int main(int argc, char *argv[])
{
  FILE *configfile;
  WJReader configread;
  WJElement configjson = NULL;
  if ((configfile = fopen(CONFIGPATH, "r")) && (configread = WJROpenFILEDocument(configfile, NULL, 0)))
    configjson = WJEOpenDocument(configread, NULL, NULL, NULL);
  else
    configjson = WJEObject(NULL, NULL, WJE_NEW);

  parseconfig(configjson);

  puts(config.schemepath);

}
