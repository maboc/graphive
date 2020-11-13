#ifndef _IO_
#define _IO_

#include <stddef.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stddef.h>
#include "logging.h"
#include "base.h"
#include "dll.h"
#include "node.h"

extern struct dll * bases;
extern int goon;

int initial_load();

int write_node(struct node_type *, struct base_type *);
int write_nodes(struct dll *, struct base_type *);
int write_attribute(struct attribute_type *, struct base_type *, struct node_type *);
int write_attributes(struct dll *, struct base_type *, struct node_type *);
unsigned long long get_empty_spot();
void set_empty_spot(unsigned long long);
int write_base(struct base_type *);
int write_bases(struct dll *);
void * data_writer(void *);

#endif
