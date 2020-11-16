#include "parser.h"

char * remove_leading_spaces(char * input){
  char * tmp;
  char * output=NULL;

  tmp=input;// for later reference
  
  while(* input == ' ') input++;
  output=malloc(strlen(input))+1; // +1 for a trailing \0
  bzero(output, strlen(input)+1);
  output=strcpy(output, input);

  free(tmp);
  return output;
  
}

char * remove_trailing_spaces(char * input){
  char * output=NULL;
  char * ep; // pointer to the current end of the string
  
  ep=input+strlen(input);
  while((*ep==' ' ) ||  (*ep=='\r') || (*ep=='\n')) ep=ep--;
  output=malloc(ep-input+1+1); //+1 (off by one) +1 om een \0 te kunen toevoegen
  bzero(output, ep-input+1+1);
  output=strcpy(output, input);

  free(input);

  return output;
}

struct dll * parse(char * input){
  struct dll * command=NULL;

  //remove leading spaces
  input=remove_leading_spaces(input);
  
  //remove trailing spaces
  input=remove_trailing_spaces(input);

  return command;
  
}
