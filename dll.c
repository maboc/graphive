#include "dll.h"

struct dll * first(struct dll *l){
  while(l->prev!=NULL){
    l=l->prev;
  }
  return l;
}

struct dll * last(struct dll * l){
  while(l->next!=NULL){
    l=l->next;
  }
  return l;
}

struct dll * dll_new(struct dll * l, void * payload){
  struct dll * n;
  
  n=malloc(sizeof(struct dll));
  n->prev=NULL;
  n->next=NULL;
  n->payload=payload;
  
  if (l!=NULL){    
    l=last(l);
    l->next=n;
    n->prev=l;
  }
  return n;
}

