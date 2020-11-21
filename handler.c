#include "handler.h"

void * handler(void * sck){
  int s = *(int *) sck;
  char * input;
  char * tmp;
  struct dll * command=NULL;
  int n;
  int proceed=0;
  char * part;
  
  output_line(s, "graphive....welcome\r\n\r\n\r\n");
  tmp=malloc(1000);
  input=malloc(1000);
  bzero(input, 1000);
  while(proceed==0){
    bzero(input, 1000);
    read(s, input, 1000);

    command=parse(input);
    n=dll_count(command);
    tmp=malloc(1000);
    bzero(tmp, 1000);

    sprintf(tmp, "args : %i\r\n", n);
    output_line(s, tmp);

    bzero(tmp,1000);
    sprintf(tmp,"Command : %s\r\n", get_parser_part(command,1));
    output_line(s, tmp);
    free(tmp);
    
    part=get_parser_part(command,1);
    if(strcmp(part, "quit")==0){
      proceed=1;
    } else if (strcmp(part,"shutdown")==0){
      logger("Shutdown");
      goon=1;
      proceed=1;
    } else if(strcmp(part, "base")==0){
      part=get_parser_part(command,2);
      if (part==NULL){
	output_line(s, "syntax error\r\n");
      } else {
	if(strcmp(part, "show")==0){
	  part=get_parser_part(command,3);
	  if (part==NULL){
	    output_line(s, "syntax error\r\n");
	  } else {
	    if (strcmp(part, "all")==0){
	      base_show_all(s);
	    } else {
	      output_line(s, "show a specific base\r\n");
	    }
	  }
	} else {
	  output_line(s, "it's not the show command\r\n");
	}
      }
    } else {
      output_line(s, "No clue what to do\r\n");
    }
    
    free_parser(command);
  }
  
  logger("Closing the socket");
  close(s);
  
  pthread_exit(NULL);
}
