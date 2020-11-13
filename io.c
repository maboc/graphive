#include "io.h"

int load(char * filename){

  return 0;
}

int create_file(char * filename){
  int rc=0;
  FILE * fp;
  int n;
  char * buffer;
  unsigned long long pospoi=0;
  
  logger("Create file");
  logger(filename);

  buffer=malloc(1024*1024);
  bzero(buffer,1024*1024);
		
  fp=fopen("graphive.dat", "a+");
  // size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
  n=fwrite(buffer, 1024*1024, 1, fp);
  fflush(fp);
  /* 1 omdat ik fwrite anders niet goed aand e praat krijg */
  if(n!=1) rc=6;
  
  bzero(buffer,1024*1024);
  sprintf(buffer, "%i", n);
  logger(buffer);
  free(buffer);
  
  fflush(fp);  
  fclose(fp);
  
  //Setting the very first entry in the file as the free position pointer
  pospoi=sizeof(unsigned long long);
  set_empty_spot(pospoi);
  
  return rc;
}

int regular_file(char * filename){
  struct stat buffer;
  int rc=0;
  int s;
  
  s=stat(filename, &buffer);
  if(S_ISREG(buffer.st_mode)){
    logger("File is a regular file");
    logger(filename);
  } else {
    logger("File is not a regular file");
    logger(filename);
    rc=6;
  }

  return rc;
}

int file_exists(char * filename){
  struct stat buffer;
  int rc = 0;
  int s;
  
  s=stat(filename, &buffer);
  if (s!=0){
    logger("I can not detemine stat for file");
    logger(filename);
    rc=4;
  } else {
    logger("I can determine stat for filename");
    logger(filename);
  }

  return rc;
}
  
/* when starting the initial load there are no bases yet...so no need to supply NULL*/
int initial_load(){
  int rc;
  FILE * fp;

  rc=file_exists("graphive.dat");
  if (rc==0){
    rc=regular_file("graphive.dat");
    if(rc==0){
      rc=load("graphive.dat");
    }
  } else {
    rc=create_file("graphive.dat");
  }

  return rc; 
}

int write_node(struct node_type * node, struct base_type * base){
  char * tmp;

  tmp=malloc(100);
  sprintf(tmp, "Write node ID : %i", node->id);
  logger(tmp);
  free(tmp);

  write_attributes(node->attributelist, base, node);
     
  return 0;
}

int write_nodes(struct dll * list, struct base_type * base){
  struct node_type * node;
  int rc=0;

  if(list==NULL){
    logger("No nodes to write");
  } else {
    logger("write nodes");
    list=first(list);
    while(list->next!=NULL){
      write_node(list->payload, base);
      list=list->next;
    }
    rc=write_node(list->payload, base);
  }
  return rc;
}

int write_attribute(struct attribute_type * attr, struct base_type * base, struct node_type * node){
  char * tmp;
  
  tmp=malloc(1000);

  sprintf(tmp, "Attribute : ID : %i Key : %s Value : %s", attr->id, attr->key, attr->val);
  logger(tmp);
  free(tmp);
  
  return 0;
}

int write_attributes(struct dll * list, struct base_type * base, struct node_type * node){
  struct attribute_type * attr;

  if (list==NULL){
    logger("No attributes to write");
  }else{
    logger("write attributes");
    
    list=first(list);
    while(list->next!=NULL){
      attr=list->payload;
      write_attribute(attr, base, node);
      list=list->next;
    }
    attr=list->payload;
    write_attribute(attr, base, node);
  }
  return 0;
}

unsigned long long get_empty_spot(){
  unsigned long long p;
  FILE * fp;

  fp=fopen("graphive.dat", "r+");
  fseek(fp, 0, SEEK_SET);
  //  size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
  fread(&p, sizeof(unsigned long long), 1,fp);
  fclose(fp);
  
  return p;
}

void set_empty_spot(unsigned long long p){
  FILE * fp;

  fp=fopen("graphive.dat", "r+");
  fseek(fp, 0, SEEK_SET);
  fwrite(&p, sizeof(unsigned long long), 1, fp);
  fclose(fp);
  
}

int write_base(struct base_type * base){
  char * tmp;
  FILE * fp;
  int t=1; //type is base ...so 1 (zie mem_disk.txt)
  unsigned long long p;
  
  tmp=malloc(100);
  sprintf(tmp, "Write base : %i", base->id);
  logger(tmp);
  free(tmp);

  if(base->status==2){
    logger("Did not change");
  } else if(base->status==1){
    unsigned long long p;
    
    logger("Just Created");
    /* file en location zullen nog niet geucvld zijn ....want nieuw */
    /* zoek eerste lege positie in de file graphive.dat */

    p=get_empty_spot();
    base->file=0;
    base->location=p;
    fp=fopen("graphive.dat", "r+");
    fseek(fp, p, SEEK_SET);
    fwrite(&t, sizeof(int), 1, fp); //type of entry
    fwrite(&(base->id), sizeof(int), 1, fp); //base_id
    fwrite(&"O", sizeof(char), 1, fp); //status

    fclose(fp);

    set_empty_spot(p+sizeof(int)+sizeof(int)+sizeof(char));
    
    base->status=2;
    
  }else if (base->status==3){
    logger("Deleted");
  }else if(base->status==4){
    logger("Updated");
  }

  write_attributes(base->attributelist, base, NULL);
  write_nodes(base->nodelist, base);
  
  return 0;
}

int write_bases(struct dll * local_bases){
  int rc;
  if(local_bases==NULL){
    logger("No bases to write");
  }else{
    logger("write bases");
    local_bases=first(local_bases);
    while(local_bases->next!=NULL){
      rc=write_base(local_bases->payload);
      local_bases=local_bases->next;
    }
    rc=write_base(local_bases->payload);
  }
  return 0;
}

void * data_writer(void * data_in){
  struct dll * local_bases;
  int rc=0;
  sleep(30);  
  logger("Starting data_writer thread");
  //  sleep(60);
  while(goon==0){
    logger("data_writer sweep");
    local_bases=bases;
    
    write_bases(local_bases);
    
    sleep(60);//just for now....every minute we sweep through the data
  }
  return NULL;
}
