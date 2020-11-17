#include "handler.h"

void * handler(void * sck){
  int s = *(int *) sck;
  char * input;
  char * tmp;
  struct dll * command=NULL;
  int n;
  int proceed=0;
  
  output_line(s, "graphive....welcome\r\n\r\n\r\n");
  tmp=malloc(1000);
  input=malloc(1000);
  bzero(input, 1000);
  while(proceed==0){
    bzero(input, 1000);
    read(s, input, 1000);

    //    output_line(s, input);

    command=parse(input);
    n=dll_count(command);
    tmp=malloc(100);
    bzero(tmp, 100);

    sprintf(tmp, "args : %i\r\n", n);
    output_line(s, tmp);

    bzero(tmp,100);
    sprintf(tmp,"Command : %s\r\n", get_parser_part(command,1));
    output_line(s, tmp);

    if(strcmp(get_parser_part(command,1), "quit")==0) proceed=1;
    
    free(tmp);
    
    if(strcmp(get_parser_part(command, 1), "shutdown")==0){
      logger("Shutdown");
      goon=1;
      proceed=1;
    }

    if(strcmp(get_parser_part(command,1), "bases")){
      if(strcmp(get_parser_part(command,2), "show")){
	if(strcmp(get_parser_part(command,3), "all")){
	  bases_show(s);	  
	}	     
      }      	      
    } else {
      output_line(s, "No clue what to do");
    }
      
    free_parser(command);
  }
  
  logger("Closing the socket");
  close(s);

  pthread_exit(NULL);
}
