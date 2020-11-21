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

int dll_count(struct dll * l){
  int n=0;

  if(l!=NULL){
    l=first(l);
    while (l->next!=NULL){
      n++;
      l=l->next;
    }
    n++;
  } else n=0;

  return n;
}
