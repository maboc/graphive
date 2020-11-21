#include "parser.h"

char * remove_leading_spaces(char * input){
  char * tmp;
  char * output=NULL;

  tmp=input;// for later reference
  
  while(* input == ' ') input++;
  output=malloc(strlen(input))+1; // +1 for a trailing \0
  bzero(output, strlen(input)+1);
  output=strcpy(output, input);

  //  free(tmp);
  return output;
  
}

char * remove_trailing_spaces(char * input){
  char * output=NULL;
  char * ep; // pointer to the current end of the string
  char * tmp=input;
  
  ep=input+strlen(input)-1;
  while((*ep==' ' ) ||  (*ep=='\r') || (*ep=='\n')) {
    ep=ep-1;
  }
  output=malloc(ep-input+1+1); //+1 (off by one) +1 om een \0 te kunen toevoegen
  bzero(output, ep-input+1+1);
  output=strncpy(output, input, ep-input+1);

  //  free(tmp); //uitzoeken waarom dit kapot loopt

  return output;
}

struct dll * split(char * input){
  struct dll * command=NULL;
  int n;
  char * p;
  char * sub=NULL;

  n=strlen(input);
  if (n>0){
    //er is niet iets leegs in onze maag gesplitst

    p=strstr(input, " ");
    while(p!=NULL){
      sub=malloc(p-input+1);
      bzero(sub, p-input+1);
      sub=strncpy(sub, input, p-input);
      command=dll_new(command, sub);
      
      input=p+1;
      p=strstr(input, " ");
    }
    sub=malloc(strlen(input)+1); // +1 voor \0
    bzero(sub, strlen(input)+1);
    sub=strncpy(sub, input, strlen(input));
    command=dll_new(command, sub);
  }

  return command; 
}

struct dll * parse(char * input){
  struct dll * command=NULL;
  char * o1;
  char * o2;
  
  //remove leading spaces
  o1=remove_leading_spaces(input);
  
  //remove trailing spaces
  o2=remove_trailing_spaces(o1);

  command=split(o2);
  
  return command;
  
}

void free_parser(struct dll * command){
  struct dll* tmp;
  
  if (command!=NULL){
    command=first(command);
    while (command->next!=NULL){
      tmp=command;
      free(command->payload);
      command=command->next;
      free(tmp);
    }
    free(command->payload);
    free(command);
  }
  
  return;
}

char * get_parser_part(struct dll * command, int pos){
  char * part=NULL;
  int n=1;

  if((command!=NULL) && (pos<=dll_count(command))){

    command=first(command);
    while(n<pos){
      command=command->next;
      n++;
    }
    part=command->payload;
  }

  return part;
}
