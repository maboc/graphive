#include "receiver.h"

void * receive(void * sck){
  int r=0;
  int s = *(int *) sck;
  int goon=0;
  char * inp_buf;
  struct dll * command=NULL;
  
  output_line(s, "Welcome to graphive\n");
  while (goon==0){
    inp_buf = malloc(1000);
    bzero(inp_buf, 1000);
    read(s, inp_buf, 1000);
    logger(inp_buf);
    output_line(s, inp_buf);
    command=command_pre_parse(command, inp_buf);
    if(dll_count(command)>0){
      if(strncmp(command_arg(command, 0), "quit", strlen(command_arg(command,0)))==0){
	goon=1;
      } else if(strncmp(command_arg(command,0), "shutdown", strlen(command_arg(command,0)))==0){
	goon=1;
	stoppenmaar=1;
      } else if(strncmp(command_arg(command, 0), "base", strlen(command_arg(command, 0)))==0){
	if(dll_count(command)>1){
	  /* meer dan 1 argument...proceed */
	  if(strncmp(command_arg(command, 1), "new", strlen(command_arg(command, 1)))==0){
	    if(dll_count(command)==3){
	      /* look okay to me */
	      
	      struct base_struct * base=base_new();
	      struct attribute_struct * attr =attribute_new("name", command_arg(command, 2));
	      base->attributes=dll_new(base->attributes);
	      base->attributes->payload=attr;
	      bases=dll_new(bases);	      
	      bases->payload=base;
	    } else {
	      output_line(s, "Not enough parameters\n");
	    }
	  } else if(strncmp(command_arg(command, 1), "list", strlen(command_arg(command, 1)))==0){
	    if (bases!=NULL){
	      if(dll_count(command)==2){
		/* list all bases */
		bases=dll_first(bases);
		while (bases->next!=NULL){
		  base_display(s, bases->payload);
		  bases=bases->next;
		}
		base_display(s, bases->payload);
	      } else if (dll_count(command)==3){
		/* list a specific base */
	      }
	    } else {
	      output_line(s, "No bases exists to display\n");
	    }
	  }
	} else{
	  output_line(s, "Not enough parameters\n");
	}
      }
    }
  }
  
  output_line(s, "Closing the socket\n");
  close(s);
  pthread_exit(NULL);
}
