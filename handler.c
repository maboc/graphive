#include "handler.h"

void * handler(void * sck){
  int s = *(int *) sck;
  char * input;
  char * tmp;
  struct dll * command=NULL;
  
  output_line(s, "graphive....welcome\n");
  tmp=malloc(1000);
  input=malloc(1000);
  bzero(input, 1000);
  while(strcmp(input, "quit\r\n")!=0){
    bzero(input, 1000);
    read(s, input, 1000);
    output_line(s, input);

    if(strcmp(input, "shutdown\r\n")==0){
      logger("Shutdown");
      goon=1;
      bzero(input,1000);
      strcpy(input, "quit\r\n");
    }

    command=parse(input);
    
  }

  logger("Closing the socket");
  close(s);

  pthread_exit(NULL);
}
