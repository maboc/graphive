#include "dll.h"

struct dll * dll_first(struct dll * l){
  if (l!=NULL){
    while(l->prev!=NULL){
      l=l->prev;
    }
  }
  
  return l;
}

struct dll * dll_last(struct dll * l){
  if(l!=NULL){
    while(l->next!=NULL){
      l=l->next;
    }
  }
  return l;
}

int dll_count(struct dll * l){
  int n;
  
  if(l!=NULL){
    l=dll_first(l);
    n=1;
    while(l->next!=NULL){
      l=l->next;
      n++;
    }
  } else {
    n=-1;
  }

  return n;
}

struct dll * dll_new(struct dll * list){
  struct dll * tmp;
  
  if (list==NULL){
    list=malloc(sizeof(struct dll));
    list->prev=NULL;
    list->next=NULL;
    list->payload=NULL;
  } else {
    list=dll_last(list);
    tmp=malloc(sizeof(struct dll));
    tmp->prev=list;
    tmp->next=NULL;
    tmp->payload=NULL;
    list->next=tmp;
    list=tmp; /* dan kan ik in een keer list teruggeven */
  }
  return list;
}
