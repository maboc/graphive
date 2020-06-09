#include "parser.h"

void command_free(struct dll * command){
  struct dll * n;
  char * tmp;
  
  if(command!=NULL){
    command=dll_first(command);
    while (command->next!=NULL){
      n=command->next;
      command->prev=NULL;
      command->next=NULL;
      //tmp=command->payload;
      //free(tmp);
      //      free(command->payload);
      command->payload=NULL;
      free(command);
      command=n;
    }
    command->prev=NULL;
    command->next=NULL;
    //tmp=command->payload;
    //free(tmp);
    //free((char *) command->payload);
    command->payload=NULL;
    free(command);

  }
}

char * remove_double_spaces(char * line){

  char * kopie;
  char * tmp;
  char * tmp_runner;
  int dubbel=0;
  
  kopie=line;
  
  tmp=malloc(strlen(line)+1);
  tmp_runner=tmp;
  bzero(tmp, strlen(line)+1);

  while(*kopie!='\n'){
    if((*kopie!=' ')||((*kopie==' ')&&(dubbel==0))){
      {
	* tmp_runner=* kopie;
	tmp_runner=tmp_runner+1;
	if(* kopie == ' '){
	    dubbel=1;
	  } else {
	    dubbel=0;
	  }
      }
    }
    kopie=kopie+1;
  }
  * tmp_runner='\n';
  
  free(line);
  
  return tmp;
}

char * remove_leading_spaces(char * line){
  char * tmp;
  char * kopie;

  kopie=line;

  while(* kopie==' '){
    kopie=kopie+1;
  }

  tmp=malloc(strlen(kopie)+1);
  bzero(tmp, strlen(kopie)+1);

  tmp=strncpy(tmp, kopie, strlen(kopie));
  free(line);
  
  return tmp;;
}

char * remove_ending_sheit(char * inp_buf){
  char * p;
  char * tmp;
  
  p=inp_buf+strlen(inp_buf)-1; /* p is the final byte */

  while((* p=='\n') || (* p =='\r') || (* p==' ')){
    * p='\0';
    p=p-1;
  }
  
  tmp=malloc(strlen(inp_buf)+1);
  bzero(tmp, strlen(inp_buf)+1);
  tmp=strncpy(tmp, inp_buf, strlen(inp_buf));

  free(inp_buf);
  
  return tmp;
}

struct dll * parse(struct dll * command, char * inp_buf){
  char * payload;
  char * p;

  if(strlen(inp_buf)>0)
    {
      p=strstr(inp_buf, " ");
      while(p!=NULL){
	payload=malloc(p-inp_buf+1);
	bzero(payload,(p-inp_buf+1));
	payload=strncpy(payload, inp_buf, p-inp_buf);
	command=dll_new(command);
	command->payload=payload;
	inp_buf=p+1;
	p=strstr(inp_buf, " ");
      }
      /* Now the last part */
      p=inp_buf+strlen(inp_buf);
      payload=malloc(p-inp_buf)+1;
      bzero(payload,(p-inp_buf)+1);
      payload=strncpy(payload, inp_buf, p-inp_buf);
      command=dll_new(command);
      command->payload=payload;
    }
  return command;
}

char * command_arg(struct dll * command, int argn){
  char * ret;
  int teller=0;
  
  if(dll_count(command)<argn+1){/* +1 want we beginnen te tellen bij 0 */
    ret=NULL;
  }else{
    command=dll_first(command);
    while(teller<argn){
      command=command->next;
      teller++;
    }
    ret=command->payload;
  }
  return ret;
}

struct dll * command_pre_parse(struct dll * command, char * inp_buf){
  
  /* Some sanatizing */
  inp_buf=remove_leading_spaces(inp_buf);
  inp_buf=remove_double_spaces(inp_buf);
  inp_buf=remove_ending_sheit(inp_buf);
  
  /* if the command dll is filled then free it totally */
  command_free(command);
  command=NULL;
  
  /* now create the command dll */
  command=parse(command, inp_buf);
  
  free(inp_buf);

  return command;
}
