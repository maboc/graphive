#include "startup_creation.h"

int startup_creation(){
  int rc;
  struct base_type * base;
  struct node_type * node;
  
  logger("Startup Creation");

  if(bases==NULL){
    /*
      base:
        attributeslist
          attr: name - base_base
        nodelist
          node
            attributeslist
              attr: name - node_1
      */
    
    base=base_new("base_base");
    base->nodelist=dll_new(base->nodelist, node_new("name", "node_1"));
    bases=dll_new(bases, base);

    /*
      base:
        attributelist
          attr: name - home_base
          attr: auteur - martijn
          attr: plaats - Wateringen
        nodelist
          node
            attributeslist
              attr: name - node_1
	      attr: auteur - marlies
	      attr: categorie - spielerei
          node
            attributeslist
              attr: name - node_2
              attr: auteur - ruben
              attr: categorie - serieus
    */
    
    base=base_new("home_base");
    base->attributelist=dll_new(base->attributelist, attribute_new("auteur", "martijn"));
    base->attributelist=dll_new(base->attributelist, attribute_new("plaats", "wateringen"));
    bases=dll_new(bases, base);

    node=node_new("name", "node_1");
    node->attributelist=dll_new(node->attributelist, attribute_new("auteur", "marlies"));
    node->attributelist=dll_new(node->attributelist, attribute_new("categorie", "spielerei"));
    base->nodelist=dll_new(base->nodelist, node);
    
    node=node_new("name", "node_2");
    node->attributelist=dll_new(node->attributelist, attribute_new("auteur", "ruben"));
    node->attributelist=dll_new(node->attributelist, attribute_new("categorie", "serieus"));
    base->nodelist=dll_new(base->nodelist, node);

  } else {
    rc=7;
    logger("Strange : there allready is a base...doing nothing");
  }
  
  return rc;
}
