#ifndef _PARSER_
#define _PARSER_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"

char * remove_leading_spaces(char *);
char * remove_trailing_spaces(char *);
struct dll * parse(char *);
void free_parser(struct dll *);
char * get_parser_part(struct dll *, int);

#endif
