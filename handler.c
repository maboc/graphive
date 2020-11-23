#include "handler.h"

void * handler(void * sck){
  struct dll * local_bases;
  struct base_type * local_base=NULL;
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
      /* ******************************* quit ************************** */
      proceed=1;
      /* ******************************* quit ************************** */
    } else if (strcmp(part,"shutdown")==0){
      /* ******************************* shutdown ************************** */
      logger("Shutdown");
      goon=1;
      proceed=1;
      /* ******************************* shutdown ************************** */
    } else if(strcmp(part, "base")==0){
      /* ******************************* base ***************************** */
      part=get_parser_part(command,2);
      if (part==NULL){
	output_line(s, "syntax error\r\n");
      } else {
	if(strcmp(part, "show")==0){
	  /* ******************************* base show***************************** */
	  part=get_parser_part(command,3);
	  if (part==NULL){
	    /* ******************************* base show current ***************************** */
	    if (local_base==NULL){
	      	output_line(s, "base not chosen\r\n");
	    } else {
	      base_show(local_base, s);
	    }
	    /* ******************************* base show current ***************************** */
	  } else {
	    if (strcmp(part, "all")==0){
	      /* ******************************* base show all ***************************** */
	      base_show_all(s);
	      /* ******************************* base show all ***************************** */
	    } else {
	      output_line(s, "Not sure what to show \r\n");
	    }
	  }
	  /* ******************************* base show ***************************** */
	} else if(strcmp(part,"new")==0){
	  /* ******************************* base new ***************************** */
	  // are there in total 3 parts in the command (base new name)
	  // name will be the first attribute of the base
	  if (dll_count(command)==3)
	    {
	      local_bases=bases;
	      local_bases=dll_new(local_bases, base_new(get_parser_part(command,3)));
	    }
	  else{
	    output_line(s, "syntax error\r\n");
	  }
	  /* ******************************* base new ***************************** */
	} else if(strcmp(part, "add")==0){
	  /* ******************************* base add  ***************************** */
	  part=get_parser_part(command, 3);
	  if(strcmp(part, "attribute")==0){
	    /* ******************************* base add attribute ***************************** */
	    //adding an attribute to the base
	    //check whethere there are 5 arguments in total (base add attribute key value)
	    if (dll_count(command)==5){
	      if(local_base==NULL){
		output_line(s, "base not chosen\r\n");
	      } else {
		local_base->attributelist=dll_new(local_base->attributelist,
						  attribute_new(get_parser_part(command, 4),
								get_parser_part(command, 5)));
	      }
	    } else {
	      output_line(s, "syntax error : to less arguments\r\n");
	    }
	    /* ******************************* base add attribute***************************** */
	  } else if(strcmp(part, "node")==0){
	    /* ******************************* base add node***************************** */
	    if(local_base==NULL){
	      output_line(s, "base not chosen\r\n");
	    } else {
	      if (dll_count(command)!=5){
		output_line(s, "syntax error: need 5 arguments\r\n");
	      }else{
		local_base->nodelist=dll_new(local_base->nodelist,
					     node_new(get_parser_part(command, 4),
						      get_parser_part(command, 5)));
	      }
	    }
	    /* ******************************* base add node***************************** */
	  }else {
	    output_line(s, "Don't know what to add\r\n"); 
	  }
	  /* ******************************* base add  ***************************** */
	} else if(strcmp(part, "view")==0){
	  /* ******************************* base view  ***************************** */
	  if (local_base==NULL){
	    output_line(s, "base not chosen\r\n");
	  } else {
	    base_view(s, local_base);
	  }
	  /* ******************************* base view  ***************************** */
	}else{
	  output_line(s, "not show/new/add/view\r\n");
	}
      }
      /* ******************************* base ***************************** */
    } else if(strcmp(part, "use")==0) {
      /* ******************************* use ***************************** */
      if(dll_count(command)!=2){
	output_line(s, "syntax error\r\n");
      } else {
	int id=0;
	id=atoi(get_parser_part(command,2));
	//let's find that base
	local_base=base_find(id);
	if(local_base==NULL){
	  output_line(s,"Not succeeded\r\n");
	}else{
	  output_line(s,"Base set\r\n");
	}
      }
      /* ******************************* use ***************************** */
    } else if(strcmp(part, "node")==0) {
      /* ******************************* node ***************************** */
      if(strcmp(get_parser_part(command,2), "add")==0){
	/* ******************************* node add ***************************** */
	if(strcmp(get_parser_part(command,3), "attribute")==0){
	  /* ******************************* node add attribute ***************************** */
	  if(dll_count(command)!=6){
	    output_line(s, "syntax error 6 arguments neede\r\n");
	  } else {
	    if(local_base==NULL){
	      output_line(s, "base not chosen\r\n");
	    } else {
	      unsigned long long id;
	      struct node_type * node;
	      
	      id =atoi(get_parser_part(command, 4));
	      node=node_search(local_base, id);

	      if (node==NULL){
		output_line(s, "Error : Node not found\r\n");
	      } else {
		node->attributelist=dll_new(node->attributelist,
					    attribute_new(get_parser_part(command,5),
							  get_parser_part(command, 6)));
	      }
	    }
	  }
	  /* ******************************* node add attribute ***************************** */
	} else if(strcmp(get_parser_part(command,3), "relation")==0){
	  /* ******************************* node add relation ***************************** */
	  /* ******************************* node add relation ***************************** */
	}
      } else {
	output_line(s, "Syntax error: don't know what to add\r\n");
      }
      /* ******************************* node ***************************** */
    } else {
      output_line(s, "No clue what to do\r\n");
    }
    
    free_parser(command);
  }
  
  logger("Closing the socket");
  close(s);
  
  pthread_exit(NULL);
}
